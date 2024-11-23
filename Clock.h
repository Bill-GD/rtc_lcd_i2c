#ifndef CLOCK
#define CLOCK

#include <Arduino.h>

struct datetime {
  int hour, min, sec, weekday, day, month, year;
};

class Clock {
public:
  int hour, min, sec, weekdayNum, day, month, year;
  String weekdayString;

  Clock(const char* date, const char* time);
  void getTime();
  String getTimeString();
  String getDateString();
};

class AlarmTime {
public:
  int hour, min, sec;

  AlarmTime(int hour, int min, int sec);
  // AlarmTime(AlarmTime other);
  String getTimeString();
  bool compareTime(Clock clock);
  void copyTime(AlarmTime other);
};

#endif