volatile boolean motionState;         // variable for reading the motion status
volatile boolean soundState;         // variable for reading the sound status

void setup(){
  pinMode(13, OUTPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  //attach interupts to the ISR vectors
  attachInterrupt(0, pin_ISR, CHANGE);  // ISR on digital pin 2
  attachInterrupt(1, sound_ISR, CHANGE);  // ISR on digital pin 3
  
  Serial.begin(9600); //start serial Monitor
}

void loop(){
  if (motionState){
    digitalWrite(13, HIGH);
    Serial.println("Motion detected");
  }
  if (soundState){
    digitalWrite(13, HIGH);
    Serial.println("Sound detected");
  }
  if (!motionState && !soundState){
    digitalWrite(13, LOW);
    Serial.println("No motion or sound detected");
  }
 
}

void pin_ISR() {
  motionState = !motionState;
}

void sound_ISR() {
  if(digitalRead(3)== 1){
    soundState = HIGH;
  }
  else{
    soundState = LOW;
  }

}
