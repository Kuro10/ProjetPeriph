#ifndef MOTEURBRAS_H
#define MOTEURBRAS_H

#include "stm32f10x.h"

void InitBras(void);
void ActiverBras(TIM_TypeDef * timer, int chanel);
void SortirBras(TIM_TypeDef * timer, int chanel);
void RentrerBras(TIM_TypeDef * timer, int chanel);
#endif
