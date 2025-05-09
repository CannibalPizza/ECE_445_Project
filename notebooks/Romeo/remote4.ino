#include <ArduinoBLE.h>
#include <Arduino.h>

#define UP_BUTTON 4
#define ACTION_BUTTON 5
#define DOWN_BUTTON 6
#define PAIR_BUTTON 7
#define LED 8

#define TOP_LEFT 14
#define TOP 9
#define TOP_RIGHT 10
#define MIDDLE 15
#define BOT_LEFT 13
#define BOT 12
#define BOT_RIGHT 11
#define DOT 16

#define doorService "806e829d-b6b2-4b3f-9e46-404136d2dca4"
#define latchService "a2123e5d-93fe-467b-9926-c295b1aea3dc"

struct Button {
  const uint8_t PIN;
  bool on;
};

Button button_up = {UP_BUTTON, false};
Button button_down = {DOWN_BUTTON, false};
Button button_action = {ACTION_BUTTON, false};
Button button_sync = {PAIR_BUTTON, false};

unsigned long timers = 0;
unsigned long actionTimer = 0;
uint8_t door_num = 0;
bool openers[10] = {false, false, false, false, false, false, false, false, false, false};
bool connecter[10] = {false, false, false, false, false, false, false, false, false, false};

BLEDevice peripheral;
BLEDevice latch;
BLEDevice door;
BLECharacteristic doorOpenCharacteristic;
BLECharacteristic doorActionCharacteristic;
BLECharacteristic latchOpenCharacteristic;
BLECharacteristic latchActionCharacteristic;

void ARDUINO_ISR_ATTR isr(void *arg) {
  if (millis() - timers  > 300) {
    Button *s = static_cast<Button *>(arg);
    s->on = true;
    if (button_action.on == true) {
      actionTimer = millis();
    }
  }
}

void hex_display() {
  if (openers[door_num]) {
    digitalWrite(DOT, LOW);
  } else {
    digitalWrite(DOT, HIGH);
  }
  if (door_num == 0) {
    digitalWrite(TOP_LEFT, LOW);
    digitalWrite(TOP, LOW);
    digitalWrite(TOP_RIGHT, LOW);
    digitalWrite(MIDDLE, HIGH);
    digitalWrite(BOT_LEFT, LOW);
    digitalWrite(BOT, LOW);
    digitalWrite(BOT_RIGHT, LOW);
  } else if (door_num == 1) {
    digitalWrite(TOP_LEFT, HIGH);
    digitalWrite(TOP, HIGH);
    digitalWrite(TOP_RIGHT, LOW);
    digitalWrite(MIDDLE, HIGH);
    digitalWrite(BOT_LEFT, HIGH);
    digitalWrite(BOT, HIGH);
    digitalWrite(BOT_RIGHT, LOW);
  } else if (door_num == 2) {
    digitalWrite(TOP_LEFT, HIGH);
    digitalWrite(TOP, LOW);
    digitalWrite(TOP_RIGHT, LOW);
    digitalWrite(MIDDLE, LOW);
    digitalWrite(BOT_LEFT, LOW);
    digitalWrite(BOT, LOW);
    digitalWrite(BOT_RIGHT, HIGH);
  } else if (door_num == 3) {
    digitalWrite(TOP_LEFT, HIGH);
    digitalWrite(TOP, LOW);
    digitalWrite(TOP_RIGHT, LOW);
    digitalWrite(MIDDLE, LOW);
    digitalWrite(BOT_LEFT, HIGH);
    digitalWrite(BOT, LOW);
    digitalWrite(BOT_RIGHT, LOW);
  } else if (door_num == 4) {
    digitalWrite(TOP_LEFT, LOW);
    digitalWrite(TOP, HIGH);
    digitalWrite(TOP_RIGHT, LOW);
    digitalWrite(MIDDLE, LOW);
    digitalWrite(BOT_LEFT, HIGH);
    digitalWrite(BOT, HIGH);
    digitalWrite(BOT_RIGHT, LOW);
  } else if (door_num == 5) {
    digitalWrite(TOP_LEFT, LOW);
    digitalWrite(TOP, LOW);
    digitalWrite(TOP_RIGHT, HIGH);
    digitalWrite(MIDDLE, LOW);
    digitalWrite(BOT_LEFT, HIGH);
    digitalWrite(BOT, LOW);
    digitalWrite(BOT_RIGHT, LOW);
  } else if (door_num == 6) {
    digitalWrite(TOP_LEFT, LOW);
    digitalWrite(TOP, LOW);
    digitalWrite(TOP_RIGHT, HIGH);
    digitalWrite(MIDDLE, LOW);
    digitalWrite(BOT_LEFT, LOW);
    digitalWrite(BOT, LOW);
    digitalWrite(BOT_RIGHT, LOW);
  } else if (door_num == 7) {
    digitalWrite(TOP_LEFT, HIGH);
    digitalWrite(TOP, LOW);
    digitalWrite(TOP_RIGHT, LOW);
    digitalWrite(MIDDLE, HIGH);
    digitalWrite(BOT_LEFT, HIGH);
    digitalWrite(BOT, HIGH);
    digitalWrite(BOT_RIGHT, LOW);
  } else if (door_num == 8) {
    digitalWrite(TOP_LEFT, LOW);
    digitalWrite(TOP, LOW);
    digitalWrite(TOP_RIGHT, LOW);
    digitalWrite(MIDDLE, LOW);
    digitalWrite(BOT_LEFT, LOW);
    digitalWrite(BOT, LOW);
    digitalWrite(BOT_RIGHT, LOW);
  } else {
    digitalWrite(TOP_LEFT, LOW);
    digitalWrite(TOP, LOW);
    digitalWrite(TOP_RIGHT, LOW);
    digitalWrite(MIDDLE, LOW);
    digitalWrite(BOT_LEFT, HIGH);
    digitalWrite(BOT, LOW);
    digitalWrite(BOT_RIGHT, LOW);
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(button_down.PIN, INPUT_PULLUP);
  attachInterruptArg(button_down.PIN, isr, &button_down, FALLING);
  pinMode(button_action.PIN, INPUT_PULLUP);
  attachInterruptArg(button_action.PIN, isr, &button_action, FALLING);
  pinMode(button_sync.PIN, INPUT_PULLUP);
  attachInterruptArg(button_sync.PIN, isr, &button_sync, FALLING);
  pinMode(button_up.PIN, INPUT_PULLUP);
  attachInterruptArg(button_up.PIN, isr, &button_up, FALLING);

  pinMode(LED, OUTPUT);
  pinMode(TOP_LEFT, OUTPUT);
  pinMode(TOP, OUTPUT);
  pinMode(TOP_RIGHT, OUTPUT);
  pinMode(MIDDLE, OUTPUT);
  pinMode(BOT_LEFT, OUTPUT);
  pinMode(BOT, OUTPUT);
  pinMode(BOT_RIGHT, OUTPUT);
  pinMode(DOT, OUTPUT);

  digitalWrite(LED, HIGH);
  digitalWrite(TOP_LEFT, LOW);
  digitalWrite(TOP, LOW);
  digitalWrite(TOP_RIGHT, LOW);
  digitalWrite(MIDDLE, LOW);
  digitalWrite(BOT_LEFT, LOW);
  digitalWrite(BOT, LOW);
  digitalWrite(BOT_RIGHT, LOW);
  digitalWrite(DOT, LOW);

  BLE.begin();
  Serial.println("Starting BLE work!");
  hex_display();
  digitalWrite(LED, LOW);
}

void loop() {
  if (button_sync.on) {
    digitalWrite(LED, HIGH);
    timers = millis();
    button_sync.on = false;
    Serial.println("Button pressed, starting scan...");

    BLE.scanForUuid(doorService, true);

    unsigned long startScan = millis();

    while (millis() - startScan < 3500) {
      peripheral = BLE.available();

      if (peripheral) {
        Serial.print("Found device: ");
        Serial.println(peripheral.address());

        door = peripheral;
        if (door.connect()) {
          Serial.println("Connected");
        } else {
          Serial.println("Failed to connect!");
          break;
        }
        door.discoverAttributes();
        Serial.println("Connected to peripheral 1.");
        doorOpenCharacteristic = door.characteristic("fda06a1a-57c6-48cf-8c02-bc1d0d6cb1f7");
        doorActionCharacteristic = door.characteristic("da78c7be-e86f-4ccd-9825-76a2dc1b86b3");
      }
    }
    BLE.stopScan();

    if (door.connected()) {
      clearconnecters();
      connecter[door_num] = true;
    }

    BLE.scanForUuid(latchService, true);
    startScan = millis();
    while (millis() - startScan < 3500) {
      peripheral = BLE.available();

      if (peripheral) {
        Serial.print("Found device: ");
        Serial.println(peripheral.address());

        latch = peripheral;
        if (latch.connect()) {
          Serial.println("Connected");
        } else {
          Serial.println("Failed to connect!");
          break;
        }
        latch.discoverAttributes();
        Serial.println("Connected to peripheral 1.");
        latchOpenCharacteristic = latch.characteristic("bf24edf2-2b75-464b-bdbc-8a3aaa4d37ea");
        latchActionCharacteristic = latch.characteristic("0ffd4445-fc36-424e-9f45-30d71f849107");
      }
    }
    digitalWrite(LED, LOW);

    BLE.stopScan(); 
    Serial.println("Stopped scan.");
    
    if (door && latch) {
      Serial.print("Found ");
      Serial.print(latch.address());
      Serial.print(" '");
      Serial.print(latch.localName());
      Serial.print("' ");
      Serial.print(latch.advertisedServiceUuid());
      Serial.println();

      if (latch.localName() != "Latch_Display") {
        latch.disconnect();
        Serial.println("Disconnected latch");
      }

      Serial.print("Found ");
      Serial.print(door.address());
      Serial.print(" '");
      Serial.print(door.localName());
      Serial.print("' ");
      Serial.print(door.advertisedServiceUuid());
      Serial.println();

      if (door.localName() != "Door_Display") {
        door.disconnect();
        Serial.println("Disconnected door");
      }
    }

  }

  if (button_up.on == true) {
    Serial.println("up");
    timers = millis();
    door_num = ((door_num + 1) % 10);
    button_up.on = false;
    if (connecter[door_num] == true && door) {
      byte isOpen = false;
      doorOpenCharacteristic.readValue(isOpen);
      openers[door_num] = isOpen;
    }
    hex_display();
  }
  if (button_down.on == true) {
    Serial.println("down");
    timers = millis();
    door_num = ((door_num + 9) % 10);
    button_down.on = false;
    if (connecter[door_num] == true && door) {
      byte isOpen = false;
      doorOpenCharacteristic.readValue(isOpen);
      openers[door_num] = isOpen;
    }
    hex_display();
  }
  if (door && latch) {
    controllies();
  }
}

void controllies() {
  if (millis() - actionTimer > 1000) {
    button_action.on = false;
  }
  if (connecter[door_num] == true && door.connected() && latch.connected()) {
    if (button_action.on == true && openers[door_num] == false) {
      timers = millis();
      button_action.on = false;
      latchActionCharacteristic.writeValue((byte)0x01);
      uint8_t latchopen = 0;
      while(latchopen == 0) {
        Serial.print("here1");
        Serial.println(latchopen);
        latchOpenCharacteristic.readValue(latchopen);
      }
      doorActionCharacteristic.writeValue((byte)0x01);
      uint8_t dooropen = 0;
      while(dooropen == 0) {
        Serial.print("here2");
        Serial.println(dooropen);
        doorOpenCharacteristic.readValue(dooropen);
      }
      openers[door_num] = true;
      hex_display();
      latchActionCharacteristic.writeValue((byte)0x01);
      Serial.println("made it here");
    } else if (button_action.on == true) {
      timers = millis();
      button_action.on = false;
      doorActionCharacteristic.writeValue((byte)0x01);
      uint8_t dooropen = 1;
      while(dooropen == 1) {
        Serial.print("here2");
        Serial.println(dooropen);
        doorOpenCharacteristic.readValue(dooropen);
      }
      openers[door_num] = false;
      hex_display();
    }
  }
}

void clearconnecters() {
  connecter[0] = false;
  connecter[1] = false;
  connecter[2] = false;
  connecter[3] = false;
  connecter[4] = false;
  connecter[5] = false;
  connecter[6] = false;
  connecter[7] = false;
  connecter[8] = false;
  connecter[9] = false;
}
