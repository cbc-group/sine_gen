#include <DueTimer.h>

#include "sine.h"

const uint32_t PERIOD_MS = 10;
const uint32_t UPDATE_US = 100;
const uint32_t SAMPLE_STEP = 42949600;

volatile uint32_t accumulator = 0;

void updateDac() {
  // 32b = 11b lookup + 16b interp + 5b ignored
  uint32_t acc = accumulator >> 5;
  uint32_t fraction = acc | 0xFFFF;
  uint32_t address = acc >> 16;

  uint32_t lo = address, hi = address+1;

  uint16_t vlo = WAVEFORM[lo], vhi = WAVEFORM[hi];
  float delta = ((float)vhi - (float)vlo) * (0.000015258789 * (float)fraction);
  uint16_t out = vlo + (uint16_t)floor(delta);
  analogWrite(DAC1, vlo);

  accumulator += SAMPLE_STEP;
}

void setup() {
  Serial.begin(57600);
  Serial.println(SAMPLE_STEP);
  
  analogWriteResolution(RESOLUTION);
  // 100us update rate
  Timer2.attachInterrupt(updateDac).setPeriod(UPDATE_US);

  // RUN!
  Timer2.start();
}

void loop() {
  //Serial.println(SAMPLE_STEP);
  // fire the timer
  //Timer2.start();
  // use infinite loop to prevent jitter from serial
  /*
  for (int i = 0; i < 2048; i++) {
    analogWrite(DAC0, i);
    analogWrite(DAC1, i);
    delay(1);
  }
  */
}
