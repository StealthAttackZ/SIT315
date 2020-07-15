boolean toggle = LOW;
volatile boolean motionFlag = LOW;
volatile boolean soundFlag = LOW;
volatile boolean moistureFlag = LOW;

void setup(){
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(13, OUTPUT);
  
  // enable interrupt for pins 2,3,4
  pciSetup(2);
  pciSetup(3);
  pciSetup(4);
  
  cli();//stop interrupts
  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  sei();//allow interrupts
  Serial.begin(9600); //start serial Monitor
}

void loop(){
 
}

// Install Pin change interrupt for a pin
 
void pciSetup(byte pin)
{
    *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // enable pin
    PCIFR  |= bit (digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
    PCICR  |= bit (digitalPinToPCICRbit(pin)); // enable interrupt for the group
}

ISR (PCINT2_vect) // handle pin change interrupt for D2 to D4 here
{
    
    if (digitalRead(2) == motionFlag){
      digitalWrite(13, HIGH);
      Serial.println("Motion detected");
    }
    else if (digitalRead(2) == LOW){
      digitalWrite(13, LOW);
      Serial.println("Motion ended");
    }
    if (digitalRead(3) == HIGH){
      digitalWrite(13, HIGH);
      Serial.println("Sound detected");
    }
    else if (digitalRead(3) == LOW){
      digitalWrite(13, LOW);
      Serial.println("Sound ended");
    }
    if (digitalRead(4) == HIGH){
      digitalWrite(13, HIGH);
      Serial.println("Moisture detected");
    }
    else if (digitalRead(4) == LOW){
      digitalWrite(13, LOW);
      Serial.println("No moisture");
    } 
}  

ISR(TIMER1_COMPA_vect){//timer1 interrupt 1Hz toggles pin 13 (LED)
//generates pulse wave of frequency 1Hz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low)
  toggle = !toggle;
  if (toggle){
    digitalWrite(13,HIGH);
  }
  else{
    digitalWrite(13,LOW);
  }
}
  
