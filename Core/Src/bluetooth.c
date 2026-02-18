#include <stdio.h>
#include <bluetooth.h>
#include <motor.h>

extern UART_HandleTypeDef huart1;
uint8_t bt_rx_data = 0;

void Bluetooth_Init(void)
{
	// Enable receive interrupt for Bluetooth
	HAL_UART_Receive_IT(&huart1, &bt_rx_data, 1);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart->Instance == USART1)  // Bluetooth
  {
    printf("BT Received: %c\r\n", bt_rx_data);

    // led control based on receive character
    switch(bt_rx_data){

    case 'a':
    	Motor_Forward();
    	break;
    case 'b':
    	Motor_Backward();
    	break;
    case 'c':
    	Motor_Left_Turn(500);
    	break;
    case 'd':
    	Motor_Right_Turn(500);
    	break;
    case '0':
	    Motor_Stop();
	    break;
    default:
    	Motor_Stop();
    	break;
    }

    // re-enable receive interrupt
    HAL_UART_Receive_IT(&huart1, &bt_rx_data, 1);
  }
}
