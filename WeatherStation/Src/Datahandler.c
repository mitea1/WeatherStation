/*
 * Datahandler.c
 *
 *  Created on: Apr 18, 2016
 *      Author: Adrian
 */
#include "Datahandler.h"

/**
 * @brief Handles all the Data from the different Sensors and shows
 * them via UART
 * @param pvargs
 */
void DataHandlerTask(void *pvargs) {

	char lightMsgBuffer[DATAHANDLER_MSG_SIZE];
	char temperatureMsgBuffer[DATAHANDLER_MSG_SIZE];
	char humidityMsgBuffer[DATAHANDLER_MSG_SIZE];
	char pressureMsgBuffer[DATAHANDLER_MSG_SIZE];
	uint16_t luxValue;
	int16_t temperatureValue;
	int16_t humditityValue;
	int16_t pressureValue;

	// A quick scan trough all message queues
	for (;;) {

		// Quick check for stored message in light queue
		if(xQueueReceive(queueLight,(void*)&luxValue,portTICK_PERIOD_MS) == pdTRUE){
			sprintf(lightMsgBuffer,"%d",luxValue);
			UART1_Write("Light: ");
			UART1_Write(lightMsgBuffer);
			UART1_Write("lux\n");
		}

		// Quick check for stored message in temperature queue
		if(xQueueReceive(queueTemperature,(void*)&temperatureValue,portTICK_PERIOD_MS) == pdTRUE){
			sprintf(lightMsgBuffer,"%d",temperatureValue);
			UART1_Write("Temperature: ");
			UART1_Write(lightMsgBuffer);
			UART1_Write("°C\n");
		}

		// Quick check for stored message in humidity queue
		if(xQueueReceive(queueHumidity,(void*)&humditityValue,portTICK_PERIOD_MS) == pdTRUE){
			sprintf(humidityMsgBuffer,"%d",humditityValue);
			UART1_Write("Humidity: ");
			UART1_Write(lightMsgBuffer);
			UART1_Write("%\n");
		}

		// Quick check for stored message in pressure queue
		if(xQueueReceive(queueHumidity,(void*)&pressureValue,portTICK_PERIOD_MS) == pdTRUE){
			sprintf(pressureMsgBuffer,"%d",pressureValue);
			UART1_Write("Pressure: ");
			UART1_Write(pressureMsgBuffer);
			UART1_Write("hPa\n");
		}

		osDelay(DATAHANDLER_TASK_DELAY_MS);
	}
}

