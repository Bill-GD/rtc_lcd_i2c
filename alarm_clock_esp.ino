#include <Arduino.h>
#define DECODE_NEC

#include "LiquidCrystal_I2C.h"
// #include "IRremote.h"
#include <IRremote.hpp>

#include "Buzzer.cpp"
#include "Helper.h"
#include "RTCControl.h"

#if !defined(STR_HELPER)
#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)
#endif

// #define IR_RECEIVE_PIN 15
const uint8_t IR_PIN = 2;
const uint8_t LED_PIN = 23;
const uint8_t BUZZER_PIN = 32;
const uint8_t BUZZER_TIME_SEC = 10;
#define REMOTE_LEFT 0xE0
#define REMOTE_RIGHT 0x90
#define REMOTE_OK 0xA8
#define REMOTE_UP 0x02
#define REMOTE_DOWN 0x98
#define REMOTE_TEST 0x22
#define REMOTE_BACK 0xC2
#define REMOTE_C 0xB0
#define REMOTE_MENU 0xE2
#define REMOTE_1 0x30
#define REMOTE_2 0x18

LiquidCrystal_I2C lcd(0x27, 16, 2);
RTCDateTime clockTime, editTime;
// IRrecv irrecv(IR_PIN);
Buzzer buzzer = Buzzer();

bool clockEnabled = true, canSetTime = false, canAlarm = false;
bool canEdit = false, showMenu = false;
int editPos = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Running: " + (String)__FILE__);
  Serial.println("Using IRremote library version " VERSION_IRREMOTE);
  RTCDateTime::initRTC(DateTime(__DATE__, __TIME__));
  lcd.init();
  lcd.backlight();
  pinMode(LED_PIN, OUTPUT);
  // irrecv.enableIRIn();
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);
  RTCDateTime::rtc.adjust(DateTime(__DATE__, "05:59:55"));

  Serial.print("Ready to receive IR signals of protocols: ");
  printActiveIRProtocols(&Serial);
  Serial.println("at pin " STR(IR_PIN));
}

void loop() {
  if (delayNoDelay(200)) {
    // decode_results result;
    if (IrReceiver.decode()) {
      unsigned long v = IrReceiver.decodedIRData.command;
      switch (v) {
        case REMOTE_UP:
          Serial.println("UP");
          if (showMenu) break;
          if (!canEdit) break;
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
          break;
        case REMOTE_DOWN:
          Serial.println("DOWN");
          if (showMenu) break;
          if (!canEdit) break;
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
          break;
        case REMOTE_OK:
          Serial.println("OK");
          if (showMenu) break;
          if (canSetTime) {
            RTCDateTime::rtc.adjust(DateTime(editTime.year, editTime.month, editTime.day, editTime.hour, editTime.min, editTime.sec));
            canSetTime = false;
          }
          if (!canEdit) clockEnabled = !clockEnabled;
          break;
        case REMOTE_LEFT:
          Serial.println("LEFT");
          if (showMenu) break;
          if (canEdit && editPos > 0) {
            if (editPos == 3) lcd.clear();
            editPos--;
          }
          Serial.println("editPos: " + (String)editPos);
          break;
        case REMOTE_RIGHT:
          Serial.println("RIGHT");
          if (showMenu) break;
          if (canEdit && editPos < 5) {
            if (editPos == 2) lcd.clear();
            editPos++;
          }
          Serial.println("editPos: " + (String)editPos);
          break;
        case REMOTE_TEST:
          Serial.println("TEST");
          if (showMenu) break;
          if (canEdit) canSetTime = true;
          if (!clockEnabled) {
            if (canEdit) clockTime.copyDateTime(editTime);
            else editTime.copyDateTime(clockTime);
            canEdit = !canEdit;
            lcd.clear();
          }
          break;
        case REMOTE_BACK:
          Serial.println("BACK");
          if (showMenu) break;
          if (canEdit && !clockEnabled) {
            canEdit = false;
            lcd.clear();
          }
          break;
        case REMOTE_C:
          Serial.println("C");
          if (showMenu) break;
          RTCDateTime::rtc.adjust(DateTime(__DATE__, __TIME__));
          break;
        case REMOTE_MENU:
          Serial.println("MENU");
          showMenu = !showMenu;
          lcd.clear();
          break;
        case REMOTE_1:
          Serial.println("1");
          if (!showMenu) break;
          break;
        case REMOTE_2:
          Serial.println("2");
          if (!showMenu) break;
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
    if (clockTime.compareTime(6, 0, 0)) {
      canAlarm = true;
    }
    if (canAlarm) {
      // tone(BUZZER_PIN, 1, BUZZER_TIME_SEC * 1000);
      bool canPlay = buzzer.playMusic(BUZZER_PIN, LED_PIN, true);
      // bool canPlay = Buzzer().playMusic(BUZZER_PIN, currentNote, LED_PIN, true);
      canAlarm = canPlay;
      // currentNote = canAlarm ? currentNote + 1 : 0;
    }
  }

  if (delayNoDelay(200)) {
    if (clockEnabled) clockTime = RTCDateTime::getRTCTime();
    if (showMenu) {
      lcdShowMenu();
    } else {
      lcdDisplayClock(canEdit ? editTime : clockTime);
      if (canEdit) lcdEditBlink();
    }
  }
  delay(50);
}

void lcdDisplayClock(RTCDateTime datetime) {
  lcd.setCursor(0, 0);
  lcd.print(" " + datetime.getTimeString() + "  " + (clockEnabled ? " ON" : "OFF") + " " + (canEdit ? "E" : "C"));
  lcd.setCursor(0, 1);
  lcd.print(datetime.getDateString() + " " + datetime.weekdayString + " " + "M");
}

void lcdEditBlink() {
  if (!delayNoDelay(200)) {
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
}

void lcdShowMenu() {
  lcd.setCursor(0, 0);
  lcd.print(F("1. Clock"));
  lcd.setCursor(0, 1);
  lcd.print(F("2. Alarm"));
  lcd.setCursor(15, 1);
  lcd.print(F("M"));
}
