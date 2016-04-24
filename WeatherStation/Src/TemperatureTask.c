/*
 * TemperatureTask.c
 *
 *  Created on: Apr 24, 2016
 *      Author: Adrian
 */

#include "TemperatureTask.h"

void TemperatureMeasureTask(void *pvargs){
	int32_t temperatureValue=0;

		for (;;) {
			// Wait for i2c bus access
			if(xSemaphoreTake(xSemaphore_I2C,portMAX_DELAY) == pdTRUE){
				// Get actual lux value from Sensor
				temperatureValue = HMDTEMP_getTemperature();
				// Wait for Temperature Message Queue access
				if(xQueueSendToBack(queueTemperature,(void*)&temperatureValue,portMAX_DELAY) == pdTRUE){

				}
				xSemaphoreGive(xSemaphore_I2C);
			}
			osDelay(TEMPERATURE_TASK_DELAY_MS);
		}
}


