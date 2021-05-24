//
// Created by 36014 on 2021/5/1.
//

#ifndef STM32_RCT6_TRACE_H
#define STM32_RCT6_TRACE_H

#include <Arduino.h>

class Trace
{
public:
    // 循迹灰度传感器 左左 左中 右中 右右
    Trace(uint8_t o1, uint8_t o2,
          uint8_t o3, uint8_t o4,uint8_t m1,uint8_t cc,uint8_t m2);
    bool gll(); // 左左
    bool glc(); // 左中
    bool grc(); // 右中
    bool grr(); // 右右
    bool gl2();
    bool gr2();
    bool g_core();
    // 0 正常 -1 -2 左亮灯 1 2 右亮灯
    float get_state(); // 获取传感器状态

private:
    uint8_t ll, lc, rc, rr,l1,r1,core; //传感器引脚
    uint8_t state;          // 当前状态
};

#endif //STM32_RCT6_TRACE_H
