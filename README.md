# Encode Me

Library for handling rotary encoders.

### Example:

```c++
#include <Arduino.h>
#include "Wire.h"
#include "Encoder.h"
#include "EncodersHandler.h"

#define ENCODER_A 23
#define ENCODER_B 30
#define ENCODER_GND 1

Encoder *encoder = new Encoder(ENCODER_A, ENCODER_B, ENCODER_GND, IN_PULLUP);
EncodersHandler encodersHandler({encoder});

auto x = 0;

void add() { x++; Serial.println(x); }

void sub() { x--; Serial.println(x); }

void setup() {
    Serial.begin(115200);
    encoder->setOnClockwise(add);
    encoder->setOnCounterClockwise(sub);
}

void loop() {
    encodersHandler.poll();
    delayMicroseconds(200);
}
```
