#ifndef Buzzer_h
#define Buzzer_h

#include "Arduino.h"
#include "Notes.cpp"

class Buzzer {
private:
  // 410 bytes
  int melody[540] PROGMEM = {
    // The Godfather theme
    // Score available at https://musescore.com/user/35463/scores/55160
    Notes::REST, 4, Notes::REST, 8, Notes::REST, 8, Notes::REST, 8, Notes::NOTE_E4, 8, Notes::NOTE_A4, 8, Notes::NOTE_C5, 8,  //1
    Notes::NOTE_B4, 8, Notes::NOTE_A4, 8, Notes::NOTE_C5, 8, Notes::NOTE_A4, 8, Notes::NOTE_B4, 8, Notes::NOTE_A4, 8, Notes::NOTE_F4, 8, Notes::NOTE_G4, 8,
    Notes::NOTE_E4, 2, Notes::NOTE_E4, 8, Notes::NOTE_A4, 8, Notes::NOTE_C5, 8,
    Notes::NOTE_B4, 8, Notes::NOTE_A4, 8, Notes::NOTE_C5, 8, Notes::NOTE_A4, 8, Notes::NOTE_C5, 8, Notes::NOTE_A4, 8, Notes::NOTE_E4, 8, Notes::NOTE_DS4, 8,

    Notes::NOTE_D4, 2, Notes::NOTE_D4, 8, Notes::NOTE_F4, 8, Notes::NOTE_GS4, 8,  //5
    Notes::NOTE_B4, 2, Notes::NOTE_D4, 8, Notes::NOTE_F4, 8, Notes::NOTE_GS4, 8,
    Notes::NOTE_A4, 2, Notes::NOTE_C4, 8, Notes::NOTE_C4, 8, Notes::NOTE_G4, 8,
    Notes::NOTE_F4, 8, Notes::NOTE_E4, 8, Notes::NOTE_G4, 8, Notes::NOTE_F4, 8, Notes::NOTE_F4, 8, Notes::NOTE_E4, 8, Notes::NOTE_E4, 8, Notes::NOTE_GS4, 8,

    Notes::NOTE_A4, 2, Notes::REST, 8, Notes::NOTE_A4, 8, Notes::NOTE_A4, 8, Notes::NOTE_GS4, 8,  //9
    Notes::NOTE_G4, 2, Notes::NOTE_B4, 8, Notes::NOTE_A4, 8, Notes::NOTE_F4, 8,
    Notes::NOTE_E4, 2, Notes::NOTE_E4, 8, Notes::NOTE_G4, 8, Notes::NOTE_E4, 8,
    Notes::NOTE_D4, 2, Notes::NOTE_D4, 8, Notes::NOTE_D4, 8, Notes::NOTE_F4, 8, Notes::NOTE_DS4, 8,

    Notes::NOTE_E4, 2, Notes::REST, 8, Notes::NOTE_E4, 8, Notes::NOTE_A4, 8, Notes::NOTE_C5, 8,  //13

    //repeats from 2
    Notes::NOTE_B4, 8, Notes::NOTE_A4, 8, Notes::NOTE_C5, 8, Notes::NOTE_A4, 8, Notes::NOTE_B4, 8, Notes::NOTE_A4, 8, Notes::NOTE_F4, 8, Notes::NOTE_G4, 8,  //2
    Notes::NOTE_E4, 2, Notes::NOTE_E4, 8, Notes::NOTE_A4, 8, Notes::NOTE_C5, 8,
    Notes::NOTE_B4, 8, Notes::NOTE_A4, 8, Notes::NOTE_C5, 8, Notes::NOTE_A4, 8, Notes::NOTE_C5, 8, Notes::NOTE_A4, 8, Notes::NOTE_E4, 8, Notes::NOTE_DS4, 8,

    Notes::NOTE_D4, 2, Notes::NOTE_D4, 8, Notes::NOTE_F4, 8, Notes::NOTE_GS4, 8,  //5
    Notes::NOTE_B4, 2, Notes::NOTE_D4, 8, Notes::NOTE_F4, 8, Notes::NOTE_GS4, 8,
    Notes::NOTE_A4, 2, Notes::NOTE_C4, 8, Notes::NOTE_C4, 8, Notes::NOTE_G4, 8,
    Notes::NOTE_F4, 8, Notes::NOTE_E4, 8, Notes::NOTE_G4, 8, Notes::NOTE_F4, 8, Notes::NOTE_F4, 8, Notes::NOTE_E4, 8, Notes::NOTE_E4, 8, Notes::NOTE_GS4, 8,

    Notes::NOTE_A4, 2, Notes::REST, 8, Notes::NOTE_A4, 8, Notes::NOTE_A4, 8, Notes::NOTE_GS4, 8,  //9
    Notes::NOTE_G4, 2, Notes::NOTE_B4, 8, Notes::NOTE_A4, 8, Notes::NOTE_F4, 8,
    Notes::NOTE_E4, 2, Notes::NOTE_E4, 8, Notes::NOTE_G4, 8, Notes::NOTE_E4, 8,
    Notes::NOTE_D4, 2, Notes::NOTE_D4, 8, Notes::NOTE_D4, 8, Notes::NOTE_F4, 8, Notes::NOTE_DS4, 8,

    Notes::NOTE_E4, 2  //13
  };
  // Notes of the melody followed by the duration.
  // a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
  // !!negative numbers are used to represent dotted notes,
  // so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
  int tempo = 80;
  int wholenote = (60000 * 4) / tempo;
  int notes = sizeof(melody) / sizeof(melody[0]) / 2;
  int currentNote = 0, noteDuration = 0;

public:
  /** The higher the tempo, the faster the song is */
  void setTempo(int tempo) {
    tempo = tempo;
    wholenote = (60000 * 4) / tempo;
  }

  bool playMusic(int buzzerPin, int ledPin = 3, bool playLed = false) {
    if (currentNote >= notes * 2) {
      currentNote = 0;
      noteDuration = 0;
      return false;
    }
    // for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {
    int divider = melody[currentNote + 1];  // duration of each note
    Serial.print(F("Playing note: "));
    Serial.print(melody[currentNote + 1]);
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
    // }
    currentNote += 2;
    return true;
  }
};

#endif