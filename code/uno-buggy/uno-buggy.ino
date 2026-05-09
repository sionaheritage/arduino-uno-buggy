#include <Servo.h>

Servo ControlServo;

// Pin Definitions
const int IN4 = 2;
const int ENB = 3;
const int IN3 = 4;
const int IN2 = 7;
const int IN1 = 8;
const int ENA = 6;
const int EchoSensor = 12;
const int TrigSensor = 13;

long distance;
const int distance_collision = 20;

void setup() {
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(ENA, OUTPUT);

  Serial.begin(9600);
  pinMode(EchoSensor, INPUT);
  pinMode(TrigSensor, OUTPUT);

  ControlServo.attach(11);
  ControlServo.write(90); 
  delay(500); // Give it time to center on startup
}

void measureAndPrintDistance() {
  digitalWrite(TrigSensor, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigSensor, HIGH);
  delayMicroseconds(10);
  digitalWrite(TrigSensor, LOW);

  long duration = pulseIn(EchoSensor, HIGH);
  distance = (duration / 2) * 0.0343;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}

void stopMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW); 
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void moveForward() {
  analogWrite(ENA, 175);
  analogWrite(ENB, 175);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void moveBackward() {
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnLeft() {
  analogWrite(ENA, 175);
  analogWrite(ENB, 175);
  // Tank Turn: Left motor backward, Right motor forward
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnRight() {
  analogWrite(ENA, 175);
  analogWrite(ENB, 175);
  // Tank Turn: Left motor forward, Right motor backward
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void checkAndTurn() {
  // Check left
  ControlServo.write(150); 
  delay(300); 
  measureAndPrintDistance();
  long leftDistance = distance;
  Serial.print("Left distance: ");
  Serial.println(leftDistance);

  // Check right
  ControlServo.write(30); 
  delay(300); 
  measureAndPrintDistance();
  long rightDistance = distance;
  Serial.print("Right distance: ");
  Serial.println(rightDistance);

  // Return servo to center
  ControlServo.write(90);
  delay(300);

  // Decide direction
  bool leftFree = leftDistance > distance_collision;
  bool rightFree = rightDistance > distance_collision;

  if (leftFree && !rightFree) {
    Serial.println("Turning left");
    turnLeft();
    delay(500); 
    stopMotors();
  } else if (!leftFree && rightFree) {
    Serial.println("Turning right");
    turnRight();
    delay(500);
    stopMotors();
  } else if (leftFree && rightFree) {
    Serial.println("Both free, defaulting right");
    turnRight();
    delay(500);
    stopMotors();
  } else {
    Serial.println("Both blocked, reversing");
    moveBackward();
    delay(600);
    // Spin around 
    turnRight();
    delay(800); 
    stopMotors();
  }
}

void loop() {
  measureAndPrintDistance();
  
  if (distance > distance_collision){
    Serial.println("Move forward");
    moveForward();
    delay(50); 
  } else {
    Serial.println("Obstacle in front");
    stopMotors();
    delay(200); // Pause to stabilize before scanning
    checkAndTurn();
  }
}