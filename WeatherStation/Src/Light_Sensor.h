/*
 * Light_Sensor.h
 *
 *  Created on: Mar 16, 2016
 *      Author: Adrian
 */

#ifndef LIGHT_SENSOR_H_
#define LIGHT_SENSOR_H_

//Addresses of the MAX44009 Light Sensor
#define LIGHT_SENSOR_ADDRESS 		0b10010100
#define LIGHT_SENSOR_CONFIG			0x02
#define LIGHT_SENSOR_LUX_H_BYTE		0x03
#define LIGHT_SENSOR_LUX_L_BYTE		0x04
#define LIGHT_SENSOR_LUX_H_L_BYTE	0x0304



// Functions

extern double LIGHT_SENSOR_getLux(void);

#endif /* LIGHT_SENSOR_H_ */
