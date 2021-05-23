//
// Created by 36014 on 2021/5/1.
//

#include "Trace.h"

Trace::Trace(uint8_t o1, uint8_t o2,
             uint8_t o3, uint8_t o4)
{
    this->ll = o1;
    this->lc = o2;
    this->rc = o3;
    this->rr = o4;
    pinMode(ll, INPUT);
    pinMode(lc, INPUT);
    pinMode(rc, INPUT);
    pinMode(rr, INPUT);
}
bool Trace::gll() // 左左传感器
{
    return digitalRead(ll);
}
bool Trace::glc() // 左中传感器
{
    return digitalRead(lc);
}
bool Trace::grc() // 右中传感器
{
    return digitalRead(rc);
}
bool Trace::grr() // 右右传感器
{
    return digitalRead(rr);
}
float Trace::get_state()
{
    // if (gll() && glc() && grc() && grr())
    //     return 100;
    // if (gll() && glc() && grc() && !grr())
    //     return 99;
    // if (!gll() && glc() && grc() && grr())
    //     return 99;

    if (gll() && !glc()) // state 10XX 大右转
        return -5.5;
    if (grr() && !grc()) // state XX01 大左转
        return 5.5;
    if (gll() && glc() && !grc()) // state 110X 中右转
        return -2;
    if (grr() && grc() && !glc()) // state X011 中左转
        return 2;
    if (glc() && !gll() && !grc()) // state 010X 小右转
        return -1;
    if (grc() && !grr() && !glc()) // state X010 小左转
        return 1;
    // left core core|| right core core || left core core right 
    
    return 0;
}
