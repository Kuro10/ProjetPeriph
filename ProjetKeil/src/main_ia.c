#include "stm32f10x.h"
#include "GPIO.h"
#include "CapteurInfra.h"
#include "timer.h"
#include "MoteurBras.h"
#include "MoteurCapot.h"
#include "Chenille.h"

#define NB_OUVERTURES_AVANT_ATTENTE 3
#define DUREE_ATTENTE 2 // Secondes



int tempsChenille = 0;
int chenilleActive = 0;

// Variables IA
enum etatsCapot {FERME, OUVERT, MIOUVERT};
//enum etatsCapteur {MODE0, MODE1, MODE2};

int countOuvertures = 0;
enum etatsCapot etatCapot = FERME;

#define NB_OUVERTURES_AVANT_CAPTEUR_MODE1 3
#define DUREE_OUVERTURE_CAPTEUR_MODE1 1
#define NB_OUVERTURES_AVANT_CAPTEUR_MODE2 6
#define DUREE_OUVERTURE_CAPTEUR_MODE2 3

#define DUREE_ANIM_CHENILLE_TOTAL 30
#define DUREE_ANIM_CHENILLE 4

#define GPIO_BOUTON GPIOB
#define GPIO_BOUTON_PIN 5


void TIM3_IRQHandler(){
	
	int distance;
	
	// Sort de l'interruption
	TIM3->SR &= ~1; // Mise � 0 du UIF
	


	//debug = (debug == 10) ? 0 : debug + 1;
	
	// TODO : traiter la d�tection des �l�ments
	//debug = getDistance();
	
	/*
		Intelligence artificielle
	*/
	
	if(chenilleActive){
		
		chenilleReculer('b');
		
		if(tempsChenille % DUREE_ANIM_CHENILLE >= DUREE_ANIM_CHENILLE/2){
			chenilleStop('d');
			chenilleReculer('g');
		}
		else{
			chenilleStop('g');
			chenilleReculer('d');
		}
		
	
		if(tempsChenille >= DUREE_ANIM_CHENILLE_TOTAL){
			chenilleStop('b');
			chenilleActive = 0;
		}
		else
			tempsChenille++;
		
		return;
	}
	
	// Bouton
	if(etatCapot != OUVERT && GPIO_Read(GPIO_BOUTON, GPIO_BOUTON_PIN)){
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
	
	// Capteur
	else if(etatCapot != OUVERT && !GPIO_Read(GPIO_BOUTON, GPIO_BOUTON_PIN)){
		
		distance = getDistance();

		// Si on est suffisamment proche
		if(distance == DISTANCE_TROP_PRES){
		
			// CAPTEUR_MODE1 = Miouverture capot
			if(countOuvertures >= NB_OUVERTURES_AVANT_CAPTEUR_MODE1
				&& countOuvertures < NB_OUVERTURES_AVANT_CAPTEUR_MODE2){
				
				OuvrirCapot(TIM2, 1);
				//sleep(DUREE_OUVERTURE_CAPTEUR_MODE1);
				//SortirBras(TIM2,2);
				etatCapot = MIOUVERT;
					
			}
				
			// CAPTEUR_MODE2 = Chenilles
			if(!chenilleActive && countOuvertures >= NB_OUVERTURES_AVANT_CAPTEUR_MODE2){
				
				/*chenilleAvancer('g');
				chenilleReculer('d');*/
				tempsChenille = 0;
				chenilleActive = 1;
				
			}
		
		
		}
		
		// Si on se recule
		else if(etatCapot == MIOUVERT && distance >= 10){
			
			FermerCapot(TIM2, 1);
			etatCapot = FERME;
			
		}
		
	}
		
}	

int main (void)
{
	
	// Le timer 3 est utilis� pour traiter la fonction principale
	//TIM_TypeDef * timer3 = (TIM_TypeDef *) TIM3;
	
	// Initialisation de l'ADC (pour la lecture du capteur)

	initADC();
	
	/****************************************************/
	// On configure le timer 3 pour �viter de tout traiter dans le while(1)

	/*
		Initialisation du timer
		Fr�quence de lecture : 10 lectures/secondes
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
	
	// D�marrage du timer
	DemarrerTimer(TIM3);
	DemarrerTimer(TIM2);
	
	// Initialisation de la chenille
	chenillesInit();
	
	while(1) {}
}
