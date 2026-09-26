/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdio.h>


#define OLED_ADDR (0x3C << 1)
#define OLED_CONTROL_CMD 0x00

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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
ADC_HandleTypeDef hadc1;

I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim3;

/* USER CODE BEGIN PV */

uint16_t dig_T1 = 0;
int16_t dig_T2 = 0;
int16_t dig_T3 = 0;


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_TIM3_Init(void);
static void MX_I2C1_Init(void);


/* USER CODE BEGIN PFP */

void OLED_SendCommand(uint8_t command);
void OLED_SendData(uint8_t dataByte);
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawChar(const uint8_t *character);
void OLED_DrawCharacter(char character);
void OLED_DrawText(const char *text);
void BMP280_Init(void);

int32_t BMP280_ReadTemperature(void);


uint8_t letter_H[5] =
{
    0xFF,
    0x08,
    0x08,
    0x08,
    0xFF
};

uint8_t letter_E[5] =
{
    0xFF,
    0x89,
    0x89,
    0x89,
    0x89
};

uint8_t letter_L[5] =
{
    0xFF,
    0x80,
	  0x80,
	  0x80,
	  0x80
};
uint8_t letter_O[5] =
{
    0x7E,
    0x81,
	  0x81,
	  0x81,
	  0x7E
};
uint8_t letter_[5] =
{
    0x00,
    0x00,
	  0x00,
	  0x00,
	  0x00
};
uint8_t letter_W[5] =
{
    0xFF,
    0x60,
	  0x10,
	  0x60,
	  0xFF
};
uint8_t letter_R[5] =
{
    0xFF,
    0x09,
	  0x09,
	  0x19,
	  0xE6
};
uint8_t letter_D[5] =
{
    0xFF,
    0x81,
	  0x81,
	  0x42,
	  0x3C
};
uint8_t letter_I[5] =
{
    0x00, 0x41, 0x7F, 0x41, 0x00
};

uint8_t letter_V[5] =
{
    0x1F, 0x20, 0x40, 0x20, 0x1F
};

uint8_t letter_T[5] =
{
    0x01, 0x01, 0x7F, 0x01, 0x01
};

uint8_t letter_M[5] =
{
    0x7F, 0x02, 0x0C, 0x02, 0x7F
};

uint8_t letter_P[5] =
{
    0x7F, 0x09, 0x09, 0x09, 0x06
};

uint8_t letter_A[5] =
{
    0x7E, 0x11, 0x11, 0x11, 0x7E
};

uint8_t letter_U[5] =
{
    0x3F, 0x40, 0x40, 0x40, 0x3F
};

const uint8_t font_numbers[10][5] =
{
    {0x3E, 0x51, 0x49, 0x45, 0x3E}, // 0
    {0x00, 0x42, 0x7F, 0x40, 0x00}, // 1
    {0x42, 0x61, 0x51, 0x49, 0x46}, // 2
    {0x21, 0x41, 0x45, 0x4B, 0x31}, // 3
    {0x18, 0x14, 0x12, 0x7F, 0x10}, // 4
    {0x27, 0x45, 0x45, 0x45, 0x39}, // 5
    {0x3C, 0x4A, 0x49, 0x49, 0x30}, // 6
    {0x01, 0x71, 0x09, 0x05, 0x03}, // 7
    {0x36, 0x49, 0x49, 0x49, 0x36}, // 8
    {0x06, 0x49, 0x49, 0x29, 0x1E}  // 9
};

const uint8_t char_dot[5] =
{
    0x00, 0x60, 0x60, 0x00, 0x00
};

const uint8_t char_minus[5] =
{
    0x08, 0x08, 0x08, 0x08, 0x08
};

const uint8_t char_C[5] =
{
    0x3E, 0x41, 0x41, 0x41, 0x22
};

const uint8_t char_space[5] =
{
    0x00, 0x00, 0x00, 0x00, 0x00
};


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

//	uint8_t calib_data[6];


	int32_t temperature = 0;
	char temp_text[16];


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
  MX_ADC1_Init();
  MX_TIM3_Init();
  MX_I2C1_Init();


  /* USER CODE BEGIN 2 */

  /* Page 0 */

  OLED_Init();

  OLED_Clear();

  BMP280_Init();



  OLED_SendCommand(0xB0);
  OLED_SendCommand(0x00);
  OLED_SendCommand(0x10);

  OLED_DrawText("LIVE TEMPERATURE.");








  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */


    /* USER CODE END WHILE */




	  while (1) {

			 		 temperature = BMP280_ReadTemperature();

			 		  snprintf(temp_text,
			 		           sizeof(temp_text),
			 		           "%ld.%02ld C",
			 		           (long)(temperature / 100),
			 		           (long)(temperature % 100));

			 		  OLED_SendCommand(0xB2);
			 		  OLED_SendCommand(0x00);
			 		  OLED_SendCommand(0x10);

			 		  OLED_DrawText(temp_text);








		  HAL_Delay(500);



	  }
     /* USER CODE BEGIN 3 */

  /* USER CODE END 3 */
}





void OLED_SendCommand(uint8_t command)
{
    uint8_t data[2];

    data[0] = OLED_CONTROL_CMD;
    data[1] = command;

    HAL_I2C_Master_Transmit(&hi2c1, OLED_ADDR, data, 2, HAL_MAX_DELAY);
}

void OLED_SendData(uint8_t dataByte)
{
    uint8_t data[2];

    data[0] = 0x40;
    data[1] = dataByte;

    HAL_I2C_Master_Transmit(&hi2c1, OLED_ADDR, data, 2, HAL_MAX_DELAY);
}

void OLED_Clear(void)
{
    for (uint8_t page = 0; page < 8; page++)
    {
        OLED_SendCommand(0xB0 + page);
        OLED_SendCommand(0x00);
        OLED_SendCommand(0x10);

        for (uint8_t column = 0; column < 128; column++)
        {
            OLED_SendData(0x00);
        }
    }
}

void OLED_DrawChar(const uint8_t *character)
{
    for (uint8_t column = 0; column < 5; column++)
    {
        OLED_SendData(character[column]);
    }

    OLED_SendData(0x00);
}

void OLED_DrawCharacter(char character)
{
    if (character == 'H')
    {
        OLED_DrawChar(letter_H);
    }

    if (character == 'E')
    {
        OLED_DrawChar(letter_E);
    }
    if (character == 'L')
	{
		OLED_DrawChar(letter_L);
	}
    if (character == 'O')
	{
		OLED_DrawChar(letter_O);
	}
    if (character == 'W')
	{
		OLED_DrawChar(letter_W);
	}
    if (character == 'R')
	{
		OLED_DrawChar(letter_R);
	}
    if (character == 'D')
	{
		OLED_DrawChar(letter_D);
	}
    if (character == 'C')
    	{
    		OLED_DrawChar(char_C);
    	}
    if (character == ' ')
    	{
    		OLED_DrawChar(letter_);
    	}
    if(character == '.'){
        	 OLED_DrawChar(char_dot);
        }
    if(character == '-'){
            	 OLED_DrawChar(char_minus);
            }
    if(character == '1'){
    	 OLED_DrawChar(font_numbers[1]);
    }
    if(character == '2'){
        	 OLED_DrawChar(font_numbers[2]);
        }
    if(character == '3'){
        	 OLED_DrawChar(font_numbers[3]);
        }
	if(character == '4'){
			 OLED_DrawChar(font_numbers[4]);
		}
	if(character == '5'){
	    	 OLED_DrawChar(font_numbers[5]);
	    }
	if(character == '6'){
			 OLED_DrawChar(font_numbers[6]);
		}
	if(character == '7'){
			 OLED_DrawChar(font_numbers[7]);
		}
	if(character == '8'){
			 OLED_DrawChar(font_numbers[8]);
		}
	if(character == '9'){
			 OLED_DrawChar(font_numbers[9]);
		}
	if(character == '0'){
			 OLED_DrawChar(font_numbers[0]);
		}
	if (character == 'I')
	{
	    OLED_DrawChar(letter_I);
	}

	if (character == 'V')
	{
	    OLED_DrawChar(letter_V);
	}

	if (character == 'T')
	{
	    OLED_DrawChar(letter_T);
	}

	if (character == 'M')
	{
	    OLED_DrawChar(letter_M);
	}

	if (character == 'P')
	{
	    OLED_DrawChar(letter_P);
	}

	if (character == 'A')
	{
	    OLED_DrawChar(letter_A);
	}

	if (character == 'U')
	{
	    OLED_DrawChar(letter_U);
	}


}

void OLED_DrawText(const char *text)
{
    while (*text != '\0')
    {
        OLED_DrawCharacter(*text);

        text++;
    }
}

void OLED_Init(void)
{
    OLED_SendCommand(0xAE);
    OLED_SendCommand(0xD5);
    OLED_SendCommand(0x80);
    OLED_SendCommand(0xA8);
    OLED_SendCommand(0x3F);
    OLED_SendCommand(0xD3);
    OLED_SendCommand(0x00);
    OLED_SendCommand(0x40);
    OLED_SendCommand(0x8D);
    OLED_SendCommand(0x14);
    OLED_SendCommand(0x20);
    OLED_SendCommand(0x00);
    OLED_SendCommand(0xA1);
    OLED_SendCommand(0xC8);
    OLED_SendCommand(0xDA);
    OLED_SendCommand(0x12);
    OLED_SendCommand(0x81);
    OLED_SendCommand(0x7F);
    OLED_SendCommand(0xD9);
    OLED_SendCommand(0xF1);
    OLED_SendCommand(0xDB);
    OLED_SendCommand(0x40);
    OLED_SendCommand(0xA4);
    OLED_SendCommand(0xA6);
    OLED_SendCommand(0xAF);
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC1_Init(void)
{

  /* USER CODE BEGIN ADC1_Init 0 */

  /* USER CODE END ADC1_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */

  /** Common config
  */
  hadc1.Instance = ADC1;
  hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc1.Init.ContinuousConvMode = DISABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Regular Channel
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_55CYCLES_5;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC1_Init 2 */

  /* USER CODE END ADC1_Init 2 */

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
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 7;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 999;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PA0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PB0 */
  GPIO_InitStruct.Pin = GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */


void BMP280_Init(void)
{
    uint8_t ctrl_meas = 0x27;

    uint8_t calib_pair_a[2] = {0};
    uint8_t calib_pair_b[2] = {0};
    uint8_t calib_pair_c[2] = {0};

    HAL_I2C_Mem_Write(&hi2c1,
                      0x76 << 1,
                      0xF4,
                      I2C_MEMADD_SIZE_8BIT,
                      &ctrl_meas,
                      1,
                      100);

    HAL_I2C_Mem_Read(&hi2c1,
                     0x76 << 1,
                     0x88,
                     I2C_MEMADD_SIZE_8BIT,
                     calib_pair_a,
                     2,
                     100);

    HAL_I2C_Mem_Read(&hi2c1,
                     0x76 << 1,
                     0x8A,
                     I2C_MEMADD_SIZE_8BIT,
                     calib_pair_b,
                     2,
                     100);

    HAL_I2C_Mem_Read(&hi2c1,
                     0x76 << 1,
                     0x8C,
                     I2C_MEMADD_SIZE_8BIT,
                     calib_pair_c,
                     2,
                     100);

    dig_T1 =
        ((uint16_t)calib_pair_a[1] << 8) |
        calib_pair_a[0];

    dig_T2 =
        (int16_t)(((uint16_t)calib_pair_b[1] << 8) |
                  calib_pair_b[0]);

    dig_T3 =
        (int16_t)(((uint16_t)calib_pair_c[1] << 8) |
                  calib_pair_c[0]);
}


int32_t BMP280_ReadTemperature(void){

    uint8_t temp_data[3] = {0};

    uint32_t raw_temperature = 0;

    int32_t adc_T = 0;
    int32_t var1 = 0;
    int32_t var2 = 0;
    int32_t t_fine = 0;
    int32_t temperature = 0;

    HAL_StatusTypeDef result = HAL_ERROR;

	 result = HAL_I2C_Mem_Read(&hi2c1,
			                            0x76 << 1,
			                            0xFA,
			                            I2C_MEMADD_SIZE_8BIT,
			                            temp_data,
			                            3,
			                            100);


			  if (result == HAL_OK){

				  raw_temperature =
				 		      ((uint32_t)temp_data[0] << 12) |
				 		      ((uint32_t)temp_data[1] << 4) |
				 		      ((uint32_t)temp_data[2] >> 4);

				 		  adc_T = (int32_t)raw_temperature;

				 		  var1 = (((adc_T >> 3) - ((int32_t)dig_T1 << 1))
				 		          * ((int32_t)dig_T2)) >> 11;

				 		  var2 = (((((adc_T >> 4) - ((int32_t)dig_T1))
				 		            * ((adc_T >> 4) - ((int32_t)dig_T1))) >> 12)
				 		          * ((int32_t)dig_T3)) >> 14;

				 		  t_fine = var1 + var2;

				 		  temperature = (t_fine * 5 + 128) >> 8;

				 		  return temperature;
			  }

			  return 0;



}


/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
