#include <Arduino.h>
#define DECODE_NEC

#include <LiquidCrystal_I2C.h>
#include "IRremote.hpp"

#include "Buzzer.cpp"
#include "Helper.h"
#include "Clock.h"
#include "NetworkInfo.h"

#define IR_PIN 14
#define LED_PIN 23
#define BUZZER_PIN 32

#define REMOTE_LEFT 0xE0
#define REMOTE_RIGHT 0x90
#define REMOTE_OK 0xA8
#define REMOTE_UP 0x2
#define REMOTE_DOWN 0x98
#define REMOTE_TEST 0x22
#define REMOTE_BACK 0xC2
#define REMOTE_C 0xB0
#define REMOTE_MENU 0xE2
#define REMOTE_OFF 0xA2
#define REMOTE_0 0x68
#define REMOTE_1 0x30
#define REMOTE_2 0x18
#define REMOTE_3 0x7A
#define REMOTE_4 0x10

#define MENU_ITEM_COUNT 4
#define NTP_SERVER "pool.ntp.org"

Clock clockTime = Clock(__DATE__, __TIME__);
AlarmTime currentAlarmTime = AlarmTime(6, 0, 0), alarmEditTime = AlarmTime(currentAlarmTime);
Buzzer buzzer = Buzzer();
LiquidCrystal_I2C lcd(0x27, 16, 2);
NetworkInfo currentNetwork;

bool clockEnabled = true, canAlarm = false;
bool showClock = true, showMenu = false, showAlarm = false, showMusic = false, showUtc = false;
bool showUiInConsole = false, isConnected = false;
int editPos = 0, menuIndex = 0, menuPage = 1, songIndex = 0;

// -12 to +12
int UTC_OFFSET = 7, UTC_OFFSET_DST = 7, editUtc = 7;

String menuItems[MENU_ITEM_COUNT] = {
  "1. Clock",
  "2. Alarm",
  "3. Music",
  "4. UTC",
};

void setup() {
  Serial.begin(115200);
  Serial.println("Running: " + (String)__FILE__);
  Serial.println("Using IRremote library version " VERSION_IRREMOTE);
  lcd.init();
  lcd.backlight();
  pinMode(LED_PIN, OUTPUT);
  IrReceiver.begin(IR_PIN, ENABLE_LED_FEEDBACK);

  lcd.setCursor(0, 0);
  printToLcd("Searching for", "open network...");

  currentNetwork = getAvailableNetwork();
  if (currentNetwork.ssid.isEmpty()) {
    printToLcd("Found no", "open network");
  } else {
    printToLcd("Connecting to", "(" + (String)currentNetwork.rssi + ")" + currentNetwork.ssid);
    connect(currentNetwork.ssid, currentNetwork.channel);
    isConnected = true;
  }

  // WiFi.begin("Wokwi-GUEST", "", 6);
  // while (WiFi.status() != WL_CONNECTED) {
  //   lcd.setCursor(0, 0);
  //   lcd.print("Connecting...");
  //   delay(250);
  // }
  updateTimeZone();
  // Clock::rtc.setTime(__DATE__, "05:59:55");

  Serial.print("Ready to receive IR signals of protocols: ");
  printActiveIRProtocols(&Serial);
  Serial.println("at pin " + (String)IR_PIN);
}

void loop() {
  if (delayNoDelay(10)) {
    if (IrReceiver.decode()) {
      unsigned long v = IrReceiver.decodedIRData.command;
      switch (v) {
        case REMOTE_OK:
          Serial.println("OK");
          if (showMenu || !isConnected) break;
          if (showAlarm) {
            lcdShowMenu();
            currentAlarmTime.copyTime(alarmEditTime);
          }
          if (showUtc) {
            lcdShowMenu();
            UTC_OFFSET = editUtc;
            UTC_OFFSET_DST = editUtc;
            updateTimeZone();
            clockTime.getTime();
            Serial.println("Updated UTC: " + (String)editUtc);
          }
          if (showMusic) {
            lcdShowMenu();
            buzzer.setSong(songIndex);
            Serial.println("Updated song: " + (String)songIndex + " - " + buzzer.names[songIndex]);
          }
          if (showClock) {
            clockEnabled = !clockEnabled;
            lcdDisplayClock(clockTime);
            Serial.print(F("Clock "));
            Serial.println(clockEnabled ? "ON" : "OFF");
          }
          break;
        case REMOTE_UP:
          Serial.println("UP");
          if (showMenu) {
            menuIndex = menuIndex <= 0 ? MENU_ITEM_COUNT - 2 : menuIndex - 1;
            menuPage = menuIndex + 1;
            lcdShowMenu();
            break;
          }
          if (showAlarm) {
            if (editPos == 0) alarmEditTime.hour = alarmEditTime.hour == 23 ? 0 : alarmEditTime.hour + 1;
            if (editPos == 1) alarmEditTime.min = alarmEditTime.min == 59 ? 0 : alarmEditTime.min + 1;
            if (editPos == 2) alarmEditTime.sec = alarmEditTime.sec == 59 ? 0 : alarmEditTime.sec + 1;
            break;
          }
          if (showUtc) {
            editUtc = editUtc >= 12 ? -12 : editUtc + 1;
            lcdEditTimeZone();
            break;
          }
          // Serial.println("Time: " + editTime.getTimeString() + " " + editTime.getDateString());
          break;
        case REMOTE_DOWN:
          Serial.println("DOWN");
          if (showMenu) {
            menuIndex = menuIndex >= MENU_ITEM_COUNT - 2 ? 0 : menuIndex + 1;
            menuPage = menuIndex + 1;
            lcdShowMenu();
            break;
          }
          if (showAlarm) {
            if (editPos == 0) alarmEditTime.hour = alarmEditTime.hour == 0 ? 23 : alarmEditTime.hour - 1;
            if (editPos == 1) alarmEditTime.min = alarmEditTime.min == 0 ? 59 : alarmEditTime.min - 1;
            if (editPos == 2) alarmEditTime.sec = alarmEditTime.sec == 0 ? 59 : alarmEditTime.sec - 1;
            break;
          }
          if (showUtc) {
            editUtc = editUtc <= -12 ? 12 : editUtc - 1;
            lcdEditTimeZone();
            break;
          }
          // Serial.println("Time: " + editTime.getTimeString() + " " + editTime.getDateString());
          break;
        case REMOTE_LEFT:
          Serial.println("LEFT");
          if (showMenu) break;
          if (showAlarm) {
            editPos--;
            if (editPos < 0) editPos = 2;
            Serial.println("editPos: " + (String)editPos);
          }
          if (showMusic) {
            songIndex--;
            if (songIndex < 0) songIndex = SONG_COUNT - 1;
            lcdChangeMusic();
          }
          break;
        case REMOTE_RIGHT:
          Serial.println("RIGHT");
          if (showMenu) break;
          if (showAlarm) {
            editPos = (editPos + 1) % 3;
            Serial.println("editPos: " + (String)editPos);
          }
          if (showMusic) {
            songIndex++;
            if (songIndex >= SONG_COUNT) songIndex = 0;
            lcdChangeMusic();
          }
          break;
        case REMOTE_TEST:
          Serial.println("TEST");
          Serial.print(showUiInConsole ? "Disabled" : "Enabled");
          Serial.println(" console time");
          showUiInConsole = !showUiInConsole;
          break;
        case REMOTE_C:
          Serial.println("C");
          // if (showMenu) break;
          // clockTime.setTime(__DATE__, __TIME__);
          break;
        case REMOTE_BACK:
          Serial.println("BACK");
          if (showClock || showMenu) break;

          if (showAlarm) alarmEditTime.copyTime(currentAlarmTime);
          if (showUtc) editUtc = UTC_OFFSET;
          if (showMusic) songIndex = buzzer.currentSong;
          lcdShowMenu();
          break;
        case REMOTE_MENU:
          Serial.println("MENU");
          if (!showClock || !isConnected) break;
          lcdShowMenu();
          if (showUiInConsole) {
            Serial.println(F("1. Clock"));
            Serial.println(F("2. Alarm"));
          }
          break;
        case REMOTE_0:
          Serial.println("0");
          break;
        case REMOTE_1:
          Serial.println("1");
          if (!showMenu) break;
          showMenu = false;
          showClock = true;
          lcdDisplayClock(clockTime);
          break;
        case REMOTE_2:
          Serial.println("2");
          if (!showMenu) break;
          showMenu = false;
          showAlarm = true;
          editPos = 0;
          break;
        case REMOTE_3:
          Serial.println("3");
          if (!showMenu) break;
          showMenu = false;
          showMusic = true;
          lcdChangeMusic();
          break;
        case REMOTE_4:
          Serial.println("4");
          if (!showMenu) break;
          showMenu = false;
          showUtc = true;
          lcdEditTimeZone();
          break;
        case REMOTE_OFF:
          Serial.println("OFF");
          if (canAlarm) {
            canAlarm = false;
            Serial.println("Turned off alarm");
          }
          break;
        default:
          Serial.print("0x");
          Serial.println(v, HEX);
          break;
      }
      IrReceiver.resume();
    }
  }

  if (delayNoDelay(50)) {
    if (clockTime.compareTime(currentAlarmTime)) {
      canAlarm = true;
      if (showUiInConsole) Serial.println("Alarm!! " + currentAlarmTime.getTimeString());
    }
    if (canAlarm) {
      bool canPlay = buzzer.playMusic(BUZZER_PIN, LED_PIN, true);
      canAlarm = canPlay;
    }
  }

  if (showAlarm) lcdEditAlarm(alarmEditTime);

  if (delayNoDelay(1000) && showClock && clockEnabled) {
    clockTime.getTime();
    lcdDisplayClock(clockTime);
    if (showUiInConsole) {
      Serial.println("Time: " + clockTime.getTimeString() + " " + clockTime.getDateString());
    }
  }

  delay(50);
}

void updateTimeZone() {
  configTime(UTC_OFFSET * 3600, UTC_OFFSET_DST * 3600, NTP_SERVER);
}

void printToLcd(const String lineOne, const String lineTwo) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(lineOne);
  lcd.setCursor(0, 1);
  lcd.print(lineTwo);
}

void lcdBlink(const uint8_t col, const uint8_t row, const uint8_t length) {
  String b = "";
  for (int i = 0; i < length; i++) b += " ";
  lcd.setCursor(col, row);
  lcd.print(b);
}

void lcdDisplayClock(Clock datetime) {
  isConnected
    ? printToLcd(
      " " + datetime.getTimeString() + "  " + (clockEnabled ? " ON" : "OFF") + " C",
      datetime.getDateString() + " " + datetime.weekdayString + " " + "M")
    : printToLcd("No network", "Please reset");
}

void lcdShowMenu() {
  showMenu = true;
  showClock = false;
  showAlarm = false;
  showUtc = false;
  showMusic = false;

  String l1 = menuItems[menuIndex], l2 = menuItems[menuIndex + 1];
  while (l1.length() < 14) l1 += " ";
  while (l2.length() < 15) l2 += " ";

  printToLcd(l1 + (menuPage < 10 ? " " + (String)menuPage : (String)menuPage), l2 + "M");

  // String l = menuItems[menuIndex + 1];
  // while (l.length() < 15) l += " ";
  // printToLcd(menuItems[menuIndex], l + "M");
}

void lcdEditAlarm(AlarmTime alarm) {
  if (!delayNoDelay(200)) {
    printToLcd(" Edit alarm:   A", " " + alarm.getTimeString() + "      M");
  }
  if (!delayNoDelay(101) && editPos < 3) {
    lcdBlink(editPos * 3 + 1, 1, 2);
  }
}

void lcdEditTimeZone() {
  String l = (String)editUtc;
  if (editUtc > 9) {
    l = " " + (String)editUtc;
  } else if (editUtc >= 0) {
    l = " " + (String)editUtc + " ";
  } else if (editUtc > -10) {
    l = (String)editUtc + " ";
  }
  printToLcd(" Change UTC:   U", "    " + l + "        M");
}

void lcdChangeMusic() {
  String name = buzzer.names[songIndex];
  while (name.length() < 16) {
    name = " " + name + " ";
  }
  String num = (String)(songIndex + 1);
  if (songIndex + 1 > 9) num = "      " + num;
  else num = "       " + num;
  num += "      ";

  printToLcd("<" + num + ">", name);
}
