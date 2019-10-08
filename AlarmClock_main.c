#include "stm32f0xx_ll_bus.h"
#include "stm32f0xx_ll_exti.h"
#include "stm32f0xx_ll_gpio.h"
#include "stm32f0xx_ll_rcc.h"
#include "stm32f0xx_ll_system.h"
#include <stdbool.h>


int digits[] = {0x3f, 0x6, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x7, 0x7f, 0x6f, 0xe6};
int coms[] = {0x700, 0xb00, 0xd00, 0xe00};

int tick=0;
int tack=0;
int minute=0;
int hour=0;
int button=0;
int button1=0;
int mode=0;
int newhour=0;
int newminute=0;
int newhour1=0;
int newminute1=0;
int alhour=0;
int alminute=0;
int alhour1=0;
int alminute1=0;
int alarmh=-1;
int alarmmin=-1;
bool set=false;
bool aset=false;


void SystemClock_Config(void);
void exti_config(void);

int  main(void) {

	
	exti_config(); 
        SystemClock_Config();
        LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);


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
	if (button<1){
		button=20;
	/*useful stuff*/
		mode=(mode+1)%11;
	}
/*EXTI->PR |= LL_EXTI_PR_PR0*/
LL_EXTI_ClearFlag_0_31(LL_EXTI_LINE_0);
}

void EXTI4_15_IRQHandler(void) {
        if (button1<1){
                button1=20;
        /*useful stuff*/
               switch (mode){
			case 0: {++minute; break;}
			case 1: {newhour1 = (newhour1+1)%3; break;}
			case 2: {newhour = (newhour+1)%10; break;}
			case 3: {newminute1 = (newminute1+1)%6; break;}
			case 4: {newminute = (newminute+1)%10; break;}
			case 5: {if (set==false)set=true; else set=false; break;}
			case 6: {alhour1 = (alhour1+1)%3; break;}
                        case 7: {alhour = (alhour+1)%10; break;}
                        case 8: {alminute1 = (alminute1+1)%6; break;}
                        case 9: {alminute = (alminute+1)%10; break;}
                        case 10: {if (aset==false) aset=true; else aset=false; break;}
			case 11: {alarmh=-1; alarmmin=-1; mode=0; break;}
		}
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

void printtime (){
	int curcom=tick%4;
	switch (curcom){
		case 0: {LL_GPIO_WriteOutputPort(GPIOA,(coms[0]+digits[minute%10])*2 );
			break;}
		case 1: {LL_GPIO_WriteOutputPort(GPIOA,(coms[1]+digits[minute/10])*2 );
                        break;}
		case 2: {
			if (tick%1000>500)
				LL_GPIO_WriteOutputPort(GPIOA,(coms[2]+digits[hour%10])*2 );
			else  LL_GPIO_WriteOutputPort(GPIOA,(coms[2]+digits[hour%10]+0x080)*2 );
                        break;}
		case 3: {LL_GPIO_WriteOutputPort(GPIOA,(coms[3]+digits[hour/10])*2 );
                        break;}
	}
		
}

void set1(){
	int curcom=tick%4;
        switch (curcom){
                case 0: {LL_GPIO_WriteOutputPort(GPIOA,(coms[0]+digits[minute%10])*2 );
                        break;}
                case 1: {LL_GPIO_WriteOutputPort(GPIOA,(coms[1]+digits[minute/10])*2 );
                        break;}
                case 2: {
                        if (tick%1000>500)
                                LL_GPIO_WriteOutputPort(GPIOA,(coms[2]+digits[hour%10])*2 );
                        else  LL_GPIO_WriteOutputPort(GPIOA,(coms[2]+digits[hour%10]+0x080)*2 );
                        break;}
                case 3: {if (tick%500>250)
				LL_GPIO_WriteOutputPort(GPIOA,(coms[3]+digits[newhour1])*2 );
                        break;}
        }
}

void set2(){
	int curcom=tick%4;
        switch (curcom){
                case 0: {LL_GPIO_WriteOutputPort(GPIOA,(coms[0]+digits[minute%10])*2 );
                        break;}
                case 1: {LL_GPIO_WriteOutputPort(GPIOA,(coms[1]+digits[minute/10])*2 );
                        break;}
                case 2: {if (tick%500>250){
	                        if (tick%1000>500)
                                	LL_GPIO_WriteOutputPort(GPIOA,(coms[2]+digits[newhour])*2 );
                        	else  LL_GPIO_WriteOutputPort(GPIOA,(coms[2]+digits[newhour]+0x080)*2 );
			}
                        break;}
                case 3: {LL_GPIO_WriteOutputPort(GPIOA,(coms[3]+digits[newhour1])*2 );
                        break;}
        }

}

void set3(){
	int curcom=tick%4;
        switch (curcom){
                case 0: {LL_GPIO_WriteOutputPort(GPIOA,(coms[0]+digits[minute%10])*2 );
                        break;}
                case 1: {if (tick%500>250)
				LL_GPIO_WriteOutputPort(GPIOA,(coms[1]+digits[newminute1])*2 );
                        break;}
                case 2: {
                        if (tick%1000>500)
                                LL_GPIO_WriteOutputPort(GPIOA,(coms[2]+digits[newhour])*2 );
                        else  LL_GPIO_WriteOutputPort(GPIOA,(coms[2]+digits[newhour]+0x080)*2 );
                        break;}
                case 3: {LL_GPIO_WriteOutputPort(GPIOA,(coms[3]+digits[newhour1])*2 );
                        break;}
        }
}


void set4 (){
	int curcom=tick%4;
        switch (curcom){
                case 0: {if (tick%500>250)
				LL_GPIO_WriteOutputPort(GPIOA,(coms[0]+digits[newminute])*2 );
                        break;}
                case 1: {LL_GPIO_WriteOutputPort(GPIOA,(coms[1]+digits[newminute1])*2 );
                        break;}
                case 2: {
                        if (tick%1000>500)
                                LL_GPIO_WriteOutputPort(GPIOA,(coms[2]+digits[newhour])*2 );
                        else  LL_GPIO_WriteOutputPort(GPIOA,(coms[2]+digits[newhour]+0x080)*2 );
                        break;}
                case 3: {LL_GPIO_WriteOutputPort(GPIOA,(coms[3]+digits[newhour1])*2 );
                        break;}
        }
}

void printok(){
	if (tick%1200>600){
		if(tick%2) 
			LL_GPIO_WriteOutputPort(GPIOA,(coms[2]+digits[0])*2 );
		else LL_GPIO_WriteOutputPort(GPIOA,(coms[1]+digits[10])*2 );
	}
	else {
		switch (tick%4){
	                case 0: {LL_GPIO_WriteOutputPort(GPIOA,(coms[0]+digits[newminute])*2 );
                        	break;}
                	case 1: {LL_GPIO_WriteOutputPort(GPIOA,(coms[1]+digits[newminute1])*2 );
        	                break;}
	                case 2: {
                	        if (tick%1000>500)
        	                        LL_GPIO_WriteOutputPort(GPIOA,(coms[2]+digits[newhour])*2 );
	                        else  LL_GPIO_WriteOutputPort(GPIOA,(coms[2]+digits[newhour]+0x080)*2 );
                        	break;}
                	case 3: {LL_GPIO_WriteOutputPort(GPIOA,(coms[3]+digits[newhour1])*2 );
        	                break;}
	        }
	}
}

void printq(){
        if (tick%1200>600)
                switch (tick%3){
                        case 0: {LL_GPIO_WriteOutputPort(GPIOA,(coms[2]+0x79)*2 ); break;}
                	case 1: {LL_GPIO_WriteOutputPort(GPIOA,(coms[1]+0x79)*2 ); break;}
			case 2: {LL_GPIO_WriteOutputPort(GPIOA,(coms[3]+0x6d)*2 ); break;}
       		}
        else {
                switch (tick%4){
                        case 0: {LL_GPIO_WriteOutputPort(GPIOA,(coms[0]+digits[newminute])*2 );
                                break;}
                        case 1: {LL_GPIO_WriteOutputPort(GPIOA,(coms[1]+digits[newminute1])*2 );
                                break;}
                        case 2: {
                                if (tick%1000>500)
                                        LL_GPIO_WriteOutputPort(GPIOA,(coms[2]+digits[newhour])*2 );
                                else  LL_GPIO_WriteOutputPort(GPIOA,(coms[2]+digits[newhour]+0x080)*2 );
                                break;}
                        case 3: {LL_GPIO_WriteOutputPort(GPIOA,(coms[3]+digits[newhour1])*2 );
                                break;}
                }
        }
}

/*__________________________________________________________________________________________________________________________________________________________alarm*/

void seta1(){
        int curcom=tick%4;
        switch (curcom){
                case 0: {LL_GPIO_WriteOutputPort(GPIOA,(coms[0]+digits[0])*2 );
                        break;}
                case 1: {LL_GPIO_WriteOutputPort(GPIOA,(coms[1]+digits[0])*2 );
                        break;}
                case 2: {LL_GPIO_WriteOutputPort(GPIOA,(coms[2]+digits[0]+0x080)*2 );
                        break;}
                case 3: {if (tick%500>250)
                                LL_GPIO_WriteOutputPort(GPIOA,(coms[3]+digits[alhour1])*2 );
                        break;}
        }
}

void seta2(){
        int curcom=tick%4;
        switch (curcom){
                case 0: {LL_GPIO_WriteOutputPort(GPIOA,(coms[0]+digits[0])*2 );
                        break;}
                case 1: {LL_GPIO_WriteOutputPort(GPIOA,(coms[1]+digits[0])*2 );
                        break;}
                case 2: {if (tick%500>250) LL_GPIO_WriteOutputPort(GPIOA,(coms[2]+digits[alhour]+0x080)*2 );
                        break;}
                case 3: {LL_GPIO_WriteOutputPort(GPIOA,(coms[3]+digits[alhour1])*2 );
                        break;}
        }

}

void seta3(){
        int curcom=tick%4;
        switch (curcom){
                case 0: {LL_GPIO_WriteOutputPort(GPIOA,(coms[0]+digits[0])*2 );
                        break;}
                case 1: {if (tick%500>250)
                                LL_GPIO_WriteOutputPort(GPIOA,(coms[1]+digits[alminute1])*2 );
                        break;}
                case 2: {LL_GPIO_WriteOutputPort(GPIOA,(coms[2]+digits[alhour]+0x080)*2 );
                        break;}
                case 3: {LL_GPIO_WriteOutputPort(GPIOA,(coms[3]+digits[alhour1])*2 );
                        break;}
        }
}

void seta4 (){
        int curcom=tick%4;
        switch (curcom){
                case 0: {if (tick%500>250)
                                LL_GPIO_WriteOutputPort(GPIOA,(coms[0]+digits[alminute])*2 );
                        break;}
                case 1: {LL_GPIO_WriteOutputPort(GPIOA,(coms[1]+digits[alminute1])*2 );
                        break;}
                case 2: {LL_GPIO_WriteOutputPort(GPIOA,(coms[2]+digits[alhour]+0x080)*2 );
                        break;}
                case 3: {LL_GPIO_WriteOutputPort(GPIOA,(coms[3]+digits[alhour1])*2 );
                        break;}
        }
}

void printaok(){
        if (tick%1200>600){
                switch(tick%4){
                        case 2: {LL_GPIO_WriteOutputPort(GPIOA,(coms[2]+digits[0])*2 ); break;}
                	case 1: {LL_GPIO_WriteOutputPort(GPIOA,(coms[1]+digits[10])*2 ); break;}
			case 3: {LL_GPIO_WriteOutputPort(GPIOA,(coms[3]+0x77)*2 ); break;}

		}		

        }
        else {
                switch (tick%4){
                        case 0: {LL_GPIO_WriteOutputPort(GPIOA,(coms[0]+digits[alminute])*2 );
                                break;}
                        case 1: {LL_GPIO_WriteOutputPort(GPIOA,(coms[1]+digits[alminute1])*2 );
                                break;}
                        case 2: {LL_GPIO_WriteOutputPort(GPIOA,(coms[2]+digits[alhour]+0x080)*2 );
                                break;}
                        case 3: {LL_GPIO_WriteOutputPort(GPIOA,(coms[3]+digits[alhour1])*2 );
                                break;}
                }
        }
}

void printaq(){
        if (tick%1200>600)
                switch (tick%4){
                        case 0: {LL_GPIO_WriteOutputPort(GPIOA,(coms[0]+0x79)*2 ); break;}
                        case 1: {LL_GPIO_WriteOutputPort(GPIOA,(coms[1]+0x79)*2 ); break;}
                        case 2: {LL_GPIO_WriteOutputPort(GPIOA,(coms[2]+0x6d)*2 ); break;}
			case 3: {LL_GPIO_WriteOutputPort(GPIOA,(coms[3]+0x77)*2 ); break;}
        }
        else {
                switch (tick%4){
                        case 0: {LL_GPIO_WriteOutputPort(GPIOA,(coms[0]+digits[alminute])*2 );
                                break;}
                        case 1: {LL_GPIO_WriteOutputPort(GPIOA,(coms[1]+digits[alminute1])*2 );
                                break;}
                        case 2: {LL_GPIO_WriteOutputPort(GPIOA,(coms[2]+digits[alhour]+0x080)*2 );
                                break;}
                        case 3: {LL_GPIO_WriteOutputPort(GPIOA,(coms[3]+digits[alhour1])*2 );
                                break;}
                }
        }
}

void alarm(){
	if (tick%1000>500){
		switch (tick%4){
                	case 0: {LL_GPIO_WriteOutputPort(GPIOA,(coms[0]+digits[minute%10])*2 );
        	                break;}
	                case 1: {LL_GPIO_WriteOutputPort(GPIOA,(coms[1]+digits[minute/10])*2+0x8000 );
                	        break;}
        	        case 2: {LL_GPIO_WriteOutputPort(GPIOA,(coms[2]+digits[hour%10])*2 );
                	        break;}
        	        case 3: {LL_GPIO_WriteOutputPort(GPIOA,(coms[3]+digits[hour/10])*2 +0x8000);
	                        break;}
        	}	
	}
	else{
		switch (tick%4){
                        case 0: {LL_GPIO_WriteOutputPort(GPIOA,(coms[0]+digits[alarmmin%10])*2+0x8000 );
                                break;}
                        case 1: {LL_GPIO_WriteOutputPort(GPIOA,(coms[1]+digits[alarmmin/10])*2+0x8000 );
                                break;}
                        case 2: {LL_GPIO_WriteOutputPort(GPIOA,(coms[2]+digits[alarmh%10]+0x4080)*2 );
                                break;}
                        case 3: {LL_GPIO_WriteOutputPort(GPIOA,(coms[3]+digits[alarmh/10])*2 +0x8000);
                                break;} 
                }

	}
}


void
SysTick_Handler(void) {
        tick++;
	if (button>0)
		--button;
	if (button1>0)
                --button1;
        if (tick >= 60000){
		tick = 0;
		++minute;
	}
	if (minute >= 60){
		++hour;
		minute=0;
	}
	if(hour >= 24){
		hour = 0;
	}
	if (mode==0){
		if (aset==true){
			aset=false;
			alarmh=alhour1*10+alhour;
			alarmmin=alminute1*10+alminute;
		}
		printtime ();
	}
	if (mode==1)
		set1 ();
	if (mode==2)
		set2();
	if (mode==3) set3();
	if (mode==4) set4();
	if (mode==5){
		if (set==true) printok();
		else printq();
	}
	if (mode==6){
		if (set==true){
			set=false;
			hour=newhour1*10+newhour; 
			minute=newminute1*10+newminute; 
			newhour1=0;
			newhour=0;
			newminute1=0;
			newminute=0;
		}
		seta1();
	}
	if (mode==7) seta2();
	if (mode==8) seta3();
	if (mode==9) seta4();
	if (mode==10){ 
			if (aset==true) printaok();
			else printaq();
	}
	if ((mode==0)&&(alarmh==hour)&&(alarmmin==minute)) mode=11;
	if (mode==11) alarm();
}
