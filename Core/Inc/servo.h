#ifndef SERVO_H
#define SERVO_H

#include "main.h"

#define SERVO_LOOK_LEFT 185
#define SERVO_LOOK_FORWARD 98
#define SERVO_LOOK_RIGHT 9

void servo_init(void);
void Set_Servo_Angle (TIM_HandleTypeDef *htim, uint32_t channel, uint8_t angle);
void look_forward(void);
void left_turn(void);
void right_turn(void);

#endif
