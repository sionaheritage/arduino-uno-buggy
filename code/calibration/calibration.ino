// Pin definitions
const int IN4 = 2;
const int ENB = 3;  
const int IN3 = 4;
const int IN2 = 7;
const int IN1 = 8;
const int ENA = 6;  

// Calibration variables - alter to account for motor friction
int leftSpeed = 175;  
int rightSpeed = 175; 

void setup() {
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(ENA, OUTPUT);

  delay(2000); 
  
  testStraightLine();
}

void testStraightLine() {
  // Apply calibrated speeds
  analogWrite(ENA, leftSpeed);
  analogWrite(ENB, rightSpeed);

  // Set direction to FORWARD
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  // Drive for 2 seconds
  delay(2000);

  // Stop motors
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void loop() {
  // Empty to run once - recallibrate: RESET button on Arduino
}