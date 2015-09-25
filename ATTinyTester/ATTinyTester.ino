

#define rxIR  4
#define txIR  3
#define txVL  2

void setup(){


  analogReference(INTERNAL);
  
  pinMode(A3, INPUT);
  pinMode(txIR, OUTPUT);
  pinMode(txVL, OUTPUT);

  digitalWrite(txVL, LOW);
  delay(2000);
  digitalWrite(txVL, HIGH);
}

void loop(){
  int rxIR_brightness = analogRead(A3);

  if(rxIR_brightness > 4){
    delay(1000);
    digitalWrite(txVL, LOW);
    delay(1000);
  }else{
    digitalWrite(txVL, HIGH);
  }
}

