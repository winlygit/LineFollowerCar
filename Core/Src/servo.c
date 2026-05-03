#include "main.h"
#include "global.h"
#include "servo.h"

void servo_init(void){

    HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_4);
    __HAL_TIM_SetCompare(&htim4,TIM_CHANNEL_4,0);

}

void set_angle(uint8_t angle){
    float add;
    add = angle/180*200/10;
    int compare = 5+add;
    __HAL_TIM_SetCompare(&htim4,TIM_CHANNEL_4,compare);
}

