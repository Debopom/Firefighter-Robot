#include <AFMotor.h>
#include <Servo.h>

const int trigPin = 9;
const int echoPin = 10;
const int espPin=12;
const int waterPump = 5;
const int servoPin = 11;
char alarm='F';

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

Servo servo;
void setup() {
  Serial.begin(115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(waterPump, OUTPUT);
  servo.attach(servoPin);
}

void loop() {
  int incoming=0;
  incoming=digitalRead(espPin);
  if(incoming==HIGH){
    Serial.println("coming signal");
  }
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = (duration / 2) / 29.1;

  Serial.print("\nDistance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if(alarm=='F'){
    int angle=servo_motor(1);
  }
  else if(alarm=='T'){
    digitalWrite(LED_BUILTIN, HIGH);
    int angle=servo_motor(0);
    Serial.println(angle);
    motor1.run(FORWARD);
    motor1.setSpeed(255);
    motor2.run(FORWARD);
    motor2.setSpeed(255);
    motor3.run(FORWARD);
    motor3.setSpeed(255);
    motor4.run(FORWARD);
    motor4.setSpeed(255);
    if (distance <= 10) {
      digitalWrite(LED_BUILTIN, HIGH);
      motor1.run(FORWARD);
      motor1.setSpeed(0);
      motor2.run(FORWARD);
      motor2.setSpeed(0);
      motor3.run(FORWARD);
      motor3.setSpeed(0);
      motor4.run(FORWARD);
      motor4.setSpeed(0);      
      digitalWrite(waterPump, HIGH);
    }
    alarm='F';
  }
}

int servo_motor(int flag){
  servo.attach(servoPin);
  int i;
  for (int i = 0; i <= 180; i++) {
    servo.write(i);
    delay(15);
    if(flag==0){
      return i;              
      }
    }
  delay(10);
  for (int i = 180; i >= 0; i--) {
    servo.write(i);
    delay(15);
    if(flag==0){
      return i;        
    }
  }
} 
