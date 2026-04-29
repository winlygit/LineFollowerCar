#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "main.h"

extern uint8_t cmd[20];
extern uint8_t state[4];

extern int error1,error2;
extern int last_error;
extern int correction;

extern const int BASE_SPEED;       // 基准速度 0~100%，根据赛道抓地力调整
extern float Kp;                  // 比例系数 (0.3~1.5 之间调整)
extern float Kd;                 // 微分系数 (0.05~0.3)
extern float Ki;                // 积分系数 (先设为 0，长直线偏航再加)
extern const int DEADBAND;          // 死区：误差绝对值小于此值视为直行，防止微抖
extern const int LOCK_CORRECTION;  // 全白脱线时的强制转向力度


// extern struct speed;









void caculate_pid(void);


#endif 
