#include "Chenille.h"
#include "stm32f10x.h"
#include "GPIO.h"


void chenilleInit(Chenille_Struct_Def * chenille){
	
	GPIO_Struct_TypeDef gpioIA;
	GPIO_Struct_TypeDef gpioIB;
	
	// Initialisation du GPIO concerné par l'IA de la chenille
	gpioIA.GPIO = chenille->IA_Gpio;
	gpioIA.GPIO_Pin = chenille->IA_Pin;
	gpioIA.GPIO_Techno = Out_Ppull;
	GPIO_Init(&gpioIA);
	// Initialisation du GPIO concerné par l'IB de la chenille
	gpioIB.GPIO = chenille->IB_Gpio;
	gpioIB.GPIO_Pin = chenille->IB_Pin;
	gpioIB.GPIO_Techno = Out_Ppull;
	GPIO_Init(&gpioIB);
}


void chenilleAvancer(Chenille_Struct_Def * chenille){
	// Pour faire avancer une chenille, on envoit 1 dans IA
	GPIO_Set(chenille->IA_Gpio, chenille->IA_Pin);
}

void chenilleReculer(Chenille_Struct_Def * chenille){
	// Pour faire avancer une chenille, on envoit 1 dans IB
	GPIO_Set(chenille->IB_Gpio, chenille->IB_Pin);
}

void chenilleStop(Chenille_Struct_Def * chenille){
	// Pour faire arrêter une chenille, on reset IA (si la chenille avancait)
	GPIO_Reset(chenille->IA_Gpio, chenille->IA_Pin);
	// et IB (si la chenille reculait)
	GPIO_Reset(chenille->IB_Gpio, chenille->IB_Pin);
}


