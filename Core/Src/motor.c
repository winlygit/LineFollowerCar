#include "main.h"
#include "global.h"
#include "motor.h"


void Motor_Init(void)
{
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);

    __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, 0);
    __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2, 0);
    __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, 0);
    __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4, 0);
}

void motor_set(int L, int R)// L, R ¡Ê [-100, 100]
{
    if (L > 0) {
        __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, 0);
        __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2, L);
    } else {
        __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, -L);
        __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2, 0);
    }

    if (R > 0) {
        __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, R);
        __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4, 0);
    } else {
        __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, 0);
        __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_4, -R);
    }
}



