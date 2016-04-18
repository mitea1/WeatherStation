/*
 * Datahandler.c
 *
 *  Created on: Apr 18, 2016
 *      Author: Adrian
 */
#include "Datahandler.h"

/**
 * @brief Handles all the Data from the different Sensor Message Queues
 * @param pvargs
 */
void DataHandlerTask(void *pvargs) {

	char lightMsgBuffer[DATAHANDLER_MSG_SIZE];
	uint16_t luxValue;

	for (;;) {
		// Wait for LightQueue Message
		if(xQueueReceive(queueLight,(void*)&luxValue,portMAX_DELAY) == pdTRUE){
			sprintf(lightMsgBuffer,"%d",luxValue);
			UART1_Write("Lux: ");
			UART1_Write(lightMsgBuffer);
			UART1_Write("\n");
		}
		UART1_Write("DataHandler\n");
		osDelay(DATAHANDLER_TASK_DELAY_MS);
	}
}

