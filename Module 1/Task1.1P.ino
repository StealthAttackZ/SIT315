/*
  This program blinks pin 13 of the Arduino (the
  built-in LED)
*/
int pirState = LOW;
void setup(){
  pinMode(13, OUTPUT);
  pinMode (2, INPUT);
  Serial.begin(9600); //start serial Monitor
}

void loop(){
  // turn the LED on (HIGH is the voltage level)
  if(digitalRead(2) == LOW){ 
  	digitalWrite(13, HIGH);
    if(pirState == LOW){
      Serial.println("Motion detected");
      pirState = HIGH;
    }
  } else {
    digitalWrite(13, LOW);
    if(pirState == HIGH){
      Serial.println("Motion ended");
      pirState = LOW;
    }
  }
}