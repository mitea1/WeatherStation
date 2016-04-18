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
int32_t bmp280_compensate_H_int32_t(int32_t,int32_t);
int64_t bmp280_compensate_P_int64(int32_t, int32_t);

//Globals
uint16_t dig_T1=27504;
int16_t dig_T2=26435;
int16_t dig_T3=-1000;
uint8_t dig_H1=255;
int16_t dig_H2=26435;
uint8_t dig_H3=100;
int16_t dig_H4=27504;
int16_t dig_H5=26435;
int8_t dig_H6=100;
uint16_t dig_P1=-1000;
int16_t dig_P2=-1000;
int16_t dig_P3=-1000;
int16_t dig_P4=-1000;
int16_t dig_P5=-1000;
int16_t dig_P6=-1000;
int16_t dig_P7=-1000;
int16_t dig_P8=-1000;
int16_t dig_P9=-1000;

uint8_t HMDTEMP_initWeatherMonitoring(void){
	//TODO implement Trimvalues H1-H6
	uint8_t config = HMDTEMP_WHEAT_OVRS_T_P;
	uint8_t *data = &config;

	// Data Container for Trim Values Temperature
	uint8_t dig_T1_raw[2];
	uint8_t dig_T2_raw[2];
	uint8_t dig_T3_raw[2];

	// Data Container for Trim Values Pressure
	uint8_t dig_P1_raw[2];
	uint8_t dig_P2_raw[2];
	uint8_t dig_P3_raw[2];
	uint8_t dig_P4_raw[2];
	uint8_t dig_P5_raw[2];
	uint8_t dig_P6_raw[2];
	uint8_t dig_P7_raw[2];
	uint8_t dig_P8_raw[2];
	uint8_t dig_P9_raw[2];

	// Data Container for Trim Values Humidity
	uint8_t dig_H1_raw[1];
	uint8_t dig_H2_raw[2];
	uint8_t dig_H3_raw[1];
	uint8_t dig_H4_raw[2];
	uint8_t dig_H5_raw[2];
	uint8_t dig_H6_raw[1];

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

	// Get the Trim parameters for the exact calculation of the Pressure
	TELTRONIC_I2C_Read(I2C2,HMDTEMP_SENSOR_ADDRESS,HMDTEMP_DIG_P1_LSB,0,&dig_P1_raw[0],1);
	TELTRONIC_I2C_Read(I2C2,HMDTEMP_SENSOR_ADDRESS,HMDTEMP_DIG_P1_MSB,0,&dig_P1_raw[1],1);
	TELTRONIC_I2C_Read(I2C2,HMDTEMP_SENSOR_ADDRESS,HMDTEMP_DIG_P2_LSB,0,&dig_P2_raw[0],1);
	TELTRONIC_I2C_Read(I2C2,HMDTEMP_SENSOR_ADDRESS,HMDTEMP_DIG_P2_MSB,0,&dig_P2_raw[1],1);
	TELTRONIC_I2C_Read(I2C2,HMDTEMP_SENSOR_ADDRESS,HMDTEMP_DIG_P3_LSB,0,&dig_P3_raw[0],1);
	TELTRONIC_I2C_Read(I2C2,HMDTEMP_SENSOR_ADDRESS,HMDTEMP_DIG_P3_MSB,0,&dig_P3_raw[1],1);
	TELTRONIC_I2C_Read(I2C2,HMDTEMP_SENSOR_ADDRESS,HMDTEMP_DIG_P4_LSB,0,&dig_P4_raw[0],1);
	TELTRONIC_I2C_Read(I2C2,HMDTEMP_SENSOR_ADDRESS,HMDTEMP_DIG_P4_MSB,0,&dig_P4_raw[1],1);
	TELTRONIC_I2C_Read(I2C2,HMDTEMP_SENSOR_ADDRESS,HMDTEMP_DIG_P5_LSB,0,&dig_P5_raw[0],1);
	TELTRONIC_I2C_Read(I2C2,HMDTEMP_SENSOR_ADDRESS,HMDTEMP_DIG_P5_MSB,0,&dig_P5_raw[1],1);
	TELTRONIC_I2C_Read(I2C2,HMDTEMP_SENSOR_ADDRESS,HMDTEMP_DIG_P6_LSB,0,&dig_P6_raw[0],1);
	TELTRONIC_I2C_Read(I2C2,HMDTEMP_SENSOR_ADDRESS,HMDTEMP_DIG_P6_MSB,0,&dig_P6_raw[1],1);
	TELTRONIC_I2C_Read(I2C2,HMDTEMP_SENSOR_ADDRESS,HMDTEMP_DIG_P7_LSB,0,&dig_P7_raw[0],1);
	TELTRONIC_I2C_Read(I2C2,HMDTEMP_SENSOR_ADDRESS,HMDTEMP_DIG_P7_MSB,0,&dig_P7_raw[1],1);
	TELTRONIC_I2C_Read(I2C2,HMDTEMP_SENSOR_ADDRESS,HMDTEMP_DIG_P8_LSB,0,&dig_P8_raw[0],1);
	TELTRONIC_I2C_Read(I2C2,HMDTEMP_SENSOR_ADDRESS,HMDTEMP_DIG_P8_MSB,0,&dig_P8_raw[1],1);
	TELTRONIC_I2C_Read(I2C2,HMDTEMP_SENSOR_ADDRESS,HMDTEMP_DIG_P9_LSB,0,&dig_P9_raw[0],1);
	TELTRONIC_I2C_Read(I2C2,HMDTEMP_SENSOR_ADDRESS,HMDTEMP_DIG_P9_MSB,0,&dig_P9_raw[1],1);

	// Convert data into values
	dig_P1=(dig_P1_raw[1]<<8)|dig_P1_raw[0];
	dig_P2=(dig_P2_raw[1]<<8)|dig_P2_raw[0];
	dig_P3=(dig_P3_raw[1]<<8)|dig_P3_raw[0];
	dig_P4=(dig_P4_raw[1]<<8)|dig_P4_raw[0];
	dig_P5=(dig_P5_raw[1]<<8)|dig_P5_raw[0];
	dig_P6=(dig_P6_raw[1]<<8)|dig_P6_raw[0];
	dig_P7=(dig_P7_raw[1]<<8)|dig_P7_raw[0];
	dig_P8=(dig_P8_raw[1]<<8)|dig_P8_raw[0];
	dig_P9=(dig_P9_raw[1]<<8)|dig_P9_raw[0];

	// Get the Trim parameters for the exact calculation of the Humidity
	TELTRONIC_I2C_Read(I2C2,HMDTEMP_SENSOR_ADDRESS,HMDTEMP_DIG_H1_LSB,0,&dig_H1_raw[0],1);
	TELTRONIC_I2C_Read(I2C2,HMDTEMP_SENSOR_ADDRESS,HMDTEMP_DIG_H2_LSB,0,&dig_H2_raw[0],1);
	TELTRONIC_I2C_Read(I2C2,HMDTEMP_SENSOR_ADDRESS,HMDTEMP_DIG_H2_MSB,0,&dig_H2_raw[1],1);
	TELTRONIC_I2C_Read(I2C2,HMDTEMP_SENSOR_ADDRESS,HMDTEMP_DIG_H3_LSB,0,&dig_H3_raw[0],1);
	TELTRONIC_I2C_Read(I2C2,HMDTEMP_SENSOR_ADDRESS,HMDTEMP_DIG_H4_LSB,0,&dig_H4_raw[0],1);
	TELTRONIC_I2C_Read(I2C2,HMDTEMP_SENSOR_ADDRESS,HMDTEMP_DIG_H4_MSB,0,&dig_H4_raw[1],1);
	TELTRONIC_I2C_Read(I2C2,HMDTEMP_SENSOR_ADDRESS,HMDTEMP_DIG_H5_LSB,0,&dig_H5_raw[0],1);
	TELTRONIC_I2C_Read(I2C2,HMDTEMP_SENSOR_ADDRESS,HMDTEMP_DIG_H5_MSB,0,&dig_H5_raw[1],1);
	TELTRONIC_I2C_Read(I2C2,HMDTEMP_SENSOR_ADDRESS,HMDTEMP_DIG_H6_LSB,0,&dig_H6_raw[0],1);

	// Convert data into values
	dig_H1=dig_H1_raw[0];
	dig_H2=(dig_H2_raw[1]<<8)|dig_H2_raw[0];
	dig_H3=dig_H3_raw[0];
	dig_H4=(dig_H4_raw[1]<<4)|(dig_H4_raw[0] & 0x0F);
	dig_H5=(4>>(dig_H5_raw[1] & 0xF0))|(dig_H5_raw[0]<<4);
	dig_H6=dig_H6_raw[0];

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
	int32_t temp_raw = (int32_t) (temp_msb[0]<<12|temp_lsb[0]<<4|temp_xlsb[0]);
	int32_t temp_fine = bmp280_compensate_T_int32(temp_raw);

	return temp_fine;
}

/**
 * Returns the Lux value from the Light Sensor
 *
 */
int32_t HMDTEMP_getHumidity(void){

	//TODO do not use before Trim Values H1-H6 are known
	// Error Value
	uint8_t error;

	// Data Containers
	uint8_t hum_msb[1];
	uint8_t hum_lsb[1];

	// Get Data via I2C
	error = TELTRONIC_I2C_Read(
			I2C2,HMDTEMP_SENSOR_ADDRESS,HMDTEMP_SENSOR_HUM_MSB,0,hum_msb,1);
	error = TELTRONIC_I2C_Read(
			I2C2,HMDTEMP_SENSOR_ADDRESS,HMDTEMP_SENSOR_HUM_LSB,0,hum_lsb,1);

	// Get exact Temperature for the humidity calculation
	int32_t temp_fine = HMDTEMP_getTemperature();

	//Build raw temp value from received data
	int32_t hum_raw = (int32_t) (hum_msb[0]<<8|hum_lsb[0]);
	int32_t hum_fine = bmp280_compensate_H_int32_t(hum_raw,temp_fine);

	return hum_fine;
}

/**
 * Returns the Lux value from the Light Sensor
 *
 */
int32_t HMDTEMP_getPressure(void){

	//TODO do not use before Trim Values H1-H6 are known
	// Error Value
	uint8_t error;

	// Data Containers
	uint8_t press_msb[1];
	uint8_t press_lsb[1];
	uint8_t press_xlsb[1];

	// Get Data via I2C
	error = TELTRONIC_I2C_Read(
			I2C2,HMDTEMP_SENSOR_ADDRESS,HMDTEMP_SENSOR_PRESS_MSB,0,press_msb,1);
	error = TELTRONIC_I2C_Read(
			I2C2,HMDTEMP_SENSOR_ADDRESS,HMDTEMP_SENSOR_PRESS_LSB,0,press_lsb,1);
	error = TELTRONIC_I2C_Read(
			I2C2,HMDTEMP_SENSOR_ADDRESS,HMDTEMP_SENSOR_PRESS_XLSB,0,press_xlsb,1);

	// Get exact Temperature for the humidity calculation
	int32_t temp_fine = HMDTEMP_getTemperature();

	//Build raw temp value from received data
	int32_t press_raw = (int32_t) (press_msb[0]<<12|press_lsb[0]<<4|press_xlsb[0]);
	int32_t press_fine = bmp280_compensate_P_int64(press_raw,temp_fine);

	return press_fine;
}

/**
 * Calculates the exact temperature. It's necessary to get the Trim values
 * dig_T1,dig_T2,dig_T3 from the sensor first before using this function.
 * Output value of “5123” equals 51.23 DegC
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

/**
 * Calculates the exact humidity. It's necessary to get the Trim values
 * dig_H1,dig_H2,dig_H3,dig_H4,dig_H5,dig_H6
 * from the sensor first before using this function
 * Output value of “47445” represents 47445/1024 = 46.333 %RH
 */
int32_t bmp280_compensate_H_int32_t(int32_t adc_H,int32_t temp_fine)
{
	int32_t v_x1_u32r;

	v_x1_u32r =  temp_fine - ((int32_t)76800);

	v_x1_u32r = (((((adc_H << 14) - (((int32_t)dig_H4) << 20) - (((int32_t)dig_H5) * v_x1_u32r)) +
			((int32_t)16384)) >> 15) * (((((((v_x1_u32r * ((int32_t)dig_H6)) >> 10) * (((v_x1_u32r *
					((int32_t)dig_H3)) >> 11) + ((int32_t)32768))) >> 10) + ((int32_t)2097152)) *
					((int32_t)dig_H2) + 8192) >> 14));

	v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) * ((int32_t)dig_H1)) >> 4));
	v_x1_u32r = (v_x1_u32r < 0 ? 0 : v_x1_u32r);
	v_x1_u32r = (v_x1_u32r > 419430400 ? 419430400 : v_x1_u32r);

	return (int32_t)(v_x1_u32r>>12);
}
/**
 * Calculates the exact pressure. Is's necessary to get the Trim values dig_P1 to dig_P9
 * Output value of “24674867” represents 24674867/256 = 96386.2 Pa = 963.862 hPa
 */
// Returns pressure in Pa as unsigned 32 bit integer in Q24.8 format (24 integer bits and 8 fractional bits).
// Output value of “24674867” represents 24674867/256 = 96386.2 Pa = 963.862 hPa
int64_t bmp280_compensate_P_int64(int32_t adc_P, int32_t temp_fine)
{
	int64_t var1, var2, p;
	var1 = ((int64_t)temp_fine) - 128000;
	var2 = var1 * var1 * (int64_t)dig_P6;
	var2 = var2 + ((var1*(int64_t)dig_P5)<<17);
	var2 = var2 + (((int64_t)dig_P4)<<35);
	var1 = ((var1 * var1 * (int64_t)dig_P3)>>8) + ((var1 * (int64_t)dig_P2)<<12);
	var1 = (((((int64_t)1)<<47)+var1))*((int64_t)dig_P1)>>33;
	if (var1 == 0)
	{
		return 0; // avoid exception caused by division by zero
	}
	p = ((int64_t)1048576)-adc_P;
	p = (((p<<31)-var2)*((int64_t)3125))/var1;
	var1 = (((int64_t)dig_P9) * (p>>13) * (p>>13)) >> 25;
	var2 = (((int64_t)dig_P8) * p) >> 19;
	p = ((p + var1 + var2) >> 8) + (((int64_t)dig_P7)<<4);
	return (int32_t)p;
}
