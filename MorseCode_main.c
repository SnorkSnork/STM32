#include "stm32f0xx_ll_bus.h"
#include "stm32f0xx_ll_gpio.h"
#include "stm32f0xx_ll_rcc.h"
#include "stm32f0xx_ll_system.h"
#include "stdio.h"
#include "string.h"

void SystemClock_Config(void);

//типа текстовая строка
char str0[]="hello world";
//переведенная строка (морзянка)
char str[1000]="/";
int amm = 0;
int i=0;

int tick = 0;
int k = -1;


int main() {



/*
перевод на морзянку
*/
        
        for (i=0; i < strlen(str0); ++i){
            switch (str0[i]) {
                case 'a': {strcat (str,  ".-/"); break;}
                case 'b': {strcat (str,  "-.../"); break;}
                case 'c': {strcat (str,  "-.-./"); break;}
                case 'd': {strcat (str,  "-../"); break;}
                case 'e': {strcat (str,  "./"); break;}
                case 'f': {strcat (str,  "..-./"); break;}
                case 'g': {strcat (str,  "--./"); break;}
                case 'h': {strcat (str,  "..../"); break;}
                case 'i': {strcat (str,  "../"); break;}
                case 'j': {strcat (str,  ".---/"); break;}
                case 'k': {strcat (str,  "-.-/"); break;}
                case 'l': {strcat (str,  ".-../"); break;}
                case 'm': {strcat (str,  "--/"); break;}
                case 'n': {strcat (str,  "-./"); break;}
                case 'o': {strcat (str,  "---/"); break;}
                case 'p': {strcat (str,  ".--./"); break;}
                case 'r': {strcat (str,  ".-./"); break;}
                case 's': {strcat (str,  ".../"); break;}
                case 't': {strcat (str,  "-/"); break;}
                case 'u': {strcat (str,  "..-/"); break;}
                case 'v': {strcat (str,  "...-/"); break;}
                case 'w': {strcat (str,  ".--/"); break;}
                case 'x': {strcat (str,  "-..-/"); break;}
                case 'y': {strcat (str,  "-.--/"); break;}
                case 'z': {strcat (str,  "--../"); break;}
                case '1': {strcat (str,  ".----/"); break;}
                case '2': {strcat (str,  "..---/"); break;}
                case '3': {strcat (str,  "...--/"); break;}
                case '4': {strcat (str,  "....-/"); break;}
                case '5': {strcat (str,  "...../"); break;}
                case '6': {strcat (str,  "-..../"); break;}
                case '7': {strcat (str,  "--.../"); break;}
                case '8': {strcat (str,  "---../"); break;}
                case '9': {strcat (str,  "----./"); break;}
                case '0': {strcat (str,  "-----/"); break;}
                case ' ': {strcat (str,  "///"); break;}
            }
        }

        amm = strlen(str);


        SystemClock_Config();
        LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);

        LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_9, LL_GPIO_MODE_OUTPUT);
        LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_8, LL_GPIO_MODE_OUTPUT);

        LL_GPIO_WriteOutputPort(GPIOC, 0x0);

/*		struct Code alphabet[] = {'a', ".-/", 'b', "-.../", 'c', "-.-./", 'd', "-../", 'e', "./", 'f', "..-./", 'g', "--./", 'h', "..../", 'i', "../", 'j', ".---/", 'k', "-.-/", 'l', ".-../", 'm', "--/", 'n', "-./",
 'o', "---/", 'p', ".--./", 'q', "--.-/", 'r', ".-./", 's', ".../", 't', "-/", 'u', "..-/", 'v', "...-/", 'w', ".--/", 'x', "-..-/", 'y', "-.--/", 'z', "--../",
 '1', ".----/", '2', "..---/", '3', "...--/", '4', "....-/", '5', "...../", '6', "-..../", '7', "--.../", '8', "---../", '9', "----./", 0, "-----/"};
*/



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
         * through SystemCoreClockUpdate function) */
        SystemCoreClock = 48000000;
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



void
SysTick_Handler(void) {

        tick--;
		if (k < amm){
			if (tick < 1) {
				++k;
				switch (str[k]){
					case '.': {tick = 500; break;}
					case '/': {tick = 1000; break;}
					case '-': {tick = 1200; break;}
				}
			}
			if (str[k] != '/'){
				if (tick > 200)
					LL_GPIO_WriteOutputPort (GPIOC, LL_GPIO_PIN_8);
                else LL_GPIO_WriteOutputPort(GPIOC, 0x0000);
                }
 
		}
}
