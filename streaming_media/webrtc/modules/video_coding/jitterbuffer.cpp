#pragma once
#include <api/units/timestamp.h>
#include <api/units/time_delta.h>

namespace webrtc {

class JitterBuffer
{
public:

  TimeDelta MeanDelay(Timestamp now);
};

} //webrtc
