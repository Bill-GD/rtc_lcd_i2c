#ifndef Buzzer_h
#define Buzzer_h

#include "Arduino.h"
#include "Notes.cpp"

class Buzzer {
private:
  // Notes of the melody followed by the duration.
  // a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
  // !!negative numbers are used to represent dotted notes,
  // so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
  int melody[500] PROGMEM = {
    // Pacman
    // Score available at https://musescore.com/user/85429/scores/107109
    Notes::NOTE_B4, 16, Notes::NOTE_B5, 16, Notes::NOTE_FS5, 16, Notes::NOTE_DS5, 16,  //1
    Notes::NOTE_B5, 32, Notes::NOTE_FS5, -16, Notes::NOTE_DS5, 8, Notes::NOTE_C5, 16,
    Notes::NOTE_C6, 16, Notes::NOTE_G6, 16, Notes::NOTE_E6, 16, Notes::NOTE_C6, 32, Notes::NOTE_G6, -16, Notes::NOTE_E6, 8,

    Notes::NOTE_B4, 16, Notes::NOTE_B5, 16, Notes::NOTE_FS5, 16, Notes::NOTE_DS5, 16, Notes::NOTE_B5, 32,  //2
    Notes::NOTE_FS5, -16, Notes::NOTE_DS5, 8, Notes::NOTE_DS5, 32, Notes::NOTE_E5, 32, Notes::NOTE_F5, 32,
    Notes::NOTE_F5, 32, Notes::NOTE_FS5, 32, Notes::NOTE_G5, 32, Notes::NOTE_G5, 32, Notes::NOTE_GS5, 32, Notes::NOTE_A5, 16, Notes::NOTE_B5, 8
  };
  int tempo = 100, wholenote = (60000 * 4) / tempo;
  int notes = sizeof(melody) / sizeof(melody[0]) / 2;

public:
  /** The higher the tempo, the faster the song is */
  void setTempo(int tempo) {
    this->tempo = tempo;
    this->wholenote = (60000 * 4) / tempo;
  }

  void playMusic(int buzzerPin, int ledPin = 3, bool playLed = false) {
    for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
      int noteDuration;
      int divider = melody[thisNote + 1];  // duration of each note

      if (playLed) digitalWrite(ledPin, HIGH);

      if (divider > 0) {
        // regular note, just proceed
        noteDuration = (wholenote) / divider;
      } else if (divider < 0) {
        // dotted notes are represented with negative durations!!
        noteDuration = (wholenote) / abs(divider);
        noteDuration *= 1.5;  // increases the duration in half for dotted notes
      }

      tone(buzzerPin, melody[thisNote], noteDuration * 0.9);  // play 90% of duration

      delay(noteDuration / 2);
      if (playLed) digitalWrite(ledPin, LOW);
      delay(noteDuration / 2);

      // stop the waveform generation before the next note.
      noTone(buzzerPin);
    }
  }

  // Buzzer() :
  //   melody
  // {}
};

#endif