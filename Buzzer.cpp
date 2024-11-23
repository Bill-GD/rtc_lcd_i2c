#ifndef BUZZER
#define BUZZER

#include "Arduino.h"
#include "Notes.cpp"

#define SONG_COUNT 3

class Buzzer {
private:
  // static int SONG_COUNT = 3;
  // Notes of the melody followed by the duration.
  // a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
  // !!negative numbers are used to represent dotted notes,
  // so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
  int tempos[SONG_COUNT] = { 144, 105, 140 };

  // the length must be the exact number of notes * 2
  int melody[SONG_COUNT][1500] PROGMEM = {
    // nokia ringtone
    {
      Notes::NOTE_E5, 8, Notes::NOTE_D5, 8, Notes::NOTE_FS4, 4, Notes::NOTE_GS4, 4,
      Notes::NOTE_CS5, 8, Notes::NOTE_B4, 8, Notes::NOTE_D4, 4, Notes::NOTE_E4, 4,
      Notes::NOTE_B4, 8, Notes::NOTE_A4, 8, Notes::NOTE_CS4, 4, Notes::NOTE_E4, 4,
      Notes::NOTE_A4, 2,
    },
    // Pacman
    {
      Notes::NOTE_B4, 16, Notes::NOTE_B5, 16, Notes::NOTE_FS5, 16, Notes::NOTE_DS5, 16, //1
      Notes::NOTE_B5, 32, Notes::NOTE_FS5, -16, Notes::NOTE_DS5, 8, Notes::NOTE_C5, 16,
      Notes::NOTE_C6, 16, Notes::NOTE_G6, 16, Notes::NOTE_E6, 16, Notes::NOTE_C6, 32, Notes::NOTE_G6, -16, Notes::NOTE_E6, 8,

      Notes::NOTE_B4, 16, Notes::NOTE_B5, 16, Notes::NOTE_FS5, 16, Notes::NOTE_DS5, 16, Notes::NOTE_B5, 32,  //2
      Notes::NOTE_FS5, -16, Notes::NOTE_DS5, 8, Notes::NOTE_DS5, 32, Notes::NOTE_E5, 32, Notes::NOTE_F5, 32,
      Notes::NOTE_F5, 32, Notes::NOTE_FS5, 32, Notes::NOTE_G5, 32, Notes::NOTE_G5, 32, Notes::NOTE_GS5, 32, Notes::NOTE_A5, 16, Notes::NOTE_B5, 8
    },
    // happy birthday
    {
      Notes::NOTE_C4,4, Notes::NOTE_C4,8,
      Notes::NOTE_D4,-4, Notes::NOTE_C4,-4, Notes::NOTE_F4,-4,
      Notes::NOTE_E4,-2, Notes::NOTE_C4,4, Notes::NOTE_C4,8,
      Notes::NOTE_D4,-4, Notes::NOTE_C4,-4, Notes::NOTE_G4,-4,
      Notes::NOTE_F4,-2, Notes::NOTE_C4,4, Notes::NOTE_C4,8,

      Notes::NOTE_C5,-4, Notes::NOTE_A4,-4, Notes::NOTE_F4,-4,
      Notes::NOTE_E4,-4, Notes::NOTE_D4,-4, Notes::NOTE_AS4,4, Notes::NOTE_AS4,8,
      Notes::NOTE_A4,-4, Notes::NOTE_F4,-4, Notes::NOTE_G4,-4,
      Notes::NOTE_F4,-2,
    }
  };
  
  // The higher the modifier, the faster the song
  int speedModifier = 1;
  int wholenote = (60000 * 4 / speedModifier) / tempos[currentSong];
  int notes = sizeof(melody[currentSong]) / sizeof(melody[currentSong][0]) / 2;
  int currentNote = 0, noteDuration = 0;
  // int noteDuration = 0;

public:
  /** The higher the tempo, the faster the song is */
  // void setTempo(int tempo) {
  //   tempo = tempo;
  //   wholenote = (60000 * 4 / speedModifier) / tempo;
  // }
  int currentSong = 0;
  String names[SONG_COUNT] = { "Nokia", "Pacman", "Happy Birthday" };

  void setSong(int index) {
    if (index >= SONG_COUNT) return;

    currentSong = index;
    wholenote = (60000 * 4 / speedModifier) / tempos[currentSong];
    notes = sizeof(melody[currentSong]) / sizeof(melody[currentSong][0]) / 2;
    currentNote = 0;
    noteDuration = 0;
  }

  // bool playMusic(int buzzerPin, int currentNote, int ledPin = 3, bool playLed = false) {
  bool playMusic(int buzzerPin, int ledPin = 3, bool playLed = false) {
    if (currentNote >= notes * 2) {
      currentNote = 0;
      noteDuration = 0;
      return false;
    }

    int divider = melody[currentSong][currentNote + 1];  // duration of each note
    // Serial.print(F("Playing note: "));
    // Serial.print(melody[currentSong][currentNote]);
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

    tone(buzzerPin, melody[currentSong][currentNote], noteDuration * 0.9);  // play 90% of duration

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