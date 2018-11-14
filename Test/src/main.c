#include "stm32f10x.h" 
#include "timer.h"
#include "GPIO.h"
#include "MoteurCapot.h"


//int TimerInit(TIM_TypeDef *timer, int arr, int psc);

//int LED; 
int open=0;
GPIO_Struct_TypeDef button;
GPIO_Struct_TypeDef capot;
GPIO_Struct_TypeDef bras;
int i=0;
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
	
	// A VERIFIER : CHOISIR DES VALEURS ADAPTEES POUR BIEN FONCTIONNER 
	
	// si le capot est ferme, et button = 1, ouvrir le capot, puis tourner le bras
	if( !open && GPIO_Read(GPIOB,5) ){
		open=1;
		//TIM2->CCR1 = 144;
		//TIM2->CCR2 = 144;
		PWM_Set_Valeur(TIM2,1,144);
		i=0;
		while(i<500000) i++;
		PWM_Set_Valeur(TIM2,2,144);
	}
	// si le capot est ouvrert, button -> 0, tourner bras, puis fermer le capot
	else if (open && !GPIO_Read(GPIOB,5)){
		open=0;
		//TIM2->CCR1 = 72;
		//TIM2->CCR2 = 72;
		PWM_Set_Valeur(TIM2,2,72);
		i=0;
		while (i<500000) i++;
		PWM_Set_Valeur(TIM2,1,72);
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
	
		//Configurer le button PB.5 en entree 
	//RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	//GPIOB->CRL &= ~(0xF<<(4*5));
	//GPIOB->CRL |= (0x4<<(4*5));
	
	button.GPIO = GPIOB;
	button.GPIO_Pin = 5;
	button.GPIO_Techno = In_Floating;
	GPIO_Init(&button);
	
	//Configurer le capot PA.0 en sortie et en mode alternate function
	//RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	//alternate push-pull
	//GPIOA->CRL &= ~(0xF<<(4*0));
	//GPIOA->CRL |= (0xB<<(4*0));

	capot.GPIO = GPIOA;
	capot.GPIO_Pin = 0;
	capot.GPIO_Techno = Alt_Out_Ppull;
	GPIO_Init(&capot);
	
	//Configurer le bras PA.1 en sortie et en mode alternate function
	//RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	//alternate push-pull
	//GPIOA->CRL &= ~(0xF<<(4*1));
	//GPIOA->CRL |= (0xB<<(4*1));

	bras.GPIO = GPIOA;
	bras.GPIO_Pin = 1;
	bras.GPIO_Techno = Alt_Out_Ppull;
	GPIO_Init(&bras);
	
	//Activer l'horloge locale de TIM2
	//RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	//Configurer TIM2 avec periode de 20ms
	//TIM2->ARR = 1439;
	//TIM2->PSC = 999;
	InitialiserTimer(TIM2,999,1439);
	
	//Configurer l'interruption de TIM2
	Init_periph(Ma_Fonction_IT);
	ConfigInterrupt(TIM2);
	//TIM2->DIER |= (0x1<<0);
	//NVIC->ISER[0] |= (1<<28);
	//NVIC->IP[28] |= (uint8_t)(0x2<<4);
	
	//configurer le canal CH1 d'un timer en mode PWM
	//il faut affecter la valeur 0b110 au bits OC1M dans le registre CCMR1 du TIM
	//sur le CH1 (broche PA.0)
	//TIM2->CCMR1 &= ~TIM_CCMR1_OC1M_0;
	//TIM2->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;
	//TIM2->CCMR1 |= TIM_CCMR1_OC1PE;
	//TIM2->CCER |= TIM_CCER_CC1E;
	PWM_Init(TIM2,1);
	//sur le CH2 (broche PA.1)
	//TIM2->CCMR1 &= ~TIM_CCMR1_OC2M_0;
	//TIM2->CCMR1 |= TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2;
	//TIM2->CCMR1 |= TIM_CCMR1_OC2PE;
	//TIM2->CCER |= TIM_CCER_CC2E;
	PWM_Init(TIM2,2);
	
	
	//Pour l'instant, fixons la duree de l'impulsion a 144 (10%)
	//TIM2->CCR1 = 144;
	//TIM2->CCR2 = 144;
	PWM_Set_Valeur(TIM2,1,144);
	PWM_Set_Valeur(TIM2,2,144);
	
	
	//Activer counter / Lancer le timer
	//TIM2->CR1 |= TIM_CR1_CEN;
  DemarrerTimer(TIM2);
	
	// boucle de traitement
		while(1)
    {  

			
    }

}
