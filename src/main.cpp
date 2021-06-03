#include <Wire.h>
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// 自定义头文件
#include <Distance.h> // 超声波测距
#include <Trace.h>    // 循迹
#include <Motor.h>    // 电机控制
#include <Battery.h>  // 电量检测
#include <Infrared.h>

// 屏幕
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// *循迹检测
#define L1 PC8
#define L2 PA8
#define L3 PC9
#define L4 PA10

#define R1 PC6
#define R2 PC7
#define R3 PB14
#define R4 PB15

#define CORE PC9

Trace t(L1,L2,L3,L4,R1,R2,R3,R4,CORE); // 初始化循迹传感器模块

// *左电机 电机检测
#define AL PA2
#define BL PA3
// *右电机 电机检测
#define AR PA4
#define BR PA12
// *左电机
#define PWML PC1  // PWM调速
#define AINL PB10 // 方向控制
#define BINL PB11 // A-B+ 前进 A+B- 后退
// *右电机
#define PWMR PC0
#define AINR PB0
#define BINR PB1
// #define DURATION 1000
Motor lm(PWML, AINL, BINL, AL, BL); // 初始化左侧电机
Motor rm(PWMR, AINR, BINR, AR, BR); // 初始化右侧电机

Battery bat; // 初始化电池对象

// *初始化速度参数 范围 0 ~ 255
#define SPEED_VALUE 35
int16_t speedl = SPEED_VALUE;
int16_t speedr = SPEED_VALUE * 1.07;  // 右电机补偿
float Kp = 4, Ki = 0, Kd = 0; // PID参数    8 0.02 35  6 0.01 20 V==20
const float MAXI = 30;           // 积分最大值
float P = 0, I = 0, D = 0;       // 比例, 积分, 微分
float pid_val = 0;               // PID修正值
float error = 0, pre_error = 0;  // 误差值, 前误差, 误差积分
unsigned long pre_time=0;
bool is_straight=false;
int count_0 = 0;
int core_val = 0,pre_core_val=0;
void calc_pid(); // 计算PID函数


void setup()
{
  // *屏幕初始化
  // Serial.begin(9600);
  // Serial.println("ultrasonic sensor");
  // while (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  // {
  //   Serial.println("SSD1306 allocation failed");
  //   delay(1000);
  // }
  // delay(1000);
  // display.clearDisplay();
  // display.setTextColor(WHITE);
  // attachInterrupt(PB1, num_add, FALLING);
  // 没有线返回 0 
  
}
void loop()
{
  display.clearDisplay();
  // !修正部分
  error = t.get_state(); // 采集误差  5 2 1
  
  calc_pid();
  lm.forward(speedl + pid_val);
  rm.forward(speedr - pid_val);

  // !显示部分
  // *显示时间
  // display.setCursor(0, 0);
  // display.print("TIME:");
  // display.print(millis() / 1000);
  // display.println("s");
  // // *显示里程数
  // display.print("RUN:");
  // display.print(num * (21.2 / 20));
  // display.println("mm");


  // *pid参数+优化
  // display.print("PID-VAL:");
  // display.println(pid_val);
  // display.print("error =>");
  // display.println(error);

  // display.display();
  // delay(100);
}

void calc_pid()
{
  P = error;             // 比例
  I += error * 0.2;      // 积分
  D = error - pre_error; // 微分
  pre_error = error;

  I = (I < -MAXI) ? -MAXI : I;
  I = (I > MAXI) ? MAXI : I;
  pid_val = (Kp * P) + (Ki * I) + (Kd * D);
}

