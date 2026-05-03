#include "main.h"
#include "global.h"
#include "motor.h"
#include "math.h"
#include "stdlib.h"



uint8_t state[4];
volatile uint8_t speed[2];
volatile uint8_t pulse[2]; 

uint8_t cmd[20];
uint8_t start_flag = 0;
uint8_t stop_flag = 0;

volatile uint8_t uart_index = 0;
volatile uint8_t ifrxstart = 0;
volatile uint8_t rxcplt_flag = 0;





int error1, error2;              //误差程度定义
int last_error = 0;              //上次的误差值
int correction = 0;              //转向修正值

const int BASE_SPEED = 75;       // 基准速度 0~100%
float Kp = 1.0;                  // 比例系数 
float Kd = 0.05;                 // 微分系数 
const int DEADBAND = 1;          // 死区：误差绝对值小于此值视为直行，防止微抖
int LOCK_CORRECTION = 5;  // 全白脱线时的强制转向力度



void caculate_pid(uint8_t *state) {

    int error = 0;        //实际误差值，正数表示偏左，负数表示偏右

    if(state[0]) error += -error2;
    if(state[1]) error +=  error1;
    if(state[2]) error += -error1;
    if(state[3]) error +=  error2;

    if(abs(error)<=1) error = 0;

    uint8_t ifall_w = (state[0] == 0) && (state[1] == 0) && (state[2] == 0) && (state[3] == 0);

    if (ifall_w) {
        if (last_error < 0) {
            correction = -LOCK_CORRECTION;
        } else if (last_error > 0) {
            correction = LOCK_CORRECTION;
        }
    } else {
        correction = Kp * error + Kd * (error - last_error);
        last_error = error;

    }


}













