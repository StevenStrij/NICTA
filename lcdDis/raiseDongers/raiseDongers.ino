#include <LiquidCrystal.h>

#define BUTTON 14
#define LATCH 11
#define DATA 12
#define CLOCK 10

LiquidCrystal lcd(6, 7, 8, 2, 3, 4, 5);

byte lSide[8] {
   B00001,
   B00010,
   B00100,
   B01000,
   B01000,
   B01000,
   B10000,
   B10000
};

byte arm[8] {
   B00000,
   B00000,
   B00000,
   B11110,
   B00001,
   B00010,
   B11100,
   B00000
};

byte eye[8] {
   B00000,
   B00100,
   B01110,
   B11111,
   B01010,
   B00100,
   B00000,
   B00000
};

byte rSide[8] {
   B10000,
   B01000,
   B00100,
   B00010,
   B00010,
   B00010,
   B00001,
   B00001
};

int buttonState;

void setup() {
   // put your setup code here, to run once:
   pinMode(BUTTON, INPUT);
   
   pinMode(LATCH, OUTPUT);
   pinMode(DATA, OUTPUT);
   pinMode(CLOCK, OUTPUT);
   
   lcd.createChar(0, lSide);
   lcd.createChar(1, arm);
   lcd.createChar(2, eye);
   lcd.createChar(3, rSide);
   lcd.begin(16,2);
   
   digitalWrite(BUTTON, HIGH);
   

}

void ledWrite(byte a) {
   digitalWrite(LATCH, LOW);
   shiftOut(DATA, CLOCK, LSBFIRST, a);
   digitalWrite(LATCH, HIGH);
}

void loop() {  
  if (digitalRead(BUTTON) == LOW) {
     printDonger();
  } else {
     lcd.clear();
  }
}

void printDonger() {
   lcd.setCursor(0,0);
   lcd.write(byte(0));
   lcd.write(byte(1));
   lcd.write(byte(2));
   lcd.write("_");
   lcd.write(byte(2));
   lcd.write(byte(3));
   lcd.write(byte(1));
   lcd.setCursor(0,1);
   lcd.write("GIVE DIRETIDE!");
}
