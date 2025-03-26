#include "Encoder.h"

PinInput::PinInput(byte id, Mode mode) : Pin(id, mode) {
    invertedState = mode == IN_PULLUP;
    state.lastRawState = RELEASED;
    state.currentState = RELEASED;
    state.lastState = RELEASED;
    state.lastChangeTime = 0;
}

PinOutput::PinOutput(byte id, bool lowOrHigh) : Pin(id, OUT) {
    constantState = lowOrHigh;
}

void PinInput::initialize() {
    if (initialized) return;
    initialized = true;
    pinMode(id, mode);
}

void PinOutput::initialize() {
    if (initialized) return;
    initialized = true;
    pinMode(id, mode);
    digitalWrite(id, constantState);
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
    auto lowOrHigh = (encoderMode == IN_PULLUP) ? LOW : HIGH;
    this->pinCommon = new PinOutput(pinCommon, lowOrHigh);
}

void Encoder::initialize() {
    pinA.initialize();
    pinB.initialize();
    if (pinCommon) pinCommon->initialize();
}

#if !LEGACY
void Encoder::setOnClockwise(std::function<void()> behavior) {
    initialize();
    this->onClockwise = std::move(behavior);
}

void Encoder::setOnCounterClockwise(std::function<void()> behavior) {
    initialize();
    this->onCounterClockwise = std::move(behavior);
}
#else
void Encoder::setOnClockwise(void (*behavior)()) {
    initialize();
    this->onClockwise = behavior;
}
void Encoder::setOnCounterClockwise(void (*behavior)()) {
    initialize();
    this->onCounterClockwise = behavior;
}
#endif
