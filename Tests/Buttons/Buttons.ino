const int button_1 = 14;
const int button_2 = 12;

const int switch_position_1 = 13;
const int switch_position_2 = 3;

void setup() {
  Serial.begin(74880);
  pinMode(button_1, INPUT);
  pinMode(button_2, INPUT);
  
  pinMode(switch_position_1, INPUT);
  pinMode(switch_position_2, INPUT);
}
void loop() {
  if(digitalRead(switch_position_1) && !digitalRead(switch_position_2)){
    Serial.println("switch_position_1 (auto)");
  }
  else if(!digitalRead(switch_position_1) && digitalRead(switch_position_2)){
    Serial.println("switch_position_2 (open)");
  }
  else if(digitalRead(switch_position_1) && digitalRead(switch_position_2)){
    Serial.println("switch_position_0 (off)");
  }
    
  if(!digitalRead(button_1)){
    Serial.println("button_1 on");
  }
  
  if(!digitalRead(button_2)){
    Serial.println("button_2 on");
  }

  delay(50);
}
