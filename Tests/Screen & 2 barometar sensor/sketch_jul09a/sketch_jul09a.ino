/*********
  https://RandomNerdTutorials.com/tca9548a-i2c-multiplexer-esp32-esp8266-arduino/
*********/

#include <Wire.h>

#include <Adafruit_Sensor.h> // https://github.com/adafruit/Adafruit_Sensor
#include <Adafruit_BMP085.h>
Adafruit_BMP085 BMP1; // I2C
Adafruit_BMP085 BMP2; // I2C

#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

#define TCAADDR 0x70

void setup() {
  Wire.begin();
  
  Serial.begin(74880);
     
  checkPorts();
  
  TCA9548A(6);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    while (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
      Serial.println("=================================================");
      Serial.println(F("SSD1306 allocation failed"));
      Serial.println("Could not find a dyspley on bus 6, check wiring!");
      Serial.println("=================================================");
  
      delay(5000);
    }
  }
  else{
      Serial.println("=================================================");
      Serial.println("Dyspley is initing!");
      Serial.println("=================================================");
      
      displayOled(6, "Let start", 2);
      
      delay(2000);
      
     display.clearDisplay();
  }
  
//  showHost(6, "host - 1.1.1.1");
//      delay(2000);
  
  TCA9548A(1);
  if(!BMP1.begin(0x77)){
    while(!BMP1.begin(0x77)) {
      Serial.println("============================================================================");
      Serial.println("Could not find a valid BME280 sensor on bus 1 (Inside sensor), check wiring!");
      Serial.println("============================================================================");
      
      delay(5000);
    }
  }
  else{
      Serial.println("=================================================");
      Serial.println("Inside termo sensor (BME280) is initing!");
      Serial.println("=================================================");
  }
  
  TCA9548A(7);
  if(!BMP2.begin(0x77)) {
    while(!BMP2.begin(0x77)) {
      Serial.println("=============================================================================");
      Serial.println("Could not find a valid BME280 sensor on bus 7 (Outside sensor), check wiring!");
      Serial.println("=============================================================================");
      
      delay(5000);
    }
  }
  else {
      Serial.println("=================================================");
      Serial.println("Outside termo sensor (BME280) is initing!");
      Serial.println("=================================================");
  }
  
  Serial.println();
}

void loop() {
  display.clearDisplay();
  printValues(BMP1, 1);
  delay(2000);
  
  display.clearDisplay();
  printValues(BMP2, 7);
  delay(2000);
}

// Select I2C BUS
void TCA9548A(uint8_t bus){
  Wire.beginTransmission(TCAADDR);  // TCA9548A address
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
}

void printValues(Adafruit_BMP085 active_bmp_sensor , int bus) {
  TCA9548A (bus);
  showHost(6, "host - 1.1.1.1");
//      delay(2000);
  
  Serial.print("Temperature = ");
  Serial.print(active_bmp_sensor.readTemperature());
  Serial.println(" *C");
  
  Serial.print("Pressure = ");
  Serial.print(active_bmp_sensor.readPressure() / 100.0F);
  Serial.println(" hPa");

  Serial.println();
  
//  display.clearDisplay();
  display.setTextSize(0.8);             
  display.setTextColor(SSD1306_WHITE);       
  display.setCursor(0,0);
  
  display.println("");
  
  display.print("Sensor bus "); 
  display.println(bus);
  
  display.print("Temperature ");
  display.print(active_bmp_sensor.readTemperature());
  display.println(" *C");
  
  display.print("Pressure ");
  display.print(active_bmp_sensor.readPressure() / 100.0F);
  display.println(" hPa");
  
  display.display(); 
}

void showHost(int bus, String host){
//  display.clearDisplay();
  display.setTextSize(1);             
  display.setTextColor(SSD1306_WHITE);       
  display.setCursor(0,0);
  display.println(host); 
  display.display();  
}

void displayOled(int bus, String text, int line){
  display.clearDisplay();
  display.setTextSize(1);             
  display.setTextColor(SSD1306_WHITE);
  
  int height = 1 + line;
  display.setCursor(0, height);
  
  display.println(text); 
  display.display();  
}

void checkPorts(){
  while (!Serial);
   delay(1000);
   Wire.begin();
   
   Serial.println("");
   Serial.println("=================================================");
   Serial.println("TCAScanner ready!");
  
   for (uint8_t t=0; t<8; t++) {
     TCA9548A(t);
     Serial.print("TCA Port #"); Serial.println(t);
     for (uint8_t addr = 0; addr<=127; addr++) {
       if (addr == TCAADDR) continue;
        Wire.beginTransmission(addr);
       if (!Wire.endTransmission()) {
        Serial.print("Found I2C 0x"); Serial.println(addr,HEX);
       }
     }
   }
   Serial.println("Scaning Compliting!");
   Serial.println("=================================================");
}
