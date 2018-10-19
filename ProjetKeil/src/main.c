#include "stm32f10x.h"
#include "GPIO.h"

int debug = 0;

int main (void)
{	
	int traitement_levier = 0;
	
	// Initialisation du GPIO D4
	GPIO_Struct_TypeDef levier;
	levier.GPIO = GPIOB;
	levier.GPIO_Pin = 5;
	levier.GPIO_Techno = In_PullUp;
	GPIO_Init(&levier);
	
	
	while(1) {
	
		// Bouton levé
		if(!traitement_levier && GPIO_Read(GPIOB, 5)){
			debug++;
		}
		else{
			debug = 0;
		}
	
	}
}
