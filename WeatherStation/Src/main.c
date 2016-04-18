/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2016 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal.h"
#include "cmsis_os.h"
#include "TELTRONIC_I2C.h"
#include "Light_Sensor.h"
#include "Humid_Temp_Sensor.h"


/* Private variables ---------------------------------------------------------*/
osThreadId defaultTaskHandle;
SemaphoreHandle_t xSemaphore_I2C;
SemaphoreHandle_t xSemaphore_Humidity;
SemaphoreHandle_t xSemaphore_Temperature;
SemaphoreHandle_t xSemaphore_Pressure;
SemaphoreHandle_t xSemaphore_Light;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void LightMeasureTask(void *pvargs);
static void TempMeasureTask(void *pvargs);

/* Private function prototypes -----------------------------------------------*/

int main(void)
{

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Hardware Configuration */
  LIGHT_SENSOR_init();
  HMDTEMP_initWeatherMonitoring();



  /* Semaphore creation */
  xSemaphore_I2C = xSemaphoreCreateMutex();
  xSemaphore_Humidity = xSemaphoreCreateBinary();
  xSemaphore_Temperature = xSemaphoreCreateBinary();
  xSemaphore_Pressure = xSemaphoreCreateBinary();
  xSemaphore_Light = xSemaphoreCreateBinary();

  /* Task creation */
//  xTaskCreate(LightMeasureTask, "Light Measurment Task", 200U, NULL, 4U, NULL);
//  xTaskCreate(TempMeasureTask, "Temperature Measurment Task", 200U, NULL, 4U, NULL);
//  vTaskStartScheduler();

  while (1)
  {

  }
  return 0;

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_5;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0);

  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 15, 0);
}


///**
// * @brief		Task that reads the Lux value from
// * 				the Lightsensor
// */
//static void LightMeasureTask(void *pvargs) {
//
//	double lux_value;
//	for (;;) {
//		// Wait for i2c bus access
//		if(xSemaphoreTake(xSemaphore_I2C,portMAX_DELAY) == pdTRUE){
//			lux_value = LIGHT_SENSOR_getLux();
//			xSemaphoreGive(xSemaphore_I2C);
//		}
//		osDelay(500);
//	}
//}
//
//static void TempMeasureTask(void *pvargs) {
//
//	uint32_t temp_value;
//	for (;;) {
//		// Wait for i2c bus access
//		if(xSemaphoreTake(xSemaphore_I2C,portMAX_DELAY) == pdTRUE){
//			temp_value = HMDTEMP_getTemperature();
//			xSemaphoreGive(xSemaphore_I2C);
//		}
//		osDelay(500);
//	}
//}


















#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
