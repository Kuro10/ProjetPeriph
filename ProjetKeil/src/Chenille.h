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
 *	Initialisation des chenilles
 */
void chenillesInit(void);


/**
 * Configuration et initialisation d'une chenille
 */
void chenilleInit(Chenille_Struct_Def * chenille);


/**
 * Faire avancer une chenille
 * @param :
 * 'g' pour faire avancer la chenille gauche, 'd' pour la droite, 'b' pour les deux (both)
 */
void chenilleAvancer(char cote);


/**
 * Faire reculer une chenille
 */
void chenilleReculer(char cote);


/**
 * Faire Arreter une chenille
 */
void chenilleStop(char cote);

#endif