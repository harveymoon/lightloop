#define rxIR  A15
#define txIR  22
#define txVL  13

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("hi");

  pinMode(rxIR, INPUT);
  pinMode(txIR, OUTPUT);
  pinMode(txVL, OUTPUT);

  digitalWrite(txVL, HIGH);
  delay(2000);
  digitalWrite(txVL, LOW);
}

void loop() {
  int rxIR_brightness = analogRead(rxIR);
  Serial.println(rxIR_brightness);
  if(rxIR_brightness > 120){
    //delay(1000);
    digitalWrite(txVL, HIGH);
    //delay(1000);
  }else{
    digitalWrite(txVL, LOW);
  }
  delay(250);
}
