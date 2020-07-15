volatile int motionState = 0;         // variable for reading the motion status
volatile int soundState = 0;         // variable for reading the sound status

void setup(){
  pinMode(13, OUTPUT);
 
  //attach interupts to the ISR vectors
  attachInterrupt(0, pin_ISR, CHANGE);  // ISR on digital pin 2
  attachInterrupt(1, sound_ISR, CHANGE);  // ISR on digital pin 3
  
  Serial.begin(9600); //start serial Monitor
}

void loop(){
 
}

void pin_ISR() {
  motionState = !motionState;
  if (motionState){
    digitalWrite(13, HIGH);
    Serial.println("Motion detected");
  }
  else{
    digitalWrite(13, LOW);
    Serial.println("Motion ended");
  }
}

void sound_ISR() {
  soundState = !soundState;
  if (soundState){
    digitalWrite(13, HIGH);
    Serial.println("Sound detected");
  }
  else{
    digitalWrite(13, LOW);
    Serial.println("Sound ended");
  }
}
