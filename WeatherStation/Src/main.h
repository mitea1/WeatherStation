/*
 * main.h
 *
 *  Created on: Apr 18, 2016
 *      Author: Adrian
 */

#ifndef MAIN_H_
#define MAIN_H_
#include "cmsis_os.h"

// QUEUE Sizes
#define QUEUE_SIZE_PRESSURE		1
#define QUEUE_SIZE_TEMPERATURE	1
#define QUEUE_SIZE_HUMIDITY		1
#define QUEUE_SIZE_LIGHT		1

//Semaphores
extern SemaphoreHandle_t xSemaphore_I2C;

//Queues
extern QueueHandle_t queueHumidity;
extern QueueHandle_t queueTemperature;
extern QueueHandle_t queueLight;
extern QueueHandle_t queuePressure;
extern QueueHandle_t queueWeatherData;

#endif /* MAIN_H_ */
