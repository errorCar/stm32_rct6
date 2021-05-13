//
// Created by 36014 on 2021/5/2.
//

#ifndef STM32_RCT6_BATTERY_H
#define STM32_RCT6_BATTERY_H
#include <Arduino.h>

#define BAT PB0

class Battery
{
public:
    Battery(uint8_t pin = BAT);
    uint16_t get_bat(); //获取设备电量

private:
    uint8_t bat;
};

#endif //STM32_RCT6_BATTERY_H
