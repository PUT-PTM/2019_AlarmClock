/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
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
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32f4xx_hal.h"
#include "ds3231.h"
#include "i2c-lcd.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
DAC_HandleTypeDef hdac;

I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c2;

TIM_HandleTypeDef htim4;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_I2C2_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_DAC_Init(void);
static void MX_TIM4_Init(void);
/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

	HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET;

	HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,SET);
   	  lcd_clear();
   	  int number=5;
   	  lcd_send_cmd(0x80);
   	  lcd_send_integer(number,2);
}




/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	uint8_t str1[]="USART Transmit\r\n";
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_I2C2_Init();
  MX_USART2_UART_Init();
  MX_DAC_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */

  int trzy=5;
  int minuty=0;
   int dziala=0;
   int prescaler=83;
   volatile int realgodziny=0;
   volatile int realminuty=0;
   int flaga=0;
   int clearc=0;
   volatile int dupa=0;
   volatile int alarmhour=0;
   volatile int alarm_sound=1;

   volatile int date_day=1, date_month=1, date_year=0;
   volatile int alarmin=0;
  //day -> dzien tygodnia od 1-7, date -> dzien miesiaca
  day= 5, date = 30, month = 5, year = 19;
  DS3231_setDate(day, date, month, year);


  hour = 19, minute = 17, seconds = 10;
  DS3231_setTime(hour, minute, seconds);
  //hour = 0, minute = 1, seconds = 0;
  //DS3231_setTime(hour, minute, seconds);

  //hour = 21, minute = 44, seconds = 0;
  //DS3231_setAlarm_e(hour, minute, seconds);

  //HAL_UART_Transmit(&huart2,str1,16,0xFFFF);
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, 1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	 getTimeAndDate();
	 switch(flaga)
	 {

	 case 0:

		 	 	 HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_RESET);
	 		 	 if(clearc==2)
	 		 	 {
	 		 		 lcd_clear();
	 		 	 }

	 		 	 clearc=1;
	 		 	 if(DS3231_Time.hours<10)
	 		 	 {
	 	 		 	 lcd_send_cmd (0x80);  // goto 1,1
	 	 		 	 lcd_send_integer(0,1);
	 	 		 	 lcd_send_cmd(0x81);
	 	 			 lcd_send_integer(DS3231_Time.hours,1);
	 		 	 }
	 		 	 if(DS3231_Time.hours>=10)
	 		 	 {
	 		 	 		 lcd_send_cmd (0x80);  // goto 1,1

	 		 	 		 lcd_send_integer(DS3231_Time.hours,2);
	 		 	 }

	 	 		lcd_send_cmd (0x82);
	 	 		lcd_send_string(":");

	 	 		if(DS3231_Time.minutes<10)
	 	 		{
	 	 			lcd_send_cmd (0x83);  // goto 1,1
	 	 			lcd_send_integer(0,1);
	 	 			lcd_send_cmd(0x84);
	 	 			lcd_send_integer(DS3231_Time.minutes,1);
	 	 		}

	 	 		if(DS3231_Time.minutes>=10)
	 	 		{
	 	 			lcd_send_cmd (0x83);  // goto 1,1
	 	 		    lcd_send_integer(DS3231_Time.minutes,2);
	 	 		}

	 	 		lcd_send_cmd (0x85);
	 	 		lcd_send_string(":");

	 	 		if(DS3231_Time.seconds<10)
	 	 		{
	 	 			lcd_send_cmd (0x86);
	 	 			lcd_send_integer(0,1);
	 	 			lcd_send_cmd(0x87);
	 	 			lcd_send_integer(DS3231_Time.seconds,1);
	 	 		}

	 	 		if(DS3231_Time.seconds>=10)
	 	 		{
	 	 				lcd_send_cmd (0x86);
	 	 				lcd_send_integer(DS3231_Time.seconds,2);
	 	 		}

	 	 		//////date////
	 	 		if(DS3231_Time.date<10)
	 	 		{
	 	 			lcd_send_cmd(0xc0);
	 	 			lcd_send_integer(0,1);
	 	 			lcd_send_cmd(0xc1);
	 	 			lcd_send_integer(DS3231_Time.date,1);
	 	 		}
	 	 		if(DS3231_Time.date>=10)
	 	 		{
	 	 			lcd_send_cmd(0xc0);
	 	 			lcd_send_integer(DS3231_Time.date,2);
	 	 		}
	 	 		lcd_send_cmd(0xc2);
	 	 		lcd_send_string(".");

	 	 		if(DS3231_Time.month<10)
	 	 		{
	 	 			lcd_send_cmd(0xc3);
	 	 			lcd_send_integer(0,1);
	 	 			lcd_send_cmd(0xc4);
	 	 			lcd_send_integer(DS3231_Time.month,1);
	 	 		}
	 	 		if(DS3231_Time.month>=10)
	 	 		{
	 	 			lcd_send_cmd(0xc3);
	 	 			lcd_send_integer(DS3231_Time.month,2);
	 	 		}

	 	 		lcd_send_cmd(0xc5);
	 	 		lcd_send_string(".");
	 	 		if(DS3231_Time.year<10)
	 	 		{
	 	 			 	lcd_send_cmd(0xc6);
	 	 			 	lcd_send_integer(0,1);
	 	 			 	lcd_send_cmd(0xc7);
	 	 			 	lcd_send_integer(DS3231_Time.year,1);
	 	 		}
	 	 		if(DS3231_Time.year>=10)
	 	 		{
	 	 			 	lcd_send_cmd(0xc6);
	 	 			 	lcd_send_integer(DS3231_Time.year,2);
	 	 		}


	 	 		// clearc=1;
	 	 		HAL_Delay(1000);
	 	  break;
	 	 case 1:
	 	 {
	 		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_12,GPIO_PIN_SET);
	 		if(clearc==1)
	 		{
	 			lcd_clear();
	 		}
	 		clearc=2;


	 		lcd_send_cmd (0x80);
	 		lcd_send_string("Ustawianie czasu");
	 		if(realgodziny<10)
	 		{
	 			lcd_send_cmd(0xc0);
	 			lcd_send_integer(0,1);
	 			lcd_send_cmd(0xc1);
	 			lcd_send_integer(realgodziny,1);
	 		}
	 		if(realgodziny>=10)
	 		{
	 			lcd_send_cmd(0xc0);
	 			lcd_send_integer(realgodziny,2);
	 		}

	 		lcd_send_cmd (0xc2);
	 		lcd_send_string(":");
	 		if(dupa<10)
	 		{
	 			lcd_send_cmd(0xc3);
	 			lcd_send_integer(0,1);
	 			lcd_send_cmd(0xc4);
	 			lcd_send_integer(dupa,1);
	 		}
	 		if(dupa>=10)
	 		{
	 			lcd_send_cmd(0xc3);
	 			lcd_send_integer(dupa,2);
	 		}



	 		HAL_Delay(1000);

	 		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == 1)
	 		{
	 				flaga=0;
	 		}
	 		if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_9) == 1)
	 		{
	 			 	flaga=3;
	 		}
	 		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) == 1)
	 		{
	 				realgodziny++;
	 		}
	 		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == 1)
	 		{
	 				dupa++;
	 		}
	 		if(realgodziny==24)
	 		{
	 				lcd_clear();
	 				realgodziny=0;
	 		}
	 		if(dupa==60)
	 		{
	 				lcd_clear();
	 				dupa=0;
	 		}
	 		if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == 1)
	 		{
	 				 DS3231_setTime(realgodziny, dupa, 0);
	 				 realgodziny=0;
	 				 dupa=0;
	 				 flaga=0;
	 		}
	 		break;

	 	 }
	 	case 2:
	 	{
	 			 if(clearc==1)
	 			 {
	 				lcd_clear();
	 			 }
	 			clearc=2;

	 			lcd_send_cmd (0x80);
	 			lcd_send_string(" Budzik");
	 			if(alarmhour<10)
	 			{
	 				lcd_send_cmd(0xc0);
	 				lcd_send_integer(0,1);
	 				lcd_send_cmd(0xc1);
	 				lcd_send_integer(alarmhour,1);
	 			}
	 			if(alarmhour>=10)
	 			{
	 				lcd_send_cmd(0xc0);
	 				lcd_send_integer(alarmhour,2);
	 			}

	 			lcd_send_cmd (0xc2);
	 			lcd_send_string(":");
	 			if(alarmin<10)
	 			{
	 				lcd_send_cmd(0xc3);
	 				lcd_send_integer(0,1);
	 				lcd_send_cmd(0xc4);
	 				lcd_send_integer(alarmin,1);
	 			}
	 			if(alarmin>=10)
	 			{
	 				lcd_send_cmd(0xc3);
	 				lcd_send_integer(alarmin,2);
	 			}

	 			lcd_send_cmd (0xc5);
	 			lcd_send_string("m");
	 			lcd_send_cmd (0xc6);
	 			lcd_send_string("u");
	 			lcd_send_cmd (0xc7);
	 			lcd_send_string("z");
	 			lcd_send_cmd (0xc8);
	 			lcd_send_string(":");
	 			lcd_send_cmd (0xc9);
	 			lcd_send_integer(alarm_sound,1);

	 			HAL_Delay(1000);

	 			if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) == 1)
	 			{
	 				alarmhour++;
	 				if(alarmhour>23)//dodalem do zerowania
	 					alarmhour=0;//dodalem do zerowania
	 			}
	 			if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == 1)
	 			{
	 				alarmin++;
	 				if(alarmin>59)//dodalem do zerowania
	 					alarmin=0;//dodalem do zerowania
	 			}
	 			if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_7) == 1)
	 			{
	 				 alarm_sound++;
	 				 if(alarm_sound>3)
	 					 alarm_sound=1;
	 			}



	 			if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == 1)
	 			{
	 				DS3231_setAlarm_e(alarmhour, alarmin, 0, alarm_sound);
	 				flaga=0;
	 			}




	 			if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == 1)
	 			{
	 				flaga=0;
	 			}

	 			if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_9) == 1)
	 			{
	 				lcd_clear();
	 				 flaga=3;
	 			}
	 			break;

	 }
	 //ustawianie daty
	 	case 3: //gpio e9
	 	{
	 		 			 if(clearc==1)
	 		 			 {
	 		 				lcd_clear();
	 		 			 }
	 		 			clearc=2;

	 		 			lcd_send_cmd (0x80);
	 		 			lcd_send_string(" Ustawianie daty");
	 		 			if(date_day<10)
	 		 			{
	 		 				lcd_send_cmd(0xc0);
	 		 				lcd_send_integer(0,1);
	 		 				lcd_send_cmd(0xc1);
	 		 				lcd_send_integer(date_day,1);
	 		 			}
	 		 			if(date_day>=10)
	 		 			{
	 		 				lcd_send_cmd(0xc0);
	 		 				lcd_send_integer(date_day,2);
	 		 			}

	 		 			lcd_send_cmd (0xc2);
	 		 			lcd_send_string(".");
	 		 			if(date_month<10)
	 		 			{
	 		 				lcd_send_cmd(0xc3);
	 		 				lcd_send_integer(0,1);
	 		 				lcd_send_cmd(0xc4);
	 		 				lcd_send_integer(date_month,1);
	 		 			}
	 		 			if(date_month>=10)
	 		 			{
	 		 				lcd_send_cmd(0xc3);
	 		 				lcd_send_integer(date_month,2);
	 		 			}
	 		 			lcd_send_cmd (0xc5);
	 		 			lcd_send_string(".");
	 		 			if(date_year<10)
	 		 			{
	 		 				lcd_send_cmd(0xc6);
	 		 				lcd_send_integer(0,1);
	 		 				lcd_send_cmd(0xc7);
	 		 				lcd_send_integer(date_year,1);
	 		 			}
	 		 			if(date_year>=10)
	 		 			{
	 		 				lcd_send_cmd(0xc6);
	 		 				lcd_send_integer(date_year,2);
	 		 			}

	 		 			HAL_Delay(1000);

	 		 			if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) == 1)
	 		 			{
	 		 				date_day++;
	 		 				if(date_day>31)//dodalem do zerowania
	 		 					date_day=1;//dodalem do zerowania
	 		 			}
	 		 			if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == 1)
	 		 			{
	 		 				date_month++;
	 		 				if(date_month>12)//dodalem do zerowania
	 		 					date_month=1;//dodalem do zerowania
	 		 			}
	 		 			if(HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_7) == 1)
	 		 			{
	 		 				 date_year++;
	 		 				 if(date_year>99)
	 		 					 date_year=0;
	 		 			}



	 		 			if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == 1)
	 		 			{
	 		 				DS3231_setDate(2,date_day, date_month, date_year);
	 		 				flaga=0;
	 		 			}




	 		 			if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2) == 1)
	 		 			{
	 		 				flaga=0;
	 		 			}

	 		 			break;

	 	}



	 }

	 if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == 1)
	 {
		 	 realgodziny=DS3231_Time.hours;
		 	 dupa=DS3231_Time.minutes;
		 	 lcd_clear();
			 flaga=1;
	 }

	 if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1) == 1)
	 {
		 	alarmhour=DS3231_Time.hours; //zeby dlugo nie ustawiac alarmu
		 	alarmin=DS3231_Time.minutes;//zeby dlugo nie ustawiac alarmu
		 	lcd_clear();
	 		flaga=2;
	 }

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /**Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 164;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief DAC Initialization Function
  * @param None
  * @retval None
  */
static void MX_DAC_Init(void)
{

  /* USER CODE BEGIN DAC_Init 0 */

  /* USER CODE END DAC_Init 0 */

  DAC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN DAC_Init 1 */

  /* USER CODE END DAC_Init 1 */
  /**DAC Initialization 
  */
  hdac.Instance = DAC;
  if (HAL_DAC_Init(&hdac) != HAL_OK)
  {
    Error_Handler();
  }
  /**DAC channel OUT1 config 
  */
  sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
  if (HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /**DAC channel OUT2 config 
  */
  if (HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DAC_Init 2 */

  /* USER CODE END DAC_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.ClockSpeed = 100000;
  hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 45;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 59;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA8 PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_8|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 PB4 
                           PB5 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_4 
                          |GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PE7 PE9 */
  GPIO_InitStruct.Pin = GPIO_PIN_7|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : PD12 PD13 PD14 PD15 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
