/*
 * HumidityTask.c
 *
 *  Created on: Apr 24, 2016
 *      Author: Adrian
 */
#include "HumidityTask.h"

void HumidityMeasureTask(void *pvargs){
	int32_t humidityValue=0;

		for (;;) {
			// Wait for i2c bus access
			if(xSemaphoreTake(xSemaphore_I2C,portMAX_DELAY) == pdTRUE){
				// Get actual Humidity value from Sensor
				humidityValue = HMDTEMP_getHumidity();
				// Wait for Humidity Message Queue access
				if(xQueueSendToBack(queueHumidity,(void*)&humidityValue,portMAX_DELAY) == pdTRUE){

				}
				xSemaphoreGive(xSemaphore_I2C);
			}
			osDelay(HUMIDITY_TASK_DELAY_MS);
		}
}

