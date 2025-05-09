#include <ArduinoBLE.h>
#include <Arduino.h>

#define MODE1 2
#define MODE2 4
#define NFAULT 5
#define PHASE 6
#define NSLEEP 7
#define ENABLE 8
#define VPROPI 9
#define DOORHIGH 10
#define DOORLOW 11

BLEService doorService("806e829d-b6b2-4b3f-9e46-404136d2dca4");
BLECharacteristic groupCharacteristic("065a2802-d86e-4ccc-ba1d-7045d2969efc", BLERead, 10);
BLECharacteristic openCharacteristic("fda06a1a-57c6-48cf-8c02-bc1d0d6cb1f7", BLERead, 1);
BLECharacteristic actionCharacteristic("da78c7be-e86f-4ccd-9825-76a2dc1b86b3", BLERead | BLEWrite, 1);

BLEDevice central;

bool true_open = false;
bool sleep_flag = false;
unsigned long timing = 0;

void setup() {
  Serial.begin(115200);

  BLE.begin();
  Serial.println("ESP32_Button is ready for connections...");

  groupCharacteristic.writeValue((byte)0x00);
  groupCharacteristic.writeValue((byte)0x01);
  openCharacteristic.writeValue((byte)0x00);
  actionCharacteristic.writeValue((byte)0x00);
  doorService.addCharacteristic(groupCharacteristic);
  doorService.addCharacteristic(openCharacteristic);  
  doorService.addCharacteristic(actionCharacteristic);
  BLE.addService(doorService);
  BLE.setLocalName("Door_Display");

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

  pinMode(NFAULT, INPUT_PULLUP);
  pinMode(VPROPI, INPUT_PULLUP);
  pinMode(DOORHIGH, INPUT_PULLUP);
  pinMode(DOORLOW, INPUT_PULLUP);

  BLE.setAdvertisedService(doorService);
  BLE.advertise();
  Serial.println("Door Motor Peripheral");
}

void loop() {
  central = BLE.central();

  if (central) {
    Serial.print("Connected to central: ");
    Serial.println(central.address());

    while (central.connected()) {
      if (actionCharacteristic.written()) {
        if (true_open == true) {
          true_open = false;
          Serial.println("closing");
          actionCharacteristic.writeValue((byte)0x00);
          digitalWrite(NSLEEP, LOW);
          digitalWrite(MODE1, LOW);
          digitalWrite(MODE2, LOW);
          digitalWrite(PHASE, LOW);
          digitalWrite(ENABLE, LOW);
          digitalWrite(PHASE, HIGH);
          digitalWrite(ENABLE, HIGH);
          digitalWrite(NSLEEP, HIGH);
          timing = millis();
          while (millis() - timing < 2250) {
            sleep_flag = !sleep_flag;
            if (millis() - timing > 1750) {
              openCharacteristic.writeValue((byte)0x00);
            }
            if (sleep_flag) {
              digitalWrite(NSLEEP, LOW);
              delay(5);
            } else {
              digitalWrite(NSLEEP, HIGH);
              delay(5);
            }
          }
          digitalWrite(NSLEEP, HIGH);
          digitalWrite(MODE1, HIGH);
          digitalWrite(ENABLE, LOW);
          digitalWrite(PHASE, LOW);
          delay(750);
          digitalWrite(NSLEEP, LOW);
          digitalWrite(MODE1, LOW);
        } else {
          true_open = true;
          Serial.println("opening");
          actionCharacteristic.writeValue((byte)0x00);
          digitalWrite(NSLEEP, LOW);
          digitalWrite(MODE1, LOW);
          digitalWrite(MODE2, LOW);
          digitalWrite(PHASE, LOW);
          digitalWrite(ENABLE, LOW);
          digitalWrite(ENABLE, HIGH);
          digitalWrite(NSLEEP, HIGH);
          timing = millis();
          while (millis() - timing < 2250) {
            sleep_flag = !sleep_flag;
            if (millis() - timing > 500) {
              openCharacteristic.writeValue((byte)0x01);
            }
            if (sleep_flag) {
              digitalWrite(NSLEEP, LOW);
              delay(5);
            } else {
              digitalWrite(NSLEEP, HIGH);
              delay(5);
            }
          }
          digitalWrite(NSLEEP, HIGH);
          digitalWrite(MODE1, HIGH);
          digitalWrite(ENABLE, LOW);
          delay(750);
          digitalWrite(NSLEEP, LOW);
          digitalWrite(MODE1, LOW);
        }
      }
    }
    digitalWrite(NSLEEP, LOW);
    digitalWrite(MODE1, LOW);
    digitalWrite(MODE2, LOW);
    digitalWrite(PHASE, LOW);
    digitalWrite(ENABLE, LOW);
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
  }
}
