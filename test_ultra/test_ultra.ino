#define TRIG 9
#define ECHO 10
// 전에는 pwm에 연결

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  long duration, distance;
  
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  
  duration = pulseIn(ECHO, HIGH);
  distance = duration * 0.034 / 2;
  
  //Serial.print("\nDuration:");
  //Serial.println(duration);
  Serial.print(distance);
  Serial.println("cm");

  /*if (distance >= 200 || distance <= 0)
  {
    Serial.println("거리를 측정할수 없음");
  }
  else
  {
    Serial.print(distance);
    Serial.println(" cm");
  }*/
  
  delay(100);
}
