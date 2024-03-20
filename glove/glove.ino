#include "init_strips.h"

const float BOARD_VOLTAGE = 3.26;
const bool DEBUG = true;
const int FREQUENCY_HZ = 10;
const int DELAY_MS = 1000 / FREQUENCY_HZ;

float resistances[STRIP_NUM];

float readResistance(Strip const& strip) {
  const int MAX_ANALOG_READ = 4095;
  int raw = analogRead(strip.pin);
  float voltageAtSensor = (raw * BOARD_VOLTAGE) / (float)MAX_ANALOG_READ;
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

  if (DEBUG) {
    Serial.printf("R[%d]: %f", STRIP_NUM, resistances[0]);
    for (int i = 1; i < STRIP_NUM; i++) {
      Serial.printf(", %f", resistances[i]);
    }
    Serial.print("\n");
  }

  delay(DELAY_MS);
}