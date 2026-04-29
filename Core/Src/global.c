#include "main.h"
#include "global.h"
#include "motor.h"
#include "math.h"
#include "stdlib.h"



uint8_t state[4];



int last_error = 0;
int correction = 0;

const int BASE_SPEED = 75;       // 基准速度 0~100%，根据赛道抓地力调整
float Kp = 1.0;                  // 比例系数 (0.3~1.5 之间调整)
float Kd = 0.05;                 // 微分系数 (0.05~0.3)
float Ki = 0.000;                // 积分系数 (先设为 0，长直线偏航再加)
const int DEADBAND = 1;          // 死区：误差绝对值小于此值视为直行，防止微抖
const int LOCK_CORRECTION = 5;  // 全白脱线时的强制转向力度



void caculate_pid(void){

    int error = 0;

    if(state[0]) error += -4;
    if(state[1]) error +=  2;
    if(state[2]) error += -2;
    if(state[3]) error +=  4;

    if(abs(error)<=1) error = 0;

    uint8_t ifall_w = (state[0] == 0) && (state[1] == 0) && (state[2] == 0) && (state[3] == 0);

    if (ifall_w) {
        if (last_error < 0) {
            correction = -LOCK_CORRECTION;
        } else if (last_error > 0) {
            correction = LOCK_CORRECTION;
        }
    } else {
        correction = Kp * error + Kd * (error - last_error) + Ki * error;
        last_error = error;

    }


}













