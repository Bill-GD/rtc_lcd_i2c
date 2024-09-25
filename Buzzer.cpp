#ifndef Buzzer_h
#define Buzzer_h

#include "Arduino.h"
#include "Notes.cpp"

class Buzzer {
private:
  // The higher the modifier, the faster the song
  int speedModifier = 4;
  // the length must be the exact number of notes * 2
  int melody[680] PROGMEM = {
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
  int tempo = 114;
  int wholenote = (60000 / speedModifier) / tempo;
  int notes = sizeof(melody) / sizeof(melody[0]) / 2;
  int currentNote = 0, noteDuration = 0;
  // int noteDuration = 0;

public:
  /** The higher the tempo, the faster the song is */
  void setTempo(int tempo) {
    tempo = tempo;
    wholenote = (60000 / speedModifier) / tempo;
  }

  // bool playMusic(int buzzerPin, int currentNote, int ledPin = 3, bool playLed = false) {
  bool playMusic(int buzzerPin, int ledPin = 3, bool playLed = false) {
    if (currentNote >= notes * 2) {
      currentNote = 0;
      noteDuration = 0;
      return false;
    }
    
    int divider = melody[currentNote + 1];  // duration of each note
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