#include "stm32f10x.h" 
 
//int TimerInit(TIM_TypeDef *timer, int arr, int psc);

int LED; 
int ok=0;
/* Fichier de la couche "application" */
void Ma_Fonction_IT ( void )
{
/* Le code à exécuter pendant l’interruption */
	/*
	LED = GPIOA->ODR>>5;
	if (LED==0)
	{
		//allumer la LED
		GPIOA->ODR |= (0x1<<5);
	}
	else
	{
		//eteindre la LED
		GPIOA->ODR &= ~(0x1<<5);
	}
	*/
	if( !ok && GPIOB->IDR & (1 << 5)){
		ok=1;
		TIM2->CCR1 = 144;
	}
	else if (ok && !(GPIOB->IDR & (1 << 5))){
		ok=0;
		TIM2->CCR1 = 0 ;
	}
	TIM2->SR &= ~0x1;
}


/* Fichier de la couche pilote */
void (* pFnc) (void) ; /* déclaration d’un pointeur de fonction */

void Init_periph (void (* ptrFonction) (void)) {
	pFnc = ptrFonction; /* affectation du pointeur */
}

//mis en place d'une routine de traitement de l'interruprion
void TIM2_IRQHandler (void){
	if (pFnc != 0)
		(*pFnc) (); /* appel indirect de la fonction */
	
}




int main (void)
{	

	/* TP3 : Timer */

		/*
	//Activer l'horloge locale de TIM2
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	//Activer counter
	TIM2->CR1 |= (1<<0);
	
	//TimerInit(TIM2,99,5759);
	TIM2->ARR = 0x63;
	TIM2->PSC = 0x167F;
	
	//Configurer l'interruption de TIM2
	Init_periph(Ma_Fonction_IT);
	TIM2->DIER |= (1<<0);
	NVIC->ISER[0] |= (1<<28);
	NVIC->IP[28] |= (uint8_t)(0x2<<4);
 
	//Configurer la LED PA.5 en sortie
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	GPIOA->CRL &= ~(0xF<<20);
	GPIOA->CRL |= (0x1<<20);
	
	//TimerStart(TIM2);
	*/
	
	
	
	//Activer l'horloge locale de TIM2
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	//Activer counter / Lancer le timer
	TIM2->CR1 |= TIM_CR1_CEN;
	
	//Configurer TIM2 avec periode de 20ms
	TIM2->ARR = 1439;
	TIM2->PSC = 999;
	
	//Configurer l'interruption de TIM2
	Init_periph(Ma_Fonction_IT);
	TIM2->DIER |= (0x1<<0);
	NVIC->ISER[0] |= (1<<28);
	NVIC->IP[28] |= (uint8_t)(0x2<<4);
	
	//configurer le canal CH1 d'un timer en mode PWM
	//il faut affecter la valeur 0b110 au bits OC1M dans le registre CCMR1 du TIM
	TIM2->CCMR1 &= ~TIM_CCMR1_OC1M_0;
	TIM2->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;
	TIM2->CCMR1 |= TIM_CCMR1_OC1PE;
	//sur le CH1 (broche PA.0)
	TIM2->CCER |= TIM_CCER_CC1E;
	
	//Pour l'instant, fixons la duree de l'impulsion a 144 (10%)
	TIM2->CCR1 = 144;
	
	//Configurer le button PB.5 en entree 
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	GPIOB->CRL &= ~(0xF<<(4*5));
	GPIOB->CRL |= (0x4<<(4*5));
	
	//Configurer la LED PA.0 en sortie et en mode alternate function
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	//alternate push-pull
	GPIOA->CRL &= ~(0xF<<(4*0));
	GPIOA->CRL |= (0xB<<(4*0));
	
  // boucle de traitement
		while(1)
    {  

    }

}
