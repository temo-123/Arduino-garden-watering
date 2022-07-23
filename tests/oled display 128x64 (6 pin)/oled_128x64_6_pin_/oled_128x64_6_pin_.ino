//    https://robotclass.ru/tutorials/arduino_oled/

//    vcc --- vcc
//    gnd --- gnd
//    scl --- D10
//    sda --- D9
//    res --- D13
//    cd  --- D11

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC   11
#define OLED_CS   12
#define OLED_RESET 13

Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

void setup()
{
    display.begin(SSD1306_SWITCHCAPVCC);
    
    // text position
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(25,25);
    
    // write text
    display.println("temo temo temo");
    display.display();
    
    delay(5000);
    
    display.clearDisplay();
}
void loop()
{
}
