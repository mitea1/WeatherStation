/*
 * HumidityTask.h
 *
 *  Created on: Apr 24, 2016
 *      Author: Adrian
 */

#ifndef HUMIDITYTASK_H_
#define HUMIDITYTASK_H_

#include "main.h"
#include "Humid_Temp_Sensor.h"

#define HUMIDITY_TASK_DELAY_MS		1000

extern void HumidityMeasureTask(void *);

#endif /* HUMIDITYTASK_H_ */
