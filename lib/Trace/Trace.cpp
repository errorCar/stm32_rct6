//
// Created by 36014 on 2021/5/1.
//

#include "Trace.h"

Trace::Trace(uint8_t o1, uint8_t o2,
             uint8_t o3, uint8_t o4,uint8_t m1,uint8_t cc,uint8_t m2)
{
    this->ll = o1;
    this->lc = o2;
    this->rc = o3;
    this->rr = o4;
    this->l1 = m1;
    this->r1 = m2;
    this->core = cc;
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
bool Trace::gl2() // 右右传感器
{
    return digitalRead(l1);
}
bool Trace::gr2() // 右右传感器
{
    return digitalRead(r1);
}
bool Trace::g_core()
{
    return digitalRead(core);
}
float Trace::get_state()
{
    // if (gll() && glc() && grc() && grr())
    //     return 100;
    // if (gll() && glc() && grc() && !grr())
    //     return 99;
    // if (!gll() && glc() && grc() && grr())
    //     return 99;

    // !如果更密集是否需要更多组合的判断???
    // 更改后  一共有5个灯 X    X   X   X   X   X   X
    //                   gll  gl2  glc core grc gr2  grr
    // 先定义6种状态,后面can define more
    // now haven't used g_core() ——> the core
    if(gll() && !gl2()) // 10X X XXX  big right   没有检测到返回1
        return -3;   // 最外面没有但是 次外有
    if(grr() && !gr2()) // XXX X X01  big left
        return 3;

    if(!gl2())  // X0X X XXX mid right  (如果l2已经检测不到了 ll )
        return -2;
    if(!gr2())  // XXX X X0X mid left 
        return 2;

    if(!glc()) // XX0 X XXX right
        return -1;
    if(!grc()) // XXX X 0XX left
        return 1;
    
    //! 检测到是 0 ?  检测到亮 集成
    //! 
    // if (gll() && !glc()) // state 10XX 大右转 没有或者说不需要考虑最左边检测到 0XXX
    //     return -5.5;
    // if (grr() && !grc()) // state XX01 大左转
    //     return 5.5;
    // if (gll() && glc() && !grc()) // state 110X 中右转
    //     return -2;
    // if (grr() && grc() && !glc()) // state X011 中左转
    //     return 2;
    // if (glc() && !gll() && !grc()) // state 010X 小右转
    //     return -1;
    // if (grc() && !grr() && !glc()) // state X010 小左转
    //     return 1;
    // left core core|| right core core || left core core right 
    
    return 0;
}
