#define rxIR    3
#define txLEDs  0
#define piezo   1

#define irThreshold 400

#define millisBeforeStarting 500

void setup() {
  analogReference(INTERNAL);

  pinMode(rxIR, INPUT);
  pinMode(txLEDs, OUTPUT);
  pinMode(piezo, OUTPUT);

  digitalWrite(piezo, LOW);

  //Startup Indication
  digitalWrite(txLEDs, HIGH);
  delay(2000);
  digitalWrite(txLEDs, LOW);
}

void loop() {
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
    for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
      analogWrite(txLEDs, fadeValue);
      delay(15);
    }
}

