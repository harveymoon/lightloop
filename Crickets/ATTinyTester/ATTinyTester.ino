#include <avr/wdt.h>
#include <avr/sleep.h>

#define rxIR    3
#define txLEDs  0
#define piezo   1

#define irThreshold 400

#define millisBeforeStarting 500

ISR(WDT_vect){
  //don't do anything. this is the watchdog interrupt action.
  //We just wake up.
}

void setup() {
  analogReference(INTERNAL);

  pinMode(rxIR, INPUT);
  pinMode(txLEDs, OUTPUT);
  pinMode(piezo, OUTPUT);

  makeADumbSound();

  digitalWrite(piezo, LOW);

  //Startup Indication
  digitalWrite(txLEDs, HIGH);
  delay(2000);
  digitalWrite(txLEDs, LOW);
}

void loop() {
  //Sleep setup
  ADCSRA &= ~(1<<ADEN); //Disable ADC, saves ~230uA
  //0=16ms, 1=32ms, 2=64ms, 3=128ms, 4=250ms, 5=500ms
  //6=1sec, 7=2sec, 8=4sec, 9=8sec
  setup_watchdog(5);
  sleep_mode();
  ADCSRA |= (1<<ADEN); //Enable ADC
  
  int rxIR_brightness = analogRead(rxIR);
  if (rxIR_brightness > irThreshold) {
    delay(millisBeforeStarting);
    turnOnAndFadeOutLEDs();
  } else {
    digitalWrite(txLEDs, LOW);
  }
}


void turnOnAndFadeOutLEDs(){
  // POP on full
    digitalWrite(txLEDs, HIGH);
    //Fade out
    makeADumbSound();
    for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
      analogWrite(txLEDs, fadeValue);
      delay(3);
    }
    
}

void makeADumbSound(){
  for(int i=0; i < 30; i++){
    int thing = i % 4;
    if (thing == 0){
      analogWrite(piezo, 128);
    }else if (thing == 2){
      analogWrite(piezo, 64);
    }else if (thing == 4){
      analogWrite(piezo, 32);
    }else if (thing == 3){
      analogWrite(piezo, 240);
    }else {
      analogWrite(piezo, 0);
    }
    delay(10);
  }
  digitalWrite(piezo, LOW);
}


void setup_watchdog(int timerPrescaler) {

  if (timerPrescaler > 9 ) timerPrescaler = 9; //Limit incoming amount to legal settings

  byte bb = timerPrescaler & 7; 
  if (timerPrescaler > 7) bb |= (1<<5); //Set the special 5th bit if necessary

  //This order of commands is important and cannot be combined
  MCUSR &= ~(1<<WDRF); //Clear the watch dog reset
  WDTCR |= (1<<WDCE) | (1<<WDE); //Set WD_change enable, set WD enable
  WDTCR = bb; //Set new watchdog timeout value
  WDTCR |= _BV(WDTIE); //Set the interrupt enable, this will keep unit from resetting after each int
}

