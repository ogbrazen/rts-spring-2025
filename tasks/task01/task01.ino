struct PulseConfig {
  uint8_t pin;
  uint32_t interval;
  volatile uint32_t lastTrigger;
  bool level;
};

PulseConfig outputs[] = {
  {3,  10000, 0, LOW},
  {5,   1000, 0, LOW},
  {6,    500, 0, LOW},
  {9,    100, 0, LOW},
  {10,    50, 0, LOW}
};
constexpr uint8_t outputCount = sizeof(outputs) / sizeof(PulseConfig);

void initializePins() {
  for (uint8_t i = 0; i < outputCount; i++) {
    pinMode(outputs[i].pin, OUTPUT);
  }
}

void processOutputs() {
  uint32_t currentMicros = micros();

  for (uint8_t i = 0; i < outputCount; i++) {
    if (currentMicros - outputs[i].lastTrigger >= outputs[i].interval) {
      outputs[i].lastTrigger = currentMicros;
      outputs[i].level = !outputs[i].level;
      digitalWrite(outputs[i].pin, outputs[i].level);
    }
  }
}

void setup() {
  initializePins();
}

void loop() {
  processOutputs();
}