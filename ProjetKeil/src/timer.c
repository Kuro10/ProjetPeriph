#include "stm32f10x.h"
#include "timer.h"

void ConfigInterrupt(TIM_TypeDef * timer){
	
	int position;
	
	switch((u32) timer){
		case (u32) TIM1:
			position = TIM1_UP_IRQn;
			break;
		
		case (u32) TIM2:
			position = TIM2_IRQn;
			break;
		
		case (u32) TIM3:
			position = TIM3_IRQn;
			break;
		
		default: // TIM4
			position = TIM4_IRQn;
			break;
	}
	
	NVIC->ISER[position/32] |= (1 << position); // Activer l'interruption sur le NVIC pour le timer
	//NVIC_EnableIRQ(position); // Même chose
	
	NVIC->IP[position] = (1 << 4); // Met le niveau de priorité à 1
	//NVIC_SetPriority(position, 1); // Même chose
	
	timer->DIER |= TIM_DIER_UIE; // p344 "Update Interrupt enable" (bit 0) à 1
	
}

void InitialiserTimer(TIM_TypeDef * timer, int prescaler, int autoreload){
	
	// Bit 0 TIMXEN: TIMX timer clock enable p116
	switch((u32) timer){
		case (u32) TIM2:
			RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // bit 0
			break;
		case (u32) TIM3:
			RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; // bit 1
			break;
		case (u32) TIM4:
			RCC->APB1ENR |= RCC_APB1ENR_TIM4EN; // bit 2
			break;
			
		default:
			break;
	}
	
	// Configurer le prescaler p367
	timer->PSC = prescaler;
	
	// Configurer l'autoreload p367
	timer->ARR = autoreload;
	
}

void DemarrerTimer(TIM_TypeDef * timer){
	
	// Activer (démarrer) le timer p404
	timer->CR1 |= TIM_CR1_CEN;
	
}

void StopTimer(TIM_TypeDef * timer){
	
	// Bit 0 TIMXEN: TIMX timer clock enable p116
	switch((u32) timer){
		case (u32) TIM2:
			RCC->APB1ENR &= ~RCC_APB1ENR_TIM2EN; // bit 0
			break;
		case (u32) TIM3:
			RCC->APB1ENR &= ~RCC_APB1ENR_TIM3EN; // bit 1
			break;
		case (u32) TIM4:
			RCC->APB1ENR &= ~RCC_APB1ENR_TIM4EN; // bit 2
			break;
			
		default:
			break;
	}
	
	// Activer (démarrer) le timer p404
	timer->CR1 &= ~TIM_CR1_CEN; // bit 0
}

void TempoCPU(void);
