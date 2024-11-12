#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SDA_PIN 26
#define SCL_PIN 25

LiquidCrystal_I2C lcd(0x27,16,2);

void setup(){
Wire.begin(SDA_PIN,SCL_PIN);
lcd.init();
lcd.backlight();
lcd.clear();
}
void loop(){
lcd.setCursor(0,0);
lcd.print("Hello,From");
lcd.setCursor(0,1);
lcd.print("Nodemcu!");

delay(1000);
lcd.clear();
}
