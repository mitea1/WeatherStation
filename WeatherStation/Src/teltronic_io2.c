/*
 * teltronic_io2.c
 *
 *  Created on: Mar 24, 2016
 *      Author: Simon
 */

/*----- Header-Files -------------------------------------------------------*/
#include <stm32l1xx.h>				/* Processor STM32F407IG				*/
#include "stm32l1xx_rcc.h"
#include <teltronic_io2.h>			/* TELTRONIC IO2 Module					*/
/**
 * @brief	TELTRONIC IO2 Port and Pin association
 */
//static TELTRONIC_Port_Pin_t TELTRONIC_IO2_Port_Pin[] = {
//		// SPI 1
//		{ GPIOA, GPIO_Pin_7, GPIO_Mode_AF, GPIO_AF_SPI1 },	/**< SPI1 MOSI	*/
//		{ GPIOA, GPIO_Pin_6, GPIO_Mode_AF, GPIO_AF_SPI1 },	/**< SPI1 MISO	*/
//		{ GPIOA, GPIO_Pin_5, GPIO_Mode_AF, GPIO_AF_SPI1 },	/**< SPI1 CLK	*/
//		{ GPIOA, GPIO_Pin_4, GPIO_Mode_OUT },				/**< SPI1 NSS	*/
//
//		// SPI to LoRa Semtech
//		{ GPIOB, GPIO_Pin_15, GPIO_Mode_AF, GPIO_AF_SPI2 },	/**< SPI1 MOSI	*/
//		{ GPIOB, GPIO_Pin_14, GPIO_Mode_AF, GPIO_AF_SPI2 },	/**< SPI1 MISO	*/
//		{ GPIOB, GPIO_Pin_13, GPIO_Mode_AF, GPIO_AF_SPI2 },	/**< SPI1 CLK	*/
//		{ GPIOB, GPIO_Pin_12, GPIO_Mode_OUT },				/**< SPI1 NSS	*/
//
//		// SPI 3
//		{ GPIOB, GPIO_Pin_5, GPIO_Mode_AF, GPIO_AF_SPI3 },	/**< SPI1 MOSI	*/
//		{ GPIOB, GPIO_Pin_4, GPIO_Mode_AF, GPIO_AF_SPI3 },	/**< SPI1 MISO	*/
//		{ GPIOB, GPIO_Pin_3, GPIO_Mode_AF, GPIO_AF_SPI3 },	/**< SPI1 CLK	*/
//		{ GPIOA, GPIO_Pin_15, GPIO_Mode_OUT },				/**< SPI1 NSS	*/
//};
/**
 *****************************************************************************
 * @brief		TELTRONIC IO2 initialization.
 *
 * @return		None
 *****************************************************************************
 */
void teltronic_IO2_Init(void){
	/* Variables */
	SPI_InitTypeDef SPI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStruct;

	/* Enable SPI clocks */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2 , ENABLE);
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3 , ENABLE);

	/* Initialize the SPI */
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;

	SPI_Init(SPI1, &SPI_InitStructure);
	SPI_Init(SPI2, &SPI_InitStructure);
//	SPI_Init(SPI3, &SPI_InitStructure);

	/* Enable SPI clocks */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB , ENABLE);

	/* Initialize the GPIO MISO MOSI CLK of GPIOA */
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* Initialize the GPIO MISO MOSI CLK of GPIOB */
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_14 | GPIO_Pin_13;
			//| GPIO_Pin_5 | GPIO_Pin_4 | GPIO_Pin_3;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* Initialize the GPIO CS of GPIOA */
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4; //| GPIO_Pin_15;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* Initialize the GPIO CS of GPIOB */
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* Set SPI 1-3 Source Pins */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_SPI2);

//	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_SPI3);
//	GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_SPI3);
//	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_SPI3);

	/* Disable Chip Select */
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
	GPIO_SetBits(GPIOB, GPIO_Pin_12);
	//GPIO_SetBits(GPIOA, GPIO_Pin_15);

	SPI_Cmd(SPI1, ENABLE);
	SPI_Cmd(SPI2, ENABLE);
	//SPI_Cmd(SPI3, ENABLE);

}

/**
 *****************************************************************************
 * @brief		Generate the chip select pin.
 *
 * @param[in]	cs		Set the chip select pin.\n
 *						@arg Bit_RESET:	CS = low\n
 *						@arg Bit_SET:	CS = high
 *				SPIx	Choose SPI_Nbr
 *						@arg 1: use SPI1
 *						@arg 2: use SPI2
 *						@arg 3: use SPI3
 * @return		None
 *****************************************************************************
 */
void TELTRONIC_IO2_SPI_CS_Out(uint8_t SPI_Nbr, uint8_t cs) {

	/* Set Chip Select Pin */
	switch(SPI_Nbr){
	case 1:
		if (cs == 0){
			GPIO_ResetBits(GPIOA, GPIO_Pin_4);
		}else{
			GPIO_SetBits(GPIOA, GPIO_Pin_4);
		}
		break;
	case 2:
		if (cs == 0){
			GPIO_ResetBits(GPIOB, GPIO_Pin_12);
		}else{
			GPIO_SetBits(GPIOB, GPIO_Pin_12);
		}
		break;
	case 3:
		if (cs == 0){
			GPIO_ResetBits(GPIOA, GPIO_Pin_15);
		}else{
			GPIO_SetBits(GPIOA, GPIO_Pin_15);
		}
		break;
	}
}
/**
 *****************************************************************************
 * @brief		Send a half word over the SPI1 port.
 *
 * @param[in]	data	Half word you want to send.
 * 				SPI		Choose SPI Nbr.
 *						@arg 1: use SPI1
 *						@arg 2: use SPI2
 *						@arg 3: use SPI3
 * @return		None
 *****************************************************************************
 */
void TELTRONIC_IO2_SPI_Send(uint8_t SPI_Nbr, uint16_t data) {
	/* write data to be transmitted to the SPI data register */
	switch(SPI_Nbr){
	case 1:

		SPI_I2S_SendData(SPI1, data);

		/* wait until transmit complete */
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
			;
		/* wait until receive complete */
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)
			;
		/* wait until SPI is not busy anymore */
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET)
			;
		break;
	case 2:
		/* write data to be transmitted to the SPI data register */
		SPI_I2S_SendData(SPI2, data);

		/* wait until transmit complete */
		while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET)
			;
		/* wait until receive complete */
		while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET)
			;
		/* wait until SPI is not busy anymore */
		while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) == SET)
			;
		break;
	case 3:
		/* write data to be transmitted to the SPI data register */
		SPI_I2S_SendData(SPI3, data);

		/* wait until transmit complete */
		while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) == RESET)
			;
		/* wait until receive complete */
		while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE) == RESET)
			;
		/* wait until SPI is not busy anymore */
		while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_BSY) == SET)
			;
		break;
	default:
		//printf("\nno valid SPI channel selected!\n");
		break;
	}
}

/**
 *****************************************************************************
 * @brief		Receive a half word from the SPI1 input buffer.
 *
 * @param[out]	pValue	Pointer to the half word buffer to write data in.
 * @return		None
 *****************************************************************************
 */
void TELTRONIC_IO2_SPI_Receive(uint8_t SPI_Nbr, uint16_t *pValue) {

	switch (SPI_Nbr){
	case 1:
		/* wait until transmit complete */
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
			;
		/* wait until receive complete */
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)
			;
		/* wait until SPI is not busy anymore */
		while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET)
			;

		*pValue = SPI_I2S_ReceiveData(SPI1);
		break;
	case 2:
		/* wait until transmit complete */
		while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET)
			;
		/* wait until receive complete */
		while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET)
			;
		/* wait until SPI is not busy anymore */
		while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) == SET)
			;

		*pValue = SPI_I2S_ReceiveData(SPI2);
		break;
	case 3:
		/* wait until transmit complete */
		while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) == RESET)
			;
		/* wait until receive complete */
		while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE) == RESET)
			;
		/* wait until SPI is not busy anymore */
		while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_BSY) == SET)
			;

		*pValue = SPI_I2S_ReceiveData(SPI3);
		break;
	default:
		//printf("\nno valid SPI channel selected!\n");
		break;
	}
}

///**
// *****************************************************************************
// * @brief		Receive a half word from the SPI1 input buffer.
// *
// * @param[out]	pValue	Pointer to the half word buffer to write data in.
// * @return		None
// *****************************************************************************
// */
//void TELTRONIC_IO2_SPI1_Receive(uint16_t *pValue) {
//
//	/* wait until transmit complete */
//	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
//		;
//	/* wait until receive complete */
//	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)
//		;
//	/* wait until SPI is not busy anymore */
//	while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_BSY) == SET)
//		;
//
//	*pValue = SPI_I2S_ReceiveData(SPI1);
//}
//
///**
// *****************************************************************************
// * @brief		Receive a half word from the SPI2 input buffer. (LoRa Semtech
// * 				Port)
// *
// * @param[out]	pValue	Pointer to the half word buffer to write data in.
// * @return		None
// *****************************************************************************
// */
//void TELTRONIC_IO2_SPI2_Receive(uint16_t *pValue) {
//
//	/* wait until transmit complete */
//	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET)
//		;
//	/* wait until receive complete */
//	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET)
//		;
//	/* wait until SPI is not busy anymore */
//	while (SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) == SET)
//		;
//
//	*pValue = SPI_I2S_ReceiveData(SPI2);
//}
///**
// *****************************************************************************
// * @brief		Receive a half word from the SPI3 input buffer.
// *
// * @param[out]	pValue	Pointer to the half word buffer to write data in.
// * @return		None
// *****************************************************************************
// */
//void TELTRONIC_IO2_SPI3_Receive(uint16_t *pValue) {
//
//	/* wait until transmit complete */
//	while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) == RESET)
//		;
//	/* wait until receive complete */
//	while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_RXNE) == RESET)
//		;
//	/* wait until SPI is not busy anymore */
//	while (SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_BSY) == SET)
//		;
//
//	*pValue = SPI_I2S_ReceiveData(SPI3);
//}
