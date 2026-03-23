// Arduino Uno/ Nano + L298N Motor Driver + HC05 BT module
#include <SoftwareSerial.h>

#define EnA 10
#define IN1 12
#define IN2 11
#define IN3 8
#define IN4 7
#define EnB 9

SoftwareSerial BT(2, 3); // RX, TX for HC-05

int motorSpeed = 150; // Default speed (0–255)

void setup() {
  pinMode(EnA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(EnB, OUTPUT);

  BT.begin(9600);
  Serial.begin(9600);
  Serial.println("Bluetooth RC Car Ready!");
}

void loop() {
  if (BT.available()) {
    char cmd = BT.read();
    Serial.println(cmd);

    switch (cmd) {
      // Basic movement
      case 'F': forward(); break;
      case 'B': backward(); break;
      case 'L': left(); break;
      case 'R': right(); break;
      case 'S': stopCar(); break;

      // Diagonal movement
      case 'G': forwardLeft(); break;   // Forward + Left
      case 'I': forwardRight(); break;  // Forward + Right
      case 'H': backwardLeft(); break;  // Backward + Left
      case 'J': backwardRight(); break; // Backward + Right

      // Speed control
      case '1': motorSpeed = 80; break;
      case '2': motorSpeed = 100; break;
      case '3': motorSpeed = 100; break;
      case '4': motorSpeed = 120; break;
      case '5': motorSpeed = 140; break;
      case '6': motorSpeed = 160; break;
      case '7': motorSpeed = 180; break;
      case '8': motorSpeed = 210; break;
      case '9': motorSpeed = 240; break;
      case 'q': motorSpeed = 255; break;
    }
  }
}

// ===== Movement Functions =====

void forward() {
  analogWrite(EnA, motorSpeed);
  analogWrite(EnB, motorSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backward() {
  analogWrite(EnA, motorSpeed);
  analogWrite(EnB, motorSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void left() {
  analogWrite(EnA, motorSpeed);
  analogWrite(EnB, motorSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void right() {
  analogWrite(EnA, motorSpeed);
  analogWrite(EnB, motorSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopCar() {
  analogWrite(EnA, 0);
  analogWrite(EnB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

// ===== Diagonal Movements =====

void forwardLeft() {
  analogWrite(EnA, 0);  // Left motor slower
  analogWrite(EnB, motorSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void forwardRight() {
  analogWrite(EnA, motorSpeed);
  analogWrite(EnB, 0);  // Right motor slower
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backwardLeft() {
  analogWrite(EnA, 0);
  analogWrite(EnB, motorSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void backwardRight() {
  analogWrite(EnA, motorSpeed);
  analogWrite(EnB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
