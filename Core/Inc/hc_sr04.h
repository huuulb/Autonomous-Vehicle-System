#ifndef HC_SR04_H
#define HC_SR04_H

#include "main.h"
#include <stdbool.h>


void HC_SR04_Init(void);
void delay_us(uint16_t us);
void HC_SR04_Read(void);
void Obstacle_Avoiding (void);

#endif
