#ifndef STM32_RCT6_BUZZER_H
#define STM32_RCT6_BUZZER_H
#include <Arduino.h>
#define BUZZ PA8
class Buzzer
{// duration pin v?
// 检测胶带！！
    private:
        uint8_t pin;
        // uint64_t duration;
    public:
        Buzzer(uint8_t pinn=BUZZ);
        void beep();
        void stop();
};

#endif