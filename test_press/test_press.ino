#define PRESS 13

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int value = analogRead(PRESS);
  value = 1023 - value;
  //value = map(value, 0, 1000, 0, 10000);
  Serial.println(value);
  delay(500);-
}
