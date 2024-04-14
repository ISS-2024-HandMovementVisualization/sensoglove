struct Strip {
  int pin;
  float knownResistor;
};

Strip strips[] = {
  {
    .pin = 32,
    .knownResistor = 1000.0,
  }
};

const int STRIP_NUM = sizeof(strips) / sizeof(Strip);