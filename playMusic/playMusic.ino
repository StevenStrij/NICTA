
#include <LiquidCrystal.h>

#define START 128
#define SAFE 131

#define STRAIGHT 32768
#define DRIVE 137

#define SCRIPT 152
#define WAIT_DIST 156

#define POTENT 3

int vel = 0;

LiquidCrystal lcd(6, 7, 8, 2, 3, 4, 5);

void sendInstruction(int inst) {
   Serial.write(inst);
   delay(100);
}

void moveDist(int dist, int vel) {
   float timeToDrive = (float)dist/(float)vel;
   
   sendInstruction(SCRIPT);
   sendInstruction(13);
   
   sendInstruction(DRIVE);
   sendInstruction(highByte(vel));
   sendInstruction(lowByte(vel));
   sendInstruction(highByte(STRAIGHT));
   sendInstruction(lowByte(STRAIGHT));
   
   sendInstruction(WAIT_DIST);
   sendInstruction(highByte(dist));
   sendInstruction(lowByte(dist));
   
   sendInstruction(DRIVE);
   sendInstruction(highByte(0));
   sendInstruction(lowByte(0));
   sendInstruction(highByte(STRAIGHT));
   sendInstruction(lowByte(STRAIGHT));
}

void move(int vel, float degOfRot) {

   sendInstruction(DRIVE);
   sendInstruction(highByte(vel));
   sendInstruction(lowByte(vel));
   sendInstruction(highByte((int)(degOfRot*2000)));
   sendInstruction(lowByte((int)(degOfRot*2000)));
   

  
}

void setup() {
   Serial.begin(57600);
   lcd.begin(16, 2);

   sendInstruction(START);
   sendInstruction(SAFE);
   
   pinMode(14, INPUT);
   pinMode(15, INPUT);
   
   digitalWrite(14, HIGH);
   digitalWrite(15, HIGH);
}

void loop() {
   int deg = analogRead(POTENT);
   
   float perRot = 0.00;
   deg -= 512;
   
   perRot = (float)deg/512;
   if (perRot < 0) {
     perRot = -1.00f - perRot;
   } else {
     perRot = 1.00f - perRot; 
   }
   
   if (deg == 1023) {
      perRot = -0.01;
   }
   
   if (digitalRead(14) == LOW) {
      vel += 50;
   } else if (digitalRead(15) == LOW) {
      vel -= 50;
   }
   
   if (vel < -500) {
      vel = -500;
   } else if (vel > 500) {
      vel = 500; 
   }
   
   String str = String(vel);
   char test[4];
   str.toCharArray(test, 4);
   lcd.clear();
   lcd.print(test);
   
   move(vel, perRot);
   delay(200);
}
