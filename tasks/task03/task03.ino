struct Blinker {
  uint8_t pin;
  unsigned long period;
  unsigned long lastToggle;
  bool state;
};

Blinker blinkers[] = {
  {3, 10000, 0, LOW},
  {5, 1000, 0, LOW},
  {6, 500, 0, LOW},
  {9, 100, 0, LOW},
  {10, 50, 0, LOW}
};

constexpr uint8_t blinkerCount = sizeof(blinkers) / sizeof(Blinker);

void configurePins() {
  for (uint8_t i = 0; i < blinkerCount; i++) {
    pinMode(blinkers[i].pin, OUTPUT);
    digitalWrite(blinkers[i].pin, blinkers[i].state);
    blinkers[i].lastToggle = micros();  // initialize all with current time
  }
}

void updateBlinker(Blinker &b, unsigned long currentMicros) {
  if (currentMicros - b.lastToggle >= b.period) {
    b.lastToggle = currentMicros;
    b.state = !b.state;
    digitalWrite(b.pin, b.state);
  }
}

void refreshAll() {
  unsigned long now = micros();
  for (uint8_t i = 0; i < blinkerCount; i++) {
    updateBlinker(blinkers[i], now);
  }
}

void setup() {
  configurePins();
}

void loop() {
  refreshAll();
}