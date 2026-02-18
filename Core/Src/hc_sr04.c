#include <hc_sr04.h>
#include <stdio.h>
#include "servo.h"
#include "motor.h"

extern TIM_HandleTypeDef htim1;
extern uint16_t Distance ;
extern void look_forward(void);
extern void left_turn(void);
extern void right_turn(void);
extern void Motor_Forward(void);
extern void Motor_Backward(void);
extern void Motor_Left_Turn(uint16_t ms);
extern void Motor_Right_Turn(uint16_t ms);



uint32_t IC_Val1 = 0;
uint32_t IC_Val2 = 0;
uint32_t Difference = 0;
uint8_t Is_First_Captured = 0;


void HC_SR04_Init(void)
{

  HAL_TIM_Base_Start(&htim1);
  HAL_TIM_IC_Start(&htim1, TIM_CHANNEL_1); //able the tim1 capture compare interrupt
  HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_RESET);
  printf("HC-SR04 Ready\r\n");
}
void delay_us(uint16_t us)
{
    // At 72MHz, roughly 72 cycles per microsecond
   for (volatile uint32_t i = 0; i < us * 18; i++);
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
	{
		if (Is_First_Captured == 0)
		{
		  IC_Val1 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
		  Is_First_Captured = 1;
		  //debug


		  __HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_FALLING);
		}
		else if (Is_First_Captured == 1)
		{
		  IC_Val2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);


		  __HAL_TIM_SET_COUNTER(htim, 0); //reset the timestamp back to 0
		  if (IC_Val2 > IC_Val1)
			{
				Difference = IC_Val2-IC_Val1;
			}

		  else if (IC_Val1 > IC_Val2)
			{
				Difference = (65535 - IC_Val1) + IC_Val2;
			}


		  Distance = (Difference * 343)/20000; //in cm
		  Is_First_Captured = 0;

            //set polarity to rising edge
		  __HAL_TIM_SET_CAPTUREPOLARITY(htim, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);
		  __HAL_TIM_DISABLE_IT(&htim1, TIM_IT_CC1); //disable tim1 capture compare interrupt
		  }
		}
}

void HC_SR04_Read (void)
{

	__HAL_TIM_SET_CAPTUREPOLARITY(&htim1, TIM_CHANNEL_1, TIM_INPUTCHANNELPOLARITY_RISING);
	Is_First_Captured = 0;
	__HAL_TIM_ENABLE_IT(&htim1, TIM_IT_CC1);//enable interrupt first
	HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_SET);
	delay_us(10);
	HAL_GPIO_WritePin(TRIG_GPIO_Port, TRIG_Pin, GPIO_PIN_RESET);

}

void Obstacle_Avoiding (void)
{
	uint16_t front_dist, left_dist, right_dist;

	look_forward();
	HAL_Delay(500);
	HC_SR04_Read();
	front_dist = Distance;

	if (front_dist >20){
		Motor_Forward();
		return;
	}

	Motor_Stop();

	left_turn();
	HAL_Delay(500);
	HC_SR04_Read();
	left_dist = Distance;
	HAL_Delay(100);

	right_turn();
	HAL_Delay(500);
	HC_SR04_Read();
	right_dist = Distance;
	HAL_Delay(100);

	if ( left_dist > right_dist && left_dist >= 20)
	{
		Motor_Left_Turn(500);
	}
	else if(right_dist > left_dist && right_dist >= 20)
	{
		Motor_Right_Turn(500);
	}
	else
	{
		Motor_Backward();
		HAL_Delay(800);
		Motor_Stop();
	}

}
