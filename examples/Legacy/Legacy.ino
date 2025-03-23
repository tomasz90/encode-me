#include <Arduino.h>
#include "Wire.h"
#include "Encoder.h"
#include "EncodersHandler.h"

#define ENCODER_A 23
#define ENCODER_B 30
#define ENCODER_GND 1

Encoder encoder(ENCODER_A, ENCODER_B, ENCODER_GND, IN_PULLUP);
Encoder *encoders[] = {&encoder};
EncodersHandler encoderHandler(encoders, sizeof(encoders) / sizeof(encoders[0]));

auto x = 0;
void add() { x++; Serial.println(x); }
void sub() { x--; Serial.println(x); }

void setup() {
    Serial.begin(115200);
    encoder.setOnCounterClockwise(sub);
    encoder.setOnClockwise(add);
}

void loop() {
    encoderHandler.poll();
    delay(1);
}