#include "stm32f10x.h"
#include "GPIO.h"

#define FERME 0
#define OUVERT 1

int debug = 0;

int main (void)
{	
	int etat_levier = FERME;
	
	// Initialisation du GPIO D4
	GPIO_Struct_TypeDef levier;
	levier.GPIO = GPIOB;
	levier.GPIO_Pin = 5;
	levier.GPIO_Techno = In_PullUp;
	GPIO_Init(&levier);
	
	
	
	
	while(1) {
	
		// Bouton levé
		if(etat_levier == FERME && GPIO_Read(GPIOB, 5)){
			// On ouvre le capot
			
			debug = 0;
			etat_levier = OUVERT;
		}
		else if(etat_levier == OUVERT && !GPIO_Read(GPIOB, 5)){
			// On ferme le capot
			
			debug = 0;
			etat_levier = FERME;
		}
		else{
			debug++;
		}
	
	}
}
