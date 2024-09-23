#ifndef Buzzer
#define Buzzer

// int melody[] = {

//   Notes.NOTE_E5,8, Notes.NOTE_E5,8, REST,8, Notes.NOTE_E5,8, REST,8, Notes.NOTE_C5,8, Notes.NOTE_E5,8, //1
//   Notes.NOTE_G5,4, REST,4, Notes.NOTE_G4,8, REST,4,
//   Notes.NOTE_C5,-4, Notes.NOTE_G4,8, REST,4, Notes.NOTE_E4,-4, // 3
//   Notes.NOTE_A4,4, Notes.NOTE_B4,4, Notes.NOTE_AS4,8, Notes.NOTE_A4,4,
//   Notes.NOTE_G4,-8, Notes.NOTE_E5,-8, Notes.NOTE_G5,-8, Notes.NOTE_A5,4, Notes.NOTE_F5,8, Notes.NOTE_G5,8,
//   REST,8, Notes.NOTE_E5,4,Notes.NOTE_C5,8, Notes.NOTE_D5,8, Notes.NOTE_B4,-4,
//   Notes.NOTE_C5,-4, Notes.NOTE_G4,8, REST,4, Notes.NOTE_E4,-4, // repeats from 3
//   Notes.NOTE_A4,4, Notes.NOTE_B4,4, Notes.NOTE_AS4,8, Notes.NOTE_A4,4,
//   Notes.NOTE_G4,-8, Notes.NOTE_E5,-8, Notes.NOTE_G5,-8, Notes.NOTE_A5,4, Notes.NOTE_F5,8, Notes.NOTE_G5,8,
//   REST,8, Notes.NOTE_E5,4,Notes.NOTE_C5,8, Notes.NOTE_D5,8, Notes.NOTE_B4,-4,

//   REST,4, Notes.NOTE_G5,8, Notes.NOTE_FS5,8, Notes.NOTE_F5,8, Notes.NOTE_DS5,4, Notes.NOTE_E5,8,//7
//   REST,8, Notes.NOTE_GS4,8, Notes.NOTE_A4,8, Notes.NOTE_C4,8, REST,8, Notes.NOTE_A4,8, Notes.NOTE_C5,8, Notes.NOTE_D5,8,
//   REST,4, Notes.NOTE_DS5,4, REST,8, Notes.NOTE_D5,-4,
//   Notes.NOTE_C5,2, REST,2,

//   REST,4, Notes.NOTE_G5,8, Notes.NOTE_FS5,8, Notes.NOTE_F5,8, Notes.NOTE_DS5,4, Notes.NOTE_E5,8,//repeats from 7
//   REST,8, Notes.NOTE_GS4,8, Notes.NOTE_A4,8, Notes.NOTE_C4,8, REST,8, Notes.NOTE_A4,8, Notes.NOTE_C5,8, Notes.NOTE_D5,8,
//   REST,4, Notes.NOTE_DS5,4, REST,8, Notes.NOTE_D5,-4,
//   Notes.NOTE_C5,2, REST,2,

//   Notes.NOTE_C5,8, Notes.NOTE_C5,4, Notes.NOTE_C5,8, REST,8, Notes.NOTE_C5,8, Notes.NOTE_D5,4,//11
//   Notes.NOTE_E5,8, Notes.NOTE_C5,4, Notes.NOTE_A4,8, Notes.NOTE_G4,2,

//   Notes.NOTE_C5,8, Notes.NOTE_C5,4, Notes.NOTE_C5,8, REST,8, Notes.NOTE_C5,8, Notes.NOTE_D5,8, Notes.NOTE_E5,8,//13
//   REST,1,
//   Notes.NOTE_C5,8, Notes.NOTE_C5,4, Notes.NOTE_C5,8, REST,8, Notes.NOTE_C5,8, Notes.NOTE_D5,4,
//   Notes.NOTE_E5,8, Notes.NOTE_C5,4, Notes.NOTE_A4,8, Notes.NOTE_G4,2,
//   Notes.NOTE_E5,8, Notes.NOTE_E5,8, REST,8, Notes.NOTE_E5,8, REST,8, Notes.NOTE_C5,8, Notes.NOTE_E5,4,
//   Notes.NOTE_G5,4, REST,4, Notes.NOTE_G4,4, REST,4,
//   Notes.NOTE_C5,-4, Notes.NOTE_G4,8, REST,4, Notes.NOTE_E4,-4, // 19

//   Notes.NOTE_A4,4, Notes.NOTE_B4,4, Notes.NOTE_AS4,8, Notes.NOTE_A4,4,
//   Notes.NOTE_G4,-8, Notes.NOTE_E5,-8, Notes.NOTE_G5,-8, Notes.NOTE_A5,4, Notes.NOTE_F5,8, Notes.NOTE_G5,8,
//   REST,8, Notes.NOTE_E5,4, Notes.NOTE_C5,8, Notes.NOTE_D5,8, Notes.NOTE_B4,-4,

//   Notes.NOTE_C5,-4, Notes.NOTE_G4,8, REST,4, Notes.NOTE_E4,-4, // repeats from 19
//   Notes.NOTE_A4,4, Notes.NOTE_B4,4, Notes.NOTE_AS4,8, Notes.NOTE_A4,4,
//   Notes.NOTE_G4,-8, Notes.NOTE_E5,-8, Notes.NOTE_G5,-8, Notes.NOTE_A5,4, Notes.NOTE_F5,8, Notes.NOTE_G5,8,
//   REST,8, Notes.NOTE_E5,4, Notes.NOTE_C5,8, Notes.NOTE_D5,8, Notes.NOTE_B4,-4,

//   Notes.NOTE_E5,8, Notes.NOTE_C5,4, Notes.NOTE_G4,8, REST,4, Notes.NOTE_GS4,4,//23
//   Notes.NOTE_A4,8, Notes.NOTE_F5,4, Notes.NOTE_F5,8, Notes.NOTE_A4,2,
//   Notes.NOTE_D5,-8, Notes.NOTE_A5,-8, Notes.NOTE_A5,-8, Notes.NOTE_A5,-8, Notes.NOTE_G5,-8, Notes.NOTE_F5,-8,

//   Notes.NOTE_E5,8, Notes.NOTE_C5,4, Notes.NOTE_A4,8, Notes.NOTE_G4,2, //26
//   Notes.NOTE_E5,8, Notes.NOTE_C5,4, Notes.NOTE_G4,8, REST,4, Notes.NOTE_GS4,4,
//   Notes.NOTE_A4,8, Notes.NOTE_F5,4, Notes.NOTE_F5,8, Notes.NOTE_A4,2,
//   Notes.NOTE_B4,8, Notes.NOTE_F5,4, Notes.NOTE_F5,8, Notes.NOTE_F5,-8, Notes.NOTE_E5,-8, Notes.NOTE_D5,-8,
//   Notes.NOTE_C5,8, Notes.NOTE_E4,4, Notes.NOTE_E4,8, Notes.NOTE_C4,2,

//   Notes.NOTE_E5,8, Notes.NOTE_C5,4, Notes.NOTE_G4,8, REST,4, Notes.NOTE_GS4,4,//repeats from 23
//   Notes.NOTE_A4,8, Notes.NOTE_F5,4, Notes.NOTE_F5,8, Notes.NOTE_A4,2,
//   Notes.NOTE_D5,-8, Notes.NOTE_A5,-8, Notes.NOTE_A5,-8, Notes.NOTE_A5,-8, Notes.NOTE_G5,-8, Notes.NOTE_F5,-8,

//   Notes.NOTE_E5,8, Notes.NOTE_C5,4, Notes.NOTE_A4,8, Notes.NOTE_G4,2, //26
//   Notes.NOTE_E5,8, Notes.NOTE_C5,4, Notes.NOTE_G4,8, REST,4, Notes.NOTE_GS4,4,
//   Notes.NOTE_A4,8, Notes.NOTE_F5,4, Notes.NOTE_F5,8, Notes.NOTE_A4,2,
//   Notes.NOTE_B4,8, Notes.NOTE_F5,4, Notes.NOTE_F5,8, Notes.NOTE_F5,-8, Notes.NOTE_E5,-8, Notes.NOTE_D5,-8,
//   Notes.NOTE_C5,8, Notes.NOTE_E4,4, Notes.NOTE_E4,8, Notes.NOTE_C4,2,
//   Notes.NOTE_C5,8, Notes.NOTE_C5,4, Notes.NOTE_C5,8, REST,8, Notes.NOTE_C5,8, Notes.NOTE_D5,8, Notes.NOTE_E5,8,
//   REST,1,

//   Notes.NOTE_C5,8, Notes.NOTE_C5,4, Notes.NOTE_C5,8, REST,8, Notes.NOTE_C5,8, Notes.NOTE_D5,4, //33
//   Notes.NOTE_E5,8, Notes.NOTE_C5,4, Notes.NOTE_A4,8, Notes.NOTE_G4,2,
//   Notes.NOTE_E5,8, Notes.NOTE_E5,8, REST,8, Notes.NOTE_E5,8, REST,8, Notes.NOTE_C5,8, Notes.NOTE_E5,4,
//   Notes.NOTE_G5,4, REST,4, Notes.NOTE_G4,4, REST,4,
//   Notes.NOTE_E5,8, Notes.NOTE_C5,4, Notes.NOTE_G4,8, REST,4, Notes.NOTE_GS4,4,
//   Notes.NOTE_A4,8, Notes.NOTE_F5,4, Notes.NOTE_F5,8, Notes.NOTE_A4,2,
//   Notes.NOTE_D5,-8, Notes.NOTE_A5,-8, Notes.NOTE_A5,-8, Notes.NOTE_A5,-8, Notes.NOTE_G5,-8, Notes.NOTE_F5,-8,

//   Notes.NOTE_E5,8, Notes.NOTE_C5,4, Notes.NOTE_A4,8, Notes.NOTE_G4,2, //40
//   Notes.NOTE_E5,8, Notes.NOTE_C5,4, Notes.NOTE_G4,8, REST,4, Notes.NOTE_GS4,4,
//   Notes.NOTE_A4,8, Notes.NOTE_F5,4, Notes.NOTE_F5,8, Notes.NOTE_A4,2,
//   Notes.NOTE_B4,8, Notes.NOTE_F5,4, Notes.NOTE_F5,8, Notes.NOTE_F5,-8, Notes.NOTE_E5,-8, Notes.NOTE_D5,-8,
//   Notes.NOTE_C5,8, Notes.NOTE_E4,4, Notes.NOTE_E4,8, Notes.NOTE_C4,2,

//   //game over sound
//   Notes.NOTE_C5,-4, Notes.NOTE_G4,-4, Notes.NOTE_E4,4, //45
//   Notes.NOTE_A4,-8, Notes.NOTE_B4,-8, Notes.NOTE_A4,-8, Notes.NOTE_GS4,-8, Notes.NOTE_AS4,-8, Notes.NOTE_GS4,-8,
//   Notes.NOTE_G4,8, Notes.NOTE_D4,8, Notes.NOTE_E4,-2,

// };

class Notes {
  static const int NOTE_B0 = 31;
  static const int NOTE_C1 = 33;
  static const int NOTE_CS1 = 35;
  static const int NOTE_D1 = 37;
  static const int NOTE_DS1 = 39;
  static const int NOTE_E1 = 41;
  static const int NOTE_F1 = 44;
  static const int NOTE_FS1 = 46;
  static const int NOTE_G1 = 49;
  static const int NOTE_GS1 = 52;
  static const int NOTE_A1 = 55;
  static const int NOTE_AS1 = 58;
  static const int NOTE_B1 = 62;
  static const int NOTE_C2 = 65;
  static const int NOTE_CS2 = 69;
  static const int NOTE_D2 = 73;
  static const int NOTE_DS2 = 78;
  static const int NOTE_E2 = 82;
  static const int NOTE_F2 = 87;
  static const int NOTE_FS2 = 93;
  static const int NOTE_G2 = 98;
  static const int NOTE_GS2 = 104;
  static const int NOTE_A2 = 110;
  static const int NOTE_AS2 = 117;
  static const int NOTE_B2 = 123;
  static const int NOTE_C3 = 131;
  static const int NOTE_CS3 = 139;
  static const int NOTE_D3 = 147;
  static const int NOTE_DS3 = 156;
  static const int NOTE_E3 = 165;
  static const int NOTE_F3 = 175;
  static const int NOTE_FS3 = 185;
  static const int NOTE_G3 = 196;
  static const int NOTE_GS3 = 208;
  static const int NOTE_A3 = 220;
  static const int NOTE_AS3 = 233;
  static const int NOTE_B3 = 247;
  static const int NOTE_C4 = 262;
  static const int NOTE_CS4 = 277;
  static const int NOTE_D4 = 294;
  static const int NOTE_DS4 = 311;
  static const int NOTE_E4 = 330;
  static const int NOTE_F4 = 349;
  static const int NOTE_FS4 = 370;
  static const int NOTE_G4 = 392;
  static const int NOTE_GS4 = 415;
  static const int NOTE_A4 = 440;
  static const int NOTE_AS4 = 466;
  static const int NOTE_B4 = 494;
  static const int NOTE_C5 = 523;
  static const int NOTE_CS5 = 554;
  static const int NOTE_D5 = 587;
  static const int NOTE_DS5 = 622;
  static const int NOTE_E5 = 659;
  static const int NOTE_F5 = 698;
  static const int NOTE_FS5 = 740;
  static const int NOTE_G5 = 784;
  static const int NOTE_GS5 = 831;
  static const int NOTE_A5 = 880;
  static const int NOTE_AS5 = 932;
  static const int NOTE_B5 = 988;
  static const int NOTE_C6 = 1047;
  static const int NOTE_CS6 = 1109;
  static const int NOTE_D6 = 1175;
  static const int NOTE_DS6 = 1245;
  static const int NOTE_E6 = 1319;
  static const int NOTE_F6 = 1397;
  static const int NOTE_FS6 = 1480;
  static const int NOTE_G6 = 1568;
  static const int NOTE_GS6 = 1661;
  static const int NOTE_A6 = 1760;
  static const int NOTE_AS6 = 1865;
  static const int NOTE_B6 = 1976;
  static const int NOTE_C7 = 2093;
  static const int NOTE_CS7 = 2217;
  static const int NOTE_D7 = 2349;
  static const int NOTE_DS7 = 2489;
  static const int NOTE_E7 = 2637;
  static const int NOTE_F7 = 2794;
  static const int NOTE_FS7 = 2960;
  static const int NOTE_G7 = 3136;
  static const int NOTE_GS7 = 3322;
  static const int NOTE_A7 = 3520;
  static const int NOTE_AS7 = 3729;
  static const int NOTE_B7 = 3951;
  static const int NOTE_C8 = 4186;
  static const int NOTE_CS8 = 4435;
  static const int NOTE_D8 = 4699;
  static const int NOTE_DS8 = 4978;
  static const int REST = 0;
};

#endif