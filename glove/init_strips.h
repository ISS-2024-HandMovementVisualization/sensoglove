struct Strip {
  int pin;
  float knownResistor;
};

Strip strips[] = {
  {
    .pin = 32,
    .knownResistor = 1000.0,
  },
  {
    .pin = 33,
    .knownResistor = 1000.0,
  },
  {
    .pin = 25,
    .knownResistor = 1000.0,
  },
  {
    .pin = 26,
    .knownResistor = 1000.0,
  }
};

const int STRIP_NUM = sizeof(strips) / sizeof(Strip);