#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include "main.h"
#include "bluetooth.h"

void Bluetooth_Init(void);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);

#endif
