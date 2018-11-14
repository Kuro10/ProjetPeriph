#include "stm32f10x.h"
#include "GPIO.h"

// Configuration d'une PIN
void GPIO_Init(GPIO_Struct_TypeDef * GPIOStructPtr){
	
	int shift = (GPIOStructPtr->GPIO_Pin) * 4;
	
	// Active l'horloge
	int mask;
	switch((int) GPIOStructPtr->GPIO){
		case (int) GPIOA:
			mask = RCC_APB2ENR_IOPAEN;
			break;
		case (int) GPIOB:
			mask = RCC_APB2ENR_IOPBEN;
			break;
		case (int) GPIOC:
			mask = RCC_APB2ENR_IOPCEN;
			break;
		case (int) GPIOD:
			mask = RCC_APB2ENR_IOPDEN;
			break;
		
		default:
			mask = RCC_APB2ENR_IOPAEN;
			break;
	}
	RCC->APB2ENR |= mask;
	
	// Met les paramètres
	if(GPIOStructPtr->GPIO_Pin < PIN_CRL_MAX){
		GPIOStructPtr->GPIO->CRL &= ~(0xF << shift);
		GPIOStructPtr->GPIO->CRL |= (GPIOStructPtr->GPIO_Techno << shift);
	}
	else{
		shift -= PIN_CRL_MAX * 4; // Correction
		GPIOStructPtr->GPIO->CRH &= ~(0xF << shift);
		GPIOStructPtr->GPIO->CRH |= (GPIOStructPtr->GPIO_Techno << shift);
	}
	
}

// Renvoie 0 ou autre chose différent de 0
int GPIO_Read(GPIO_TypeDef * GPIO, char GPIO_Pin){
	
	return GPIO->IDR & (1 << GPIO_Pin);
	
}

// Met 3,3V sur la pin et le GPIO souhaités
void GPIO_Set(GPIO_TypeDef * GPIO, char GPIO_Pin){
	
	GPIO->BSRR |= (1 << GPIO_Pin);
	
}

// Met 0V sur la pin et le GPIO souhaités
void GPIO_Reset(GPIO_TypeDef * GPIO, char GPIO_Pin){
	
	GPIO->BSRR |= (1 << (GPIO_Pin + 16));
	
}
