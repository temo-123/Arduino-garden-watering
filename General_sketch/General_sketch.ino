
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

/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-esp8266-input-data-html-form/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/

#include <Arduino.h>
#ifdef ESP32
  #include <WiFi.h>
  #include <AsyncTCP.h>
#else
  #include <ESP8266WiFi.h>
  #include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>

#include <Wire.h>

//const char **host_ip = WiFi.localIP()

//#include <Adafruit_Sensor.h> // https://github.com/adafruit/Adafruit_Sensor
//#include <Adafruit_BMP085.h>
//Adafruit_BMP085 BMP1; // I2C
//Adafruit_BMP085 BMP2; // I2C
//
//#include <Adafruit_SSD1306.h>
//#include <Adafruit_GFX.h>
//
//Adafruit_SSD1306 display(128, 64, &Wire, -1);

#define TCAADDR 0x70

AsyncWebServer server(80);

//float host_name = 0.0.0.0;
String host_name = "0.0.0.0";

// REPLACE WITH YOUR NETWORK CREDENTIALS
const char* ssid = "Temo";
const char* password = "qwerty!!!";

//const char* PARAM_INPUT_1 = "input1";
//const char* PARAM_INPUT_2 = "input2";
//const char* PARAM_INPUT_3 = "input3";



// HTML web page to handle 3 input fields (input1, input2, input3)
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP Input Form</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
</head>
<body>
<h1>test</h1>
</body></html>)rawliteral";
//const char index_html[] PROGMEM = R"rawliteral(
//<!DOCTYPE HTML><html><head>
//  <title>ESP Input Form</title>
//  <meta name="viewport" content="width=device-width, initial-scale=1">
//  </head><body>
//  <form action="/get">
//    input1: <input type="text" name="input1">
//    <input type="submit" value="Submit">
//  </form><br>
//  <form action="/get">
//    input2: <input type="text" name="input2">
//    <input type="submit" value="Submit">
//  </form><br>
//  <form action="/get">
//    input3: <input type="text" name="input3">
//    <input type="submit" value="Submit">
//  </form>
//</body></html>)rawliteral";

//void notFound(AsyncWebServerRequest *request) {
//  request->send(404, "text/plain", "Not found");
//}

void setup() {
//  Serial.begin(115200);
  Wire.begin();
  
  Serial.begin(74880);
  
  checkPorts();
  
  TCA9548A(6);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    while (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
      printStatus("SSD1306 allocation failed. Could not find a dyspley on bus 6, check wiring!");
      delay(5000);
    }
  }
  else{
      String status = "Dyspley is initing!";
      printStatus(status);
      displayOled(6, status, 2);
      delay(5000);
  }
  
  TCA9548A(1);
  if(!BMP1.begin(0x77)){
    while(!BMP1.begin(0x77)) {
      String status = "Could not find a valid BME280 sensor on bus 1 (Inside sensor), check wiring!";
      printStatus(status);
      displayOled(6, status, 2);
      delay(5000);
    }
  }
  else{
      String status = "Inside termo sensor (BME280) is initing!";
      printStatus(status);
      displayOled(6, status, 2);
      delay(5000);
  }
  
  TCA9548A(7);
  if(!BMP2.begin(0x77)) {
    while(!BMP2.begin(0x77)) {
      String status = "Could not find a valid BME280 sensor on bus 7 (Outside sensor), check wiring!";
      printStatus(status);
      displayOled(6, status, 2);
      delay(5000);
    }
  }
  else {
      String status = "Outside termo sensor (BME280) is initing!";
      printStatus(status);
      displayOled(6, status, 2);
      delay(5000);
  }
  
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    while(WiFi.waitForConnectResult() != WL_CONNECTED) {
      String status = "WiFi Failed!";
      printStatus(status);
      displayOled(6, status, 2);
      delay(5000);
    }
  }
  else {
      host_name = WiFi.localIP().toString();
      String status = "WiFi initing! IP Address: " + host_name;
      printStatus(status);
      displayOled(6, status, 2);
      delay(5000);
  }
  
  Serial.println();

//  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
//    request->send(SPIFFS, "/web_assets/index.html", "text/html");
//  });
// 
//  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request){
//    request->send(SPIFFS, "/web_assets/style.css", "text/css");
//  });

  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
//    request->send(200, "/web_assets/index.html", "text/html");
    
    request->send(SPIFFS, "/index.html", String(), false);
  });

  server.begin();
  
//  // Send web page with input fields to client
//  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
//    request->send_P(200, "text/html", index_html);
//  });
//
//  // Send a GET request to <ESP_IP>/get?input1=<inputMessage>
//  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
//    String inputMessage;
//    String inputParam;
//    // GET input1 value on <ESP_IP>/get?input1=<inputMessage>
//    if (request->hasParam(PARAM_INPUT_1)) {
//      inputMessage = request->getParam(PARAM_INPUT_1)->value();
//      inputParam = PARAM_INPUT_1;
//    }
//    // GET input2 value on <ESP_IP>/get?input2=<inputMessage>
//    else if (request->hasParam(PARAM_INPUT_2)) {
//      inputMessage = request->getParam(PARAM_INPUT_2)->value();
//      inputParam = PARAM_INPUT_2;
//    }
//    // GET input3 value on <ESP_IP>/get?input3=<inputMessage>
//    else if (request->hasParam(PARAM_INPUT_3)) {
//      inputMessage = request->getParam(PARAM_INPUT_3)->value();
//      inputParam = PARAM_INPUT_3;
//    }
//    else {
//      inputMessage = "No message sent";
//      inputParam = "none";
//    }
//    Serial.println(inputMessage);
//    request->send(200, "text/html", "HTTP GET request sent to your ESP on input field (" 
//                                     + inputParam + ") with value: " + inputMessage +
//                                     "<br><a href=\"/\">Return to Home Page</a>");
//  });
//  server.onNotFound(notFound);
//  server.begin();
}

void loop() {
  printValues(BMP1, 1);
  delay(2000);
  
  printValues(BMP2, 7);
  delay(2000);
}

void index_page(){
  // 
}


// Select I2C BUS
void TCA9548A(uint8_t bus){
  Wire.beginTransmission(TCAADDR);  // TCA9548A address
  Wire.write(1 << bus);          // send byte to select bus
  Wire.endTransmission();
}

void printValues(Adafruit_BMP085 active_bmp_sensor , int bus) {
  display.clearDisplay();
  TCA9548A (bus);
  showHost(6, "host - "+host_name);
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

void printStatus(String statsus){
  Serial.println("=================================================");
  Serial.println(statsus);
  Serial.println("=================================================");
}

void checkPorts(){
  while (!Serial);
   delay(1000);
   Wire.begin();
   
//   Serial.println("");
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
   Serial.println("=================================================");
   Serial.println("Scaning Compliting!");
   Serial.println("=================================================");
}
