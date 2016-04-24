/*
 * PressureTask.c
 *
 *  Created on: Apr 24, 2016
 *      Author: Adrian
 */
#include "PressureTask.h"

void PressureMeasureTask(void *pvargs){
	int32_t pressureValue=0;

		for (;;) {
			// Wait for i2c bus access
			if(xSemaphoreTake(xSemaphore_I2C,portMAX_DELAY) == pdTRUE){
				// Get actual Pressure value from Sensor
				pressureValue = HMDTEMP_getPressure();
				// Wait for Pressure Message Queue access
				if(xQueueSendToBack(queuePressure,(void*)&pressureValue,portMAX_DELAY) == pdTRUE){

				}
				xSemaphoreGive(xSemaphore_I2C);
			}
			osDelay(PRESSURE_TASK_DELAY_MS);
		}
}
