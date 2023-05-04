#ifndef PACED_SENDER_H
#define PACED_SENDER_H

#include <vector>
#include <memory>
#include "protocol.h"
#include "api/units/timestamp.h"
#include "api/units/time_delta.h"
#include "api/units/data_size.h"
#include "api/units/data_rate.h"
#include "system_wrappers/include/clock.h"
#include "modules/rtp_rtcp/include/rtp_rtcp_defines.h"

using std::vector;
using std::unique_ptr;

class BasePkt
{
public:
  virtual const char* Data();
  virtual size_t Size();
};

namespace webrtc {

// This class implements a leaky-bucket packet pacing algorithm. It handles the
// logic of determining which packets to send when, but the actual timing of
// the processing is done externally (e.g. RtpPacketPacer). Furthermore, the
// forwarding of packets when they are ready to be sent is also handled
// externally, via the PacingController::PacketSender interface.
class PacingController
{
public:
  class PacketSender {
     public:
      virtual ~PacketSender() = default;
      virtual void SendPacket(std::unique_ptr<RtpPacketToSend> packet,
                              const PacedPacketInfo& cluster_info) = 0;
      // Should be called after each call to SendPacket().
      virtual std::vector<std::unique_ptr<RtpPacketToSend>> FetchFec() = 0;
      virtual std::vector<std::unique_ptr<RtpPacketToSend>> GeneratePadding(
          DataSize size) = 0;
    };

  // Interface for class hanlding storage of and prioritization of packets
  // pending to be sent by the pacer.
  // Note that for the methods taking a Timestamp as parameter, the parameter
  // will never decrease between two subsequent calls.
  class PacketQueue {
  public:
    virtual ~PacketQueue() = default;

    virtual void Push(Timestamp enqueue_time,
                      std::unique_ptr<RtpPacketToSend> packet) = 0;
    virtual std::unique_ptr<RtpPacketToSend> Pop() = 0;

    virtual int SizeInPackets() const = 0;
    bool Empty() const { return SizeInPackets() == 0; }
    virtual DataSize SizeInPayloadBytes() const = 0;

    // Total packets in the queue per media type (RtpPacketMediaType values are
    // used as lookup index).
    virtual const std::array<int, kNumMediaTypes>&
    SizeInPacketsPerRtpPacketMediaType() const = 0;

    // If the next packet, that would be returned by Pop() if called
    // now, is an audio packet this method returns the enqueue time
    // of that packet. If queue is empty or top packet is not audio,
    // returns Timestamp::MinusInfinity().
    virtual Timestamp LeadingAudioPacketEnqueueTime() const = 0;

    // Enqueue time of the oldest packet in the queue,
    // Timestamp::MinusInfinity() if queue is empty.
    virtual Timestamp OldestEnqueueTime() const = 0;

    // Average queue time for the packets currently in the queue.
    // The queuing time is calculated from Push() to the last UpdateQueueTime()
    // call - with any time spent in a paused state subtracted.
    // Returns TimeDelta::Zero() for an empty queue.
    virtual TimeDelta AverageQueueTime() const = 0;

    // Called during packet processing or when pause stats changes. Since the
    // AverageQueueTime() method does not look at the wall time, this method
    // needs to be called before querying queue time.
    virtual void UpdateAverageQueueTime(Timestamp now) = 0;

    // Set the pause state, while `paused` is true queuing time is not counted.
    virtual void SetPauseState(bool paused, Timestamp now) = 0;
  };

  PacingController(Clock* clock,
                   PacketSender* packet_sender,
                   const FieldTrialsView& field_trials);
  ~PacingController();
  // Adds the packet to the queue and calls PacketRouter::SendPacket() when
    // it's time to send.
  void EnqueuePacket(std::unique_ptr<RtpPacketToSend> packet);

  void SetPacingRate(int Bps) { target_Bps_ = Bps; }

  void EnqueuePackets(vector<unique_ptr<BasePkt>> pkts);
  void ProcessPackets();
  Timestamp NextSendTime();

private:
  TimeDelta UpdateTimeAndGetElapsed(Timestamp now);
  Timestamp CurrentTime() const;

  void UpdateBudgetWithElapsedTime(TimeDelta delta);
  void UpdateBudgetWithSentData(DataSize size);
  void UpdatePaddingBudgetWithSentData(DataSize size);

  std::unique_ptr<RtpPacketToSend> GetPendingPacket(
      const PacedPacketInfo& pacing_info,
      Timestamp target_send_time,
      Timestamp now);
  void OnPacketSent(RtpPacketMediaType packet_type,
                    DataSize packet_size,
                    Timestamp send_time);
  void MaybeUpdateMediaRateDueToLongQueue(Timestamp now);

  Clock* const clock_;
  PacketSender* const packet_sender_;

  // Amount of outstanding data for media and padding.
  DataSize media_debt_;
  DataSize padding_debt_;

  // The target pacing rate, signaled via SetPacingRates().
  DataRate pacing_rate_;
  // The media send rate, which might adjusted from pacing_rate_, e.g. if the
  // pacing queue is growing too long.
  DataRate adjusted_media_rate_;

  int target_bps_;
  Timestamp last_process_time_;
  Timestamp last_send_time_;

  // TODO(webrtc:9716): Remove this when we are certain clocks are monotonic.
  // The last millisecond timestamp returned by `clock_`.
  mutable Timestamp last_timestamp_;

  std::unique_ptr<PacketQueue> packet_queue_;
};

} // namespace webrtc

#endif // PACED_SENDER_H
