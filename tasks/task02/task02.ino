void initialize() {
  Serial.begin(9600);
  pinMode(18, INPUT);
  attachInterrupt(digitalPinToInterrupt(18), handleInterrupt, HIGH);
}

uint32_t sampleCounter = 0;
uint32_t totalDuration = 0;

constexpr int SAMPLE_LIMIT = 1000;
uint32_t timeDiffs[SAMPLE_LIMIT];

void loop() {
  if (sampleCounter == SAMPLE_LIMIT) {
    noInterrupts();

    float average = totalDuration / (float) sampleCounter;
    float squaredErrorSum = 0;
    for (int idx = 0; idx < SAMPLE_LIMIT; idx++) {
      squaredErrorSum += pow(timeDiffs[idx] - average, 2);
    }

    Serial.print("Average: ");
    Serial.print(average);
    Serial.print(" us, RMS deviation: ");
    Serial.print(sqrt(squaredErrorSum / sampleCounter));
    Serial.println(" us");

    sampleCounter = 0;
    totalDuration = 0;

    interrupts();
  }
}

uint32_t lastTimestamp = 0;
void handleInterrupt() {
  uint32_t currentTime = micros();
  uint32_t interval = currentTime - lastTimestamp;

  timeDiffs[sampleCounter] = interval;
  totalDuration += interval;
  sampleCounter++;

  lastTimestamp = currentTime;
}