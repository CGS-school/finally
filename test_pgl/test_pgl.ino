#define PGL 52

void setup() {
  // put your setup code here, to run once:
  pinMode(PGL, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(PGL, HIGH);
  delay(1000);
    digitalWrite(PGL, LOW);
    delay(1000);
}
