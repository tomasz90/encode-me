#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

#if defined(USE_LEGACY) || defined(ARDUINO_ARCH_AVR)
#define LEGACY 1
#else
#define LEGACY 0
#include <functional>
#endif

#define RELEASED 0
#define PRESSED 1

enum Mode {
    IN_PULLUP = INPUT_PULLUP,
#ifdef INPUT_PULLDOWN
    IN_PULLDOWN = INPUT_PULLDOWN,
#else
    IN_PULLDOWN = INPUT,
#endif
    OUT = OUTPUT,
};

struct Pin {
    Pin(byte id, Mode mode) : id(id), mode(mode) {}
    byte id;
    Mode mode;
    bool initialized = false;

    virtual void initialize();
};

struct PinInput : Pin {

    PinInput(byte id, Mode mode);
    bool invertedState;

    struct {
        bool lastRawState;
        bool currentState;
        bool lastState;
        unsigned long lastChangeTime;
    } state;

    void initialize() override;
};

struct PinOutput : Pin {

    PinOutput(byte id, bool lowOrHigh);
    bool constantState;

    void initialize() override;
};

struct Encoder {
    // common GND
    Encoder(byte pinA, byte pinB);

    // common GND or VCC
    Encoder(byte pinA, byte pinB, Mode encoderMode);

    // common ordinary pin
    Encoder(byte pinA, byte pinB, byte pinCommon, Mode encoderMode);

    PinInput pinA;
    PinInput pinB;
    PinOutput *pinCommon = nullptr;

    volatile long position = 0;
    int accumulated = 0;

#if !LEGACY
    std::function<void()> onClockwise = nullptr;
    std::function<void()> onCounterClockwise = nullptr;
    void setOnClockwise(std::function<void()> behavior);
    void setOnCounterClockwise(std::function<void()> behavior);
#else
    void (*onClockwise)() = nullptr;
    void (*onCounterClockwise)() = nullptr;
    void setOnClockwise(void (*behavior)());
    void setOnCounterClockwise(void (*behavior)());
#endif

private:
    void initialize();
};

#endif //ENCODER_H
