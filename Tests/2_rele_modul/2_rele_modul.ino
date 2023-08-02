/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp8266-relay-module-ac-web-server/
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*********/

const int relay1 = 0;
const int relay2 = 2;

void setup() {
  Serial.begin(74880);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
}

void loop() {
  digitalWrite(relay1, LOW);
  Serial.println("Current Flowing 1");
  delay(1000); 
  
  digitalWrite(relay2, LOW);
  Serial.println("Current Flowing 2");
  delay(5000); 


  
  digitalWrite(relay1, HIGH);
  Serial.println("Current not Flowing 1");
  delay(1000);
  
  digitalWrite(relay2, HIGH);
  Serial.println("Current not Flowing 2");
  delay(5000);
}
