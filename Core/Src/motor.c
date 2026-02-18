#include "motor.h"

//let them know htim3 exists somewhere else
extern TIM_HandleTypeDef htim3;


void Motor_Init(void){
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
}

void Right_Motor_SetSpeed(uint8_t speed) {
	uint32_t pwm_value = (speed * __HAL_TIM_GET_AUTORELOAD(&htim3)) /100;
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, pwm_value);
}

void Left_Motor_SetSpeed(uint8_t speed) {
	uint32_t pwm_value = (speed * __HAL_TIM_GET_AUTORELOAD(&htim3)) /100;
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, pwm_value);
}
void Motor_Stop(void){

	    Left_Motor_SetSpeed(MOTOR_SPEED_STOP);
		Right_Motor_SetSpeed(MOTOR_SPEED_STOP);
		HAL_GPIO_WritePin(GPIOC, In1_Pin, GPIO_PIN_RESET);//in1=high
		HAL_GPIO_WritePin(GPIOC, In2_Pin, GPIO_PIN_RESET); //in2=low
		HAL_GPIO_WritePin(GPIOC, In3_Pin, GPIO_PIN_RESET);//in1=high
		HAL_GPIO_WritePin(GPIOC, In4_Pin, GPIO_PIN_RESET); //in2=low
}
void Motor_Forward(void){
		HAL_GPIO_WritePin(GPIOC, In1_Pin, GPIO_PIN_SET);//in1=high
		HAL_GPIO_WritePin(GPIOC, In2_Pin, GPIO_PIN_RESET); //in2=low
		HAL_GPIO_WritePin(GPIOC, In3_Pin, GPIO_PIN_SET);//in1=high
		HAL_GPIO_WritePin(GPIOC, In4_Pin, GPIO_PIN_RESET); //in2=low
		Left_Motor_SetSpeed(MOTOR_SPEED_DEFAULT);
		Right_Motor_SetSpeed(MOTOR_SPEED_DEFAULT);

}
void Motor_Backward(void){
	    HAL_GPIO_WritePin(GPIOC, In1_Pin, GPIO_PIN_RESET);//in1=low
	    HAL_GPIO_WritePin(GPIOC, In2_Pin, GPIO_PIN_SET); //
		HAL_GPIO_WritePin(GPIOC, In3_Pin, GPIO_PIN_RESET);//in1=low
		HAL_GPIO_WritePin(GPIOC, In4_Pin, GPIO_PIN_SET); //
	    Left_Motor_SetSpeed(MOTOR_SPEED_DEFAULT);
		Right_Motor_SetSpeed(MOTOR_SPEED_DEFAULT);

}

void Motor_Left_Turn(uint16_t ms){
	    HAL_GPIO_WritePin(GPIOC, In1_Pin, GPIO_PIN_SET);//in1=high
	    HAL_GPIO_WritePin(GPIOC, In2_Pin, GPIO_PIN_RESET);
	    Right_Motor_SetSpeed(MOTOR_SPEED_DEFAULT);
	    HAL_GPIO_WritePin(GPIOC, In3_Pin, GPIO_PIN_RESET);
	    HAL_GPIO_WritePin(GPIOC, In4_Pin, GPIO_PIN_SET);
	    Left_Motor_SetSpeed(MOTOR_SPEED_LOW);
	    HAL_Delay(ms);
	    Motor_Stop();

}
void Motor_Right_Turn(uint16_t ms){
		HAL_GPIO_WritePin(GPIOC, In3_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, In4_Pin, GPIO_PIN_RESET);
		Left_Motor_SetSpeed(MOTOR_SPEED_DEFAULT);
		HAL_GPIO_WritePin(GPIOC, In1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, In2_Pin, GPIO_PIN_SET);
		Right_Motor_SetSpeed(MOTOR_SPEED_LOW);
	    HAL_Delay(ms);
	    Motor_Stop();

}
