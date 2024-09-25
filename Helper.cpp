#include "Helper.h"

#define MAX_DELAY_COUNT 10

struct DelayCallback {
  unsigned int lastExecutionTime;
  unsigned int delayDuration;
};

DelayCallback delays[MAX_DELAY_COUNT]; // Assuming the maximum number of different delay values

bool delayNoDelay(unsigned int ms) {
  unsigned int now = millis();

  for (int i = 0; i < MAX_DELAY_COUNT; i++) {
    if (delays[i].delayDuration == ms) {
      if (now - delays[i].lastExecutionTime >= ms) {
        delays[i].lastExecutionTime = now;
        // Serial.print(F("Delayed: " (String)ms "ms"));
        return true;
      }
    } else if (delays[i].delayDuration == 0) { // find an empty slot to add new delay
      delays[i].delayDuration = ms;
      delays[i].lastExecutionTime = now;
      return false;
    }
  }
  return false; // if no empty slot and no matches found
}
