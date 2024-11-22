#ifndef CLOCK
#define CLOCK

#include <Arduino.h>

struct datetime {
  int hour, min, sec, weekday, day, month, year;
};

class AlarmTime {
public:
  int hour, min, sec;

  AlarmTime(int hour, int min, int sec);
  // AlarmTime(AlarmTime other);
  String getTimeString();
  void copyTime(AlarmTime other);
};

class Clock {
public:
  int hour, min, sec, weekdayNum, day, month, year;
  String weekdayString;

  Clock();
  Clock(const char* date, const char* time);
  void getTime();
  void setTime(const char* date, const char* time);
  String getTimeString();
  String getDateString();
  bool compareTime(int hour, int min, int sec);
  bool compareTime(AlarmTime alarm);
  bool compareDate(int day, int month, int year);
  void copyDateTime(const Clock other);
};

#endif