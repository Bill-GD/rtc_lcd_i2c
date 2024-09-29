#ifndef RTCControl_h
#define RTCControl_h

#include "RTClib.h"

class AlarmTime {
public:
  int hour;
  int min;
  int sec;
  AlarmTime(int hour, int min, int sec);
  String getTimeString();
  void copyTime(AlarmTime other);
};

class RTCDateTime {
public:
  int hour, min, sec, weekdayNum, day, month, year;
  String weekdayString;
  static RTC_DS1307 rtc;

  static void initRTC(DateTime time);
  RTCDateTime();
  RTCDateTime(int hour, int min, int sec, int dayOfTheWeek, int day, int month, int year);
  static RTCDateTime getRTCTime();
  String getTimeString();
  String getDateString();
  bool compareTime(int hour, int min, int sec);
  bool compareTime(AlarmTime alarm);
  bool compareDate(int day, int month, int year);
  void copyDateTime(RTCDateTime other);
};

#endif
