#include <AFMotor.h>

// Motor initialization
AF_DCMotor motor1(1); 
AF_DCMotor motor2(2); 
AF_DCMotor motor3(3); 
AF_DCMotor motor4(4); 

char command; 
int speed = 100; 

void setup() {
  Serial.begin(9600); 

  // Set initial speed for all motors
  motor1.setSpeed(speed);
  motor2.setSpeed(speed);
  motor3.setSpeed(speed);
  motor4.setSpeed(speed);

  // Display available commands
  Serial.println("Omni-directional Robot Ready");
  Serial.println("Commands: F (Forward), B (Backward), L (Left), R (Right),");
  Serial.println("1 (Forward-Right), 2 (Forward-Left), 3 (Backward-Right), 4 (Backward-Left),");
  Serial.println("Z (Spin Left), X (Spin Right), S (Stop), + (Speed Up), - (Slow Down)");
}

void loop() {
  // Check if a command is received
  if (Serial.available()) {
    command = Serial.read();
    processCommand(command);
  }
}

void processCommand(char cmd) {
  switch (cmd) {
    case 'F':
      move(FORWARD, FORWARD, FORWARD, FORWARD);
      Serial.println("Moving Forward");
      break;
    case 'B':
      move(BACKWARD, BACKWARD, BACKWARD, BACKWARD);
      Serial.println("Moving Backward");
      break;
    case 'L':
      move(BACKWARD, FORWARD, FORWARD, BACKWARD);
      Serial.println("Moving Left");
      break;
    case 'R':
      move(FORWARD, BACKWARD, BACKWARD, FORWARD);
      Serial.println("Moving Right");
      break;
    case '1': // Forward-Right
      move(FORWARD, RELEASE, RELEASE, FORWARD);
      Serial.println("Moving Forward-Right");
      break;
    case '2': // Forward-Left
      move(RELEASE, FORWARD, FORWARD, RELEASE);
      Serial.println("Moving Forward-Left");
      break;
    case '3': // Backward-Right
      move(BACKWARD, RELEASE, RELEASE, BACKWARD);
      Serial.println("Moving Backward-Right");
      break;
    case '4': // Backward-Left
      move(RELEASE, BACKWARD, BACKWARD, RELEASE);
      Serial.println("Moving Backward-Left");
      break;
    case 'Z': // Spin Left
      move(BACKWARD, FORWARD, BACKWARD, FORWARD);
      Serial.println("Spinning Left");
      break;
    case 'X': // Spin Right
      move(FORWARD, BACKWARD, FORWARD, BACKWARD);
      Serial.println("Spinning Right");
      break;
    case 'S':
      stopMotors();
      Serial.println("Stopped");
      break;
    case '+':
      adjustSpeed(10); // Increase speed by 10
      break;
    case '-':
      adjustSpeed(-10); // Decrease speed by 10
      break;
    default:
      Serial.println("Invalid Command");
  }
}

void move(int m1Dir, int m2Dir, int m3Dir, int m4Dir) {
  motor1.run(m1Dir);
  motor2.run(m2Dir);
  motor3.run(m3Dir);
  motor4.run(m4Dir);
}

void stopMotors() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void adjustSpeed(int delta) {
  speed = constrain(speed + delta, 0, 255); // Adjust speed within valid range
  motor1.setSpeed(speed);
  motor2.setSpeed(speed);
  motor3.setSpeed(speed);
  motor4.setSpeed(speed);

  Serial.print("Speed adjusted to: ");
  Serial.println(speed);
} 
