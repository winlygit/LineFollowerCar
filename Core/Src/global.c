#include "main.h"
#include "global.h"
#include "motor.h"
#include "math.h"
#include "stdlib.h"
#include "servo.h"

/*********公共变量*********/


volatile uint8_t speed[2];
volatile uint8_t pulse[2]; 

int speed_L,speed_R;

uint8_t cmd[20];
uint8_t start_flag = 0;
uint8_t stop_flag = 0;
uint8_t cross_flag = 0;

volatile uint8_t uart_index = 0;
volatile uint8_t ifrxstart = 0;
volatile uint8_t rxcplt_flag = 0;

uint8_t value;


int correction = 0;              //转向修正值
int state_ifelse;
const int BASE_SPEED = 63;       // 基准速度 0~100
int LOCK_CORRECTION = 10;  // 全白脱线时的强制转向力度


/**************PID模式参数定义**************/
uint8_t state[4];
int error1 = 1;              //误差程度定义
int error2 = 3;              //误差程度定义
int last_error = 0;              //上次的误差值
float Kp = 2.0;                  // 比例系数 
float Kd = 0.05;                 // 微分系数 
const int DEADBAND = 1;          // 死区：误差绝对值小于此值视为直行，防止微抖


/*****************IF-ELSE模式状态定义*****************/
int state_ifelse;
int cor1 = 1; // 轻微偏差的转向修正值
int cor2 = 3; // 严重偏差的转向修正值
int last_cor = 0; // 上一次的状态




/*PID模式函数*/

void Calculate_pid(uint8_t *state) {

    int error = 0;        //实际误差值，正数表示偏左，负数表示偏右
    

    if(state[0]) error += -error2;
    if(state[1]) error += -error1;
    if(state[2]) error +=  error1;
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

    speed_L = BASE_SPEED + correction;
    speed_R = BASE_SPEED - correction;

}
/*
    修正时，左轮在原基础上加correction，右轮在原基础上减correction
    也就是说：correction大于0时右转回正，correction小于0时左转回正
    急转弯情况单独处理，调用特殊处理函数
*/
void CalculateIfelse(int state_ifelse) {
    switch (state_ifelse) {
        case Normal:{         //正常状态
            correction = 0;
            speed_L = BASE_SPEED;
            speed_R = BASE_SPEED;
            break;
        }
        case Left1:{
            correction = cor1;
            speed_L = BASE_SPEED + correction;
            speed_R = BASE_SPEED - correction;
            break;
        }
        case Right1:{
            correction = -cor1;
            speed_L = BASE_SPEED + correction;
            speed_R = BASE_SPEED - correction;
            break;
        }
        case Left2:{
            correction = cor2;
            speed_L = BASE_SPEED + correction;
            speed_R = BASE_SPEED - correction;
            break;
        }
        case Right2:{
            correction = -cor2;
            speed_L = BASE_SPEED + correction;
            speed_R = BASE_SPEED - correction;
            break;
        }
        case AllWhite:{
            if (last_cor < 0) {
                correction = LOCK_CORRECTION;
            } else if (last_cor > 0) {
                correction = -LOCK_CORRECTION;
            }
            speed_L = BASE_SPEED + correction;
            speed_R = BASE_SPEED - correction;
            break;
        }
        case LeftAcute:{
            // HAL_Delay(ACUTE_DELAY); // 延时等待车子到转弯位置
            correction = cor2 * STRENGTHEN_ACUTE_TURN; // 急转弯加大转向力度
            break;
        }
        case RightAcute:{
            // HAL_Delay(ACUTE_DELAY); // 延时等待车子到转弯位置
            correction = -cor2 * STRENGTHEN_ACUTE_TURN; // 急转弯加大转向力度
            break;
        }
        case Cross:{            //十字路口刷卡
            cross_flag = 1;
            HAL_Delay(ACUTE_DELAY); // 延时等待车子完全进入十字路口
            motor_set(0, 0); // 停车
            cross_deal(); // 十字路口特殊处理函数
            break;
        }
    }
}

void cross_deal(){
    
    correction = 0;
}











