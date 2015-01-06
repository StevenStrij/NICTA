#include <LiquidCrystal.h>
LiquidCrystal lcd(6,7,8,2,3,4,5);

int incomingByte = 0;

unsigned long lastLCDUpdate = 0;
unsigned long lastLoop = 0;

int velocity = 0;

void setup() {
  Serial.begin(57600);
  delay(100);
  Serial.write(128);
  delay(100);
  Serial.write(132);
  lcd.begin(16,2);
  lcd.print("ayy lmao");
  
  pinMode(14,INPUT);//brakes
  pinMode(15,INPUT);//throttle
  
  velocity = 0;
}

void sendBuffer(char* buf,int len)
{
  int i;
  for (i = 0; i < len; i++)
  {
    Serial.write(buf[i]);
    //delay(100);
  }
}

void loop() {
  int sensorValue = analogRead(3);//read in from pot
  int radius = 0x8000;//straight
  if(!(sensorValue > 500 && sensorValue < 524))//if not straight.
  {
    sensorValue = sensorValue - 512;
    sensorValue = 2000*12/sensorValue;
    radius = sensorValue;
  }
  
  //change velocity when holding down buttons.
  digitalWrite(14,HIGH);
  int brake = digitalRead(14);
  digitalWrite(15,HIGH);
  int throttle = digitalRead(15);
  if(brake == LOW)
  {
    velocity -= 100;
  }
  else if (throttle == LOW)
  {
    velocity += 100;
  }
  
  if(velocity > 500) {velocity = 500;}
  if(velocity < 0) {velocity = 0;}
  
  char squ[] = {137, 0x1, 0x2C, 0x7F, 0xFF};//drive command.
  squ[1] = highByte(velocity);
  squ[2] = lowByte(velocity);
  squ[3] = highByte(radius);
  squ[4] = lowByte(radius);
  
  sendBuffer(squ,sizeof(squ));
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Speed: ");
  lcd.print(velocity);
  lcd.print(" mm/s");
  
  delay(200);//200ms;
}
