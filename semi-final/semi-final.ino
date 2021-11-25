#include <Servo.h>

#define VRL 25
#define VYL 29
#define VGL 33
#define PRL 22
#define PGL 36
#define LED_SW 53
#define TEST_LED 49
#define SOUND_SW1 8
#define SOUND_SW2 11
#define SOUND 7
#define SERVO_PIN 40

Servo servo;

void setup() {
  pinMode(VRL, OUTPUT);
  pinMode(VYL, OUTPUT);
  pinMode(VGL, OUTPUT);
  pinMode(PRL, OUTPUT);
  pinMode(PGL, OUTPUT);
  pinMode(LED_SW, INPUT);
  pinMode(TEST_LED, OUTPUT);
  pinMode(SOUND_SW1, INPUT);
  pinMode(SOUND_SW2, INPUT);
  pinMode(SOUND, OUTPUT);
  pinMode(SERVO_PIN, OUTPUT);
  servo.attach(SERVO_PIN);
}

void keep_VGL_on();
void VTimeTaken(unsigned long VTT, int* PSW, int ISO);
void OnOthers(unsigned long VTT[3], int* ISO);
void turnSound(int ISO);

void loop() {
  // 0 : RED
  // 1 : GREEN
  // 2 : YELLOW
  unsigned long VTT[3] = {5000, 3000, 1000};
  static int VCount = 0;
  static int save_SW;
  int* PSW = &save_SW;
  int ISO;
  keep_VGL_on();

  servo.write(0);
  ISO = 0;
  VTimeTaken(VTT[VCount], PSW, ISO);

  
  if (VCount == 0 && save_SW == 1)
      {
        save_SW = 0;
        digitalWrite(TEST_LED, LOW);
        OnOthers(VTT, &ISO);
      }
  if (VCount == 2)
    VCount = 0;
  else
    VCount++;
}

void keep_VGL_on()
{
  digitalWrite(PRL, HIGH);
  digitalWrite(VGL, HIGH);
  digitalWrite(PGL, LOW);
  digitalWrite(VYL, LOW);
  digitalWrite(VRL, LOW);
}

void VTimeTaken(unsigned long VTT, int* PSW, int ISO)
{
  unsigned long cur_time = 0, old_time = 0;
  unsigned long time_taken = 0;
  int swInput;
  
  while(time_taken < VTT)
  {
    old_time = millis();
    swInput = digitalRead(LED_SW);
    if (swInput == LOW)
    {
      *PSW = 1;
      digitalWrite(TEST_LED, HIGH);
    }
    turnSound(ISO);
    cur_time = millis();
    time_taken += cur_time - old_time;
  }
}

void OnOthers(unsigned long VTT[3], int* ISO)
{
  int temp = 0;
  int *pTemp = &temp;
  digitalWrite(VYL, HIGH);
  digitalWrite(VGL, LOW);
  VTimeTaken(VTT[2], pTemp, *ISO);
  *ISO = 1;
  servo.write(90);
  digitalWrite(VYL, LOW);
  digitalWrite(VRL, HIGH);
  digitalWrite(PRL, LOW);
  digitalWrite(PGL, HIGH);
  VTimeTaken(VTT[1], pTemp, *ISO);
}

void turnSound(int ISO)
{
  int swValue1 = digitalRead(SOUND_SW1);
  int swValue2 = digitalRead(SOUND_SW2);

  if (swValue1 == LOW && swValue2 == LOW)
    noTone(SOUND);
  else if (ISO == 0 && swValue1 == LOW && swValue2 == HIGH)
    tone(SOUND, 523);
  else if (ISO == 0 && swValue2 == LOW && swValue1 == HIGH)
    tone(SOUND, 523);
  else
    noTone(SOUND);
}
