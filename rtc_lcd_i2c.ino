#include "LiquidCrystal_I2C.h"
#include "IRremote.h"

#include "Buzzer.cpp"
#include "Helper.h"
#include "RTCControl.h"

#define IR_PIN 2
#define LED_PIN 3
#define BUZZER_PIN 4
#define BUZZER_TIME_SEC 2
#define REMOTE_LEFT 0xFFE01F
#define REMOTE_RIGHT 0xFF906F
#define REMOTE_OK 0xFFA857
#define REMOTE_UP 0xFF02FD
#define REMOTE_DOWN 0xFF9867
#define REMOTE_TEST 0xFF22DD
#define REMOTE_BACK 0xFFC23D
#define REMOTE_C 0xFFB04F
#define REMOTE_MENU 0xFFE21D

LiquidCrystal_I2C lcd(0x27, 16, 2);
RTCDateTime clockTime, editTime;
IRrecv irrecv(IR_PIN);
bool clockEnabled = true, canEdit = false, canSetTime = false;
int editPos = 0;
unsigned int currentTime = 0;
Buzzer buzzer = Buzzer();

void setup() {
  Serial.begin(9600);
  Serial.println("Running: " + (String)__FILE__);
  RTCDateTime::initRTC(DateTime(F(__DATE__), F(__TIME__)));
  lcd.init();
  lcd.backlight();
  pinMode(LED_PIN, OUTPUT);
  irrecv.enableIRIn();
  buzzer.setTempo(105);
}

void loop() {
  if (delayNoDelay(200)) {
    decode_results result;
    if (irrecv.decode(&result)) {
      unsigned long v = result.value;
      switch (v) {
        case REMOTE_UP:
          Serial.println("UP");
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
          if (canSetTime) {
            RTCDateTime::rtc.adjust(DateTime(editTime.year, editTime.month, editTime.day, editTime.hour, editTime.min, editTime.sec));
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
            if (canEdit) clockTime.copyDateTime(editTime);
            else editTime.copyDateTime(clockTime);
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
          RTCDateTime::rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
          break;
        case REMOTE_MENU:
          Serial.println("MENU");
          break;
        default:
          Serial.println(v, HEX);
      }
      irrecv.resume();
    }
  }

  if (delayNoDelay(10)) {
    if (clockTime.compareTime(6, 0, 0)) {
      digitalWrite(LED_PIN, HIGH);
      // tone(BUZZER_PIN, 1, BUZZER_TIME_SEC * 1000);
      buzzer.playMusic(BUZZER_PIN, LED_PIN, true);  // causing problem
    } else {
      digitalWrite(LED_PIN, LOW);
    }
  }

  if (delayNoDelay(200)) {
    if (clockEnabled) clockTime = RTCDateTime::getRTCTime();
    lcdMainDisplay(canEdit ? editTime : clockTime);
    if (canEdit) lcdEditBlink();
  }
  delay(50);
}

void lcdMainDisplay(RTCDateTime datetime) {
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
