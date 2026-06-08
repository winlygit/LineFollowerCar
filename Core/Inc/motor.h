#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "main.h"



void Motor_Init(void);
void motor_set(int L, int R);// L, R ¡Ê [-1000, 1000]
void motor_stop(void);






#endif
