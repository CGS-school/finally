#include <Servo.h>

#define VRL 24
#define VYL 29
#define VGL 33
#define PRL 22
#define PGL 36
#define TEST_LED 49
#define SOUND 7
#define SERVO_PIN 40
// 초음파 거리 센서
#define TRIG 9
#define ECHO 10
// 압력 센서
#define PRESS 13

Servo servo;

void setup() {
  pinMode(VRL, OUTPUT);
  pinMode(VYL, OUTPUT);
  pinMode(VGL, OUTPUT);
  pinMode(PRL, OUTPUT);
  pinMode(PGL, OUTPUT);
  pinMode(TEST_LED, OUTPUT);
  pinMode(SOUND, OUTPUT);
  pinMode(SERVO_PIN, OUTPUT);
  servo.attach(SERVO_PIN);
  // 초음파 거리 센서
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  // 압력 센서
  pinMode(PRESS, INPUT);
}

// 초음파 거리 센서 입력 함수
long ulSenIn();
// 압력센서 입력 함수
int presSenIn();
void keep_VGL_on();
void VTimeTaken(unsigned long VTT, long* p_dis, int ISO, int isGOn);
void OnOthers(unsigned long VTT[3], int*ISO);
void turnSound(int ISO, unsigned long VTT, int isGOn);

void loop() {
  // 0 : GREEN
  // 1 : YELLOW
  // 2 : RED
  unsigned long VTT[3] = {5000, 1000, 3000};
  static int VCount = 0;
  int ISO;
  static long distance;
  long* p_dis = &distance;
  keep_VGL_on();
  
  servo.write(0);
  ISO = 0;
  VTimeTaken(VTT[VCount], p_dis, ISO, 0);

  if (VCount == 2)
    {
      VCount = 0;
    }
  else
    {
      VCount++;
    }

  if (VCount == 1 && distance < 16)
   {
     digitalWrite(TEST_LED, LOW);
     OnOthers(VTT, &ISO);
   }
}

void VTimeTaken(unsigned long VTT, long* p_dis, int ISO, int isGOn)
{
  unsigned long cur_time = 0, old_time = 0;
  unsigned long time_taken = 0;

  while(time_taken < VTT)
  {
    old_time = millis();
    *p_dis = ulSenIn();

    if (*p_dis > 15 || isGOn == 1)
    {
      digitalWrite(TEST_LED, LOW);
    }
    else
    {
      digitalWrite(TEST_LED, HIGH);
    }
    turnSound(ISO, VTT, isGOn);
    cur_time = millis();
    time_taken += cur_time - old_time;
  }
}

void OnOthers(unsigned long VTT[3], int*ISO)
{
  long temp = 0;
  digitalWrite(VYL, HIGH);
  digitalWrite(VGL, LOW);
  VTimeTaken(VTT[1], &temp, *ISO, 0);
  *ISO = 1;
  servo.write(90);
  digitalWrite(VYL, LOW);
  digitalWrite(VRL, HIGH);
  digitalWrite(PRL, LOW);
  digitalWrite(PGL, HIGH);
  VTimeTaken(VTT[2], &temp, *ISO, 1);  
}

void turnSound(int ISO, unsigned long VTT, int isGOn)
{
  int presValue;
  presValue = presSenIn();

  if (presValue < 100 || isGOn == 1)
  {
    noTone(SOUND);
  }
  else
  {
    tone(SOUND, 532);
  }
}

// 초음파 거리 센서 입력 함수
long ulSenIn()
{
  long duration, distance;
  
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  
  duration = pulseIn(ECHO, HIGH);
  distance = duration * 0.034 / 2;

  return distance;
}

// 압력서 입력 함수
int presSenIn()
{
  int value = analogRead(PRESS);
  value = 1023 - value;
  //value = map(value, 0, 1000, 0, 255);

  return value;
}

void keep_VGL_on()
{
  digitalWrite(PRL, HIGH);
  digitalWrite(VGL, HIGH);
  digitalWrite(PGL, LOW);
  digitalWrite(VYL, LOW);
  digitalWrite(VRL, LOW);
}
