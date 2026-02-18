#ifndef MOTOR_H
#define MOTOR_H

#include "main.h"

#define MOTOR_SPEED_DEFAULT 50
#define MOTOR_SPEED_FAST 70
#define MOTOR_SPEED_LOW 30
#define MOTOR_SPEED_STOP 0

void Motor_Init(void);
void Motor_Forward(void);
void Motor_Backward(void);
void Motor_Left_Turn(uint16_t ms);
void Motor_Right_Turn(uint16_t ms);
void Motor_Stop(void);

void Left_Motor_SetSpeed(uint8_t speed);
void Right_Motor_SetSpeed(uint8_t speed);

#endif
