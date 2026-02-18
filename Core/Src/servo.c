#include "motor.h"
#include "servo.h"

extern TIM_HandleTypeDef htim4;

void servo_init(void){
	  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
}

void Set_Servo_Angle (TIM_HandleTypeDef *htim, uint32_t channel, uint8_t angle){
	//map angle from 0 to 180 to pulse width (500-2500)
	uint32_t pulse_length = 500+ (angle *(2500-500)/180);
	__HAL_TIM_SET_COMPARE(htim, channel, pulse_length);

}
void left_turn(void){

	Set_Servo_Angle(&htim4, TIM_CHANNEL_1, SERVO_LOOK_LEFT);
	HAL_Delay(500);
	Set_Servo_Angle(&htim4, TIM_CHANNEL_1, SERVO_LOOK_FORWARD);
	HAL_Delay(500);
}

void right_turn(void){

	Set_Servo_Angle(&htim4, TIM_CHANNEL_1, SERVO_LOOK_RIGHT);
	HAL_Delay(500);
	Set_Servo_Angle(&htim4, TIM_CHANNEL_1, SERVO_LOOK_FORWARD);
	HAL_Delay(500);
}

void look_forward(void){
	Set_Servo_Angle(&htim4, TIM_CHANNEL_1, SERVO_LOOK_FORWARD);
	HAL_Delay(500);
}
