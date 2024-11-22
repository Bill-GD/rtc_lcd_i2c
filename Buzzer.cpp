#ifndef BUZZER
#define BUZZER

#include "Arduino.h"
#include "Notes.cpp"

class Buzzer {
private:
  // The higher the modifier, the faster the song
  int speedModifier = 1;
  // Notes of the melody followed by the duration.
  // a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
  // !!negative numbers are used to represent dotted notes,
  // so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
  int tempo = 144;
  // the length must be the exact number of notes * 2
  int melody[1500] PROGMEM = {
    // nokia ringtone
    Notes::NOTE_E5, 8, Notes::NOTE_D5, 8, Notes::NOTE_FS4, 4, Notes::NOTE_GS4, 4,
    Notes::NOTE_CS5, 8, Notes::NOTE_B4, 8, Notes::NOTE_D4, 4, Notes::NOTE_E4, 4,
    Notes::NOTE_B4, 8, Notes::NOTE_A4, 8, Notes::NOTE_CS4, 4, Notes::NOTE_E4, 4,
    Notes::NOTE_A4, 2, 
  };
  int wholenote = (60000 * 4 / speedModifier) / tempo;
  int notes = sizeof(melody) / sizeof(melody[0]) / 2;
  int currentNote = 0, noteDuration = 0;
  // int noteDuration = 0;

public:
  /** The higher the tempo, the faster the song is */
  void setTempo(int tempo) {
    tempo = tempo;
    wholenote = (60000 * 4 / speedModifier) / tempo;
  }

  // bool playMusic(int buzzerPin, int currentNote, int ledPin = 3, bool playLed = false) {
  bool playMusic(int buzzerPin, int ledPin = 3, bool playLed = false) {
    if (currentNote >= notes * 2) {
      currentNote = 0;
      noteDuration = 0;
      return false;
    }

    int divider = melody[currentNote + 1];  // duration of each note
    // Serial.print(F("Playing note: "));
    // Serial.print(melody[currentNote]);
    // Serial.print(F(" ("));
    // Serial.print(noteDuration);
    // Serial.println(F(")"));

    if (playLed) digitalWrite(ledPin, HIGH);

    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    }
    else if (divider < 0) {
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