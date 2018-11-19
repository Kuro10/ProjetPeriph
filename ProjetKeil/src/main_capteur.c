#include "stm32f10x.h"
#include "GPIO.h"
#include "CapteurInfra.h"
#include "timer.h"

#define FERME 0
#define OUVERT 1

int debug = 0;

/*
 * Interruption = fonction principale
 * On traite ici la d�tection du levier, du capteur, etc.
 */
void TIM3_IRQHandler(){
	
	// Sort de l'interruption
	TIM3->SR &= ~1; // Mise � 0 du UIF

	//debug = (debug == 10) ? 0 : debug + 1;
	
	// TODO : traiter la d�tection des �l�ments
	debug = getDistance();
	
}

int main (void)
{
	
	// Le timer 3 est utilis� pour traiter la fonction principale
	TIM_TypeDef * timer3 = (TIM_TypeDef *) TIM3;
	
	// Initialisation de l'ADC (pour la lecture du capteur)
	initADC();
	
	/****************************************************/
	// On configure le timer 3 pour �viter de tout traiter dans le while(1)

	// Configuration de l'interruption
	ConfigInterrupt(timer3);
	
	/*
		Initialisation du timer
		Fr�quence de lecture : 10 lectures/secondes
		f = 10 Hz --> T = 1/10
		PSC = 7199 --> ARR = 1/10*72000000/7200 - 1 = 999
	*/
	InitialiserTimer(timer3, 7199, 999);
	
	// D�marrage du timer
	DemarrerTimer(timer3);
		
	
	while(1) {}
}
