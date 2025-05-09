#include <Arduino.h>

#define LATCH 2

bool flag = false;
static uint32_t lastMillis = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");
  pinMode(LATCH, OUTPUT);
}

void loop() {
  if (!flag) {
    digitalWrite(LATCH, HIGH);
  } else {
    digitalWrite(LATCH, LOW);
  }
  if (millis() - lastMillis > 5000) {
    flag = !flag;
    lastMillis = millis();
  }
}
