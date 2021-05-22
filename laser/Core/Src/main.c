/* USER CODE BEGIN Header */
//stm32l152
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define delay_us10 uscnt=1;while(uscnt!=0)
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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

uint32_t cnt=0,mcnt=0,Gcnt=0,Ocnt=0,Wcnt=0;
//volatile _Bool uscnt=0,mscnt=0;
volatile uint32_t uscnt=0,mscnt=0;
uint16_t n=0,nn=0;
extern _Bool shot;
_Bool G=0,C=0,S=0;
uint16_t i=0;
//void delay_ms(uint32_t d){
//	mscnt=d;
//	while(mscnt!=0);
//}
/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */

	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_COMP);
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

	NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	/* System interrupt init*/

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_TIM3_Init();
	/* USER CODE BEGIN 2 */
	//HAL_TIM_Base_Start_IT(&htim3);
	LL_TIM_EnableCounter(TIM3);
	LL_TIM_EnableIT_UPDATE(TIM3);
	//LL_TIM_EnableCounter(TIM4);
	//LL_TIM_EnableIT_UPDATE(TIM4);
	//	while(1){
	//		LL_GPIO_TogglePin(LO_GPIO_Port, LO_Pin);LL_GPIO_TogglePin(led_GPIO_Port, led_Pin);
	//		delay_ms(4);
	//	}
	if (((LL_GPIO_ReadInputPort(sw_GPIO_Port)) & (1<<8)) == 0){
		//HAL_Delay(100);
		LL_mDelay(100);
		if (((LL_GPIO_ReadInputPort(sw_GPIO_Port)) & (1<<8)) == 0)S=1;
	}
	if(!S)
		LL_GPIO_SetOutputPin(led_GPIO_Port, led_Pin);
	else
		LL_GPIO_ResetOutputPin(led_GPIO_Port, led_Pin);
	//while(1){}
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1)
	{
		show_n(nn, 0);
		i=0;
		//				LL_GPIO_SetOutputPin(LO_GPIO_Port, LO_Pin);
		while(i<200)
		{
			delay_us10;
			i++;
			if(i%4==0){
				LL_GPIO_SetOutputPin(do_GPIO_Port, do_Pin);
			}else{
				LL_GPIO_ResetOutputPin(do_GPIO_Port, do_Pin);
			}
		}


		show_n(nn, 1);
		i=0;
		//				LL_GPIO_SetOutputPin(LO_GPIO_Port, LO_Pin);
		while(i<200)
		{
			delay_us10;
			i++;
			if(i%4==0){
				LL_GPIO_SetOutputPin(yo_GPIO_Port, yo_Pin);
			}else{
				LL_GPIO_ResetOutputPin(yo_GPIO_Port, yo_Pin);
			}
		}

		if (((LL_GPIO_ReadInputPort(button_GPIO_Port)) & (1<<7)) == 0){
			Gcnt++;
			if(Gcnt>150000)
				C=1;
		}else{
			if(Gcnt>150000)
				C=1;
			else if(Gcnt>10000)
			{
				G=1;
				C=0;
			}
			Gcnt=0;
		}
		if((G || S)&&!C)
			//while(1)
		{
			//LL_GPIO_ResetOutputPin(led_GPIO_Port, led_Pin);
			//while(1)
			if(shot)
			{
				//LL_mDelay(20);
				i=0;
				//				LL_GPIO_SetOutputPin(LO_GPIO_Port, LO_Pin);
				while(i<135)
				{
					LL_GPIO_SetOutputPin(LO_GPIO_Port, LO_Pin);
					delay_us10;
					LL_GPIO_ResetOutputPin(LO_GPIO_Port, LO_Pin);
					delay_us10;
					i++;
				}
				//GPIOA->ODR = (GPIOA->ODR)&(0b1111111111111011);
				//				LL_GPIO_ResetOutputPin(LO_GPIO_Port, LO_Pin);
				i=0;
				while(i<375){
					delay_us10;
					i++;
				}
				//LL_mDelay(6);
				i=0;
				//			LL_GPIO_SetOutputPin(LO_GPIO_Port, LO_Pin);
				while(i<175)
				{
					LL_GPIO_SetOutputPin(LO_GPIO_Port, LO_Pin);
					delay_us10;
					LL_GPIO_ResetOutputPin(LO_GPIO_Port, LO_Pin);
					delay_us10;
					i++;
				}
				//GPIOA->ODR = (GPIOA->ODR)&(0b1111111111111011);
				//		LL_GPIO_ResetOutputPin(LO_GPIO_Port, LO_Pin);
				//LL_mDelay(7);
				i=0;
				while(i<440){
					delay_us10;
					i++;
				}
				i=0;
				while(i<500){
					LL_GPIO_SetOutputPin(LO_GPIO_Port, LO_Pin);
					delay_us10;
					LL_GPIO_ResetOutputPin(LO_GPIO_Port, LO_Pin);
					delay_us10;
					i++;
				}
				//				while(i<16)
				//				{
				//					LL_GPIO_SetOutputPin(LO_GPIO_Port, LO_Pin);
				//					delay_ms(1);
				//					//					delay_us10;
				//					//GPIOA->ODR = (GPIOA->ODR)&(0b1111111111111011);
				//					//					delay_us10;
				//					i++;
				//				}
				//LL_GPIO_ResetOutputPin(LO_GPIO_Port, LO_Pin);
				//GPIOA->ODR = (GPIOA->ODR)&(0b1111111111111011);
				shot=0;
				nn++;
				//if(n>100)n=0;
				G=0;
			}
		}
		//		else{
		//			LL_GPIO_SetOutputPin(led_GPIO_Port, led_Pin);
		//		}
		if(C){//calibration of laser
			if(Wcnt%3==0)
				LL_GPIO_SetOutputPin(LO_GPIO_Port, LO_Pin);
			else
				LL_GPIO_ResetOutputPin(LO_GPIO_Port, LO_Pin);
		}else{
			LL_GPIO_ResetOutputPin(LO_GPIO_Port, LO_Pin);
		}


		if(G||S){
			LL_GPIO_ResetOutputPin(led_GPIO_Port, led_Pin);
		}else{
			LL_GPIO_SetOutputPin(led_GPIO_Port, led_Pin);
		}
		Wcnt++;
		//		if(shot){
		//			LL_GPIO_TogglePin(LO_GPIO_Port, LO_Pin);
		//			HAL_Delay(500);
		//			LL_GPIO_TogglePin(LO_GPIO_Port, LO_Pin);
		//			HAL_Delay(500);
		//			shot=0;
		//			n++;
		//		}
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
		//		if(uscnt>50000){
		//			uscnt=0;
		//			LL_GPIO_TogglePin(LO_GPIO_Port, LO_Pin);
		//		}
		//		while(Ocnt==Wcnt);//one ms for while
		//	Ocnt=Wcnt;
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{

	LL_FLASH_Enable64bitAccess();

	LL_FLASH_SetLatency(LL_FLASH_LATENCY_1);
	while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_1)
	{
	}
	LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
	LL_RCC_HSE_Enable();

	/* Wait till HSE is ready */
	while(LL_RCC_HSE_IsReady() != 1)
	{

	}
	LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLL_MUL_8, LL_RCC_PLL_DIV_2);
	LL_RCC_PLL_Enable();

	/* Wait till PLL is ready */
	while(LL_RCC_PLL_IsReady() != 1)
	{

	}
	LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
	LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
	LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
	LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

	/* Wait till System clock is ready */
	while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
	{

	}

	LL_Init1msTick(32000000);

	LL_SetSystemCoreClock(32000000);
}

/* USER CODE BEGIN 4 */
void show_n(uint8_t n,_Bool q){
	uint8_t b=0;
	if(q)
	{
		b=n%10;
		LL_GPIO_SetOutputPin(yo_GPIO_Port, yo_Pin);
		LL_GPIO_ResetOutputPin(do_GPIO_Port, do_Pin);
	}else{
		b=(n/10)%10;
		LL_GPIO_ResetOutputPin(yo_GPIO_Port, yo_Pin);
		LL_GPIO_SetOutputPin(do_GPIO_Port, do_Pin);
	}
	switch(b){
	case 0:
		LL_GPIO_SetOutputPin(a_GPIO_Port, a_Pin);
		LL_GPIO_SetOutputPin(b_GPIO_Port, b_Pin);
		LL_GPIO_SetOutputPin(c_GPIO_Port, c_Pin);
		LL_GPIO_SetOutputPin(d_GPIO_Port, d_Pin);
		LL_GPIO_SetOutputPin(e_GPIO_Port, e_Pin);
		LL_GPIO_SetOutputPin(f_GPIO_Port, f_Pin);
		LL_GPIO_ResetOutputPin(g_GPIO_Port, g_Pin);
		break;
	case 1:
		LL_GPIO_ResetOutputPin(a_GPIO_Port, a_Pin);
		LL_GPIO_SetOutputPin(b_GPIO_Port, b_Pin);
		LL_GPIO_SetOutputPin(c_GPIO_Port, c_Pin);
		LL_GPIO_ResetOutputPin(d_GPIO_Port, d_Pin);
		LL_GPIO_ResetOutputPin(e_GPIO_Port, e_Pin);
		LL_GPIO_ResetOutputPin(f_GPIO_Port, f_Pin);
		LL_GPIO_ResetOutputPin(g_GPIO_Port, g_Pin);
		break;
	case 2:
		LL_GPIO_SetOutputPin(a_GPIO_Port, a_Pin);
		LL_GPIO_SetOutputPin(b_GPIO_Port, b_Pin);
		LL_GPIO_ResetOutputPin(c_GPIO_Port, c_Pin);
		LL_GPIO_SetOutputPin(d_GPIO_Port, d_Pin);
		LL_GPIO_SetOutputPin(e_GPIO_Port, e_Pin);
		LL_GPIO_ResetOutputPin(f_GPIO_Port, f_Pin);
		LL_GPIO_SetOutputPin(g_GPIO_Port, g_Pin);
		break;
	case 3:
		LL_GPIO_SetOutputPin(a_GPIO_Port, a_Pin);
		LL_GPIO_SetOutputPin(b_GPIO_Port, b_Pin);
		LL_GPIO_SetOutputPin(c_GPIO_Port, c_Pin);
		LL_GPIO_SetOutputPin(d_GPIO_Port, d_Pin);
		LL_GPIO_ResetOutputPin(e_GPIO_Port, e_Pin);
		LL_GPIO_ResetOutputPin(f_GPIO_Port, f_Pin);
		LL_GPIO_SetOutputPin(g_GPIO_Port, g_Pin);
		break;
	case 4:
		LL_GPIO_ResetOutputPin(a_GPIO_Port, a_Pin);
		LL_GPIO_SetOutputPin(b_GPIO_Port, b_Pin);
		LL_GPIO_SetOutputPin(c_GPIO_Port, c_Pin);
		LL_GPIO_ResetOutputPin(d_GPIO_Port, d_Pin);
		LL_GPIO_ResetOutputPin(e_GPIO_Port, e_Pin);
		LL_GPIO_SetOutputPin(f_GPIO_Port, f_Pin);
		LL_GPIO_SetOutputPin(g_GPIO_Port, g_Pin);
		break;
	case 5:
		LL_GPIO_SetOutputPin(a_GPIO_Port, a_Pin);
		LL_GPIO_ResetOutputPin(b_GPIO_Port, b_Pin);
		LL_GPIO_SetOutputPin(c_GPIO_Port, c_Pin);
		LL_GPIO_SetOutputPin(d_GPIO_Port, d_Pin);
		LL_GPIO_ResetOutputPin(e_GPIO_Port, e_Pin);
		LL_GPIO_SetOutputPin(f_GPIO_Port, f_Pin);
		LL_GPIO_SetOutputPin(g_GPIO_Port, g_Pin);
		break;
	case 6:
		LL_GPIO_SetOutputPin(a_GPIO_Port, a_Pin);
		LL_GPIO_ResetOutputPin(b_GPIO_Port, b_Pin);
		LL_GPIO_SetOutputPin(c_GPIO_Port, c_Pin);
		LL_GPIO_SetOutputPin(d_GPIO_Port, d_Pin);
		LL_GPIO_SetOutputPin(e_GPIO_Port, e_Pin);
		LL_GPIO_SetOutputPin(f_GPIO_Port, f_Pin);
		LL_GPIO_SetOutputPin(g_GPIO_Port, g_Pin);
		break;
	case 7:
		LL_GPIO_SetOutputPin(a_GPIO_Port, a_Pin);
		LL_GPIO_SetOutputPin(b_GPIO_Port, b_Pin);
		LL_GPIO_SetOutputPin(c_GPIO_Port, c_Pin);
		LL_GPIO_ResetOutputPin(d_GPIO_Port, d_Pin);
		LL_GPIO_ResetOutputPin(e_GPIO_Port, e_Pin);
		LL_GPIO_ResetOutputPin(f_GPIO_Port, f_Pin);
		LL_GPIO_ResetOutputPin(g_GPIO_Port, g_Pin);
		break;
	case 8:
		LL_GPIO_SetOutputPin(a_GPIO_Port, a_Pin);
		LL_GPIO_SetOutputPin(b_GPIO_Port, b_Pin);
		LL_GPIO_SetOutputPin(c_GPIO_Port, c_Pin);
		LL_GPIO_SetOutputPin(d_GPIO_Port, d_Pin);
		LL_GPIO_SetOutputPin(e_GPIO_Port, e_Pin);
		LL_GPIO_SetOutputPin(f_GPIO_Port, f_Pin);
		LL_GPIO_SetOutputPin(g_GPIO_Port, g_Pin);
		break;
	case 9:
		LL_GPIO_SetOutputPin(a_GPIO_Port, a_Pin);
		LL_GPIO_SetOutputPin(b_GPIO_Port, b_Pin);
		LL_GPIO_SetOutputPin(c_GPIO_Port, c_Pin);
		LL_GPIO_SetOutputPin(d_GPIO_Port, d_Pin);
		LL_GPIO_ResetOutputPin(e_GPIO_Port, e_Pin);
		LL_GPIO_SetOutputPin(f_GPIO_Port, f_Pin);
		LL_GPIO_SetOutputPin(g_GPIO_Port, g_Pin);
		break;
	}

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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
