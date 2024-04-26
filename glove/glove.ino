#include "init_strips.h"

const float BOARD_VOLTAGE = 3.26;
const bool DEBUG = true;
const int FREQUENCY_HZ = 1;
// const int DELAY_MS = 1000 / FREQUENCY_HZ;
const int DELAY_MS = 100;

const char* ssid = "511_A(starion)";
const char* password = "zwykleHaslo";
const char* serverName = "http://192.168.0.145:8080";

float resistances[STRIP_NUM];

float readResistance(Strip const& strip) {
  const float MAX_ANALOG_READ = 4095.0;
  int raw = analogRead(strip.pin);
  float voltageAtSensor = (raw * BOARD_VOLTAGE) / MAX_ANALOG_READ;
  float factor = (BOARD_VOLTAGE / voltageAtSensor) - 1;
  return strip.knownResistor * factor;
}

void setup() {
  Serial.begin(9600);

  for (int i = 0; i < STRIP_NUM; i++) {
    resistances[i] = 0.0;
  }
}

void loop() {
  for (int i = 0; i < STRIP_NUM; i++) {
    resistances[i] = readResistance(strips[i]);
  }

  Serial.printf(">R[%d]:%d", STRIP_NUM, (int)resistances[0]);
  for (int i = 1; i < STRIP_NUM; i++) {
    Serial.printf(", %d", (int)resistances[i]);
  }
  Serial.print("\n");

  delay(DELAY_MS);
}