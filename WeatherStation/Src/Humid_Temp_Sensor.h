/*
 * Humid_Temp_Sensor.h
 *
 *  Created on: Mar 31, 2016
 *      Author: Adrian
 */

#ifndef HUMID_TEMP_SENSOR_H_
#define HUMID_TEMP_SENSOR_H_

//Addresses of the BME280 Sensor
#define HMDTEMP_SENSOR_ADDRESS 		0b11101110
#define HMDTEMP_SENSOR_ID			0xD0
#define HMDTEMP_SENSOR_RESET		0xE0
#define HMDTEMP_SENSOR_CTRL_HUM		0xF2
#define HMDTEMP_SENSOR_STATUS		0xF3
#define HMDTEMP_SENSOR_CTRL_MEAS	0xF4
#define HMDTEMP_SENSOR_CONFIG		0xF5
#define HMDTEMP_SENSOR_PRESS_MSB	0xF7
#define HMDTEMP_SENSOR_PRESS_LSB	0xF8
#define HMDTEMP_SENSOR_PRESS_XLSB	0xF9
#define HMDTEMP_SENSOR_TEMP_MSB		0x00FA
#define HMDTEMP_SENSOR_TEMP_LSB		0x00FB
#define HMDTEMP_SENSOR_TEMP_XLSB	0x00FC
#define HMDTEMP_SENSOR_HUM_MSB		0xFD
#define HMDTEMP_SENSOR_HUM_LSB		0xFE

// CTRL_HUM  Humidity oversampling Settings
#define HMDTEMP_HUM_SKPPD			0b000
#define HMDTEMP_HUM_OVRS_1			0b001
#define HMDTEMP_HUM_OVRS_2			0b010
#define HMDTEMP_HUM_OVRS_4			0b011
#define HMDTEMP_HUM_OVRS_8			0b100
#define HMDTEMP_HUM_OVRS_16			0b101

// CTRL_HUM  Pressure oversampling Settings
#define HMDTEMP_PRESS_SKPPD			0b000
#define HMDTEMP_PRESS_OVRS_1		0b001
#define HMDTEMP_PRESS_OVRS_2		0b010
#define HMDTEMP_PRESS_OVRS_4		0b011
#define HMDTEMP_PRESS_OVRS_8		0b100
#define HMDTEMP_PRESS_OVRS_16		0b101

// CTRL_HUM  Temperature oversampling Settings
#define HMDTEMP_TEMP_SKPPD			0b000
#define HMDTEMP_TEMP_OVRS_1			0b001
#define HMDTEMP_TEMP_OVRS_2			0b010
#define HMDTEMP_TEMP_OVRS_4			0b011
#define HMDTEMP_TEMP_OVRS_8			0b100
#define HMDTEMP_TEMP_OVRS_16		0b101

// Trimming Parameters Temperature & Pressure
#define HMDTEMP_DIG_T1_LSB			0x88
#define HMDTEMP_DIG_T1_MSB			0x89
#define HMDTEMP_DIG_T2_LSB			0x8A
#define HMDTEMP_DIG_T2_MSB			0x8B
#define HMDTEMP_DIG_T3_LSB			0x8C
#define HMDTEMP_DIG_T3_MSB			0x8D
#define HMDTEMP_DIG_H1_LSB			0xA1
#define HMDTEMP_DIG_H2_LSB			0xE1
#define HMDTEMP_DIG_H2_MSB			0xE2
#define HMDTEMP_DIG_H3_LSB			0xE3
#define HMDTEMP_DIG_H4_MSB			0xE4
#define HMDTEMP_DIG_H4_LSB			0xE5
#define HMDTEMP_DIG_H5_LSB			0xE6
#define HMDTEMP_DIG_H5_MSB			0xE5
#define HMDTEMP_DIG_H6_LSB			0xE7

// CTRL_MEAS Settings Modes
#define HMDTEMP_SLEEP_MODE			0b00
#define HMDTEMP_FORCED_MODE			0b01
#define HMDTEMP_NORMAL_MODE			0b11


//Oversampling Settings
#define HMDTEMP_WHEAT_OVRS_T_P		(HMDTEMP_TEMP_OVRS_1<<5)|(HMDTEMP_PRESS_OVRS_1<<2)|HMDTEMP_NORMAL_MODE
#define HMDTEMP_WHEAT_OVRS_H		HMDTEMP_HUM_OVRS_1

// Functions
extern uint8_t HMDTEMP_initWeatherMonitoring(void);
extern int32_t HMDTEMP_getTemperature(void);
extern int32_t HMDTEMP_getHumidity(void);

#endif /* HUMID_TEMP_SENSOR_H_ */
