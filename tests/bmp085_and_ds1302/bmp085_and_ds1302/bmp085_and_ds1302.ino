#include <Adafruit_BMP085.h>

#include <ThreeWire.h>
#include <RtcDS1302.h>

#define rainAnalog A1
#define sensorPower 7
boolean bIsRaining;

Adafruit_BMP085 bmp;
ThreeWire myWire(8, 9, 7); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

void setup() {
    Serial.begin(9600);
    
    if (!bmp.begin()) {
      Serial.println("Could not find a valid BMP085 sensor, check wiring!");
      while (1) {}
    }
  
    Serial.print("compiled: ");
    Serial.print(__DATE__);
    Serial.println(__TIME__);
  
    Rtc.Begin();
  
    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    printDateTime(compiled);
    Serial.println();
  
    if (!Rtc.IsDateTimeValid())
    {
      // Common Causes:
      //    1) first time you ran and the device wasn't running yet
      //    2) the battery on the device is low or even missing
  
      Serial.println("RTC lost confidence in the DateTime!");
      Rtc.SetDateTime(compiled);
    }
  
    if (Rtc.GetIsWriteProtected())
    {
      Serial.println("RTC was write protected, enabling writing now");
      Rtc.SetIsWriteProtected(false);
    }
  
    if (!Rtc.GetIsRunning())
    {
      Serial.println("RTC was not actively running, starting now");
      Rtc.SetIsRunning(true);
    }
  
    RtcDateTime now = Rtc.GetDateTime();
    if (now < compiled)
    {
      Serial.println("RTC is older than compile time!  (Updating DateTime)");
      Rtc.SetDateTime(compiled);
    }
    else if (now > compiled)
    {
      Serial.println("RTC is newer than compile time. (this is expected)");
    }
    else if (now == compiled)
    {
      Serial.println("RTC is the same as compile time! (not expected but all is fine)");
    }
}
  
void loop() {
  
    digitalWrite(sensorPower, HIGH);  // Turn the sensor ON
    delay(10);              // Allow power to settle
    int rainAnalogVal = analogRead(rainAnalog);
  
    if(rainAnalogVal < 100) {
      bIsRaining = true;
    }
    else {
      bIsRaining = false;
    }
    digitalWrite(sensorPower, LOW);    // Turn the sensor OFF
  
    Serial.print("Rein sensor data = ");
    Serial.print(rainAnalogVal);
    Serial.print("\t");
    Serial.println(bIsRaining);

  
    Serial.print("Temperature = ");
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");
    
    Serial.print("Pressure = ");
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");
    
    // Calculate altitude assuming 'standard' barometric
    // pressure of 1013.25 millibar = 101325 Pascal
    Serial.print("Altitude = ");
    Serial.print(bmp.readAltitude());
    Serial.println(" meters");

    Serial.print("Pressure at sealevel (calculated) = ");
    Serial.print(bmp.readSealevelPressure());
    Serial.println(" Pa");

    // you can get a more precise measurement of altitude
    // if you know the current sea level pressure which will
    // vary with weather and such. If it is 1015 millibars
    // that is equal to 101500 Pascals.
    Serial.print("Real altitude = ");
    Serial.print(bmp.readAltitude(101500));
    Serial.println(" meters");
    
    Serial.println();

    RtcDateTime now = Rtc.GetDateTime();

    printDateTime(now);
    Serial.println();
  
    if (!now.IsValid())
    {
      // Common Causes:
      //    1) the battery on the device is low or even missing and the power line was disconnected
      Serial.println("RTC lost confidence in the DateTime!");
    }

    delay(500);
}

#define countof(a) (sizeof(a) / sizeof(a[0]))

void printDateTime(const RtcDateTime& dt)
{
  char datestring[20];

  snprintf_P(datestring,
             countof(datestring),
             PSTR("%02u/%02u/%04u %02u:%02u:%02u"),
             dt.Month(),
             dt.Day(),
             dt.Year(),
             dt.Hour(),
             dt.Minute(),
             dt.Second() );
  Serial.print(datestring);
}
