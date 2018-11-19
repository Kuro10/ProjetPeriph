#include "Chenille.h"
#include "stm32f10x.h"
#include "GPIO.h"


Chenille_Struct_Def chenilleDroite;
Chenille_Struct_Def chenilleGauche;

void chenillesInit(void){
	// Initialisation de la chenille droite branchée IA sur C.0 et IB sur C.1
	chenilleDroite.IA_Gpio = GPIOC;
	chenilleDroite.IA_Pin = 0;
	chenilleDroite.IB_Gpio = GPIOC;
	chenilleDroite.IB_Pin = 1;
	chenilleInit(&chenilleDroite);

	// Initialisation de la chenille gauche branchée IA sur B.8 et IB sur B.9
	chenilleGauche.IA_Gpio = GPIOB;
	chenilleGauche.IA_Pin = 8;
	chenilleGauche.IB_Gpio = GPIOB;
	chenilleGauche.IB_Pin = 9;
	chenilleInit(&chenilleGauche);
}

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


void chenilleAvancer(char cote){
	// Pour faire avancer une chenille, on envoie 1 dans IA
	if (cote == 'g'){
		GPIO_Set(chenilleGauche.IA_Gpio, chenilleGauche.IA_Pin);
	}
	if (cote == 'd'){
		GPIO_Set(chenilleDroite.IA_Gpio, chenilleDroite.IA_Pin);
	}
	if (cote == 'b'){
		GPIO_Set(chenilleDroite.IA_Gpio, chenilleDroite.IA_Pin);
		GPIO_Set(chenilleGauche.IA_Gpio, chenilleGauche.IA_Pin);
	} 
}



void chenilleReculer(char cote){
	// Pour faire reculer une chenille, on envoie 1 dans IB
	if (cote == 'g'){
		GPIO_Set(chenilleGauche.IB_Gpio, chenilleGauche.IB_Pin);
	}
	if (cote == 'd'){
		GPIO_Set(chenilleDroite.IB_Gpio, chenilleDroite.IB_Pin);
	}
	if (cote == 'b'){
		GPIO_Set(chenilleDroite.IB_Gpio, chenilleDroite.IB_Pin);
		GPIO_Set(chenilleGauche.IB_Gpio, chenilleGauche.IB_Pin);
	}
}

void chenilleStop(char cote){
	// Pour faire arrêter une chenille, on reset IA (si la chenille avancait) et IB (si la chenille reculait)
	if (cote == 'g'){
		GPIO_Reset(chenilleGauche.IB_Gpio, chenilleGauche.IB_Pin);
		GPIO_Reset(chenilleGauche.IA_Gpio, chenilleGauche.IA_Pin);
	}
	if (cote == 'd'){
		GPIO_Reset(chenilleDroite.IB_Gpio, chenilleDroite.IB_Pin);
		GPIO_Reset(chenilleDroite.IA_Gpio, chenilleDroite.IA_Pin);
	}
	if (cote == 'b'){
		GPIO_Reset(chenilleGauche.IB_Gpio, chenilleGauche.IB_Pin);
		GPIO_Reset(chenilleGauche.IA_Gpio, chenilleGauche.IA_Pin);
		GPIO_Reset(chenilleDroite.IB_Gpio, chenilleDroite.IB_Pin);
		GPIO_Reset(chenilleDroite.IA_Gpio, chenilleDroite.IA_Pin);
	}
}


