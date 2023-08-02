int soilSignal = A0; //Define the Analog pin# on the Arduino for the soil moisture sensor signal
int rainDigPin = 16; //Define the Digital Input on the Arduino for the sensor signal

void setup() {
  Serial.begin(74880); // Start the serial communication
  pinMode(rainDigPin, INPUT); //Step pin as input
}
 
void loop() {
  int soil = analogRead(soilSignal);
  Serial.print("Soil Moisture Level: ");
  Serial.println(soil);
  delay(200);
  
  Serial.print("Soil Moisture Level (Dejital): ");
  if (!digitalRead(rainDigPin)) {
    Serial.println("Wet");
  }
  else {
    Serial.println("Dry");
  }
  delay(200);
}






//int Soil_moisture_signal = A0; //Define the Analog pin# on the Arduino for the soil moisture sensor signal
//int Soil_sesor_pin = 5; //Define the Digital Input on the Arduino for the sensor signal
//int Soil_sensor_state = 0; 
//
//int Rein_dig_pin = 8;
//int Rein_sensor_stasus = 0;
//void setup() {
//  Serial.begin(74880); // Start the serial communication
//  Serial.print("Starting!");
//  pinMode(Soil_sesor_pin, INPUT); //Step pin as input
//  pinMode(Rein_dig_pin, INPUT); //Step pin as input
//}
// 
//void loop() {
//  soil_secsor();
//  delay(100);
//
//  rein_sensor();
//  delay(100);
//}
//
//void soil_secsor(){
//  int Moisture = analogRead(Soil_moisture_signal);
//  Serial.print("Soil Moisture Level: ");
//  Serial.println(Moisture);
//  delay(200);
//  
//  Serial.print("Soil Moisture Level (Dejital): ");
//  Soil_sensor_state = digitalRead(Soil_sesor_pin);
//  if (Soil_sensor_state == 1) {
//    Serial.println("Wet");
//  }
//  else {
//    Serial.println("Dry");
//  }
//  delay(200);
//}
//
//void rein_sensor(){
//  Serial.print("Rein Moisture Level (Dejital): ");
//  Rein_sensor_stasus = digitalRead(Rein_dig_pin);
//  if (Rein_sensor_stasus == 1) {
//    Serial.println("Wet");
//  }
//  else {
//    Serial.println("Dry");
//  }
//  delay(200);
//}
