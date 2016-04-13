/*
 * teltronic_io2.h
 *
 *  Created on: Mar 24, 2016
 *      Author: Simon
 */

#ifndef TELTRONIC_IO2_H_
#define TELTRONIC_IO2_H_



#endif /* TELTRONIC_IO2_H_ */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*----- Header-Files -------------------------------------------------------*/
#include <stm32l1xx.h>				/* Processor STM32F407IG				*/
#include "stm32l1xx_rcc.h"
//#include <TELTRONIC.h>					/* TELTRONIC Module							*/

/*----- Macros -------------------------------------------------------------*/
#define TELTRONIC_ERROR_IO2_NO_DATA				(TELTRONIC_ERROR_IO2_BASE + 0)	/**< No data available		*/
#define TELTRONIC_ERROR_IO2_PWM_WRONG_CHANNEL	(TELTRONIC_ERROR_IO2_BASE + 1)	/**< Wrong PWM channel		*/

#define TELTRONIC_IO2_GPIO_OUT_PIN0		0x1		/**< GPIO Out Pin 0				*/
#define TELTRONIC_IO2_GPIO_OUT_PIN1		0x2		/**< GPIO Out Pin 1				*/
#define TELTRONIC_IO2_GPIO_OUT_PIN2		0x4		/**< GPIO Out Pin 2				*/

/* LTC2622 DAC Commands */
#define TELTRONIC_IO2_LTC2622_CMD_W		0x00	/**< Write to Input Register n							*/
#define TELTRONIC_IO2_LTC2622_CMD_Un	0x01	/**< Update (Power Up) DAC Register n					*/
#define TELTRONIC_IO2_LTC2622_CMD_WUa	0x02	/**< Write to Input registers, Update (Power Up) All n	*/
#define TELTRONIC_IO2_LTC2622_CMD_WUn	0x03	/**< Write to and Update (Power Up) n					*/
#define TELTRONIC_IO2_LTC2622_CMD_Off	0x04	/**< Power Down n										*/
#define TELTRONIC_IO2_LTC2622_CMD_None	0xFF	/**< No Operation										*/

/* LTC2622 DAC Addresses */
#define TELTRONIC_IO2_LTC2622_ADDR_A	0x00	/**< DAC A						*/
#define TELTRONIC_IO2_LTC2622_ADDR_B	0x01	/**< DAC B						*/
#define TELTRONIC_IO2_LTC2622_ADDR_ALL	0xFF	/**< All DACs					*/

/* AGPIO list */
#define TELTRONIC_AGPIO_9				GPIOI, GPIO_Pin_5	/**< Additional GPIO 9				*/
#define TELTRONIC_AGPIO_13				GPIOG, GPIO_Pin_15	/**< Additional GPIO 13				*/
#define TELTRONIC_AGPIO_21				GPIOI, GPIO_Pin_4	/**< Additional GPIO 21				*/
#define TELTRONIC_AGPIO_22				GPIOH, GPIO_Pin_2	/**< Additional GPIO 22				*/
#define TELTRONIC_AGPIO_90				GPIOF, GPIO_Pin_11	/**< Additional GPIO 90				*/
#define TELTRONIC_AGPIO_91				GPIOF, GPIO_Pin_10	/**< Additional GPIO 91				*/
#define TELTRONIC_AGPIO_93				GPIOF, GPIO_Pin_9	/**< Additional GPIO 93				*/
#define TELTRONIC_AGPIO_94				GPIOF, GPIO_Pin_8	/**< Additional GPIO 94				*/
#define TELTRONIC_AGPIO_96				GPIOF, GPIO_Pin_7	/**< Additional GPIO 96				*/
#define TELTRONIC_AGPIO_97				GPIOF, GPIO_Pin_6	/**< Additional GPIO 97				*/
#define TELTRONIC_AGPIO_99				GPIOC, GPIO_Pin_7	/**< Additional GPIO 99				*/
#define TELTRONIC_AGPIO_101				GPIOB, GPIO_Pin_15	/**< Additional GPIO 101			*/
#define TELTRONIC_AGPIO_102				GPIOB, GPIO_Pin_14	/**< Additional GPIO 102			*/
#define TELTRONIC_AGPIO_103				GPIOI, GPIO_Pin_0	/**< Additional GPIO 103			*/
#define TELTRONIC_AGPIO_105				GPIOB, GPIO_Pin_8	/**< Additional GPIO 105			*/
#define TELTRONIC_AGPIO_108				GPIOB, GPIO_Pin_6	/**< Additional GPIO 108			*/
#define TELTRONIC_AGPIO_115				GPIOB, GPIO_Pin_2	/**< Additional GPIO 115			*/
#define TELTRONIC_AGPIO_116				GPIOB, GPIO_Pin_1	/**< Additional GPIO 116			*/
#define TELTRONIC_LED_GREEN				GPIOI, GPIO_Pin_6	/**< Green LED on module			*/
#define TELTRONIC_LED_RED				GPIOI, GPIO_Pin_7	/**< Red LED on module				*/

/* AGPIO Pin list */
#define TELTRONIC_AGPIO_PIN_116			((uint32_t)0x00001)	/**< Additional GPIO 116 Pin		*/
#define TELTRONIC_AGPIO_PIN_115			((uint32_t)0x00002)	/**< Additional GPIO 115 Pin		*/
#define TELTRONIC_AGPIO_PIN_108			((uint32_t)0x00004)	/**< Additional GPIO 108 Pin		*/
#define TELTRONIC_AGPIO_PIN_105			((uint32_t)0x00008)	/**< Additional GPIO 105 Pin		*/
#define TELTRONIC_AGPIO_PIN_103			((uint32_t)0x00010)	/**< Additional GPIO 103 Pin		*/
#define TELTRONIC_AGPIO_PIN_102			((uint32_t)0x00020)	/**< Additional GPIO 102 Pin		*/
#define TELTRONIC_AGPIO_PIN_101			((uint32_t)0x00040)	/**< Additional GPIO 101 Pin		*/
#define TELTRONIC_AGPIO_PIN_99			((uint32_t)0x00080)	/**< Additional GPIO 99 Pin			*/
#define TELTRONIC_AGPIO_PIN_97			((uint32_t)0x00100)	/**< Additional GPIO 97 Pin			*/
#define TELTRONIC_AGPIO_PIN_96			((uint32_t)0x00200)	/**< Additional GPIO 96 Pin			*/
#define TELTRONIC_AGPIO_PIN_94			((uint32_t)0x00400)	/**< Additional GPIO 94 Pin			*/
#define TELTRONIC_AGPIO_PIN_93			((uint32_t)0x00800)	/**< Additional GPIO 93 Pin			*/
#define TELTRONIC_AGPIO_PIN_91			((uint32_t)0x01000)	/**< Additional GPIO 91 Pin			*/
#define TELTRONIC_AGPIO_PIN_90			((uint32_t)0x02000)	/**< Additional GPIO 90 Pin			*/
#define TELTRONIC_AGPIO_PIN_22			((uint32_t)0x04000)	/**< Additional GPIO 22 Pin			*/
#define TELTRONIC_AGPIO_PIN_21			((uint32_t)0x08000)	/**< Additional GPIO 21 Pin			*/
#define TELTRONIC_AGPIO_PIN_13			((uint32_t)0x10000)	/**< Additional GPIO 13 Pin			*/
#define TELTRONIC_AGPIO_PIN_9			((uint32_t)0x20000)	/**< Additional GPIO 9 Pin			*/
#define TELTRONIC_LED_PIN_GREEN			((uint32_t)0x40000)	/**< Green LED Pin					*/
#define TELTRONIC_LED_PIN_RED			((uint32_t)0x80000)	/**< Red LED Pin					*/

/* TELTRONIC error codes */
#define TELTRONIC_NO_ERROR				0x0				/**< No error			*/
#define TELTRONIC_ERROR_IO1_BASE		0x10			/**< TELTRONIC IO1 errors	*/
#define TELTRONIC_ERROR_IO2_BASE		0x20			/**< TELTRONIC IO2 errors	*/
#define TELTRONIC_ERROR_UART_BASE		0x30			/**< UART errors		*/
#define TELTRONIC_ERROR_CAN_BASE		0x40			/**< CAN errors			*/
#define TELTRONIC_ERROR_I2C_BASE		0x60			/**< I2C errors			*/
#define TELTRONIC_ERROR_AUDIO_BASE		0x80			/**< Audio codec errors	*/
#define TELTRONIC_ERROR_ETH_BASE		0xA0			/**< Ethernet errors	*/
#define TELTRONIC_ERROR_USB_BASE		0xC0			/**< USB errors			*/
#define TELTRONIC_ERROR_EEPROM_BASE		0xE0			/**< EEPROM errors		*/
/*----- Data types ---------------------------------------------------------*/
typedef struct _TELTRONIC_Port_Pin_t {
	GPIO_TypeDef* GPIOx;
	uint16_t GPIO_Pin;
	GPIOMode_TypeDef GPIO_Mode;
	uint8_t GPIO_AF;
} TELTRONIC_Port_Pin_t;


/**
 * @brief	ADC port names.
 */
typedef enum _TELTRONIC_IO2_SPI_CHANNEL {
	TELTRONIC_IO2_nPSC0 = 0,				/**< DAC, SPI0						*/
	TELTRONIC_IO2_nPSC1 = 1,					/**< External, SPI1					*/
	TELTRONIC_IO2_nPSC2 = 2 // Edited bolzs2
} TELTRONIC_IO2_SPI_CHANNEL;

///**
// * @brief	PWM port names.
// */
//typedef enum _TELTRONIC_IO2_PWM_CHANNEL {
//	TELTRONIC_IO2_PWM0,						/**< PWM0							*/
//	TELTRONIC_IO2_PWM1,						/**< PWM1							*/
//	TELTRONIC_IO2_PWM2,						/**< PWM2							*/
//	TELTRONIC_IO2_PWM3						/**< PWM3, Motor Out				*/
//} TELTRONIC_IO2_PWM_CHANNEL;
//
///**
// * @brief	DC motor direction.
// */
//typedef enum _TELTRONIC_IO2_PWM_PHASE {
//	TELTRONIC_IO2_PWM_NORMAL_DIRECTION,		/**< Forward						*/
//	TELTRONIC_IO2_PWM_OPPOSITE_DIRECTION	/**< Backward						*/
//} TELTRONIC_IO2_PWM_PHASE;

 /* Function Prototypes */
extern void teltronic_IO2_Init(void);
extern void TELTRONIC_IO2_SPI_Select(TELTRONIC_IO2_SPI_CHANNEL select);
extern void TELTRONIC_IO2_SPI_CS_Out(uint8_t SPI_nbr, uint8_t cs);
extern void TELTRONIC_IO2_SPI_Send(uint8_t SPI_Nbr, uint16_t data);
//extern void TELTRONIC_IO2_SPI2_Send(uint16_t data);
//extern void TELTRONIC_IO2_SPI3_Send(uint16_t data);
extern void TELTRONIC_IO2_SPI_Receive(uint8_t SPI_Nbr, uint16_t *pValue);
//extern void TELTRONIC_IO2_SPI2_Receive(uint16_t *pValue);
//extern void TELTRONIC_IO2_SPI3_Receive(uint16_t *pValue);
extern void TELTRONIC_GPIO_Init(TELTRONIC_Port_Pin_t *pPortPinAssociation,
                            GPIO_InitTypeDef *pGPIO_InitStruct, uint8_t size);


extern void RCC_Configuration(void);
extern void GPIO_SPI_Configure(void);
