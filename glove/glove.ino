#include "init_strips.h"

const float BOARD_VOLTAGE = 3.26;
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
  // Serial.println(STRIP_NUM);
  for (int i = 0; i < STRIP_NUM; i++) {
    resistances[i] = readResistance(strips[i]);
  }

  Serial.printf("R: %f\n", resistances[0]);
  delay(50);
}