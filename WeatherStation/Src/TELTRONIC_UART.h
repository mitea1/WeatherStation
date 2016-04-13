/*
 * UART_Print.h
 *
 *  Created on: Mar 16, 2016
 *      Author: Adrian
 */
#include "stm32l1xx.h"
#include "stm32l1xx_rcc.h"
#include "stm32l1xx_gpio.h"
#include "stm32l1xx_usart.h"

#ifndef UART_PRINT_H_
#define UART_PRINT_H_

extern void Usart1Init(void);
extern void UART1_Write(char *);

#endif /* UART_PRINT_H_ */
