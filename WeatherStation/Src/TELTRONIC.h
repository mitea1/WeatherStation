/*
 * teltronic.h
 *
 *  Created on: Mar 19, 2016
 *      Author: Adrian
 */

#ifndef TELTRONIC_H_
#define TELTRONIC_H_


typedef uint8_t ERROR_CODES;
#define TELTRONIC_NO_ERROR 			0x0
#define TELTRONIC_ERROR_I2C_BASE   	0x60


typedef struct _TELTRONIC_Port_Pin_t {
     GPIO_TypeDef* GPIOx;
     uint16_t GPIO_Pin;
     GPIOMode_TypeDef GPIO_Mode;
     uint8_t GPIO_AF;
} TELTRONIC_Port_Pin_t;

#endif /* TELTRONIC_H_ */
