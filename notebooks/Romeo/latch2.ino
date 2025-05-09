#include <ArduinoBLE.h>
#include <Arduino.h>

#define OPEN 2
#define READLATCH 1

BLEService latchService("a2123e5d-93fe-467b-9926-c295b1aea3dc");
BLECharacteristic groupCharacteristic("48e1f5f8-d846-493d-9e6f-db9f5d25c04d", BLERead, 10);
BLECharacteristic openCharacteristic("bf24edf2-2b75-464b-bdbc-8a3aaa4d37ea", BLERead, 1);
BLECharacteristic actionCharacteristic("0ffd4445-fc36-424e-9f45-30d71f849107", BLERead | BLEWrite, 1);

BLEDevice central;

bool true_open = false;
bool want_open = false;

void setup() {
  Serial.begin(115200);
  
  BLE.begin();
  Serial.println("ESP32_Button is ready for connections...");

  groupCharacteristic.writeValue((byte)0x00);
  openCharacteristic.writeValue((byte)0x00);
  actionCharacteristic.writeValue((byte)0x00);
  latchService.addCharacteristic(groupCharacteristic);
  latchService.addCharacteristic(openCharacteristic);  
  latchService.addCharacteristic(actionCharacteristic);
  BLE.addService(latchService);
  BLE.setLocalName("Latch_Display");

  pinMode(OPEN, OUTPUT);
  pinMode(READLATCH, INPUT_PULLUP);

  digitalWrite(OPEN, LOW);

  BLE.setAdvertisedService(latchService);
  BLE.advertise();
  Serial.println("Door Latch Peripheral");
}

void loop() {
  central = BLE.central();
  if (central) {
    Serial.print("Connected to central: ");
    Serial.println(central.address());
    while (central.connected()) {
      if (actionCharacteristic.written()) {
        if (true_open == true) {
          actionCharacteristic.writeValue((byte)0x00);
          digitalWrite(OPEN, LOW);
        } else if (true_open == false) {
          actionCharacteristic.writeValue((byte)0x00);
          digitalWrite(OPEN, HIGH);
        }
      }
      
      Serial.println(digitalRead(READLATCH));
      if (digitalRead(READLATCH) == LOW && true_open == false) {
        Serial.println("low");
        true_open = true;
        openCharacteristic.writeValue((byte)0x01);
      } else if (digitalRead(READLATCH) == HIGH && true_open == true) {
        true_open = false;
        openCharacteristic.writeValue((byte)0x00);
      }
    }
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
  }
}
