#define kGreenLED 3

void setup() {
  // put your setup code here, to run once:
  pinMode(kGreenLED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(kGreenLED, HIGH);
  delay(1000);
  digitalWrite(kGreenLED, LOW);
  delay(1000);
}
