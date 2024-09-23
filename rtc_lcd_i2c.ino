#include "RTClib.h"
#include "LiquidCrystal_I2C.h"
#include "IRremote.h"
#include "Buzzer.cpp"

#define IR_PIN 2
#define LED_PIN 3
#define BUZZER_PIN 13
#define BUZZER_TIME_SEC 2
#define REMOTE_LEFT 0xFFE01F
#define REMOTE_RIGHT 0xFF906F
#define REMOTE_OK 0xFFA857
#define REMOTE_UP 0xFF02FD
#define REMOTE_DOWN 0xFF9867
#define REMOTE_TEST 0xFF22DD
#define REMOTE_BACK 0xFFC23D
#define REMOTE_C 0xFFB04F
#define REMOTE_MENU 0xFF47B8

struct date_time {
  int hour;
  int min;
  int sec;
  int weekdayNum;
  String weekdayString;
  int day;
  int month;
  int year;
  String time_string;
  String date_string;
  String full_string;
};

String daysOfTheWeek[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

RTC_DS1307 rtc;  // required
LiquidCrystal_I2C lcd(0x27, 16, 2);
Notes allNotes;
date_time dt, dtEdit;
IRrecv irrecv(IR_PIN);
decode_results result;
bool clockEnabled = true, canEdit = false, canSetTime = false;
int editPos = 0;

void setup() {
  Serial.begin(9600);
  rtc.begin();
  lcd.init();
  pinMode(LED_PIN, OUTPUT);
  lcd.backlight();
  irrecv.enableIRIn();
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void loop() {
  if (irrecv.decode(&result)) {
    unsigned long v = result.value;
    switch (v) {
      case REMOTE_UP:
        Serial.println("UP");
        if (!canEdit) break;
        if (editPos == 0) dtEdit.hour = dtEdit.hour == 23 ? 0 : dtEdit.hour + 1;
        if (editPos == 1) dtEdit.min = dtEdit.min == 59 ? 0 : dtEdit.min + 1;
        if (editPos == 2) dtEdit.sec = dtEdit.sec == 59 ? 0 : dtEdit.sec + 1;
        if (editPos == 3) {
          int d = 0;
          if (dtEdit.month == 2) d = dtEdit.year % 4 == 0 ? 29 : 28;
          else if (dtEdit.month == 4 || dtEdit.month == 6 || dtEdit.month == 9 || dtEdit.month == 11) d = 30;
          else d = 31;
          dtEdit.day = dtEdit.day == d ? 1 : dtEdit.day + 1;
          dtEdit.weekdayNum = (dtEdit.weekdayNum + 1) % 7;
        }
        if (editPos == 4) dtEdit.month = dtEdit.month == 12 ? 1 : dtEdit.month + 1;
        if (editPos == 5) dtEdit.year++;
        break;
      case REMOTE_DOWN:
        Serial.println("DOWN");
        if (!canEdit) break;
        if (editPos == 0) dtEdit.hour = dtEdit.hour == 0 ? 23 : dtEdit.hour - 1;
        if (editPos == 1) dtEdit.min = dtEdit.min == 0 ? 59 : dtEdit.min - 1;
        if (editPos == 2) dtEdit.sec = dtEdit.sec == 0 ? 59 : dtEdit.sec - 1;
        if (editPos == 3) {
          int d = 0;
          if (dtEdit.month == 2) d = dtEdit.year % 4 == 0 ? 29 : 28;
          else if (dtEdit.month == 4 || dtEdit.month == 6 || dtEdit.month == 9 || dtEdit.month == 11) d = 30;
          else d = 31;
          dtEdit.day = dtEdit.day == 1 ? d : dtEdit.day - 1;
          dtEdit.weekdayNum = dtEdit.weekdayNum == 0 ? 6 : dtEdit.weekdayNum - 1;
        }
        if (editPos == 4) dtEdit.month = dtEdit.month == 1 ? 12 : dtEdit.month - 1;
        if (editPos == 5 && dtEdit.year > 0) dtEdit.year--;
        break;
      case REMOTE_OK:
        Serial.println("OK");
        if (canSetTime) {
          rtc.adjust(DateTime(dtEdit.year, dtEdit.month, dtEdit.day, dtEdit.hour, dtEdit.min, dtEdit.sec));
          canSetTime = false;
        }
        if (!canEdit) clockEnabled = !clockEnabled;
        break;
      case REMOTE_LEFT:
        Serial.println("LEFT");
        if (canEdit && editPos > 0) {
          if (editPos == 3) lcd.clear();
          editPos--;
        }
        Serial.println("editPos: " + (String)editPos);
        break;
      case REMOTE_RIGHT:
        Serial.println("RIGHT");
        if (canEdit && editPos < 5) {
          if (editPos == 2) lcd.clear();
          editPos++;
        }
        Serial.println("editPos: " + (String)editPos);
        break;
      case REMOTE_TEST:
        Serial.println("TEST");
        if (canEdit) canSetTime = true;
        if (!clockEnabled) {
          if (canEdit) dt = copyDateTime(dtEdit);
          else dtEdit = copyDateTime(dt);
          canEdit = !canEdit;
          lcd.clear();
        }
        break;
      case REMOTE_BACK:
        Serial.println("BACK");
        if (canEdit && !clockEnabled) {
          canEdit = false;
          lcd.clear();
        }
        break;
      case REMOTE_C:
        Serial.println("C");
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
        break;
      default:
        Serial.println(v, HEX);
    }
    irrecv.resume();
  }

  if (clockEnabled) dt = getRTCTime();

  if (dt.hour == 6 && dt.min == 0 && dt.sec == 0 && clockEnabled) {
    digitalWrite(LED_PIN, HIGH);
    // tone(BUZZER_PIN, 1, BUZZER_TIME_SEC * 1000);
  } else {
    digitalWrite(LED_PIN, LOW);
  }

  lcdMainDisplay(canEdit ? dtEdit : dt);
  if (canEdit) lcdEditBlink();

  delay(200);
}

void lcdMainDisplay(date_time datetime) {
  datetime.time_string = newTimeString(datetime);
  datetime.date_string = newDateString(datetime);

  lcd.setCursor(0, 0);
  lcd.print(" " + datetime.time_string + "  " + (clockEnabled ? " ON" : "OFF") + " " + (canEdit ? "E" : "C"));
  lcd.setCursor(0, 1);
  lcd.print(datetime.date_string + " " + datetime.weekdayString + " " + "M");
}

void lcdEditBlink() {
  // blink time
  delay(200);
  if (editPos < 3) {
    lcd.setCursor(editPos * 3 + 1, 0);
    lcd.print("  ");
    return;
  }
  // blink date
  String empty = "  ";
  if (editPos == 5) empty += "  ";
  lcd.setCursor((editPos - 3) * 3, 1);
  lcd.print(empty);
}

date_time getRTCTime() {
  DateTime now = rtc.now();

  date_time dt;
  dt.hour = now.hour();
  dt.min = now.minute();
  dt.sec = now.second();
  dt.weekdayNum = now.dayOfTheWeek();
  dt.weekdayString = daysOfTheWeek[now.dayOfTheWeek()];
  dt.day = now.day();
  dt.month = now.month();
  dt.year = now.year();

  dt.time_string = newTimeString(dt);
  dt.date_string = newDateString(dt);
  dt.full_string = dt.time_string + " " + dt.weekdayString + " " + dt.date_string;

  return dt;
}

String newTimeString(date_time datetime) {
  String hs = datetime.hour >= 10 ? String(datetime.hour) : "0" + String(datetime.hour),
         mis = datetime.min >= 10 ? String(datetime.min) : "0" + String(datetime.min),
         ss = datetime.sec >= 10 ? String(datetime.sec) : "0" + String(datetime.sec);
  return hs + ":" + mis + ":" + ss;
}

String newDateString(date_time datetime) {
  String ds = datetime.day >= 10 ? String(datetime.day) : "0" + String(datetime.day),
         ms = datetime.month >= 10 ? String(datetime.month) : "0" + String(datetime.month);
  return ds + "-" + ms + "-" + String(datetime.year);
}

date_time copyDateTime(date_time other) {
  date_time self;

  self.hour = other.hour;
  self.min = other.min;
  self.sec = other.sec;
  self.weekdayNum = other.weekdayNum;
  self.weekdayString = other.weekdayString;
  self.day = other.day;
  self.month = other.month;
  self.year = other.year;

  self.time_string = newTimeString(self);
  self.date_string = newDateString(self);
  self.full_string = self.time_string + " " + self.weekdayString + " " + self.date_string;

  return self;
}
