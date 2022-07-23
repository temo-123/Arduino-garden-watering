#include <ThreeWire.h>
#include <RtcDS1302.h>

ThreeWire myWire(8, 9, 7); // IO, SCLK, CE ds1302
RtcDS1302<ThreeWire> Rtc(myWire);

void setup() {
    Serial.begin(9600);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);
}
  
void loop() {
    Serial.println();
    
    RtcDateTime now = Rtc.GetDateTime();
    printDateTime(now);

//    Serial.print(Rtc.GetDateTime().Second());
    
    delay(1000);
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
