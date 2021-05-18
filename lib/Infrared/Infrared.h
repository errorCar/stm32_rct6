//
// Created by 36014 on 2021/5/1.
//

#ifndef STM32_RCT6_INFRARED_H
#define STM32_RCT6_INFRARED_H

#include <Arduino.h>
// 红外检测模块
class Infrared
{
    public:
        Infrared(uint8_t pinn);// digitalRead()
        uint8_t get_val();
    private:
        uint8_t pin,val;

};

#endif // STM32_RCT6_DISTANCE_H
