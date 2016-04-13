/**
 *	@file	uart1.c
 *  @brief	Methods for the usage of UART
 *  @date	07.04.2016
 *  @author	Adrian Mitevski
 */

#include "TELTRONIC_UART.h"

/**
 * @brief Initializes UART1
 */
void Usart1Init(void)

{

	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStructure;

	//Set USART1 Tx (PA.09) as AF push-pull
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_400KHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);

	/* Enable the USART 1 clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	 /* Configure USART 1 */
	USART_ClockStructInit(&USART_ClockInitStructure);
	USART_ClockInit(USART1,&USART_ClockInitStructure);
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
	USART_Init(USART1, &USART_InitStructure);

	 //Enable USART1
	 USART_Cmd(USART1, ENABLE);

}

/**
 * @brief Sends a String via UART1
 * @param Buffer	Text String containing data
 */
void UART1_Write(char *Buffer)
{
	uint32_t len = strlen(Buffer);

	/*Send every single character via UART */
	 for (; len > 0; len--) {
		 /*Wait until UART is Ready to send*/
		 while (USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
		 USART_SendData(USART1, *Buffer);
		 Buffer++;
	 }
}

/**
 * @brief Sends a single 8bit char via UART1
 * @param ch	char that has to be sent
 */
void Usart1Put(uint8_t ch)
{
      USART_SendData(USART1, (uint8_t) ch);
      /*Loop until the end of transmission*/
      while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
      {
      }
}

/**
 * @brief Gets a single 8bit char via UART1
 * @return
 */
uint8_t Usart1Get(void){
     while ( USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
        return (uint8_t)USART_ReceiveData(USART1);
}
