//
// Created by 36014 on 2021/5/1.
//

#include "Trace.h"

Trace::Trace(uint8_t o1, uint8_t o2,
             uint8_t o3, uint8_t o4,uint8_t mid)
{
    this->ll = o1;
    this->lc = o2;
    this->rc = o3;
    this->rr = o4;
    this->core = mid;
    // this->big_l = bl;
    // this->big_r = br;
    pinMode(ll, INPUT);
    pinMode(lc, INPUT);
    pinMode(rc, INPUT);
    pinMode(rr, INPUT);
    pinMode(big_l,INPUT);
    pinMode(big_r,INPUT);
    pinMode(core,INPUT);
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
// bool Trace::gl2() // m1
// {// 设置全部检测到返回 1 
//     return digitalRead(l1);
// }
// bool Trace::gr2() // m2
// {
//     return digitalRead(r1);
// }
// bool Trace::gbl()
// {
//     return digitalRead(big_l);
// }
// bool Trace::gbr()
// {
//     return digitalRead(big_r);
// }
bool Trace::g_core() // core
{
    return digitalRead(core);
}
float Trace::get_state()
{
    // 更改后  一共有5个灯 X   X      X         X     X   X
    //                   gbl gll   glc       grc  grr   gbr
    // float r = 0;
    if(glc())// left 返回负值 左边检测到了往左
        return -2;
    if(grc())// right return +
        return 2;
    if(gll())
        return -5;
    if(grr())//right
        return 5;     
    return 0;
    // return r;
    //! 检测到是 1 !!!!  检测到亮 集成

    //! 实际上是左???   
    // if(gbl())
    //     return -6;
    // if(gbr())
    //     return 6;
   
    // if (gll() && glc() && !grc()) // state 110X 中右转
    //     return -2;
    // if (grr() && grc() && !glc()) // state X011 中左转
    //     return 2;
    // if (glc() && !gll() && !grc()) // state 010X 小右转
    //     return -1.5;
    // if (grc() && !grr() && !glc()) // state X010 小左转
    //     return 1.5;
    // if (gll() && !glc()) // state 10XX 大右转 没有或者说不需要考虑最左边检测到 0XXX
    //     return -4;   //左
    // if (grr() && !grc()) // state XX01 大左转
    //     return 4;
    
}
