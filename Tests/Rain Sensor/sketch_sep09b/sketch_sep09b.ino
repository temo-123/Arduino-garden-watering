/*** www.arduinopoint.com ***/
/*** Arduino Rain Detector Project***/
/*** https://arduinopoint.com/rain-sensor-arduino-project/ ***/

int rainAnalogPin = A1;
int rainDigitalPin = 12;

void setup(){
  pinMode(rainAnalogPin, INPUT);
  pinMode(rainDigitalPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // read the input on analog pin 0:
  int sensorAnalogValue = analogRead(rainAnalogPin);
  Serial.print("Rain sensor analog value: ");
  Serial.println(sensorAnalogValue);
  
  // read the input on digital pin 2:
  int sensorDigitalValue = digitalRead(rainDigitalPin);
  Serial.print("Rain sensor digital value: ");
  Serial.println(sensorDigitalValue);
  
//digital output
 if(sensorDigitalValue == HIGH) //High means rain detected; In some case vise versa
 {
 Serial.println("Rain Detected");
 }
 else {
 Serial.println("No Rain Detected");
 }
 delay(250);
}
