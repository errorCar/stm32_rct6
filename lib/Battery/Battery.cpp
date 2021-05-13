//
// Created by 36014 on 2021/5/2.
//

#include "Battery.h"

Battery::Battery(uint8_t pin)
{
    this->bat = pin;
}

uint16_t Battery::get_bat()
{
    uint16_t val = analogRead(bat); // 5v / 1024 读取电压数据
    return (val - 190);             // 换算成百分比
}