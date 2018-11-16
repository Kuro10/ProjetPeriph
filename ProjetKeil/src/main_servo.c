
#include "stm32f10x.h" 
#include "timer.h"
#include "GPIO.h"
#include "MoteurBras.h"
#include "MoteurCapot.h"

int open=0;
GPIO_Struct_TypeDef button;

/* Fichier de la couche "application" */
void Ma_Fonction_IT ( void )
{
/* Le code à exécuter pendant l’interruption */
	
	// si le capot est ferme, et button = 0, ouvrir le capot, puis tourner le bras
	if( !open && GPIO_Read(GPIOB,5) ){
		open=1;
		OuvrirCapot(TIM2,1);
		SortirBras(TIM2,2);
	}
	// si le capot est ouvrert, button -> 1, tourner bras, puis fermer le capot
	else if (open && !GPIO_Read(GPIOB,5)){
		open=0;
		FermerCapot(TIM2,1);
		RentrerBras(TIM2,2);
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

	//Configurer le button PB.5 en entree 
	button.GPIO = GPIOB;
	button.GPIO_Pin = 5;
	button.GPIO_Techno = In_Floating;
	GPIO_Init(&button);
	
	//Configurer le capot PA.0 en sortie et en mode alternate function
	//alternate push-pull
	InitCapot();
	
	//Configurer le bras PA.1 en sortie et en mode alternate function
	//alternate push-pull
	InitBras();
	
	//Activer l'horloge locale de TIM2
	//Configurer TIM2 avec periode de 20ms
	InitialiserTimer(TIM2,999,1439);
	
	//Configurer l'interruption de TIM2
	Init_periph(Ma_Fonction_IT);
	ConfigInterrupt(TIM2);
	
	//configurer le canal CH1 d'un timer en mode PWM
	//il faut affecter la valeur 0b110 au bits OC1M dans le registre CCMR1 du TIM
	//sur le CH1 (broche PA.0)
	ActiverCapot(TIM2,1);
	//sur le CH2 (broche PA.1)
	ActiverBras(TIM2,2);
	
	//Pour l'instant, fixons la duree de l'impulsion a 144 (10%)
	//PWM_Set_Valeur(TIM2,1,0);
	//PWM_Set_Valeur(TIM2,2,0);
	
	
	//Activer counter / Lancer le timer
  	DemarrerTimer(TIM2);
	
	// boucle de traitement
		while(1)
    {  

			
    }

}
