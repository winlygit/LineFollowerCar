#include "main.h"
#include "sensor.h"
#include "global.h"


void get_follower_sensor(uint8_t *state){

    state[0] = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12);
    state[1] = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13);
    state[2] = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14);
    state[3] = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15);
    state_ifelse = state[0]*1000 + state[1]*100 + state[2]*10 + state[3];
}



// void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
//     if(GPIO_Pin == GPIO_PIN_1){
//         pulse[0]++;
//     }else if(GPIO_Pin == GPIO_PIN_2){
//         pulse[1]++;
//     }
// }

//  void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
//     if(htim->Instance == TIM2){
//         speed[0] = pulse[0]/20*10;//单位转每秒
//         speed[1] = pulse[1]/20*10;//单位转每秒
//         pulse[0] = 0;
//         pulse[1] = 0;
//     }
// }




