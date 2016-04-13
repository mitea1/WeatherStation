#ifndef __I2C_H__
#define __I2C_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*----- Header-Files -------------------------------------------------------*/
#include <stm32l1xx.h>                /* Processor STM32F407IG                */
#include <stm32l1xx_rcc.h>
#include <stm32l1xx_gpio.h>
#include <stm32l1xx_i2c.h>
#include "teltronic.h"                 /* CARME Module                         */

/*----- Macros -------------------------------------------------------------*/
#define CARME_I2C_BOARD             I2C2
#define CARME_I2C_AUDIO             I2C3
#define CARME_I2C_SPEED             100000
#define CARME_I2C_ADDR_BOARD        0xA0
#define CARME_I2C_ADDR_AUDIO        0x33
#define CARME_ERROR_I2C_TIMEOUT     TELTRONIC_ERROR_I2C_BASE + 0
/*----- Data types ---------------------------------------------------------*/

/*----- Function prototypes ------------------------------------------------*/
extern void TELTRONIC_I2C_Init(I2C_TypeDef *I2Cx);
ERROR_CODES TELTRONIC_I2C_Write(I2C_TypeDef *I2Cx, uint8_t addr, uint16_t reg,
		uint8_t twoByte, uint8_t *pdata, uint16_t count);
ERROR_CODES TELTRONIC_I2C_Read(I2C_TypeDef *I2Cx, uint8_t addr, uint16_t reg,
		uint8_t twoByte, uint8_t *pdata, uint16_t count);

/*----- Data ---------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __I2C_H__ */
