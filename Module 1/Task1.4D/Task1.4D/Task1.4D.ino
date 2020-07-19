#include <avr/io.h>
#include <avr/interrupt.h>

volatile boolean toggle;
volatile boolean motionState;
volatile boolean soundState;
volatile boolean moistureState;


void setup(){
  pinMode(13, OUTPUT);
  
  // set pins as input and enable pin change interrupts
  pciSetup(2); // motion sensor
  pciSetup(3); // sound sensor
  pciSetup(A1); // moisture sensor
  
  cli();//stop interrupts
  //set timer1 interrupt at 1Hz
  TCCR1A = 0;// set TCCR1A register to 0
  TCCR1B = 0;// set TCCR1B register to 0
  TCNT1  = 0;// initialize counter value to 0
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
  if(motionState){
    Serial.println("Motion detected");
    digitalWrite(13,HIGH);
  }
  if(soundState){
    Serial.println("Sound detected");
    digitalWrite(13,HIGH);
  }
  if(moistureState){
    Serial.println("Moisture detected");
    digitalWrite(13,HIGH); 
  }
  if(!motionState && !soundState && !moistureState){
    Serial.println("No sensor detection");
    if (toggle){
      digitalWrite(13,HIGH);
    }
    else{
      digitalWrite(13,LOW);
    }
  }
 
  delay(1000);

}

// Pin change interrupt for a pin
 
void pciSetup(byte pin)
{
    *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // enable pin
    PCIFR  |= bit (digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
    PCICR  |= bit (digitalPinToPCICRbit(pin)); // enable interrupt for the group
    pinMode(pin, INPUT);
  
}

ISR (PCINT1_vect) // handle pin change interrupts for D2 to D4 here
{ 
    if(analogRead(A1)>500){
      moistureState = HIGH;
    } 
    else{
      moistureState = LOW;
    }
}
    
ISR (PCINT2_vect) // handle pin change interrupts for D2 to D4 here
{ 
   if(digitalRead(2)== 1){
     motionState = HIGH;
   }
   else{
     motionState = LOW;
   }
   if(digitalRead(3)== 1){
     soundState = HIGH;
   }
   else{
     soundState = LOW;
   }
   
}  

ISR(TIMER1_COMPA_vect){//timer1 interrupt 1Hz toggles pin 13 (LED)
//generates pulse wave of frequency 1Hz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low)
  toggle = !toggle;
}
  
