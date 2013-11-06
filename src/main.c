/**
 *****************************************************************************
 **
 **  File        : main.c
 **
 **  Abstract    : main function.
 **
 **  Functions   : main
 **
 **  Environment : Atollic TrueSTUDIO(R)
 **                STMicroelectronics STM32F4xx Standard Peripherals Library
 **
 **  Distribution: The file is distributed “as is,” without any warranty
 **                of any kind.
 **
 **  (c)Copyright Atollic AB.
 **  You may use this file as-is or modify it according to the needs of your
 **  project. This file may only be built (assembled or compiled and linked)
 **  using the Atollic TrueSTUDIO(R) product. The use of this file together
 **  with other tools than Atollic TrueSTUDIO(R) is not permitted.
 **
 *****************************************************************************
 */

/* Includes */
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "stm32f4xx_gpio.h"

#include <stdio.h>
#include <math.h>

/* Private macro */
/* Private variables */
/* Private function prototypes */
/* Private functions */

int szamlalo = 0;

char* motor1;
char* motor2;
char* motor3;
char* motor4;

typedef enum
{
  MOTOR1E = GPIO_Pin_2,
  MOTOR1H = GPIO_Pin_3,
  MOTOR2E = GPIO_Pin_4,
  MOTOR2H = GPIO_Pin_5,
  MOTOR3E = GPIO_Pin_6,
  MOTOR3H = GPIO_Pin_7,
  MOTOR4E = GPIO_Pin_8,
  MOTOR4H = GPIO_Pin_9,
} Motor_TypeDef;

void Delay(__IO uint32_t nCount);
void MotorSeb(int motor, float seb);
void MotorVez();
void MY_LEDInit(Motor_TypeDef motor);
void MY_LEDOn(Motor_TypeDef motor);
void MY_LEDOff(Motor_TypeDef motor);
/**
 **===========================================================================
 **
 **  Abstract: main program
 **
 **===========================================================================
 */
int main(void) {
	int i = 0;
	int bool = 0;

	/**
	 *  IMPORTANT NOTE!
	 *  The symbol VECT_TAB_SRAM needs to be defined when building the project
	 *  if code has been located to RAM and interrupts are used.
	 *  Otherwise the interrupt table located in flash will be used.
	 *  See also the <system_*.c> file and how the SystemInit() function updates
	 *  SCB->VTOR register.
	 *  E.g.  SCB->VTOR = 0x20000000;
	 */

	/* TODO - Add your application code here */

	/* Initialize LEDs */
	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);
	STM_EVAL_LEDInit(LED5);
	STM_EVAL_LEDInit(LED6);

	MY_LEDInit(MOTOR1E);
	MY_LEDOn(MOTOR1E);
	MY_LEDInit(MOTOR1H);
	MY_LEDOn(MOTOR1H);
	MY_LEDInit(MOTOR2E);
	MY_LEDOn(MOTOR2E);
	MY_LEDInit(MOTOR2H);
	MY_LEDOn(MOTOR2H);
	MY_LEDInit(MOTOR3E);
	MY_LEDOn(MOTOR3E);
	MY_LEDInit(MOTOR3H);
	MY_LEDOn(MOTOR3H);
	MY_LEDInit(MOTOR4E);
	MY_LEDOn(MOTOR4E);
	MY_LEDInit(MOTOR4H);
	MY_LEDOn(MOTOR4H);
	/* Turn on LEDs */

	/* Infinite loop */
	while (1) {
		if (i > 16800000 && bool == 0) {
			MotorSeb(1, 8);
			MotorSeb(2, 0);
			MotorSeb(3, 8);
			MotorSeb(4, 0);
			bool = 1;
			i = 0;
		} else if (i > 16800000 && bool == 1) {
			MotorSeb(1, 0);
			MotorSeb(2, 8);
			MotorSeb(3, 0);
			MotorSeb(4, 8);
			bool = 0;
			i = 0;
		}

//		MotorSeb(2,10);
//		MotorSeb(3,1);
//		if (STM_EVAL_PBGetState(BUTTON_USER)!=0x00)
//		{
//			i++;
//		}
//		MotorSeb(4,i);
		MotorVez();
		i++;
	}
}

void Delay(__IO uint32_t nCount) {
	while (nCount--) {
	}
}

void MotorSeb(int motor, float seb) {
	char* tomb = "0000000000";
	int sw = roundf(seb);
	if (sw > 10) {
		sw = 10;
	}
	switch (sw) {
	case 0:
		tomb = "0000000000";
		break;
	case 1:
		tomb = "1000000000";
		break;
	case 2:
		tomb = "1000010000";
		break;
	case 3:
		tomb = "1001000100";
		break;
	case 4:
		tomb = "1001010010";
		break;
	case 5:
		tomb = "1010101010";
		break;
	case 6:
		tomb = "1011010110";
		break;
	case 7:
		tomb = "1101101101";
		break;
	case 8:
		tomb = "1101111011";
		break;
	case 9:
		tomb = "1111101111";
		break;
	case 10:
		tomb = "1111111111";
		break;
	default:
		tomb = "0000000000";
		break;
	}

	switch (motor) {
	case 1:
		motor1 = tomb;
		break;
	case 2:
		motor2 = tomb;
		break;
	case 3:
		motor3 = tomb;
		break;
	case 4:
		motor4 = tomb;
		break;
	default:
		break;
	}
}

void MotorVez() {
	if (motor1[szamlalo] == '1') {
		STM_EVAL_LEDOn(LED3);
	} else {
		STM_EVAL_LEDOff(LED3);
	}
	if (motor2[szamlalo] == '1') {
		STM_EVAL_LEDOn(LED4);
	} else {
		STM_EVAL_LEDOff(LED4);
	}
	if (motor3[szamlalo] == '1') {
		STM_EVAL_LEDOn(LED5);
	} else {
		STM_EVAL_LEDOff(LED5);
	}
	if (motor4[szamlalo] == '1') {
		STM_EVAL_LEDOn(LED6);
	} else {
		STM_EVAL_LEDOff(LED6);
	}
	szamlalo++;
	if (szamlalo > 9) {
		szamlalo = 0;
	}
}

void MY_LEDInit(Motor_TypeDef motor) {
	GPIO_InitTypeDef GPIO_InitStructure;

	/* Enable the GPIO_LED Clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	/* Configure the GPIO_LED pin */
	GPIO_InitStructure.GPIO_Pin = motor; //GPIO_PIN[Led];
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA , &GPIO_InitStructure);

}

void MY_LEDOn(Motor_TypeDef motor) {
	GPIOA->BSRRL = motor;
}

void MY_LEDOff(Motor_TypeDef motor) {
	GPIOA->BSRRH = motor;
}



/*
 * Callback used by stm32f4_discovery_audio_codec.c.
 * Refer to stm32f4_discovery_audio_codec.h for more info.
 */
void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size) {
	/* TODO, implement your code here */
	return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void) {
	/* TODO, implement your code here */
	return -1;
}
