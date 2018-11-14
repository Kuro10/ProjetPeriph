#ifndef MOTEUR_H
#define MOTEUR_H

#include "stm32f10x.h"

void PWM_Init (TIM_TypeDef * timer, int chanel); 
void PWM_Set_Valeur(TIM_TypeDef * timer,int channel, int val);

#endif
