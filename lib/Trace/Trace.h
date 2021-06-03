//
// Created by 36014 on 2021/5/1.
//

#ifndef STM32_RCT6_TRACE_H
#define STM32_RCT6_TRACE_H

#include <Arduino.h>

class Trace
{
public:
    // 循迹灰度传感器 
    Trace(uint8_t l11, uint8_t l21,uint8_t l31, uint8_t l41,
        uint8_t r11,uint8_t r21,uint8_t r31,uint8_t r41,uint8_t mid);
    uint8_t get_scan();
    bool g_core();
    // 0 正常 -1 -2 左亮灯 1 2 右亮灯
    float get_state(); // 获取传感器状态

private:
    uint8_t l1,l2,l3,l4, r1,r2,r3,r4,core; //传感器引脚
    uint8_t state;          // 当前状态
    uint8_t scanvalue;
};

#endif //STM32_RCT6_TRACE_H
