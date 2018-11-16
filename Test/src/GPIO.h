#ifndef GPIO_H
#define GPIO_H

#include "stm32f10x.h"

#define In_Floating 4
#define In_PullDown 8
#define In_PullUp 8
#define In_Analog 0
#define Out_Ppull 1 // 10 MHz
#define Out_OD 5
#define Alt_Out_Ppull 0xB

#define PIN_CRL_MAX 8

typedef struct{
  GPIO_TypeDef * GPIO;
  char GPIO_Pin;
  char GPIO_Techno;
} GPIO_Struct_TypeDef;

// Configuration d'une PIN
void GPIO_Init(GPIO_Struct_TypeDef * GPIOStructPtr);

// Renvoie 0 ou autre chose différent de 0
int GPIO_Read(GPIO_TypeDef * GPIO, char GPIO_Pin);

// Met 3,3V sur la pin et le GPIO souhaités
void GPIO_Set(GPIO_TypeDef * GPIO, char GPIO_Pin);

// Met 0V sur la pin et le GPIO souhaités
void GPIO_Reset(GPIO_TypeDef * GPIO, char GPIO_Pin);

#endif
