#ifndef MOTEURCAPOT_H
#define MOTEURCAPOT_H

#include "stm32f10x.h"

void InitCapot(void);
void ActiverCapot(TIM_TypeDef * timer, int chanel);
void OuvrirCapot(TIM_TypeDef * timer, int chanel);
void FermerCapot(TIM_TypeDef * timer, int chanel);

#endif
