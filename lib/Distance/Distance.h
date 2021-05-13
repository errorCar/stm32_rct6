//
// Created by 36014 on 2021/5/1.
//

#ifndef STM32_RCT6_DISTANCE_H
#define STM32_RCT6_DISTANCE_H

#include <Arduino.h>
// 蜂鸣器
#define BUZ PA8

class Dis
{
public:
    Dis(uint8_t trig_, uint8_t echo_, uint8_t buz = BUZ);
    int get_dis();                        // 先使用has_obs,返回记录的dis
    bool has_obs(uint8_t threshold = 15); // 测距并判断是否有障碍
    static void beep();
    static void stop_beep();

private:
    uint8_t buz;  // 蜂鸣器引脚
    uint8_t trig; // 超声波触发引脚
    uint8_t echo; // 超声波反馈引脚

    int dis; // 记录测试的距离
};

#endif // STM32_RCT6_DISTANCE_H
