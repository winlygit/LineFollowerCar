#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "main.h"


#define ACUTE_DELAY 200
#define IFPID 0 // 1使用PID控制，0使用if-else控制
#define STRENGTHEN_ACUTE_TURN 2 // 急转弯转向力度倍数


extern uint8_t cmd[20];
extern volatile uint8_t speed[2];
extern volatile uint8_t pulse[2]; 

extern int speed_L,speed_R;

extern uint8_t state[4];
extern uint8_t start_flag;
extern uint8_t stop_flag;
extern volatile uint8_t uart_index;
extern volatile uint8_t ifrxstart;
extern volatile uint8_t rxcplt_flag;
extern uint8_t cross_flag;

extern uint8_t value;

extern int error1,error2;
extern int last_error;
extern int correction;

extern int state_ifelse;

extern const int BASE_SPEED;       // 基准速度 0~100%，根据赛道抓地力调整
extern float Kp;                  // 比例系数 (0.3~1.5 之间调整)
extern float Kd;                 // 微分系数 (0.05~0.3)
extern float Ki;                // 积分系数 (先设为 0，长直线偏航再加)
extern const int DEADBAND;          // 死区：误差绝对值小于此值视为直行，防止微抖
extern int LOCK_CORRECTION;  // 全白脱线和急转弯时的强制转向力度


// extern struct speed;

typedef enum{
    Normal = 1001,    // 正常状态
    Left1 = 1101,     // 左偏轻微
    Right1 = 1011,    // 右偏轻微
    Left2 = 1110,     // 左偏严重
    Right2 = 0111,    // 右偏严重
    AllWhite = 1111,  // 全白状态
    LeftAcute = 0001, // 左急转弯
    RightAcute = 1000,// 右急转弯
    Cross = 0000,     // 十字路口
}state_t;








void Calculate_pid(uint8_t *state);


#endif 
