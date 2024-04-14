#include "init_strips.h"
#include <WiFi.h>
#include <HTTPClient.h>

const float BOARD_VOLTAGE = 3.26;
const bool DEBUG = true;
const int FREQUENCY_HZ = 1;
// const int DELAY_MS = 1000 / FREQUENCY_HZ;
const int DELAY_MS = 1000;

const char* ssid = "511_A(starion)";
const char* password = "zwykleHaslo";
const char* serverName = "http://192.168.0.145:8080";

float resistances[STRIP_NUM];

float readResistance(Strip const& strip) {
  const float MAX_ANALOG_READ = 4095.0;
  int raw = analogRead(strip.pin);
  Serial.print("raw ");
  Serial.println(raw);
  float voltageAtSensor = (raw * BOARD_VOLTAGE) / MAX_ANALOG_READ;
  float factor = (BOARD_VOLTAGE / voltageAtSensor) - 1;
  return strip.knownResistor * factor;
}

void setup() {
  Serial.begin(9600);
  // Serial.println("Connecting...");
  // WiFi.begin(ssid, password);
  // while(Wisrintln(WiFi.localIP());

  for (int i = 0; i < STRIP_NUM; i++) {
    resistances[i] = 0.0;
  }
}

void loop() {
  for (int i = 0; i < STRIP_NUM; i++) {
    resistances[i] = readResistance(strips[i]);
  }

  if (DEBUG) {
    Serial.printf("R[%d]: %d", STRIP_NUM, (int)resistances[0]);
    for (int i = 1; i < STRIP_NUM; i++) {
      Serial.printf(", %d", (int)resistances[i]);
    }
    Serial.print("\n");
  }

  // if (WiFi.status() == WL_CONNECTED) {
  //   WiFiClient client;
  //   HTTPClient http;

  //   http.begin(client, serverName);
  //   http.addHeader("Content-Type", "text/plain");



  //   String httpRequestData = "";
  //   int httpResponseCode = http.POST("dupa");

  //   Serial.print("HTTP Response code: ");
  //   Serial.println(httpResponseCode);
  //   http.end();
  // }

  delay(DELAY_MS);
}

// curl -X POST -H "Content-Type: application/json" -H "Content-Length: 0" http://192.168.0.145:8080
// curl -X POST -H "Content-Type: application/json" -H "Content-Length: 0" http://192.168.0.145:8080
// curl -X POST -H "Content-Type: application/json" -d "number1=1&number2=2&number3=3&number4=4" http://192.168.0.145:8080