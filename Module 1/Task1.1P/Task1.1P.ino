void setup(){
  pinMode(13, OUTPUT);
  pinMode (2, INPUT);
  Serial.begin(9600); //start serial Monitor
}

void loop(){
 
  if(digitalRead(2) == HIGH){ 
    digitalWrite(13, HIGH);
    Serial.println("Motion detected");
    
  } else {
    digitalWrite(13, LOW);
    Serial.println("Motion ended");
  }
  delay(1000);
}
