#ifndef TIMER_H
#define TIMER_H

#include "stm32f10x.h"

void ConfigInterrupt(TIM_TypeDef * timer);
void InitialiserTimer(TIM_TypeDef * timer, int prescaler, int autoreload);
void DemarrerTimer(TIM_TypeDef * timer);
void StopTimer(TIM_TypeDef * timer);

#endif
