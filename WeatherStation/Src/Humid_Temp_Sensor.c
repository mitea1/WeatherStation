/*
 * Humid_Temp_Sensor.c
 *
 *  Created on: Mar 31, 2016
 *      Author: Adrian
 */

#include "TELTRONIC_I2C.h"
#include "Humid_Temp_Sensor.h"

//Functions
int32_t bmp280_compensate_T_int32(int32_t);

//Globals
int16_t dig_T1=27504;
int16_t dig_T2=26435;
int16_t dig_T3=-1000;

uint8_t HMDTEMP_initWeatherMonitoring(void){

	uint8_t config = HMDTEMP_WHEAT_OVRS_T_P;
	uint8_t *data = &config;

	// Data Container for Trim Values
	uint8_t dig_T1_raw[2];
	uint8_t dig_T2_raw[2];
	uint8_t dig_T3_raw[2];

	// Initialize I2C
	TELTRONIC_I2C_Init(I2C2);

	// Set Configurations for Wheater Monitoring
	TELTRONIC_I2C_Write(I2C2,HMDTEMP_SENSOR_ADDRESS,HMDTEMP_SENSOR_CTRL_MEAS,0,data,1);

	// Get the Trim parameters for the exact calculation of the Temperature
	TELTRONIC_I2C_Read(I2C2,HMDTEMP_SENSOR_ADDRESS,HMDTEMP_DIG_T1_LSB,0,&dig_T1_raw[0],1);
	TELTRONIC_I2C_Read(I2C2,HMDTEMP_SENSOR_ADDRESS,HMDTEMP_DIG_T1_MSB,0,&dig_T1_raw[1],1);
	TELTRONIC_I2C_Read(I2C2,HMDTEMP_SENSOR_ADDRESS,HMDTEMP_DIG_T2_LSB,0,&dig_T2_raw[0],1);
	TELTRONIC_I2C_Read(I2C2,HMDTEMP_SENSOR_ADDRESS,HMDTEMP_DIG_T2_MSB,0,&dig_T2_raw[1],1);
	TELTRONIC_I2C_Read(I2C2,HMDTEMP_SENSOR_ADDRESS,HMDTEMP_DIG_T3_LSB,0,&dig_T3_raw[0],1);
	TELTRONIC_I2C_Read(I2C2,HMDTEMP_SENSOR_ADDRESS,HMDTEMP_DIG_T3_MSB,0,&dig_T3_raw[1],1);

	// Convert data into values
	dig_T1=(dig_T1_raw[1]<<8)|dig_T1_raw[0];
	dig_T2=(dig_T2_raw[1]<<8)|dig_T2_raw[0];
	dig_T3=(dig_T3_raw[1]<<8)|dig_T3_raw[0];


	return 0;
}

/**
 * Returns the Lux value from the Light Sensor
 */
int32_t HMDTEMP_getTemperature(void){

	// Error Value
	uint8_t error;

	// Data Containers
	uint8_t temp_msb[1];
	uint8_t temp_lsb[1];
	uint8_t temp_xlsb[1];

	// Get Data via I2C
	error = TELTRONIC_I2C_Read(
			I2C2,HMDTEMP_SENSOR_ADDRESS,HMDTEMP_SENSOR_TEMP_MSB,0,temp_msb,1);
	error = TELTRONIC_I2C_Read(
			I2C2,HMDTEMP_SENSOR_ADDRESS,HMDTEMP_SENSOR_TEMP_LSB,0,temp_lsb,1);
	error = TELTRONIC_I2C_Read(
			I2C2,HMDTEMP_SENSOR_ADDRESS,HMDTEMP_SENSOR_TEMP_XLSB,0,temp_xlsb,1);

	//Build raw temp value from received data
	int32_t temp_raw = (int32_t) (temp_msb[0]<<12|temp_lsb[0]<<3|temp_xlsb[0]);
	int32_t temp_fine = bmp280_compensate_T_int32(temp_raw);

	return temp_fine;
}

/**
 * Calculates the exact temperature. It's necessary to get the Trim values
 * dig_T1,dig_T2,dig_T3 from the sensor first before using this function
 */
int32_t bmp280_compensate_T_int32(int32_t adc_T)
{
	int32_t var1, var2, T;
	var1  = ((((adc_T>>3) - ((int32_t)dig_T1<<1))) * ((int32_t)dig_T2)) >> 11;
	var2  = (((((adc_T>>4) - ((int32_t)dig_T1)) * ((adc_T>>4) - ((int32_t)dig_T1))) >> 12) *
	((int32_t)dig_T3)) >> 14;
	int32_t t_fine = var1 + var2;
	T  = (t_fine * 5 + 128) >> 8;
	return T;
}
