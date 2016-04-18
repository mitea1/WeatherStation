/*
 * Datahandler.h
 *
 *  Created on: Apr 18, 2016
 *      Author: Adrian
 */

#ifndef DATAHANDLER_H_
#define DATAHANDLER_H_

#include "main.h"
#include "TELTRONIC_UART.h"

#define DATAHANDLER_TASK_DELAY_MS		1000
#define DATAHANDLER_MSG_SIZE			10

extern void DataHandlerTask(void*);


#endif /* DATAHANDLER_H_ */
