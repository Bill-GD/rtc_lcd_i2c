#ifndef HELPER
#define HELPER

#include "Arduino.h"

struct DelayCallback {
  unsigned int lastExecutionTime;
  unsigned int delayDuration;
};

bool delayNoDelay(unsigned int ms);
#endif