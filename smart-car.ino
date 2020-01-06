#include <Servo.h>

#define TRIG 11
#define ECHO 12
#define GREEN_LED 2
#define RED_LED 3
Servo servo1;
Servo servo2;
enum { NO_OBS, OBS, STUCK } state;

int offset = 4;
float duration;
float distance;

void setup() {
  servo1.attach(9);
  servo2.attach(10);
  state = NO_OBS;
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
}

void loop() {

  switch( state ) {
    
    case NO_OBS:
      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(RED_LED, LOW);
      driveForward();
      if (readDistance() < 13) {
        state = OBS;
      }   
      break;
    
    case OBS:
      digitalWrite(RED_LED, HIGH);
      digitalWrite(GREEN_LED, LOW);
      spinLeft();
      if (readDistance() >= 13) {
        state = NO_OBS;
        break;
      }
      spinLeft();
      if (readDistance() >= 13) {
        state = NO_OBS;
        break;
      }
      spinLeft();
      if (readDistance() >= 13) {
        state = NO_OBS;
        break;
      } 
      else {
        state = STUCK;
      }
      break;

    case STUCK:
      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(RED_LED, HIGH);
      driveBackward();
      driveBackward();
      driveBackward();
      turnLeft();
      state = NO_OBS;
      break;
  }
}

int readDistance() {
  digitalWrite(TRIG,LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG,LOW);

  duration = pulseIn(ECHO,HIGH);
  duration = duration / 1000000;
  distance = (duration * 35200) / 2;
  return distance;
}

void driveForward() {
  servo1.write(81 + offset);
  servo2.write(99 + offset);
  delay(100);
}

void driveBackward() {
  servo1.write(104 + offset);
  servo2.write(76 + offset);
  delay(500);
}

void turnLeft() {
  servo1.write(81 + offset);
  servo2.write(90 + offset);
  delay(500);
}

void turnRight() {
  servo1.write(90 + offset);
  servo2.write(99 + offset);
  delay(500);
}

void spinLeft() {
  servo1.write(81 + offset);
  servo2.write(81 + offset);
  delay(500);
}

void spinRight() {
  servo1.write(99 + offset);
  servo2.write(99 + offset);
  delay(500);
}
