#ifndef ENCODERHANDLER_H
#define ENCODERHANDLER_H

#include "Encoder.h"
#include <vector>

// Quadrature decoding table (4x4 state machine)
constexpr static int8_t decoder[4][4] = {
        {  0, +1, -1,  0 },   // Previous 00
        { -1,  0,  0, +1 },   // Previous 01
        { +1,  0,  0, -1 },   // Previous 10
        {  0, -1, +1,  0 }    // Previous 11
};

class EncodersHandler {
public:
    EncodersHandler(std::initializer_list<Encoder *> encoders);
    void poll();
    void setDebounceTime(unsigned long debounceTimeUs);

private:
    unsigned long debounceTimeUs = 1000;
    std::vector<Encoder *> encoders;
    bool initializedEncoders = false;

    void initializeEncodersPins();
    void pollEncoderState(Encoder *encoder) const;
    void pollPinState(Pin *pin) const;
    void processEncoderState(Encoder *encoder) const;
    void resetState(Encoder *encoder) const;
};

#endif //ENCODERHANDLER_H
