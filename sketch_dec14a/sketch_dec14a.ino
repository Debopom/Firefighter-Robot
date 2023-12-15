#include <AFMotor.h>
#include <Servo.h>

const int trigPin = 9;
const int echoPin = 10;
const int waterPump = 5;
const int servoPin = 8;

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

Servo servo;

void setup() {
  Serial.begin(9600); // Initialize serial communication
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(waterPump, OUTPUT);
  servo.attach(servoPin);
}

void loop() {
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

  int stopAngle = -999; // Default value to indicate uninitialized state

  if (distance < 10) {
    stopAngle = servo_motor(0);
    motor1.run(FORWARD);
    motor1.setSpeed(0);
    motor2.run(FORWARD);
    motor2.setSpeed(0);
    motor3.run(FORWARD);
    motor3.setSpeed(0);
    motor4.run(FORWARD);
    motor4.setSpeed(0);

    Serial.print("\nServo stopped at angle: ");
    Serial.println(stopAngle);

    digitalWrite(waterPump, HIGH);
  } else {
    stopAngle = servo_motor(1);
    motor1.run(FORWARD);
    motor1.setSpeed(255);
    motor2.run(FORWARD);
    motor2.setSpeed(255);
    motor3.run(FORWARD);
    motor3.setSpeed(255);
    motor4.run(FORWARD);
    motor4.setSpeed(255);

    Serial.print("\nServo moving to angle: ");
    Serial.println(stopAngle);
  }
}

int servo_motor(int flag) {
  int stopAngle = -999; // Default value to indicate uninitialized state

  if (flag == 1) {
    if (!servo.attached()) {
      // Reattach the servo if it's currently detached
      servo.attach(servoPin);
      Serial.println("\nServo reattached");
    }

int i;
    for (int i = 0; i <= 180; i++) {
      servo.write(i);
      delay(15);
      delay(15); // Additional delay to allow the servo to reach the position
    }

    stopAngle = i; // Set the angle at which the servo was stopped
    delay(15);

    for (int i = 180; i >= 0; i--) {
      servo.write(i);
      delay(15);
      delay(15); // Additional delay to allow the servo to reach the position
    }
  } else if (flag == 0) {
    if (servo.attached()) {
      // Get the current angle before detaching the servo
      stopAngle = servo.read();
      servo.write(stopAngle); // Ensure the servo stays at the current position
      delay(15);
      servo.detach();
      Serial.print("\nServo stopped at angle: ");
      Serial.println(stopAngle);
    }
  }

  return stopAngle;
}
