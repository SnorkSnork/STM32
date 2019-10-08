#include "stm32f0xx_ll_bus.h"
#include "stm32f0xx_ll_exti.h"
#include "stm32f0xx_ll_gpio.h"
#include "stm32f0xx_ll_rcc.h"
#include "stm32f0xx_ll_system.h"
#include <stdbool.h>


int digits[] = {0x3f, 0x6, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x7, 0x7f, 0x6f, 0xe6, 0x40};
int coms[] = {0x700, 0xb00, 0xd00, 0xe00};

int bufer[] = {11,11,11,11};

int tick = 0;

int button = 0;
int button1 = 0;
int one = 0;
int zero = 0;


void SystemClock_Config(void);
void exti_config(void);

int  main(void) {

	
	exti_config(); 
        SystemClock_Config();
        LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
        LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);


        LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_1, LL_GPIO_MODE_OUTPUT);
        LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_2, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_3, LL_GPIO_MODE_OUTPUT);
        LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_4, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_5, LL_GPIO_MODE_OUTPUT);
        LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_6, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_7, LL_GPIO_MODE_OUTPUT);
        LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_8, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_9, LL_GPIO_MODE_OUTPUT);
        LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_10, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_11, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_12, LL_GPIO_MODE_OUTPUT);

        LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_13, LL_GPIO_MODE_OUTPUT);
        LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_14, LL_GPIO_MODE_INPUT);
        LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_15, LL_GPIO_MODE_OUTPUT);

	LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_8, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_9, LL_GPIO_MODE_OUTPUT);





        while (1);
}

/**
  * System Clock Configuration
  * The system Clock is configured as follow :
  *    System Clock source            = PLL (HSI/2)
  *    SYSCLK(Hz)                     = 48000000
  *    HCLK(Hz)                       = 48000000
  *    AHB Prescaler                  = 1
  *    APB1 Prescaler                 = 1
  *    HSI Frequency(Hz)              = 8000000
  *    PLLMUL                         = 12
  *    Flash Latency(WS)              = 1
  */

void
SystemClock_Config() {
        /* Set FLASH latency */
        LL_FLASH_SetLatency(LL_FLASH_LATENCY_1);

        /* Enable HSI and wait for activation*/
        LL_RCC_HSI_Enable();
        while (LL_RCC_HSI_IsReady() != 1);

        /* Main PLL configuration and activation */
        LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSI_DIV_2,
                                  LL_RCC_PLL_MUL_12);

        LL_RCC_PLL_Enable();
        while (LL_RCC_PLL_IsReady() != 1);

        /* Sysclk activation on the main PLL */
        LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
        LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
        while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL);

        /* Set APB1 prescaler */
        LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);

        /* Set systick to 1ms */
        SysTick_Config(48000000/1000);

        /* Update CMSIS variable (which can be updated also
         * through SysitemCoreClockUpdate function) */
        SystemCoreClock = 48000000;
}

void exti_config(void) {
LL_SYSCFG_SetEXTISource (LL_SYSCFG_EXTI_PORTA, LL_SYSCFG_EXTI_LINE0);
LL_SYSCFG_SetEXTISource (LL_SYSCFG_EXTI_PORTA, LL_SYSCFG_EXTI_LINE14);


/*detecting FALLING edge on pin 0*/
LL_EXTI_EnableFallingTrig_0_31(LL_EXTI_LINE_0);
LL_EXTI_EnableFallingTrig_0_31(LL_EXTI_LINE_14);

/*enable interrupt on line 0*/
LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_0);
LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_14);


NVIC_SetPriority(EXTI0_1_IRQn, 1);
NVIC_EnableIRQ(EXTI0_1_IRQn);
NVIC_SetPriority(EXTI4_15_IRQn, 1);
NVIC_EnableIRQ(EXTI4_15_IRQn);

}

void EXTI0_1_IRQHandler(void) {
//	if (button<1)
    {
//		button=20;
	/*useful stuff*/
        if (LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_14)){
            bufer[3] = bufer[2];
            bufer[2] = bufer[1];
            bufer[1] = bufer[0];
            bufer [0] = 1;
            one = 30;
        }
        else {
            bufer[3] = bufer[2];
            bufer[2] = bufer[1];
            bufer[1] = bufer[0];
            bufer [0] = 0;
            zero = 30;
        }
	}
/*EXTI->PR |= LL_EXTI_PR_PR0*/
LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_0);
}

void EXTI4_15_IRQHandler(void) {
        if (button1<1){
                button1=20;
        /*useful stuff*/
/*
        bufer[3] = bufer[2];
        bufer[2] = bufer[1];
        bufer[1] = bufer[0];
        bufer [0] = 1;
        one = 50;
*/
        }
/*EXTI->PR |= LL_EXTI_PR_PR0*/
LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_14);
}


void
NMI_Handler(void) {
}

void
HardFault_Handler(void) {
        while (1);
}

void
SVC_Handler(void) {
}

void
PendSV_Handler(void) {
}

void printbuf (){
	int curcom=tick%4;
	switch (curcom){
		case 0: {LL_GPIO_WriteOutputPort(GPIOA,(coms[0]+digits[bufer[3]])*2 );
			break;}
		case 1: {LL_GPIO_WriteOutputPort(GPIOA,(coms[1]+digits[bufer[2]])*2 );
                        break;}
		case 2: {LL_GPIO_WriteOutputPort(GPIOA,(coms[2]+digits[bufer[1]])*2 );
                        break;}
		case 3: {LL_GPIO_WriteOutputPort(GPIOA,(coms[3]+digits[bufer[0]])*2 );
                        break;}
	}
		
}




void
SysTick_Handler(void) {
        tick++;
    LL_GPIO_WriteOutputPort(GPIOC, 0x0000);
	if (button>0)
		    --button;
	if (button1>0)
            --button1;

	printbuf ();
    if (tick==4)
        tick = 0;
    if (one>0){
        --one;
        LL_GPIO_WriteOutputPort(GPIOC, LL_GPIO_PIN_8);
    }
    if (zero>0){
        --zero;
        LL_GPIO_WriteOutputPort(GPIOC, LL_GPIO_PIN_9);
    }
}
