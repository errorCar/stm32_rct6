//
// Created by 36014 on 2021/5/1.
//

#include "Trace.h"

Trace::Trace(uint8_t l11, uint8_t l21,uint8_t l31, uint8_t l41,
        uint8_t r11,uint8_t r21,uint8_t r31,uint8_t r41,uint8_t mid)
{
    this->l1 = l11;
    this->l2 = l21;
    this->l3 = l31;
    this->l4 = l41;
    
    this->r1 = r11;
    this->r2 = r21;
    this->r3 = r31;
    this->r4 = r41;

    this->core = mid;

    pinMode(l1, INPUT);
    pinMode(l2, INPUT);
    pinMode(l3, INPUT);
    pinMode(l4, INPUT);
    pinMode(r1, INPUT);
    pinMode(r2, INPUT);
    pinMode(r3, INPUT);
    pinMode(r4, INPUT);
    pinMode(core,INPUT);
}
uint8_t Trace::get_scan()
{
    uint8_t scanvalue=0;
	uint8_t l11_ = digitalRead(l1);
	uint8_t l21_ = digitalRead(l2);
	uint8_t l31_ = digitalRead(l3);
	uint8_t l41_ = digitalRead(l4);
    uint8_t r11_ = digitalRead(r1);
	uint8_t r21_ = digitalRead(r2);
	uint8_t r31_ = digitalRead(r3);
	uint8_t r41_ = digitalRead(r4);// 最右的是反的
    scanvalue += l11_ << 7;
    scanvalue += l21_ << 6;
    scanvalue += l31_ << 5;
    scanvalue += l41_ << 4;
    scanvalue += r11_ << 3;
    scanvalue += r21_ << 2;
    scanvalue += r31_ << 1;
    scanvalue += r41_ ;
    return scanvalue;
}
bool Trace::g_core() // core
{
    return digitalRead(core);
}
float Trace::get_state()
{
    /*
        1000 0000 128 0x80
        0100 0000 64  0x40
        0010 0000 32  0x20   
        0001 0000 16  0x10  
        0000 1000 8   0x08
        0000 0100 4   0x04
        0000 0010 2   0x02
        0000 0001 1   0x01
    */
    uint8_t v = get_scan();// 左边传感器检测到 返回负
    if(v == 0xc0)//1100 0000 => v==0xc0
        return -10;// 0110 0000 => 
    if(v & 0x01)
        return 10;
    if(v & 0x40)
        return -7;
    if(v & 0x02)
        return 7;
    if(v & 0x20)
        return -5;
    if(v & 0x04)
        return 5;
    if(v & 0x10)
        return -3;
    if(v & 0x08)
        return 3;

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
