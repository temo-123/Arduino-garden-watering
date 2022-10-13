/*
 * 14CORE TEST CODE FOR SOIL MOISTURE SENSOR
 * www.14core.com 
 * 
 * https://www.14core.com/wiring-the-soil-moisture-with-arduino/
 */

//int myLed = 10;
int sensorPin = A0;    // Analog select the input pin for the potentiometer
int sensorValue = 13;  // The variable to store the value coming from the sensor

void setup() {

   //pinMode(myLed, OUTPUT);
   Serial.begin(9600);  //Start Serial Communication at boud rate 9600 To verify the ourput
}

void loop() {
  sensorValue = analogRead(sensorPin); //Reads the value from the sensor
  delay(1000);          
  Serial.print("sensor = " );                       
  Serial.println(sensorValue);                   
}
