#include "stm32f10x.h"
#include "MoteurCapot.h"

void PWM_Init (TIM_TypeDef * timer, int chanel){
	
	switch (chanel) {
		
		case 1 :
				timer->CCMR1 &= ~(0xF<<3);
				timer->CCMR1 |= (0xD<<3);
				timer->CCER |= TIM_CCER_CC1E;
				break;
		
		case 2 : 
				timer->CCMR1 &= ~(0xF<<11);
				timer->CCMR1 |= (0xD<<11);
				timer->CCER |= TIM_CCER_CC2E;
				break;
		
		case 3 : 
				timer->CCMR2 &= ~(0xF<<3);
				timer->CCMR2 |= (0xD<<3);
				timer->CCER |= TIM_CCER_CC3E;	
				break;
	
		case 4 : 

				timer->CCMR2 &= ~(0xF<<11);
				timer->CCMR2 |= (0xD<<11);
				timer->CCER |= TIM_CCER_CC4E;	
				break;
	}
	
}

void PWM_Set_Valeur(TIM_TypeDef * timer,int channel, int val){
	
	switch (channel) {
		
		case 1 : 
				timer->CCR1 = val;
				break;
		
		case 2 : 
				timer->CCR2 = val;
				break;
		
		case 3 : 
				timer->CCR3 = val;
				break;
		
		case 4 : 
				timer->CCR4 = val;
				break;
		
	}
	
}

