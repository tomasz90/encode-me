#ifndef ENCODERHANDLER_H
#define ENCODERHANDLER_H

#include "Encoder.h"
#include <vector>

#if defined(ESP32) || defined(NRF52840_XXAA) || defined(USE_POLL_ONCE)
#define IS_FREE_RTOS_SUPPORTED 1
#else
#define IS_FREE_RTOS_SUPPORTED 0
#endif

// Quadrature decoding table (4x4 state machine)
constexpr static int8_t decoder[4][4] = {
        {  0, +1, -1,  0 },
        { -1,  0,  0, +1 },
        { +1,  0,  0, -1 },
        {  0, -1, +1,  0 }
};

class EncodersHandler {
public:
    EncodersHandler(std::initializer_list<Encoder *> encoders);
    void poll();

#if IS_FREE_RTOS_SUPPORTED
    void pollOnce(int pollInterval = 1);
    void pollStop();
#endif

    void setDebounceTime(unsigned long debounceTimeUs);

private:
    unsigned long debounceTimeUs = 1000;
    std::vector<Encoder *> encoders;

#if IS_FREE_RTOS_SUPPORTED
    TimerHandle_t timer;
#endif

    void initializeEncodersPins();
    void pollEncoderState(Encoder *encoder) const;
    void pollPinState(Pin *pin) const;
    void processEncoderState(Encoder *encoder) const;
    void resetState(Encoder *encoder) const;
};

#endif //ENCODERHANDLER_H
