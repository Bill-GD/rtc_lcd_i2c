#include <Arduino.h>
#define DECODE_NEC

#include <WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "IRremote.hpp"

#include "Buzzer.cpp"
#include "Helper.h"
#include "Clock.h"

#define IR_PIN 14
#define LED_PIN 23
#define BUZZER_PIN 32

#define REMOTE_LEFT 0x07
#define REMOTE_RIGHT 0x09
#define REMOTE_OK 0x15
#define REMOTE_UP 0x40
#define REMOTE_DOWN 0x19
#define REMOTE_TEST 0x44
#define REMOTE_BACK 0x43
#define REMOTE_C 0x0D
#define REMOTE_MENU 0x47
#define REMOTE_1 0x30
#define REMOTE_2 0x18

#define NTP_SERVER     "pool.ntp.org"
#define UTC_OFFSET     0
#define UTC_OFFSET_DST 0

LiquidCrystal_I2C lcd(0x27, 16, 2);
Clock clockTime = Clock(__DATE__, __TIME__), editTime = Clock(__DATE__, __TIME__);
AlarmTime currentAlarmTime = AlarmTime(6, 0, 0), alarmEditTime = AlarmTime(6, 0, 0);
Buzzer buzzer = Buzzer();

bool clockEnabled = true, canEditTime = false, canSetTime = false, canAlarm = false;
bool showMenu = false, showAlarm = false;
int editPos = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Running: " + (String)__FILE__);
  Serial.println("Using IRremote library version " VERSION_IRREMOTE);
  lcd.init();
  lcd.backlight();
  pinMode(LED_PIN, OUTPUT);
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);

  WiFi.begin("Wokwi-GUEST", "", 6);
  while (WiFi.status() != WL_CONNECTED) {
    lcd.setCursor(0, 0);
    lcd.print("Connecting...");
    delay(250);
  }
  configTime(UTC_OFFSET, UTC_OFFSET_DST, NTP_SERVER);
  // Clock::rtc.setTime(__DATE__, "05:59:55");

  Serial.print("Ready to receive IR signals of protocols: ");
  printActiveIRProtocols(&Serial);
  Serial.println("at pin " + (String)IR_PIN);
}

void loop() {
  if (delayNoDelay(100)) {
    if (IrReceiver.decode()) {
      unsigned long v = IrReceiver.decodedIRData.command;
      switch (v) {
        case REMOTE_OK:
          Serial.println("OK");
          if (showMenu) break;
          if (canSetTime) {
            clockTime.copyDateTime(editTime);
            canSetTime = false;
          }
          if (!canEditTime) {
            clockEnabled = !clockEnabled;
            Serial.print(F("Clock "));
            Serial.println(clockEnabled ? "ON" : "OFF");
          }
          break;
        case REMOTE_UP:
          Serial.println("UP");
          if (showMenu) break;
          if (showAlarm) {
            if (editPos == 0) alarmEditTime.hour = alarmEditTime.hour == 23 ? 0 : alarmEditTime.hour + 1;
            if (editPos == 1) alarmEditTime.min = alarmEditTime.min == 59 ? 0 : alarmEditTime.min + 1;
            if (editPos == 2) alarmEditTime.sec = alarmEditTime.sec == 59 ? 0 : alarmEditTime.sec + 1;
            break;
          }
          if (!canEditTime) break;
          if (editPos == 0) editTime.hour = editTime.hour == 23 ? 0 : editTime.hour + 1;
          if (editPos == 1) editTime.min = editTime.min == 59 ? 0 : editTime.min + 1;
          if (editPos == 2) editTime.sec = editTime.sec == 59 ? 0 : editTime.sec + 1;
          if (editPos == 3) {
            int d = 0;
            if (editTime.month == 2) d = editTime.year % 4 == 0 ? 29 : 28;
            else if (editTime.month == 4 || editTime.month == 6 || editTime.month == 9 || editTime.month == 11) d = 30;
            else d = 31;
            editTime.day = editTime.day == d ? 1 : editTime.day + 1;
          }
          if (editPos == 4) editTime.month = editTime.month == 12 ? 1 : editTime.month + 1;
          if (editPos == 5) editTime.year++;
          Serial.println("Time: " + editTime.getTimeString() + " " + editTime.getDateString());
          break;
        case REMOTE_DOWN:
          Serial.println("DOWN");
          if (showMenu) break;
          if (showAlarm) {
            if (editPos == 0) alarmEditTime.hour = alarmEditTime.hour == 0 ? 23 : alarmEditTime.hour - 1;
            if (editPos == 1) alarmEditTime.min = alarmEditTime.min == 0 ? 59 : alarmEditTime.min - 1;
            if (editPos == 2) alarmEditTime.sec = alarmEditTime.sec == 0 ? 59 : alarmEditTime.sec - 1;
            break;
          }
          if (!canEditTime) break;
          if (editPos == 0) editTime.hour = editTime.hour == 0 ? 23 : editTime.hour - 1;
          if (editPos == 1) editTime.min = editTime.min == 0 ? 59 : editTime.min - 1;
          if (editPos == 2) editTime.sec = editTime.sec == 0 ? 59 : editTime.sec - 1;
          if (editPos == 3) {
            int d = 0;
            if (editTime.month == 2) d = editTime.year % 4 == 0 ? 29 : 28;
            else if (editTime.month == 4 || editTime.month == 6 || editTime.month == 9 || editTime.month == 11) d = 30;
            else d = 31;
            editTime.day = editTime.day == 1 ? d : editTime.day - 1;
          }
          if (editPos == 4) editTime.month = editTime.month == 1 ? 12 : editTime.month - 1;
          if (editPos == 5 && editTime.year > 0) editTime.year--;
          Serial.println("Time: " + editTime.getTimeString() + " " + editTime.getDateString());
          break;
        case REMOTE_LEFT:
          Serial.println("LEFT");
          if (showMenu) break;
          if (editPos > 0) {
            if (canEditTime && editPos == 3) lcd.clear();
            editPos--;
            Serial.println("editPos: " + (String)editPos);
          }
          break;
        case REMOTE_RIGHT:
          Serial.println("RIGHT");
          if (showMenu) break;
          if (editPos < 5) {
            if (canEditTime && editPos == 2) lcd.clear();
            editPos++;
            Serial.println("editPos: " + (String)editPos);
          }
          break;
        case REMOTE_TEST:
          Serial.println("TEST");
          if (showMenu) break;
          if (canEditTime) canSetTime = true;
          if (!clockEnabled) {
            if (canEditTime) clockTime.copyDateTime(editTime);
            else editTime.copyDateTime(clockTime);
            canEditTime = !canEditTime;
            if (canEditTime) Serial.println("Time: " + editTime.getTimeString() + " " + editTime.getDateString());
            lcd.clear();
          }
          break;
        case REMOTE_C:
          Serial.println("C");
          if (showMenu) break;
          clockTime.setTime(__DATE__, __TIME__);
          break;
        case REMOTE_BACK:
          Serial.println("BACK");
          if (showMenu) break;
          if (canEditTime && !clockEnabled) {
            canEditTime = false;
            lcd.clear();
          }
          if (showAlarm) {
            showMenu = true;
            showAlarm = false;
            alarmEditTime.copyTime(currentAlarmTime);
          }
          break;
        case REMOTE_MENU:
          Serial.println("MENU");
          showMenu = !showMenu;
          if (showMenu) {
            Serial.println(F("1. Clock"));
            Serial.println(F("2. Alarm"));
          }
          showAlarm = false;
          currentAlarmTime.copyTime(alarmEditTime);
          lcd.clear();
          break;
        case REMOTE_1:
          Serial.println("1");
          if (!showMenu) break;
          showMenu = false;
          break;
        case REMOTE_2:
          Serial.println("2");
          if (!showMenu) break;
          lcd.clear();
          showMenu = false;
          showAlarm = true;
          editPos = 0;
          break;
        default:
          Serial.print("0x");
          Serial.println(v, HEX);
          if (canAlarm) canAlarm = false;
          break;
      }
      IrReceiver.resume();
    }
  }

  if (delayNoDelay(10)) {
    if (clockTime.compareTime(currentAlarmTime)) {
      canAlarm = true;
      Serial.println("Alarm!! " + currentAlarmTime.getTimeString());
    }
    if (canAlarm) {
      bool canPlay = buzzer.playMusic(BUZZER_PIN, LED_PIN, true);
      canAlarm = canPlay;
    }
  }

  if (delayNoDelay(100)) {
    if (clockEnabled) clockTime.getTime();
    if (showMenu) {
      lcdShowMenu();
    } else if (showAlarm) {
      lcdEditAlarm(alarmEditTime);
      lcdAlarmEditBlink();
    } else {
      lcdDisplayClock(canEditTime ? editTime : clockTime);
      if (canEditTime) lcdClockEditBlink();
    }
  }

  if (delayNoDelay(1000) && !canEditTime) {
    Serial.println("Time: " + clockTime.getTimeString() + " " + clockTime.getDateString());
  }

  delay(50);
}

void lcdDisplayClock(Clock datetime) {
  lcd.setCursor(0, 0);
  lcd.print(" " + datetime.getTimeString() + "  " + (clockEnabled ? " ON" : "OFF") + " " + (canEditTime ? "E" : "C"));
  lcd.setCursor(0, 1);
  lcd.print(datetime.getDateString() + " " + datetime.weekdayString + " " + "M");
}

void lcdClockEditBlink() {
  if (delayNoDelay(200)) return;
  // blink time
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

void lcdShowMenu() {
  lcd.setCursor(0, 0);
  lcd.print(F("1. Clock    "));
  lcd.setCursor(0, 1);
  lcd.print(F("2. Alarm    "));

  lcd.setCursor(15, 1);
  lcd.print(F("M"));
}

void lcdEditAlarm(AlarmTime alarm) {
  lcd.setCursor(15, 0);
  lcd.print(F("M"));

  lcd.setCursor(1, 0);
  lcd.print(F("Edit alarm:"));
  lcd.setCursor(1, 1);
  lcd.print(alarm.getTimeString());
}

void lcdAlarmEditBlink() {
  if (delayNoDelay(200)) return;

  if (editPos < 3) {
    lcd.setCursor(editPos * 3 + 1, 1);
    lcd.print("  ");
  }
}
