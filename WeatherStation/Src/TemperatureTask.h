/*
 * TemperatureTask.h
 *
 *  Created on: Apr 24, 2016
 *      Author: Adrian
 */

#ifndef TEMPERATURETASK_H_
#define TEMPERATURETASK_H_

#include "main.h"
#include "Humid_Temp_Sensor.h"

#define TEMPERATURE_TASK_DELAY_MS		1000

extern void TemperatureMeasureTask(void *);

#endif /* TEMPERATURETASK_H_ */
