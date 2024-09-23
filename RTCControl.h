#ifndef RTCControl_h
#define RTCControl_h

#include "RTClib.h"

class RTCDateTime {
public:
  int hour, min, sec, weekdayNum, day, month, year;
  String weekdayString;
  static RTC_DS1307 rtc;

  static void initRTC();
  RTCDateTime();
  RTCDateTime(int hour, int min, int sec, int dayOfTheWeek, int day, int month, int year);
  static RTCDateTime getRTCTime();
  String getTimeString();
  String getDateString();
  void copyDateTime(RTCDateTime other);
};

#endif
