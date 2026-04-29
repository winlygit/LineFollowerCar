#include "main.h"
#include "sensor.h"
#include "global.h"


void get_follower_sensor(uint8_t *state)
{
    state[0] = !HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12);
    state[1] = !HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13);
    state[2] = !HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14);
    state[3] = !HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15);
}




