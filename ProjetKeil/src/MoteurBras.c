#include "MoteurBras.h"
#include "GPIO.h"
#include "Moteur.h"

void InitBras() {
	GPIO_Struct_TypeDef bras;
	
	bras.GPIO = GPIOA;
	bras.GPIO_Pin = 1;
	bras.GPIO_Techno = Alt_Out_Ppull;
	GPIO_Init(&bras);
	
}

void ActiverBras(TIM_TypeDef * timer, int chanel){
	PWM_Init(timer,chanel);
}

void SortirBras(TIM_TypeDef * timer, int chanel){
	PWM_Set_Valeur(timer,chanel,135);
}

void RentrerBras(TIM_TypeDef * timer, int chanel){
	PWM_Set_Valeur(timer,chanel,34);
}
