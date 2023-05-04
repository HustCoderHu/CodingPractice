#ifndef TASK_QUEUE_PACED_SENDER_H
#define TASK_QUEUE_PACED_SENDER_H

#include <stdint.h>

class TaskQueuePacedSender
{
public:
  TaskQueuePacedSender();
  ~TaskQueuePacedSender();

  void SetPacingRate(uint64_t Bps);

  uint64_t pacing_Bps_;
}

#endif // TASK_QUEUE_PACED_SENDER_H
