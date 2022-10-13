void setup() {
  // initialize the digital pin as an output.
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop() {
  digitalWrite(3, HIGH);   // turn the BULB on (HIGH is the voltage level)
  digitalWrite(4, HIGH);   // turn the BULB on (HIGH is the voltage level)
  digitalWrite(13, HIGH);   // turn the BULB on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(3, LOW);    // turn the BULB off by making the voltage LOW
  digitalWrite(4, LOW);    // turn the BULB off by making the voltage LOW
  delay(1000);               // wait for a second
}
