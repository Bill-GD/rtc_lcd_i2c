#include "Clock.h"

#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>

String daysOfTheWeek[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

/*!
    @param date __DATE__ string, e.g. "Apr 16 2020".
    @param time __TIME__ string, e.g. "18:34:56".
*/
datetime getDateTime(const char* date, const char* time) {
  String dateStr = String(date), timeStr = String(time);

  /** hour, min, sec, weekday, day, month, year */
  datetime res = datetime();

  res.year = atoi(dateStr.substring(8).c_str());
  res.day = atoi(dateStr.substring(5, 8).c_str());

  res.hour = atoi(timeStr.substring(0, 2).c_str());
  res.min = atoi(timeStr.substring(3, 5).c_str());
  res.sec = atoi(timeStr.substring(6).c_str());

  // Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec
  switch (dateStr[0]) {
    case 'J':
      res.month = (dateStr[1] == 'a') ? 1 : ((dateStr[2] == 'n') ? 6 : 7);
      break;
    case 'F':
      res.month = 2;
      break;
    case 'A':
      res.month = dateStr[2] == 'r' ? 4 : 8;
      break;
    case 'M':
      res.month = dateStr[2] == 'r' ? 3 : 5;
      break;
    case 'S':
      res.month = 9;
      break;
    case 'O':
      res.month = 10;
      break;
    case 'N':
      res.month = 11;
      break;
    case 'D':
      res.month = 12;
      break;
  }

  return res;
}

AlarmTime::AlarmTime(int hour, int min, int sec) {
  this->hour = hour;
  this->min = min;
  this->sec = sec;
  // Serial.println("Alarm at: " + this->getTimeString());
}

// AlarmTime::AlarmTime(AlarmTime other) {
//   this->hour = other->hour;
//   this->min = other->min;
//   this->sec = other->sec;
// }

String AlarmTime::getTimeString() {
  String hs = this->hour >= 10 ? String(this->hour) : "0" + String(this->hour),
         ms = this->min >= 10 ? String(this->min) : "0" + String(this->min),
         ss = this->sec >= 10 ? String(this->sec) : "0" + String(this->sec);
  return hs + ":" + ms + ":" + ss;
}

void AlarmTime::copyTime(AlarmTime other) {
  this->hour = other.hour;
  this->min = other.min;
  this->sec = other.sec;
  Serial.println("Alarm at: " + other.getTimeString());
}

Clock::Clock() {}

Clock::Clock(const char* date, const char* time) {
  datetime dt = getDateTime(date, time);
  this->hour = dt.hour;
  this->min = dt.min;
  this->sec = dt.sec;
  this->weekdayNum = dt.weekday;
  this->day = dt.day;
  this->month = dt.month;
  this->year = dt.year;
  this->weekdayString = daysOfTheWeek[dt.weekday];
}

void Clock::getTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    return;
  }

  this->hour = timeinfo.tm_hour;
  this->min = timeinfo.tm_min;
  this->sec = timeinfo.tm_sec;
  this->weekdayNum = timeinfo.tm_wday;
  this->day = timeinfo.tm_mday;
  this->month = timeinfo.tm_mon + 1;
  this->year = timeinfo.tm_year + 1900;
  this->weekdayString = daysOfTheWeek[timeinfo.tm_wday];
}

void Clock::setTime(const char* date, const char* time) {
  datetime dt = getDateTime(date, time);
  this->hour = dt.hour;
  this->min = dt.min;
  this->sec = dt.sec;
  this->weekdayNum = dt.weekday;
  this->day = dt.day;
  this->month = dt.month;
  this->year = dt.year;
  this->weekdayString = daysOfTheWeek[dt.weekday];
}

String Clock::getTimeString() {
  String hs = this->hour >= 10 ? String(this->hour) : "0" + String(this->hour),
         ms = this->min >= 10 ? String(this->min) : "0" + String(this->min),
         ss = this->sec >= 10 ? String(this->sec) : "0" + String(this->sec);
  return hs + ":" + ms + ":" + ss;
}

String Clock::getDateString() {
  String ds = this->day >= 10 ? String(this->day) : "0" + String(this->day),
         ms = this->month >= 10 ? String(this->month) : "0" + String(this->month);
  return ds + "-" + ms + "-" + String(this->year);
}

bool Clock::compareTime(int hour, int min, int sec) {
  return this->hour == hour && this->min == min && this->sec == sec;
}

bool Clock::compareTime(AlarmTime alarm) {
  return this->hour == alarm.hour && this->min == alarm.min && this->sec == alarm.sec;
}

bool Clock::compareDate(int day, int month, int year) {
  return this->day == day && this->month == month && this->year == year;
}

void Clock::copyDateTime(const Clock other) {
  this->hour = other.hour;
  this->min = other.min;
  this->sec = other.sec;
  this->weekdayNum = other.weekdayNum;
  this->weekdayString = other.weekdayString;
  this->day = other.day;
  this->month = other.month;
  this->year = other.year;
}