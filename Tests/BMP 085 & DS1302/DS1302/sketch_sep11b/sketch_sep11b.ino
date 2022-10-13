// https://www.14core.com/the-ds1302-real-time-clock-on-arduino/

#include <MyRealTimeClock.h>
 
MyRealTimeClock myRTC(9, 8, 7); // Assign Digital Pins 
 
void setup() {
  Serial.begin(9600);
 
  myRTC.setDS1302Time(00, 59, 10, 12 , 10, 07, 2015);
}
 
void loop() {
  // Allow the update of variables for time / accessing the individual element. 
  myRTC.updateTime();
   
  Serial.print("Current Date / Time: "); 
  Serial.print(myRTC.dayofmonth); // Element 1
  Serial.print("/"); 
  Serial.print(myRTC.month); // Element 2
  Serial.print("/");
  Serial.print(myRTC.year); // Element 3
  Serial.print(" ");
  Serial.print(myRTC.hours); // Element 4
  Serial.print(":");
  Serial.print(myRTC.minutes); // Element 5
  Serial.print(":");
  Serial.println(myRTC.seconds); // Element 6
  delay( 1000);
}
