#include <Arduino.h>

#define MODE1 2
#define MODE2 4
#define PHASE 6
#define NSLEEP 7
#define ENABLE 8

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");
  
  Serial.begin(115200);
  Serial.println("ESP32_Button is ready for connections...");

  pinMode(MODE1, OUTPUT);
  pinMode(MODE2, OUTPUT);
  pinMode(PHASE, OUTPUT);
  pinMode(NSLEEP, OUTPUT);
  pinMode(ENABLE, OUTPUT);

  digitalWrite(MODE1, LOW);
  digitalWrite(MODE2, LOW);
  digitalWrite(PHASE, LOW);
  digitalWrite(NSLEEP, LOW);
  digitalWrite(ENABLE, LOW);
}

void loop() {
  digitalWrite(PHASE, HIGH);
  digitalWrite(ENABLE, HIGH);
  digitalWrite(NSLEEP, HIGH);
  delay(2500);

  digitalWrite(MODE1, HIGH);
  digitalWrite(ENABLE, LOW);
  digitalWrite(PHASE, LOW);
  delay(500);

  digitalWrite(NSLEEP, LOW);
  digitalWrite(MODE1, LOW);
  delay(500);

  digitalWrite(ENABLE, HIGH);
  digitalWrite(NSLEEP, HIGH);
  delay(2500);

  digitalWrite(MODE1, HIGH);
  digitalWrite(ENABLE, LOW);
  delay(500);

  digitalWrite(NSLEEP, LOW);
  digitalWrite(MODE1, LOW);
  delay(500);
}
