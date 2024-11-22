#include "Helper.h"

#define MAX_DELAY_COUNT 10

Delay delays[MAX_DELAY_COUNT];

bool delayNoDelay(unsigned int ms) {
  unsigned int now = millis();

  for (int i = 0; i < MAX_DELAY_COUNT; i++) {
    if (delays[i].delayDuration == ms) {
      int timePassed = now - delays[i].lastExecutionTime;
      // Serial.println("Time passed: " + (String)timePassed + "ms");
      if (timePassed >= ms) {
        delays[i].lastExecutionTime = now;
        // Serial.println("Delayed: " + (String)ms + "ms");
        return true;
      }
      return false;
    } else if (delays[i].delayDuration == 0) {  // add new
      delays[i].delayDuration = ms;
      delays[i].lastExecutionTime = now;
      return false;
    }
  }
  return false;
}
