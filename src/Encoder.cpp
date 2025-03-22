#include "Encoder.h"

Pin::Pin(byte id, Mode mode) : id(id), mode(mode) {
    pinMode(id, mode);
    invertedState = mode == IN_PULLUP;
    state.lastRawState = RELEASED;
    state.currentState = RELEASED;
    state.lastState = RELEASED;
    state.lastChangeTime = 0;
}

Pin::Pin(byte id, byte lowOrHigh) : id(id), mode(OUT) {
    state.currentState = lowOrHigh;
}

void Pin::initialize() const {
    pinMode(id, mode);
    if (mode == OUT) {
        digitalWrite(id, state.currentState);
    }
}

Encoder::Encoder(byte pinA, byte pinB)
        : pinA(pinA, IN_PULLUP),
          pinB(pinB, IN_PULLUP) {}

// common GND or VCC
Encoder::Encoder(byte pinA, byte pinB, Mode encoderMode)
        : pinA(pinA, encoderMode),
          pinB(pinB, encoderMode) {}

// common ordinary pin
Encoder::Encoder(byte pinA, byte pinB, byte pinCommon, Mode encoderMode)
        : pinA(pinA, encoderMode),
          pinB(pinB, encoderMode) {
    auto lowOrHigh = (encoderMode == INPUT_PULLUP) ? LOW : HIGH;
    this->pinCommon = new Pin(pinCommon, lowOrHigh);
}

void Encoder::setOnClockwise(std::function<void()> behavior) {
    this->onClockwise = std::move(behavior);
}

void Encoder::setOnCounterClockwise(std::function<void()> behavior) {
    this->onCounterClockwise = std::move(behavior);
}
