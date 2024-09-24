#ifndef Buzzer_h
#define Buzzer_h

#include "Arduino.h"
#include "Notes.cpp"

class Buzzer {
private:
  // the length must be the exact number of notes * 2
  uint8_t melody[680] PROGMEM = {
    // rick roll here
    Notes::NOTE_D5,-4, Notes::NOTE_E5,-4, Notes::NOTE_A4,4, //1
    Notes::NOTE_E5,-4, Notes::NOTE_FS5,-4, Notes::NOTE_A5,16, Notes::NOTE_G5,16, Notes::NOTE_FS5,8,
    Notes::NOTE_D5,-4, Notes::NOTE_E5,-4, Notes::NOTE_A4,2,
    Notes::NOTE_A4,16, Notes::NOTE_A4,16, Notes::NOTE_B4,16, Notes::NOTE_D5,8, Notes::NOTE_D5,16,
    Notes::NOTE_D5,-4, Notes::NOTE_E5,-4, Notes::NOTE_A4,4, //repeat from 1
    Notes::NOTE_E5,-4, Notes::NOTE_FS5,-4, Notes::NOTE_A5,16, Notes::NOTE_G5,16, Notes::NOTE_FS5,8,
    Notes::NOTE_D5,-4, Notes::NOTE_E5,-4, Notes::NOTE_A4,2,
    Notes::NOTE_A4,16, Notes::NOTE_A4,16, Notes::NOTE_B4,16, Notes::NOTE_D5,8, Notes::NOTE_D5,16,
    Notes::REST,4, Notes::NOTE_B4,8, Notes::NOTE_CS5,8, Notes::NOTE_D5,8, Notes::NOTE_D5,8, Notes::NOTE_E5,8, Notes::NOTE_CS5,-8,
    Notes::NOTE_B4,16, Notes::NOTE_A4,2, Notes::REST,4,

    Notes::REST,8, Notes::NOTE_B4,8, Notes::NOTE_B4,8, Notes::NOTE_CS5,8, Notes::NOTE_D5,8, Notes::NOTE_B4,4, Notes::NOTE_A4,8, //7
    Notes::NOTE_A5,8, Notes::REST,8, Notes::NOTE_A5,8, Notes::NOTE_E5,-4, Notes::REST,4,
    Notes::NOTE_B4,8, Notes::NOTE_B4,8, Notes::NOTE_CS5,8, Notes::NOTE_D5,8, Notes::NOTE_B4,8, Notes::NOTE_D5,8, Notes::NOTE_E5,8, Notes::REST,8,
    Notes::REST,8, Notes::NOTE_CS5,8, Notes::NOTE_B4,8, Notes::NOTE_A4,-4, Notes::REST,4,
    Notes::REST,8, Notes::NOTE_B4,8, Notes::NOTE_B4,8, Notes::NOTE_CS5,8, Notes::NOTE_D5,8, Notes::NOTE_B4,8, Notes::NOTE_A4,4,
    Notes::NOTE_E5,8, Notes::NOTE_E5,8, Notes::NOTE_E5,8, Notes::NOTE_FS5,8, Notes::NOTE_E5,4, Notes::REST,4,

    Notes::NOTE_D5,2, Notes::NOTE_E5,8, Notes::NOTE_FS5,8, Notes::NOTE_D5,8, //13
    Notes::NOTE_E5,8, Notes::NOTE_E5,8, Notes::NOTE_E5,8, Notes::NOTE_FS5,8, Notes::NOTE_E5,4, Notes::NOTE_A4,4,
    Notes::REST,2, Notes::NOTE_B4,8, Notes::NOTE_CS5,8, Notes::NOTE_D5,8, Notes::NOTE_B4,8,
    Notes::REST,8, Notes::NOTE_E5,8, Notes::NOTE_FS5,8, Notes::NOTE_E5,-4, Notes::NOTE_A4,16, Notes::NOTE_B4,16, Notes::NOTE_D5,16, Notes::NOTE_B4,16,
    Notes::NOTE_FS5,-8, Notes::NOTE_FS5,-8, Notes::NOTE_E5,-4, Notes::NOTE_A4,16, Notes::NOTE_B4,16, Notes::NOTE_D5,16, Notes::NOTE_B4,16,

    Notes::NOTE_E5,-8, Notes::NOTE_E5,-8, Notes::NOTE_D5,-8, Notes::NOTE_CS5,16, Notes::NOTE_B4,-8, Notes::NOTE_A4,16, Notes::NOTE_B4,16, Notes::NOTE_D5,16, Notes::NOTE_B4,16, //18
    Notes::NOTE_D5,4, Notes::NOTE_E5,8, Notes::NOTE_CS5,-8, Notes::NOTE_B4,16, Notes::NOTE_A4,8, Notes::NOTE_A4,8, Notes::NOTE_A4,8,
    Notes::NOTE_E5,4, Notes::NOTE_D5,2, Notes::NOTE_A4,16, Notes::NOTE_B4,16, Notes::NOTE_D5,16, Notes::NOTE_B4,16,
    Notes::NOTE_FS5,-8, Notes::NOTE_FS5,-8, Notes::NOTE_E5,-4, Notes::NOTE_A4,16, Notes::NOTE_B4,16, Notes::NOTE_D5,16, Notes::NOTE_B4,16,
    Notes::NOTE_A5,4, Notes::NOTE_CS5,8, Notes::NOTE_D5,-8, Notes::NOTE_CS5,16, Notes::NOTE_B4,8, Notes::NOTE_A4,16, Notes::NOTE_B4,16, Notes::NOTE_D5,16, Notes::NOTE_B4,16,

    Notes::NOTE_D5,4, Notes::NOTE_E5,8, Notes::NOTE_CS5,-8, Notes::NOTE_B4,16, Notes::NOTE_A4,4, Notes::NOTE_A4,8,  //23
    Notes::NOTE_E5,4, Notes::NOTE_D5,2, Notes::REST,4,
    Notes::REST,8, Notes::NOTE_B4,8, Notes::NOTE_D5,8, Notes::NOTE_B4,8, Notes::NOTE_D5,8, Notes::NOTE_E5,4, Notes::REST,8,
    Notes::REST,8, Notes::NOTE_CS5,8, Notes::NOTE_B4,8, Notes::NOTE_A4,-4, Notes::REST,4,
    Notes::REST,8, Notes::NOTE_B4,8, Notes::NOTE_B4,8, Notes::NOTE_CS5,8, Notes::NOTE_D5,8, Notes::NOTE_B4,8, Notes::NOTE_A4,4,
    Notes::REST,8, Notes::NOTE_A5,8, Notes::NOTE_A5,8, Notes::NOTE_E5,8, Notes::NOTE_FS5,8, Notes::NOTE_E5,8, Notes::NOTE_D5,8,

    Notes::REST,8, Notes::NOTE_A4,8, Notes::NOTE_B4,8, Notes::NOTE_CS5,8, Notes::NOTE_D5,8, Notes::NOTE_B4,8, //29
    Notes::REST,8, Notes::NOTE_CS5,8, Notes::NOTE_B4,8, Notes::NOTE_A4,-4, Notes::REST,4,
    Notes::NOTE_B4,8, Notes::NOTE_B4,8, Notes::NOTE_CS5,8, Notes::NOTE_D5,8, Notes::NOTE_B4,8, Notes::NOTE_A4,4, Notes::REST,8,
    Notes::REST,8, Notes::NOTE_E5,8, Notes::NOTE_E5,8, Notes::NOTE_FS5,4, Notes::NOTE_E5,-4,
    Notes::NOTE_D5,2, Notes::NOTE_D5,8, Notes::NOTE_E5,8, Notes::NOTE_FS5,8, Notes::NOTE_E5,4,
    Notes::NOTE_E5,8, Notes::NOTE_E5,8, Notes::NOTE_FS5,8, Notes::NOTE_E5,8, Notes::NOTE_A4,8, Notes::NOTE_A4,4,

    Notes::REST,-4, Notes::NOTE_A4,8, Notes::NOTE_B4,8, Notes::NOTE_CS5,8, Notes::NOTE_D5,8, Notes::NOTE_B4,8, //35
    Notes::REST,8, Notes::NOTE_E5,8, Notes::NOTE_FS5,8, Notes::NOTE_E5,-4, Notes::NOTE_A4,16, Notes::NOTE_B4,16, Notes::NOTE_D5,16, Notes::NOTE_B4,16,
    Notes::NOTE_FS5,-8, Notes::NOTE_FS5,-8, Notes::NOTE_E5,-4, Notes::NOTE_A4,16, Notes::NOTE_B4,16, Notes::NOTE_D5,16, Notes::NOTE_B4,16,
    Notes::NOTE_E5,-8, Notes::NOTE_E5,-8, Notes::NOTE_D5,-8, Notes::NOTE_CS5,16, Notes::NOTE_B4,8, Notes::NOTE_A4,16, Notes::NOTE_B4,16, Notes::NOTE_D5,16, Notes::NOTE_B4,16,
    Notes::NOTE_D5,4, Notes::NOTE_E5,8, Notes::NOTE_CS5,-8, Notes::NOTE_B4,16, Notes::NOTE_A4,4, Notes::NOTE_A4,8,

    Notes::NOTE_E5,4, Notes::NOTE_D5,2, Notes::NOTE_A4,16, Notes::NOTE_B4,16, Notes::NOTE_D5,16, Notes::NOTE_B4,16, //40
    Notes::NOTE_FS5,-8, Notes::NOTE_FS5,-8, Notes::NOTE_E5,-4, Notes::NOTE_A4,16, Notes::NOTE_B4,16, Notes::NOTE_D5,16, Notes::NOTE_B4,16,
    Notes::NOTE_A5,4, Notes::NOTE_CS5,8, Notes::NOTE_D5,-8, Notes::NOTE_CS5,16, Notes::NOTE_B4,8, Notes::NOTE_A4,16, Notes::NOTE_B4,16, Notes::NOTE_D5,16, Notes::NOTE_B4,16,
    Notes::NOTE_D5,4, Notes::NOTE_E5,8, Notes::NOTE_CS5,-8, Notes::NOTE_B4,16, Notes::NOTE_A4,4, Notes::NOTE_A4,8,
    Notes::NOTE_E5,4, Notes::NOTE_D5,2, Notes::NOTE_A4,16, Notes::NOTE_B4,16, Notes::NOTE_D5,16, Notes::NOTE_B4,16,

    Notes::NOTE_FS5,-8, Notes::NOTE_FS5,-8, Notes::NOTE_E5,-4, Notes::NOTE_A4,16, Notes::NOTE_B4,16, Notes::NOTE_D5,16, Notes::NOTE_B4,16, //45
    Notes::NOTE_A5,4, Notes::NOTE_CS5,8, Notes::NOTE_D5,-8, Notes::NOTE_CS5,16, Notes::NOTE_B4,8, Notes::NOTE_A4,16, Notes::NOTE_B4,16, Notes::NOTE_D5,16, Notes::NOTE_B4,16,
    Notes::NOTE_D5,4, Notes::NOTE_E5,8, Notes::NOTE_CS5,-8, Notes::NOTE_B4,16, Notes::NOTE_A4,4, Notes::NOTE_A4,8,
    Notes::NOTE_E5,4, Notes::NOTE_D5,2, Notes::NOTE_A4,16, Notes::NOTE_B4,16, Notes::NOTE_D5,16, Notes::NOTE_B4,16,
    Notes::NOTE_FS5,-8, Notes::NOTE_FS5,-8, Notes::NOTE_E5,-4, Notes::NOTE_A4,16, Notes::NOTE_B4,16, Notes::NOTE_D5,16, Notes::NOTE_B4,16, //45

    Notes::NOTE_A5,4, Notes::NOTE_CS5,8, Notes::NOTE_D5,-8, Notes::NOTE_CS5,16, Notes::NOTE_B4,8, Notes::NOTE_A4,16, Notes::NOTE_B4,16, Notes::NOTE_D5,16, Notes::NOTE_B4,16,
    Notes::NOTE_D5,4, Notes::NOTE_E5,8, Notes::NOTE_CS5,-8, Notes::NOTE_B4,16, Notes::NOTE_A4,4, Notes::NOTE_A4,8,

    Notes::NOTE_E5,4, Notes::NOTE_D5,2, Notes::REST,4
  };
  // Notes of the melody followed by the duration.
  // a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
  // !!negative numbers are used to represent dotted notes,
  // so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
  uint8_t tempo = 114;
  int wholenote = (60000 * 4) / tempo;
  int notes = sizeof(melody) / sizeof(melody[0]) / 2;
  uint8_t currentNote = 0, noteDuration = 0;
  // uint8_t noteDuration = 0;

public:
  /** The higher the tempo, the faster the song is */
  void setTempo(uint8_t tempo) {
    tempo = tempo;
    wholenote = (60000 * 4) / tempo;
  }

  // bool playMusic(uint8_t buzzerPin, uint8_t currentNote, uint8_t ledPin = 3, bool playLed = false) {
  bool playMusic(uint8_t buzzerPin, uint8_t ledPin = 3, bool playLed = false) {
    if (currentNote >= notes * 2) {
      currentNote = 0;
      noteDuration = 0;
      return false;
    }
    uint8_t divider = melody[currentNote + 1];  // duration of each note
    Serial.print(F("Playing note: "));
    Serial.print(melody[currentNote]);
    Serial.print(F(" ("));
    Serial.print(noteDuration);
    Serial.println(F(")"));

    if (playLed) digitalWrite(ledPin, HIGH);

    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5;  // increases the duration in half for dotted notes
    }

    tone(buzzerPin, melody[currentNote], noteDuration * 0.9);  // play 90% of duration

    delay(noteDuration / 2);
    if (playLed) digitalWrite(ledPin, LOW);
    delay(noteDuration / 2);

    // stop the waveform generation before the next note.
    noTone(buzzerPin);
    currentNote += 2;
    return true;
  }
};

#endif