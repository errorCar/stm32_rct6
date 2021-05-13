//
// Created by 36014 on 2021/5/1.
//

#include "Motor.h"

long cnt = 0; // 霍尔测速用计数器

Motor::Motor(uint8_t pwm, uint8_t ain, uint8_t bin, uint8_t BA, uint8_t BB)
{
    this->pwm = pwm;
    this->ain = ain;
    this->bin = bin;
    this->a = BA;
    this->b = BB;

    pinMode(ain, OUTPUT);
    pinMode(bin, OUTPUT);
    pinMode(pwm, OUTPUT);
    pinMode(a, INPUT);
    pinMode(b, INPUT);
}
inline void count() // 内联函数
{
    cnt++;
}

float Motor::speed()
{
    cnt = 0;
    unsigned long t1 = millis();       //获取当前时间(毫秒)
    attachInterrupt(a, count, CHANGE); // 绑定a下降沿
    attachInterrupt(b, count, CHANGE); // 绑定b下降沿
    delay(10);
    detachInterrupt(a);
    detachInterrupt(b);
    return cnt / (millis() - t1 / 1.0);
}

void Motor::forward(int16_t speed)
{
    if (speed < 0)
        backward(-speed);
    else
    {
        // 前进
        digitalWrite(ain, LOW);
        digitalWrite(bin, HIGH);
        speed = (speed > MAX_SPEED) ? MAX_SPEED : speed;
        analogWrite(pwm, speed);
    }
}
void Motor::backward(int16_t speed)
{
    if (speed < 0)
        forward(-speed);
    else
    {
        // 后退
        digitalWrite(ain, HIGH);
        digitalWrite(bin, LOW);
        speed = (speed > MAX_SPEED) ? MAX_SPEED : speed;
        analogWrite(pwm, speed);
    }
}
void Motor::stop()
{
    digitalWrite(ain, LOW);
    digitalWrite(bin, LOW);
    analogWrite(pwm, 255);
}