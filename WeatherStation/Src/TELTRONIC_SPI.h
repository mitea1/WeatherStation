/*
 * teltronic_io2.h
 *
 *  Created on: Mar 24, 2016
 *      Author: Simon
 */

#ifndef SPI_H_
#define SPI_H_

#endif /* TELTRONIC_IO2_H_ */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


 /* Function Prototypes */
extern void teltronic_SPI_Init(void);
extern void TELTRONIC_SPI_CS_Out(uint8_t SPI_nbr, uint8_t cs);
extern void TELTRONIC_SPI_Send(uint8_t SPI_Nbr, uint16_t data);
extern void TELTRONIC_SPI_Receive(uint8_t SPI_Nbr, uint16_t *pValue);
extern void RCC_Configuration(void);
extern void GPIO_SPI_Configure(void);
