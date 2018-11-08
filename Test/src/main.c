#include "stm32f10x.h"
#include "GPIO.h"

int ok=0;
/* Fichier de la couche "application" */
void Ma_Fonction_IT ( void )
{
/* Le code à exécuter pendant l’interruption */
	
	if( !ok && GPIOB->IDR & (1 << 5)){
		ok=1;
		TIM2->CCR1 = 144;
	}
	else if (ok && !(GPIOB->IDR & (1 << 5))){
		ok=0;
		TIM2->CCR1 = 0;
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
	
	//Configurer l'interruption de TIM2
	Init_periph(Ma_Fonction_IT);
	TIM2->DIER |= (1<<0);
	NVIC->ISER[0] |= (1<<28);
	NVIC->IP[28] |= (uint8_t)(0x2<<4);
	
	//Configurer la LED PA.5 en sortie et en mode alternate function
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	//alternate push-pull
	GPIOA->CRL &= ~(0xF<<(4*5));
	GPIOA->CRL |= (0xA<<(4*5));
 	
	//Activer l'horloge locale de TIM2
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	
	//Configurer TIM2 avec periode de 20ms
	TIM2->ARR = 1439;
	TIM2->PSC = 999;

	//configurer le canal CH0 d'un timer en mode PWM
	//il faut affecter la valeur 0b110 au bits OC1M dans le registre CCMR1 du TIM
	TIM2->CCMR1 &= ~TIM_CCMR1_OC1M_0;
	TIM2->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;
	//sur le CH1
	TIM2->CCER |= TIM_CCER_CC1E;
	
	//Pour l'instant, fixons la duree de l'impulsion a 144 (10%)
	TIM2->CCR1 = 144;
	
	//Activer counter / Lancer le timer
	TIM2->CR1 |= TIM_CR1_CEN;
	
	while(1) {

	}
}
