#include "pacing_controller.h"
#include "modules/pacing/round_robin_packet_queue.h"
#include "modules/pacing/prioritized_packet_queue.h"

constexpr TimeDelta kMaxElapsedTime = TimeDelta::Seconds(2);
constexpr TimeDelta kMaxDebtInTime = TimeDelta::Millis(500);

namespace webrtc {


namespace {
// Time limit in milliseconds between packet bursts.
constexpr TimeDelta kDefaultMinPacketLimit = TimeDelta::Millis(5);
constexpr TimeDelta kCongestedPacketInterval = TimeDelta::Millis(500);
// TODO(sprang): Consider dropping this limit.
// The maximum debt level, in terms of time, capped when sending packets.
constexpr TimeDelta kMaxDebtInTime = TimeDelta::Millis(500);
constexpr TimeDelta kMaxElapsedTime = TimeDelta::Seconds(2);
constexpr TimeDelta kTargetPaddingDuration = TimeDelta::Millis(5);

bool IsDisabled(const FieldTrialsView& field_trials, absl::string_view key) {
  return absl::StartsWith(field_trials.Lookup(key), "Disabled");
}

bool IsEnabled(const FieldTrialsView& field_trials, absl::string_view key) {
  return absl::StartsWith(field_trials.Lookup(key), "Enabled");
}

std::unique_ptr<PacingController::PacketQueue> CreatePacketQueue(
    const FieldTrialsView& field_trials,
    Timestamp creation_time) {
  if (field_trials.IsDisabled("WebRTC-Pacer-UsePrioritizedPacketQueue")) {
    return std::make_unique<RoundRobinPacketQueue>(creation_time);
  }
  return std::make_unique<PrioritizedPacketQueue>(creation_time);
}

}  // namespace

const TimeDelta PacingController::kMaxExpectedQueueLength =
    TimeDelta::Millis(2000);
const float PacingController::kDefaultPaceMultiplier = 2.5f;
const TimeDelta PacingController::kPausedProcessInterval =
    kCongestedPacketInterval;
const TimeDelta PacingController::kMinSleepTime = TimeDelta::Millis(1);
const TimeDelta PacingController::kMaxEarlyProbeProcessing =
    TimeDelta::Millis(1);


void PacingController::EnqueuePacket(std::unique_ptr<RtpPacketToSend> packet)
{
  RTC_DCHECK(pacing_rate_ > DataRate::Zero())
      << "SetPacingRate must be called before InsertPacket.";
  RTC_CHECK(packet->packet_type());

  prober_.OnIncomingPacket(DataSize::Bytes(packet->payload_size()));

  const Timestamp now = CurrentTime();
  if (packet_queue_->Empty()) {
    // If queue is empty, we need to "fast-forward" the last process time,
    // so that we don't use passed time as budget for sending the first new
    // packet.
    Timestamp target_process_time = now;
    Timestamp next_send_time = NextSendTime();
    if (next_send_time.IsFinite()) {
      // There was already a valid planned send time, such as a keep-alive.
      // Use that as last process time only if it's prior to now.
      target_process_time = std::min(now, next_send_time);
    }
    UpdateBudgetWithElapsedTime(UpdateTimeAndGetElapsed(target_process_time));
  }
  packet_queue_->Push(now, std::move(packet));
  seen_first_packet_ = true;

  // Queue length has increased, check if we need to change the pacing rate.
  MaybeUpdateMediaRateDueToLongQueue(now);
}

void PacingController::ProcessPackets()
{
  const Timestamp now = CurrentTime();
  Timestamp target_send_time = now;
  // process padding return

  target_send_time = NextSendTime();
  if (now < target_send_time) {
    // We are too early, but if queue is empty still allow draining some debt.
    // Probing is allowed to be sent up to kMinSleepTime early.
    UpdateBudgetWithElapsedTime(UpdateTimeAndGetElapsed(now));
    return ;
  }

  TimeDelta elapsed_time = UpdateTimeAndGetElapsed(target_send_time);

  if (elapsed_time > TimeDelta::Zero()) {
    UpdateBudgetWithElapsedTime(elapsed_time);
  }

  DataSize data_sent = DataSize::Zero();
  // Circuit breaker, making sure main loop isn't forever.
  static constexpr int kMaxIterations = 1 << 16;
  int iteration = 0;
  int packets_sent = 0;
  int padding_packets_generated = 0;
  for (; iteration < kMaxIterations; ++iteration) {
    // Fetch packet, so long as queue is not empty or budget is not
    // exhausted.
    std::unique_ptr<RtpPacketToSend> rtp_packet =
        GetPendingPacket(pacing_info, target_send_time, now);
    if (rtp_packet == nullptr) {
      // No packet available to send, check if we should send padding.
      DataSize padding_to_add = PaddingToAdd(recommended_probe_size, data_sent);
      if (padding_to_add > DataSize::Zero()) {
        std::vector<std::unique_ptr<RtpPacketToSend>> padding_packets =
            packet_sender_->GeneratePadding(padding_to_add);
        if (!padding_packets.empty()) {
          padding_packets_generated += padding_packets.size();
          for (auto& packet : padding_packets) {
            EnqueuePacket(std::move(packet));
          }
          // Continue loop to send the padding that was just added.
          continue;
        } else {
          // Can't generate padding, still update padding budget for next send
          // time.
          UpdatePaddingBudgetWithSentData(padding_to_add);
        }
      }
      // Can't fetch new packet and no padding to send, exit send loop.
      break;
    } else {
      RTC_DCHECK(rtp_packet);
      RTC_DCHECK(rtp_packet->packet_type().has_value());
      const RtpPacketMediaType packet_type = *rtp_packet->packet_type();
      DataSize packet_size = DataSize::Bytes(rtp_packet->payload_size() +
                                             rtp_packet->padding_size());

      if (include_overhead_) {
        packet_size += DataSize::Bytes(rtp_packet->headers_size()) +
            transport_overhead_per_packet_;
      }

      packet_sender_->SendPacket(std::move(rtp_packet), pacing_info);
      for (auto& packet : packet_sender_->FetchFec()) {
        EnqueuePacket(std::move(packet));
      }
      data_sent += packet_size;
      ++packets_sent;

      // Send done, update send time.
      OnPacketSent(packet_type, packet_size, now);

      if (is_probing) {
        pacing_info.probe_cluster_bytes_sent += packet_size.bytes();
        // If we are currently probing, we need to stop the send loop when we
        // have reached the send target.
        if (data_sent >= recommended_probe_size) {
          break;
        }
      }

      // Update target send time in case that are more packets that we are late
      // in processing.
      target_send_time = NextSendTime();
      if (target_send_time > now) {
        // Exit loop if not probing.
        if (!is_probing) {
          break;
        }
        target_send_time = now;
      }
      UpdateBudgetWithElapsedTime(UpdateTimeAndGetElapsed(target_send_time));
    }
  }

  if (iteration >= kMaxIterations) {
    // Circuit break activated. Log warning, adjust send time and return.
    // TODO(sprang): Consider completely clearing state.
    RTC_LOG(LS_ERROR) << "PacingController exceeded max iterations in "
                         "send-loop: packets sent = "
                      << packets_sent << ", padding packets generated = "
                      << padding_packets_generated
                      << ", bytes sent = " << data_sent.bytes();
    last_send_time_ = now;
    last_process_time_ = now;
    return;
  }
}

Timestamp PacingController::NextSendTime()
{
  const Timestamp now = CurrentTime();
  Timestamp next_send_time = Timestamp::PlusInfinity();

  if (paused_) {
    return last_send_time_ + kPausedProcessInterval;
  }

  // If probing is active, that always takes priority.
  if (prober_.is_probing() && !probing_send_failure_) {
    Timestamp probe_time = prober_.NextProbeTime(now);
    if (!probe_time.IsPlusInfinity()) {
      return probe_time.IsMinusInfinity() ? now : probe_time;
    }
  }

  // Not pacing audio, if leading packet is audio its target send
  // time is the time at which it was enqueued.
  Timestamp unpaced_audio_time =
      pace_audio_ ? Timestamp::PlusInfinity()
                  : packet_queue_->LeadingAudioPacketEnqueueTime();
  if (unpaced_audio_time.IsFinite()) {
    return unpaced_audio_time;
  }

  if (congested_ || !seen_first_packet_) {
    // We need to at least send keep-alive packets with some interval.
    return last_send_time_ + kCongestedPacketInterval;
  }

  if (adjusted_media_rate_ > DataRate::Zero() && !packet_queue_->Empty()) {
    // If packets are allowed to be sent in a burst, the
    // debt is allowed to grow up to one packet more than what can be sent
    // during 'send_burst_period_'.
    TimeDelta drain_time = media_debt_ / adjusted_media_rate_;
    next_send_time =
        last_process_time_ +
        ((send_burst_interval_ > drain_time) ? TimeDelta::Zero() : drain_time);
  } else if (padding_rate_ > DataRate::Zero() && packet_queue_->Empty()) {
    // If we _don't_ have pending packets, check how long until we have
    // bandwidth for padding packets. Both media and padding debts must
    // have been drained to do this.
    RTC_DCHECK_GT(adjusted_media_rate_, DataRate::Zero());
    TimeDelta drain_time = std::max(media_debt_ / adjusted_media_rate_,
                                    padding_debt_ / padding_rate_);

    if (drain_time.IsZero() &&
        (!media_debt_.IsZero() || !padding_debt_.IsZero())) {
      // We have a non-zero debt, but drain time is smaller than tick size of
      // TimeDelta, round it up to the smallest possible non-zero delta.
      drain_time = TimeDelta::Micros(1);
    }
    next_send_time = last_process_time_ + drain_time;
  } else {
    // Nothing to do.
    next_send_time = last_process_time_ + kPausedProcessInterval;
  }

  if (send_padding_if_silent_) {
    next_send_time =
        std::min(next_send_time, last_send_time_ + kPausedProcessInterval);
  }

  return next_send_time;
}

TimeDelta PacingController::UpdateTimeAndGetElapsed(Timestamp now)
{
  if (now < last_process_time_)
    return TimeDelta::Zero();

  TimeDelta elapsed_time = now - last_process_time_;
  last_process_time_ = now;
  if (elapsed_time > kMaxElapsedTime) {
    RTC_LOG(LS_WARNING) << "Elapsed time (" << elapsed_time.ms()
                        << " ms) longer than expected, limiting to "
                        << kMaxElapsedTime.ms();
    elapsed_time = kMaxElapsedTime;
  }
  return elapsed_time;
}

Timestamp PacingController::CurrentTime() const
{
  Timestamp time = clock_->CurrentTime();

  if (time < last_timestamp_) {
    RTC_LOG(LS_WARNING)
        << "Non-monotonic clock behavior observed. Previous timestamp: "
        << last_timestamp_.ms() << ", new timestamp: " << time.ms();
    RTC_DCHECK_GE(time, last_timestamp_);
    time = last_timestamp_;
  }
  last_timestamp_ = time;
  return time;
}


void PacingController::UpdateBudgetWithElapsedTime(TimeDelta delta) {
  media_debt_ -= std::min(media_debt_, adjusted_media_rate_ * delta);
  //  padding_debt_ -= std::min(padding_debt_, padding_rate_ * delta);
}

void PacingController::UpdateBudgetWithSentData(DataSize size) {
  media_debt_ += size;
  media_debt_ = std::min(media_debt_, adjusted_media_rate_ * kMaxDebtInTime);
  UpdatePaddingBudgetWithSentData(size);
}

void PacingController::UpdatePaddingBudgetWithSentData(DataSize size) {
  padding_debt_ += size;
  padding_debt_ = std::min(padding_debt_, padding_rate_ * kMaxDebtInTime);
}

std::unique_ptr<RtpPacketToSend> PacingController::GetPendingPacket(
    const PacedPacketInfo &pacing_info, Timestamp target_send_time, Timestamp now)
{
  if (packet_queue_->Empty()) {
    return nullptr;
  }

  // First, check if there is any reason _not_ to send the next queued packet.

  // Unpaced audio packets and probes are exempted from send checks.
  bool unpaced_audio_packet =
      !pace_audio_ && packet_queue_->LeadingAudioPacketEnqueueTime().IsFinite();
  if (!unpaced_audio_packet) {
    if (congested_) {
      // Don't send anything if congested.
      return nullptr;
    }

    if (now <= target_send_time && send_burst_interval_.IsZero()) {
      // We allow sending slightly early if we think that we would actually
      // had been able to, had we been right on time - i.e. the current debt
      // is not more than would be reduced to zero at the target sent time.
      // If we allow packets to be sent in a burst, packet are allowed to be
      // sent early.
      TimeDelta flush_time = media_debt_ / adjusted_media_rate_;
      if (now + flush_time > target_send_time) {
        return nullptr;
      }
    }
  }

  return packet_queue_->Pop();
}

void PacingController::MaybeUpdateMediaRateDueToLongQueue(Timestamp now)
{
  adjusted_media_rate_ = pacing_rate_;
  if (!drain_large_queues_) {
    return;
  }

  DataSize queue_size_data = QueueSizeData();
  if (queue_size_data > DataSize::Zero()) {
    // Assuming equal size packets and input/output rate, the average packet
    // has avg_time_left_ms left to get queue_size_bytes out of the queue, if
    // time constraint shall be met. Determine bitrate needed for that.
    packet_queue_->UpdateAverageQueueTime(now);
    TimeDelta avg_time_left =
        std::max(TimeDelta::Millis(1),
                 queue_time_limit_ - packet_queue_->AverageQueueTime()); // queue_time_limit_
    // default 2000
    DataRate min_rate_needed = queue_size_data / avg_time_left;
    if (min_rate_needed > pacing_rate_) {
      adjusted_media_rate_ = min_rate_needed;
      RTC_LOG(LS_VERBOSE) << "bwe:large_pacing_queue pacing_rate_kbps="
                          << pacing_rate_.kbps();
    }
  }
}

void PacingController::OnPacketSent(PacketMediaType packet_type, DataSize packet_size, Timestamp send_time)
{
  bool audio_packet = packet_type == PacketMediaType::kAudio;
  if ((!audio_packet) && packet_size > DataSize::Zero()) {
    UpdateBudgetWithSentData(packet_size);
  }
  last_send_time_ = send_time;
}

} // namespace webrtc
