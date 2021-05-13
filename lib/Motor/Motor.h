//
// Created by 36014 on 2021/5/1.
//

#ifndef STM32_RCT6_MOTOR_H
#define STM32_RCT6_MOTOR_H

#include <Arduino.h>
#define MAX_SPEED 60

class Motor
{
public:
    Motor(uint8_t pwm, uint8_t ain, uint8_t bin,
          uint8_t BA, uint8_t BB);
    void forward(int16_t speed = 16);  // 前进
    void backward(int16_t speed = 16); // 后退
    void stop();                       // 刹车
    float speed();                     // 电机的速度
    float route();                     // 返回小行驶的距离

private:
    // a,b相测速
    uint8_t a;
    uint8_t b;
    // 电机控制
    uint8_t ain;
    uint8_t bin;
    uint8_t pwm;
    // 行驶距离
    uint64_t route_cnt;
};

#endif //STM32_RCT6_MOTOR_H
