/*
 * LightTask.c
 *
 *  Created on: Apr 18, 2016
 *      Author: Adrian
 */

/**
 * @brief		Task that reads the Lux value from
 * 				the Lightsensor
 */
#include "LightTask.h"
#include "TELTRONIC_UART.h"
void LightMeasureTask(void *pvargs) {

	uint16_t luxValue=0;

	for (;;) {

		// Wait for i2c bus access
		if(xSemaphoreTake(xSemaphore_I2C,portMAX_DELAY) == pdTRUE){

			// Get actual lux value from Sensor
			luxValue = LIGHT_SENSOR_getLux();
			// Wait for Message Queue access

			if(xQueueSendToBack(queueLight,(void*)&luxValue,portMAX_DELAY) == pdTRUE){

			}

			xSemaphoreGive(xSemaphore_I2C);

		}
		osDelay(LIGHT_TASK_DELAY_MS);
	}
}
