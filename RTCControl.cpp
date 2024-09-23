#include "RTCControl.h"

RTC_DS1307 RTCDateTime::rtc;
String daysOfTheWeek[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

void RTCDateTime::initRTC() {
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

RTCDateTime::RTCDateTime() {}

RTCDateTime::RTCDateTime(int hour, int min, int sec, int dayOfTheWeek, int day, int month, int year) {
  this->hour = hour;
  this->min = min;
  this->sec = sec;
  this->weekdayNum = dayOfTheWeek;
  this->day = day;
  this->month = month;
  this->year = year;
  this->weekdayString = daysOfTheWeek[dayOfTheWeek];
}

RTCDateTime RTCDateTime::getRTCTime() {
  DateTime now = rtc.now();
  return RTCDateTime(now.hour(), now.minute(), now.second(), now.dayOfTheWeek(), now.day(), now.month(), now.year());
}

String RTCDateTime::getTimeString() {
  String hs = this->hour >= 10 ? String(this->hour) : "0" + String(this->hour),
    ms = this->min >= 10 ? String(this->min) : "0" + String(this->min),
    ss = this->sec >= 10 ? String(this->sec) : "0" + String(this->sec);
  return hs + ":" + ms + ":" + ss;
}

String RTCDateTime::getDateString() {
  String ds = this->day >= 10 ? String(this->day) : "0" + String(this->day),
    ms = this->month >= 10 ? String(this->month) : "0" + String(this->month);
  return ds + "-" + ms + "-" + String(this->year);
}

void RTCDateTime::copyDateTime(RTCDateTime other) {
  this->hour = other.hour;
  this->min = other.min;
  this->sec = other.sec;
  this->weekdayNum = other.weekdayNum;
  this->weekdayString = other.weekdayString;
  this->day = other.day;
  this->month = other.month;
  this->year = other.year;
}