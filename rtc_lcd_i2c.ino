#include "RTClib.h"
#include "LiquidCrystal_I2C.h"
#include "IRremote.h"

#define IR_PIN 2
#define LED_PIN 3
#define BUZZER_PIN 13
#define BUZZER_TIME_SEC 2
#define REMOTE_B_LEFT 0xFFE01F
#define REMOTE_B_RIGHT 0xFF906F
#define REMOTE_B_OK 0xFFA857
#define REMOTE_B_UP 0xFF02FD
#define REMOTE_B_DOWN 0xFF9867
#define REMOTE_B_TEST 0xFF22DD
#define REMOTE_B_BACK 0xFFC23D
#define REMOTE_B_C 0xFFB04F
#define REMOTE_B_MENU 0xFF47B8

#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978
#define REST 0

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
date_time dt;
IRrecv irrecv(IR_PIN);
decode_results result;
bool clockEnabled = true, canEdit = false, canSetTime = false;
int editPos = 0;

// int melody[] = {

//   NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,8, //1
//   NOTE_G5,4, REST,4, NOTE_G4,8, REST,4,
//   NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // 3
//   NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
//   NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
//   REST,8, NOTE_E5,4,NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,
//   NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // repeats from 3
//   NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
//   NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
//   REST,8, NOTE_E5,4,NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,


//   REST,4, NOTE_G5,8, NOTE_FS5,8, NOTE_F5,8, NOTE_DS5,4, NOTE_E5,8,//7
//   REST,8, NOTE_GS4,8, NOTE_A4,8, NOTE_C4,8, REST,8, NOTE_A4,8, NOTE_C5,8, NOTE_D5,8,
//   REST,4, NOTE_DS5,4, REST,8, NOTE_D5,-4,
//   NOTE_C5,2, REST,2,

//   REST,4, NOTE_G5,8, NOTE_FS5,8, NOTE_F5,8, NOTE_DS5,4, NOTE_E5,8,//repeats from 7
//   REST,8, NOTE_GS4,8, NOTE_A4,8, NOTE_C4,8, REST,8, NOTE_A4,8, NOTE_C5,8, NOTE_D5,8,
//   REST,4, NOTE_DS5,4, REST,8, NOTE_D5,-4,
//   NOTE_C5,2, REST,2,

//   NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4,//11
//   NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,

//   NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,8, NOTE_E5,8,//13
//   REST,1,
//   NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4,
//   NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,
//   NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,4,
//   NOTE_G5,4, REST,4, NOTE_G4,4, REST,4,
//   NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // 19

//   NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
//   NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
//   REST,8, NOTE_E5,4, NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,

//   NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // repeats from 19
//   NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
//   NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
//   REST,8, NOTE_E5,4, NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,

//   NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,//23
//   NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
//   NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8,

//   NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2, //26
//   NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
//   NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
//   NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8,
//   NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,

//   NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,//repeats from 23
//   NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
//   NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8,

//   NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2, //26
//   NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
//   NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
//   NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8,
//   NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,
//   NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,8, NOTE_E5,8,
//   REST,1,

//   NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4, //33
//   NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,
//   NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,4,
//   NOTE_G5,4, REST,4, NOTE_G4,4, REST,4,
//   NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
//   NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
//   NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8,

//   NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2, //40
//   NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
//   NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
//   NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8,
//   NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,

//   //game over sound
//   NOTE_C5,-4, NOTE_G4,-4, NOTE_E4,4, //45
//   NOTE_A4,-8, NOTE_B4,-8, NOTE_A4,-8, NOTE_GS4,-8, NOTE_AS4,-8, NOTE_GS4,-8,
//   NOTE_G4,8, NOTE_D4,8, NOTE_E4,-2,

// };

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
      case REMOTE_B_UP:
        Serial.println("UP");
        if (!canEdit) break;
        if (editPos == 0) dt.hour = dt.hour == 23 ? 0 : dt.hour + 1;
        if (editPos == 1) dt.min = dt.min == 59 ? 0 : dt.min + 1;
        if (editPos == 2) dt.sec = dt.sec == 59 ? 0 : dt.sec + 1;
        if (editPos == 3) {
          int d = 0;
          if (dt.month == 2) d = dt.year % 4 == 0 ? 29 : 28;
          else if (dt.month == 4 || dt.month == 6 || dt.month == 9 || dt.month == 11) d = 30;
          else d = 31;
          dt.day = dt.day == d ? 1 : dt.day + 1;
          dt.weekdayNum = (dt.weekdayNum + 1) % 7;
        }
        if (editPos == 4) dt.month = dt.month == 12 ? 1 : dt.month + 1;
        if (editPos == 5) dt.year++;
        break;
      case REMOTE_B_DOWN:
        Serial.println("DOWN");
        if (!canEdit) break;
        if (editPos == 0) dt.hour = dt.hour == 0 ? 23 : dt.hour - 1;
        if (editPos == 1) dt.min = dt.min == 0 ? 59 : dt.min - 1;
        if (editPos == 2) dt.sec = dt.sec == 0 ? 59 : dt.sec - 1;
        if (editPos == 3) {
          int d = 0;
          if (dt.month == 2) d = dt.year % 4 == 0 ? 29 : 28;
          else if (dt.month == 4 || dt.month == 6 || dt.month == 9 || dt.month == 11) d = 30;
          else d = 31;
          dt.day = dt.day == 1 ? d : dt.day - 1;
          dt.weekdayNum = dt.weekdayNum == 0 ? 6 : dt.weekdayNum - 1;
        }
        if (editPos == 4) dt.month = dt.month == 1 ? 12 : dt.month - 1;
        if (editPos == 5 && dt.year > 0) dt.year--;
        break;
      case REMOTE_B_OK:
        Serial.println("OK");
        if (canSetTime) {
          rtc.adjust(DateTime(dt.year, dt.month, dt.day, dt.hour, dt.min, dt.sec));
          canSetTime = false;
        }
        if (!canEdit) clockEnabled = !clockEnabled;
        break;
      case REMOTE_B_LEFT:
        Serial.println("LEFT");
        if (canEdit && editPos > 0) {
          if (editPos == 3) lcd.clear();
          editPos--;
        }
        Serial.println("editPos: " + (String)editPos);
        break;
      case REMOTE_B_RIGHT:
        Serial.println("RIGHT");
        if (canEdit && editPos < 5) {
          if (editPos == 2) lcd.clear();
          editPos++;
        }
        Serial.println("editPos: " + (String)editPos);
        break;
      case REMOTE_B_TEST:
        Serial.println("TEST");
        if (canEdit) canSetTime = true;
        if (!clockEnabled) {
          canEdit = !canEdit;
          lcd.clear();
        }
        break;
      case REMOTE_B_BACK:
        Serial.println("BACK");
        if (canEdit && !clockEnabled) {
          canEdit = false;
          lcd.clear();
        }
        break;
      case REMOTE_B_C:
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

  displayLcd(dt);
  delay(200);
}

void displayLcd(date_time dt) {
  dt.time_string = newTimeString();
  dt.date_string = neweekdayNumateString();

  lcd.setCursor(0, 0);
  lcd.print(dt.time_string + "   " + (clockEnabled ? " ON" : "OFF") + " " + (canEdit ? "E" : "C"));
  lcd.setCursor(0, 1);
  lcd.print(dt.date_string + " " + dt.weekdayString);

  if (canEdit) {
    // blink time
    delay(200);
    if (editPos < 3) {
      lcd.setCursor(editPos * 3, 0);
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

  dt.time_string = newTimeString();
  dt.date_string = neweekdayNumateString();
  dt.full_string = dt.time_string + " " + dt.weekdayString + " " + dt.date_string;

  return dt;
}

String newTimeString() {
  String hs = dt.hour >= 10 ? String(dt.hour) : "0" + String(dt.hour),
         mis = dt.min >= 10 ? String(dt.min) : "0" + String(dt.min),
         ss = dt.sec >= 10 ? String(dt.sec) : "0" + String(dt.sec);
  return hs + ":" + mis + ":" + ss;
}

String neweekdayNumateString() {
  String ds = dt.day >= 10 ? String(dt.day) : "0" + String(dt.day),
         ms = dt.month >= 10 ? String(dt.month) : "0" + String(dt.month);
  return ds + "-" + ms + "-" + String(dt.year);
}
