
#include <OneWire.h>
//temp sensor handle
OneWire thermometer(4);
//temp sensor address
byte tempExt[8] = {0x28, 0x9C, 0x59, 0x4, 0x0, 0x0, 0x80, 0x36};







// lcd screen library
#include <LiquidCrystal_I2C.h>
//library for the language the lcd screen speaks
#include <Wire.h>
//lcd screen handle
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display








void setup(void)
{

  // start serial port
  Serial.begin(9600);
  
  lcd.init(); //initialize the lcd
//  lcd.backlight(); //turn on the backlight//
}










void loop(void)
{ 
    lcd.clear();
    
    byte data[12];
    thermometer.reset();
    thermometer.select(tempExt);
    thermometer.write(0x44, 1);
    thermometer.reset();
    thermometer.select(tempExt);
    thermometer.write(0xBE);
    for (int i = 0; i < 9; i++) {           // we need 9 bytes
        data[i] = thermometer.read();
    }
    int16_t raw = (data[1] << 8) | data[0];
    float tempC = (float)(raw / 16.0) * 1.8 + 32.0;



    lcd.print(tempC, 1);
    delay(1000);
}
