#include <Servo.h>

#define VRL 25
#define VYL 29
#define VGL 33
#define PRL 22
#define PGL 36
#define TEST_LED 49
#define SOUND 7
#define SERVO_PIN 40
// 초음파 거리 센서
#define TRIG 11
#define ECHO 8
// 압력 센서
#include PRESS 13

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
void ulSenIn();
// 압력센서 입력 함수
void presSenIn();

void loop() {
  // 0 : RED
  // 1 : GREEN
  // 2 : YELLOW
  unsigned long VTT[3] = {5000, 3000, 1000};
  static int VCount = 0;
}

// 초음파 거리 센서 입력 함수
void ulSenIn() {
  
}
// 압력센서 입력 함수
void presSenIn() {
  
}
