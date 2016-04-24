/*
 * PressureTask.h
 *
 *  Created on: Apr 24, 2016
 *      Author: Adrian
 */

#ifndef PRESSURETASK_H_
#define PRESSURETASK_H_

#include "main.h"
#include "Humid_Temp_Sensor.h"

#define PRESSURE_TASK_DELAY_MS		1000

void PressureMeasureTask(void *pvargs);



#endif /* PRESSURETASK_H_ */
