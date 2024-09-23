#include "Helper.h"

bool delayNoDelay(unsigned int *current, unsigned int ms) {
  unsigned int now = millis();
  if (now - *current >= ms) {
    *current = now;
    return true;
  }
  return false;
}