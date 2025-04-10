const int ledPins[] = {3, 5, 6, 9, 10};
const unsigned long togglePeriods[] = {10000, 1000, 500, 100, 50};
volatile bool toggleStates[] = {LOW, LOW, LOW, LOW, LOW};

unsigned long lastFlip0;
unsigned long lastFlip1;
unsigned long lastFlip2;
unsigned long lastFlip3;
unsigned long lastFlip4;

void initialize() {
  for (int j = 0; j < 5; j++) {
    pinMode(ledPins[j], OUTPUT);
  }

  unsigned long startupTime = micros();
  lastFlip0 = startupTime;
  lastFlip1 = startupTime;
  lastFlip2 = startupTime;
  lastFlip3 = startupTime;
  lastFlip4 = startupTime;
}

void loop() {
  unsigned long nowMicros = micros();

  if (nowMicros - lastFlip4 >= togglePeriods[4]) {
    PORTB ^= B00000100;
    lastFlip4 = nowMicros;
  }
  if (nowMicros - lastFlip3 >= togglePeriods[3]) {
    PORTB ^= B00000010;
    lastFlip3 = nowMicros;
  }
  if (nowMicros - lastFlip2 >= togglePeriods[2]) {
    PORTD ^= B01000000;
    lastFlip2 = nowMicros;
  }
  if (nowMicros - lastFlip1 >= togglePeriods[1]) {
    PORTD ^= B00100000;
    lastFlip1 = nowMicros;
  }
  if (nowMicros - lastFlip0 >= togglePeriods[0]) {
    PORTD ^= B00001000;
    lastFlip0 = nowMicros;
  }
}

void setup() {
  initialize();
}