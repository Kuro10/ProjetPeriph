#include "stm32f10x.h"
#include "GPIO.h"
#include "CapteurInfra.h"

#define FERME 0
#define OUVERT 1

int debug = 0;

int main (void)
{
	
	// Initialisation du GPIOX N (Capteur infrarouge)
	/*GPIO_Struct_TypeDef capteur;
	capteur.GPIO = GPIOA; // TODO
	capteur.GPIO_Pin = 1; // TODO
	capteur.GPIO_Techno = In_Analog;
	GPIO_Init(&capteur);*/
	
	initADC();
	
	
	while(1) {
		
		debug = getDistance();
	
	}
}
