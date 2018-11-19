#include "stm32f10x.h"
#include "GPIO.h"
#include "CapteurInfra.h"
#include "timer.h"
#include "MoteurBras.h"
#include "MoteurCapot.h"

#define NB_OUVERTURES_AVANT_ATTENTE 3
#define DUREE_ATTENTE 2 // Secondes

enum etatsCapot {FERME, OUVERT};
//enum etatsCapteur {MODE0, MODE1, MODE2};
#define NB_OUVERTURES_AVANT_CAPTEUR_MODE1 6
#define DUREE_OUVERTURE_CAPTEUR_MODE1 1
#define NB_OUVERTURES_AVANT_CAPTEUR_MODE2 6
#define DUREE_OUVERTURE_CAPTEUR_MODE2 3

#define GPIO_BOUTON GPIOB
#define GPIO_BOUTON_PIN 5

/*int lireBouton(){
	return 1;
}

void ouvrirCapot(){
	
}

void fermerCapot(){
	
}*/

int debug = 0;

// Variables IA
int countOuvertures = 0;
enum etatsCapot etatCapot = FERME;


void TIM3_IRQHandler(){
	


	//debug = (debug == 10) ? 0 : debug + 1;
	
	// TODO : traiter la détection des éléments
	//debug = getDistance();
	
	/*
		Intelligence artificielle
	*/
	//int distance;
	
	// Bouton
	if(etatCapot == FERME && GPIO_Read(GPIO_BOUTON, GPIO_BOUTON_PIN)){
		// On ouvre le capot
		
		OuvrirCapot(TIM2, 1);
		SortirBras(TIM2, 2);
		
		countOuvertures++;
		etatCapot = OUVERT;
	}
	else if(etatCapot == OUVERT && !GPIO_Read(GPIO_BOUTON, GPIO_BOUTON_PIN)){
		// On ferme le capot
		
		RentrerBras(TIM2, 2);
		FermerCapot(TIM2, 1);
		etatCapot = FERME;
	}
	
	// Sort de l'interruption
	TIM3->SR &= ~1; // Mise à 0 du UIF
	
	// Capteur
	/*else if(etatCapot == FERME && !GPIO_Read(GPIO_BOUTON, GPIO_BOUTON_PIN)){
		
		distance = getDistance();
		
		// Si on est suffisamment proche
		if(distance == DISTANCE_TROP_PRES){
		
			// CAPTEUR_MODE1
			if(countOuvertures >= NB_OUVERTURES_AVANT_CAPTEUR_MODE1
				&& countOuvertures < NB_OUVERTURES_AVANT_CAPTEUR_MODE2){
				
				OuvrirCapot(TIM2, 1);
				//sleep(DUREE_OUVERTURE_CAPTEUR_MODE1);
				SortirBras(TIM2,2);
					
			}
				
			// CAPTEUR_MODE2
			else if(countOuvertures >= NB_OUVERTURES_AVANT_CAPTEUR_MODE2){
				
				OuvrirCapot();
				//sleep(DUREE_OUVERTURE_CAPTEUR_MODE1);
				fermerCapot();
				
				ouvrirCapot();
				//sleep(DUREE_OUVERTURE_CAPTEUR_MODE1);
				fermerCapot();
				
			}
		
		
		
		
	}*/
}	

int main (void)
{
	
	// Le timer 3 est utilisé pour traiter la fonction principale
	//TIM_TypeDef * timer3 = (TIM_TypeDef *) TIM3;
	
	// Initialisation de l'ADC (pour la lecture du capteur)
	initADC();
	
	/****************************************************/
	// On configure le timer 3 pour éviter de tout traiter dans le while(1)

	/*
		Initialisation du timer
		Fréquence de lecture : 10 lectures/secondes
		f = 10 Hz --> T = 1/10
		PSC = 7199 --> ARR = 1/10*72000000/7200 - 1 = 999
	*/
	InitialiserTimer(TIM3, 7199, 999);
	
	// Initialisation Timer bras
	InitialiserTimer(TIM2, 999, 1439);
	
	// Configuration de l'interruption
	ConfigInterrupt(TIM3);
	
	
	InitBras();
	ActiverBras(TIM2, 2);
	InitCapot();
	ActiverCapot(TIM2, 1);
	
	// Démarrage du timer
	DemarrerTimer(TIM3);
	DemarrerTimer(TIM2);
	
	//SortirBras(TIM2, 2);
		
	
	while(1) {}
}
