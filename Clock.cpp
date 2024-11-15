#ifndef CLOCK
#define CLOCK

#include <WiFi.h>
#include <Wire.h>

String daysOfTheWeek[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

/*!
    @param date __DATE__ string, e.g. "Apr 16 2020".
    @param time __TIME__ string, e.g. "18:34:56".
*/
int[] getDateTime(const char *date, const char *time) {
  String dateStr = String(date), timeStr = String(time);

  /** hour, min, sec, weekday, day, month, year */
  int res[7] = { 0, 0, 0, 0, 0, 0, 0 };

  res[6] = dateStr.substring(8);
  res[4] = dateStr.substring(5, 8);

  res[0] = timeStr.substring(0, 2);
  res[1] = timeStr.substring(3, 5);
  res[2] = timeStr.substring(6);

  // Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec
  switch (dateStr[0]) {
    case 'J':
      res[5] = (dateStr[1] == 'a') ? 1 : ((dateStr[2] == 'n') ? 6 : 7);
      break;
    case 'F':
      res[5] = 2;
      break;
    case 'A':
      res[5] = dateStr[2] == 'r' ? 4 : 8;
      break;
    case 'M':
      res[5] = dateStr[2] == 'r' ? 3 : 5;
      break;
    case 'S':
      res[5] = 9;
      break;
    case 'O':
      res[5] = 10;
      break;
    case 'N':
      res[5] = 11;
      break;
    case 'D':
      res[5] = 12;
      break;
  }

  return res;
}

class AlarmTime {
public:
  int hour, min, sec;

  AlarmTime(int hour, int min, int sec) {
    this->hour = hour;
    this->min = min;
    this->sec = sec;
    Serial.println("Alarm at: " + this->getTimeString());
  }

  String getTimeString() {
    String hs = this->hour >= 10 ? String(this->hour) : "0" + String(this->hour),
           ms = this->min >= 10 ? String(this->min) : "0" + String(this->min),
           ss = this->sec >= 10 ? String(this->sec) : "0" + String(this->sec);
    return hs + ":" + ms + ":" + ss;
  }

  void copyTime(AlarmTime other) {
    this->hour = other.hour;
    this->min = other.min;
    this->sec = other.sec;
    Serial.println("Alarm at: " + other.getTimeString());
  }
};

class Clock {
public:
  int hour, min, sec, weekdayNum, day, month, year;
  String weekdayString;

  Clock() {}

  Clock(const char *date, const char *time) {
    int[] datetime = getDateTime(date, time);
    this->hour = datetime[0];
    this->min = datetime[1];
    this->sec = datetime[2];
    this->weekdayNum = datetime[3];
    this->day = datetime[4];
    this->month = datetime[5];
    this->year = datetime[6];
    this->weekdayString = daysOfTheWeek[datetime[3]];
  }

  Clock(const int[] datetime) {
    /** hour, min, sec, weekday, day, month, year */
    this->hour = datetime[0];
    this->min = datetime[1];
    this->sec = datetime[2];
    this->weekdayNum = datetime[3];
    this->day = datetime[4];
    this->month = datetime[5];
    this->year = datetime[6];
    this->weekdayString = daysOfTheWeek[datetime[3]];
  }

  void getTime() {
    // Clock r = Clock(now.hour(), now.minute(), now.second(), now.dayOfTheWeek(), now.day(), now.month(), now.year());
    struct tm timeinfo;

    if (!getLocalTime(&timeinfo)) {
      // LCD.setCursor(0, 1);
      // LCD.println("Connection Err");
      return;
    }

    Serial.print(timeinfo);

    // LCD.setCursor(8, 0);
    // LCD.println(&timeinfo, "%H:%M:%S");

    // LCD.setCursor(0, 1);
    // LCD.println(&timeinfo, "%d/%m/%Y   %Z");
  }

  void setTime(const char *date, const char *time) {
    int[] datetime = getDateTime(date, time);
    this->hour = datetime[0];
    this->min = datetime[1];
    this->sec = datetime[2];
    this->weekdayNum = datetime[3];
    this->day = datetime[4];
    this->month = datetime[5];
    this->year = datetime[6];
    this->weekdayString = daysOfTheWeek[datetime[3]];
  }

  String getTimeString() {
    String hs = this->hour >= 10 ? String(this->hour) : "0" + String(this->hour),
           ms = this->min >= 10 ? String(this->min) : "0" + String(this->min),
           ss = this->sec >= 10 ? String(this->sec) : "0" + String(this->sec);
    return hs + ":" + ms + ":" + ss;
  }

  String getDateString() {
    String ds = this->day >= 10 ? String(this->day) : "0" + String(this->day),
           ms = this->month >= 10 ? String(this->month) : "0" + String(this->month);
    return ds + "-" + ms + "-" + String(this->year);
  }

  bool compareTime(int hour, int min, int sec) {
    return this->hour == hour && this->min == min && this->sec == sec;
  }

  bool compareTime(AlarmTime alarm) {
    return this->hour == alarm.hour && this->min == alarm.min && this->sec == alarm.sec;
  }

  bool compareDate(int day, int month, int year) {
    return this->day == day && this->month == month && this->year == year;
  }

  void copyDateTime(const Clock other) {
    this->hour = other.hour;
    this->min = other.min;
    this->sec = other.sec;
    this->weekdayNum = other.weekdayNum;
    this->weekdayString = other.weekdayString;
    this->day = other.day;
    this->month = other.month;
    this->year = other.year;
  }
};

#endif