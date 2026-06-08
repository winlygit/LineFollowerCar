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
const int BASE_SPEED = 70;       // 基准速度 0~100
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
int cor1 = -6; // 轻微偏差的转向修正值
int cor2 = -12; // 严重偏差的转向修正值
int last_cor = 0; // 上一次的状态

float k = 1.2; 




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

    speed_L = BASE_SPEED + k*correction;
    speed_R = BASE_SPEED - correction;

}
/*
    修正时，左轮在原基础上加correction，右轮在原基础上减correction
    也就是说：correction大于0时右转回正，correction小于0时左转回正
    急转弯情况单独处理，调用特殊处理函数
*/

void cross_deal(){
    
    HAL_Delay(300);
    motor_set(0,0);  //停车一下
    set_angle(90); 
    HAL_Delay(3000);
    set_angle(0);
    HAL_Delay(3000);
    cross_flag = 0;
}

void CalculateIfelse() {
    if(X1==0&&X3==0&&X2==1&&X4==1) motor_set(600,600);
		
	if(X1==1&&X3==0&&X2==1&&X4==1) motor_set(680,520);   //小右转
		
	if(X1==0&&X3==1&&X2==1&&X4==1) motor_set(520,680);   //小左转
	
	if(X2==1&&X1==1&&X3==1&&X4==0) motor_set(880,320);   //大右转
		
	if(X2==0&&X1==1&&X3==1&&X4==1) motor_set(320,880);   //大左转
		
	
	//拐大角度弯
	if((X1==1&&X2==1&&X3==0&&X4==0)||(X1==0&&X2==1&&X3==0&&X4==0))
	{
        HAL_Delay(40);
        if(X2==0&&X1==0&&X3==0&&X4==0){
            cross_deal();
        }
        
        if((X1==1&&X2==1&&X3==0&&X4==0)||(X1==0&&X2==1&&X3==0&&X4==0)){
            HAL_Delay(300);
            motor_set(0,0);  //停车一下
            HAL_Delay(500);
            do
            {
                motor_set(500,-500);  //原地右转
            }while(X1==0);
        }
        
	}
	
	//拐大角度弯
	if((X2==0&&X1==0&&X3==1&&X4==1)||(X2==0&&X1==0&&X3==0&&X4==1))
	{
        HAL_Delay(40);
        if(X2==0&&X1==0&&X3==0&&X4==0){
            cross_deal();
        }
        
        if((X2==0&&X1==0&&X3==1&&X4==1)||(X2==0&&X1==0&&X3==0&&X4==1)){
            HAL_Delay(300);
            motor_set(0,0);  //停车一下
            HAL_Delay(500);
            do
            {
                motor_set(-500,500);  //原地左转
            }while(X3==0);
        }
        
        
	}
    
    

}













