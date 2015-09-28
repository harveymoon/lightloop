#define kPuckOne 13
#define kPuckTwo 12

void setup() {
  Serial.begin(9600);
  pinMode(kPuckOne, OUTPUT);
  pinMode(kPuckTwo, OUTPUT);
  digitalWrite(kPuckOne, HIGH);
  digitalWrite(kPuckTwo, HIGH);
}

void loop() {
  int num = random(250, 1200);
  delay(num/2);
  if(num%2 == 0){
    digitalWrite(kPuckOne, LOW);
    delay(num);
    digitalWrite(kPuckOne, HIGH);
  }else{
    digitalWrite(kPuckTwo, LOW);
    delay(num);
    digitalWrite(kPuckTwo, HIGH);
  }
}
