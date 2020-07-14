volatile int motionState = 0;         // variable for reading the motion status

void setup(){
  pinMode(13, OUTPUT);
  pinMode (2, INPUT);
  //attach interupt to the ISR vector
  attachInterrupt(0, pin_ISR, CHANGE);
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
