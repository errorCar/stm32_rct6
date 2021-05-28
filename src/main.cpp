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
// *超声波引脚
// #define DL_TRIG PC2
// #define DL_ECHO PC3
// #define DC_TRIG PC0
// #define DC_ECHO PC1
// #define DR_TRIG PC14
// #define DR_ECHO PC15
// Dis dl(DL_TRIG, DL_ECHO); // 左超声波
// Dis dc(DC_TRIG, DC_ECHO); // 中超声波
// Dis dr(DR_TRIG, DR_ECHO); // 右超声波

// *循迹检测
#define LL PA15
#define LC PC10
#define RC PC11
#define RR PC12

#define CORE PC9
#define BIG_L PC13
#define BIG_R PC15
Trace t(LL, LC, RC, RR,CORE); // 初始化循迹传感器模块

// *左电机 电机检测
#define AL PA2
#define BL PA3
// *右电机 电机检测
#define AR PA4
#define BR PA5
// *左电机
#define PWML PB8  // PWM调速
#define AINL PB10 // 方向控制
#define BINL PB11 // A-B+ 前进 A+B- 后退
// *右电机
#define PWMR PB9
#define AINR PB12
#define BINR PB13
// *左右红外检测
#define INFRA_L PC0
#define INFRA_R PC1
// *big turn value
#define BIG_TURN_V  5 
#define TURN_V 3
// #define DURATION 1000
Motor lm(PWML, AINL, BINL, AL, BL); // 初始化左侧电机
Motor rm(PWMR, AINR, BINR, AR, BR); // 初始化右侧电机
Infrared Inf_l(INFRA_L);// 红外模块_左
Infrared Inf_r(INFRA_R);// 红外模块_右
Battery bat; // 初始化电池对象

// *初始化速度参数 范围 0 ~ 255
#define SPEED_VALUE 30
int16_t speedl = SPEED_VALUE;
int16_t speedr = SPEED_VALUE * 1.07;  // 右电机补偿
float Kp = 6, Ki = 0.01, Kd = 10; // PID参数    8 0.02 35  6 0.01 20 V==20
const float MAXI = 30;           // 积分最大值
float P = 0, I = 0, D = 0;       // 比例, 积分, 微分
float pid_val = 0;               // PID修正值
float error = 0, pre_error = 0;  // 误差值, 前误差, 误差积分
unsigned long pre_time=0,begin_slowtime=0;
bool is_straight=false;
int count_0 = 0;
int core_val = 0,pre_core_val=0;
void calc_pid(); // 计算PID函数

int num = 0,state_straight=1;
void num_add()
{
   num++;
}
void count_zero()
{
  count_0++;
}
void setup()
{
  // *屏幕初始化
  Serial.begin(9600);
  Serial.println("ultrasonic sensor");
  while (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println("SSD1306 allocation failed");
    delay(1000);
  }
  delay(1000);
  display.clearDisplay();
  display.setTextColor(WHITE);
  attachInterrupt(PB1, num_add, FALLING);
  // 没有线返回 0 
  
}
// PA15
// PC10
// PC11
// PC12
void loop()
{
  display.clearDisplay();
  // !修正部分
  error = t.get_state(); // 采集误差  5 2 1
  // // 加上角度!!!!
  // 检测 0 
  core_val = digitalRead(CORE);
  // if(core_val != pre_core_val)
  // {
  //   count_0 ++;
  // }
  count_0 += core_val^pre_core_val; // 相同为0,不同为1
  pre_core_val = core_val;
  if(count_0 > 5 && state_straight ==1)// 0 超过 7个 (或者更多) 直线状态
  {// 进入某种state,使得一段时间(2s)不会再执行清零稳定保持减速),而不是在2s内随机清零 
    state_straight = 0;
    begin_slowtime = millis();
    speedl = SPEED_VALUE * 0.5;
    speedr = speedl * 1.07;
    // 进入 0 state 时才开始计时 3 => slow down 3s
    
  }
  else if(state_straight == 1)// 直线状态速度恢复正常
  {
    speedl = SPEED_VALUE;
    speedr = speedl * 1.07;
  }

  if(state_straight==0  && millis()-begin_slowtime>3000)
  {// 弯道状态开始时才会执行此行 && 弯道state 已经经过了3s 以上
    state_straight = 1;// return to straight_state
  }
  if(millis()-pre_time > 2000)
  {
    pre_time = millis();
    count_0 = 0;
  }
  calc_pid();
  lm.forward(speedl + pid_val);
  rm.forward(speedr - pid_val);
  // !显示部分
  // *显示时间
  display.setCursor(0, 0);
  display.print("TIME:");
  display.print(millis() / 1000);
  display.println("s");
  // *显示里程数
  display.print("RUN:");
  display.print(num * (21.2 / 20));
  display.println("mm");

  // *显示速度信息
  // display.print("LMS:"); // 左轮速度
  // display.print(lm.speed());
  // display.print(" RMS:"); // 右轮速度
  // display.println(rm.speed());

  // *pid参数+优化
  display.print("PID-VAL:");
  display.println(pid_val);
  display.print("error =>");
  display.println(error);
  //!
  display.print("num-core = ");// 打印中间的状态!!
  display.print(count_0);
  
  // *显示电量
  // display.print("BAT:");
  // display.print(bat.get_bat());
  // display.println("%");

  // 显示返回值!!
  // display.print("l1 = ");
  // display.print(digitalRead(L2));
  // display.print("r1 = ");
  // display.println(digitalRead(R2));
  // display.print(digitalRead(PA15));
  // display.print(digitalRead(PC10));
  // display.print(digitalRead(PC11));
  // display.print(digitalRead(PC12));
// PA15
// #define LC PC10
// #define RC PC11
// #define RR PC12

  display.display();
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

