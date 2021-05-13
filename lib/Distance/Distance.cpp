//
// Created by 36014 on 2021/5/1.
//

#include "Distance.h"

Dis::Dis(uint8_t trig_, uint8_t echo_, uint8_t buz_)
{
    // 蜂鸣器
    this->buz = buz_;
    pinMode(buz, OUTPUT);
    digitalWrite(buz, HIGH);
    // 超声波
    this->trig = trig_;
    this->echo = echo_;
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
}

int Dis::get_dis()
{
    return dis;
}

bool Dis::has_obs(uint8_t threshold)
{
    // 触发
    digitalWrite(trig, LOW); // 产生一个10US的高脉冲去触发Trigpin
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    // 反馈
    this->dis = pulseIn(echo, HIGH) / 58; //检测脉冲宽度，并计算出距离  
    if (dis < threshold)                  //小于阈值,存在障碍物
    {
        digitalWrite(buz, LOW); //触发蜂鸣器
        return true;
    }
    // 不存在障碍物
    digitalWrite(buz, HIGH);
    return false;
}

void Dis::beep()
{
    digitalWrite(BUZ, LOW); //触发蜂鸣器
}
void Dis::stop_beep()
{
    digitalWrite(BUZ, HIGH); //触发蜂鸣器
}