void setup() {
  // initialize the digital pin as an output.
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(10, HIGH);   // turn the BULB on (HIGH is the voltage level)
//  delay(1000); 
  digitalWrite(11, HIGH);   // turn the BULB on (HIGH is the voltage level)
//  delay(1000); 
  digitalWrite(13, HIGH);   // turn the BULB on (HIGH is the voltage level)
  delay(5000);               // wait for a second
  
  digitalWrite(10, LOW);    // turn the BULB off by making the voltage LOW
  digitalWrite(11, LOW);    // turn the BULB off by making the voltage LOW
  digitalWrite(13, LOW);   // turn the BULB on (HIGH is the voltage level)
  delay(5000);               // wait for a second
}
