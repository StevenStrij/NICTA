#include <LiquidCrystal.h>

LiquidCrystal lcd(6, 7, 8, 2, 3, 4, 5);

byte glyph[8] {
   B10001,
   B01010,
   B01010,
   B00100,
   B00100,
   B01010,
   B01010,
   B10001
};

void setup() {
   // put your setup code here, to run once:
   lcd.createChar(0, glyph);
   lcd.begin(16,2);
   lcd.write(byte(0));
}

void loop() {}
