/* OSEMK Hangman Game in C.
   Copyright (C) 2022 Onur Erginer <https://onur.erginer.net/>
   This file is part of an open source license.
  */
   
// include SPI, MP3 and SD libraries, Adafruit_VS1053 lib needed
#include <SPI.h>
#include <Adafruit_VS1053.h>
#include <SD.h>

#define CLK 13       // SPI Clock, shared with SD card
#define MISO 12      // Input data, from VS1053/SD card
#define MOSI 11      // Output data, to VS1053/SD card
#define BREAKOUT_RESET  8      // VS1053 reset pin (output)
#define BREAKOUT_CS     6     // VS1053 chip select pin (output)
#define BREAKOUT_DCS    7      // VS1053 Data/command select pin (output)
// These are the pins used for the music maker shield
#define SHIELD_RESET  -1      // VS1053 reset pin (unused!)
#define SHIELD_CS     7      // VS1053 chip select pin (output)
#define SHIELD_DCS    6      // VS1053 Data/command select pin (output)
const int trigPin1 = A1;
const int echoPin1 = A0;
const int trigPin2 = A3;
const int echoPin2 = A2;
const int trigPin3 = A5;
const int echoPin3 = A4;
// These are common pins between breakout and shield
#define CARDCS 9     // Card chip select pin
#define DREQ 2       // VS1053 Data request, ideally an Interrupt pin

Adafruit_VS1053_FilePlayer musicPlayer = 
  Adafruit_VS1053_FilePlayer(BREAKOUT_RESET, BREAKOUT_CS, BREAKOUT_DCS, DREQ, CARDCS);

long duration1;
int distance1;
long duration2;
int distance2;
long duration3;
int distance3;
  
  int a=0;
void setup() {
  Serial.begin(9600); // serial 9600 important!
  Serial.println("Adafruit VS1053 Simple Test");
pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin1, INPUT); // Sets the echoPin as an Input
pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin2, INPUT); // Sets the echoPin as an Input
pinMode(trigPin3, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin3, INPUT); // Sets the echoPin as an Input
  if (! musicPlayer.begin()) { // initialise the music player
     Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
     while (1);
  }
  Serial.println(F("VS1053 found"));
    
   if (!SD.begin(CARDCS)) {
    Serial.println(F("SD failed, or not present"));
    musicPlayer.sineTest(0x43, 100);   
    musicPlayer.sineTest(0x43, 100); 
    musicPlayer.sineTest(0x43, 100);   
    while (1);  // don't do anything more
  }
  
    musicPlayer.sineTest(0x44, 500);   
  // list files
  printDirectory(SD.open("/"), 0);
  
  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(20,20);

  // If DREQ is on an interrupt pin (on uno, #2 or #3) we can do background
  // audio playing
  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int
 
}

void loop() {
  
long duration1, distance1;
  digitalWrite(trigPin1, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin1, LOW);
  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = (duration1/2) / 29.1;

delayMicroseconds(10);
long duration2, distance2;
  digitalWrite(trigPin2, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin2, LOW);
  duration2 = pulseIn(echoPin2, HIGH);
  distance2= (duration2/2) / 29.1;


delayMicroseconds(10);
  long duration3, distance3;
  digitalWrite(trigPin3, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin3, LOW);
  duration3 = pulseIn(echoPin3, HIGH);
  distance3= (duration3/2) / 29.1;
delayMicroseconds(10);
  Serial.print("Sensor1  ");
    Serial.print(distance1); 
    Serial.print(" Sensor2  ");
    Serial.print(distance2);
    Serial.print(" Sensor3  ");
    Serial.print(distance3);
    Serial.println("cm");
if((distance1<70 && distance1>0) || (distance2<70 && distance2>0 )|| (distance3<70 && distance3>0)){
a++;
if(a==14){
  musicPlayer.playFullFile("/1.mp3");
}
else if(a==29){
  musicPlayer.playFullFile("/2.mp3");
}
else if(a==44){
  musicPlayer.playFullFile("/3.mp3");
  a=0;
}
}
else 
a=0;

  delay(3000);
}


/// File listing helper
void printDirectory(File dir, int numTabs) {
   while(true) {
     
     File entry =  dir.openNextFile();
     if (! entry) {
       // no more files
       //Serial.println("**nomorefiles**");
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');
     }
     Serial.print(entry.name());
     if (entry.isDirectory()) {
       Serial.println("/");
       printDirectory(entry, numTabs+1);
     } else {
       // files have sizes, directories do not
       Serial.print("\t\t");
       Serial.println(entry.size(), DEC);
     }
     entry.close();
   }
}

