#ifndef CHENILLE_H
#define CHENILLE_H

#include "stm32f10x.h"

typedef struct {
	GPIO_TypeDef * IA_Gpio; // Le GPIO ou est branché l'IA de la chenille
	char IA_Pin;						// Pin ou est branché l'IA de la chenille
	GPIO_TypeDef * IB_Gpio; // Le GPIO ou est branché l'IB de la chenille
	char IB_Pin;						// Pin ou est branché l'IB de la chenille
} Chenille_Struct_Def;


/**
 * Configuration et initialisation d'une chenille
 */
void chenilleInit(Chenille_Struct_Def * chenille);
/**
 * Faire avancer une chenille
 */
void chenilleAvancer(Chenille_Struct_Def * chenille);
/**
 * Faire reculer une chenille
 */
void chenilleReculer(Chenille_Struct_Def * chenille);
/**
 * Faire Arreter une chenille
 */
void chenilleStop(Chenille_Struct_Def * chenille);

#endif