#include "MoteurCapot.h"
#include "GPIO.h"
#include "Moteur.h"

void InitCapot() {
	GPIO_Struct_TypeDef capot;
	
	capot.GPIO = GPIOA;
	capot.GPIO_Pin = 0;
	capot.GPIO_Techno = Alt_Out_Ppull;
	GPIO_Init(&capot);
	
}

void ActiverCapot(TIM_TypeDef * timer, int chanel){
	PWM_Init(timer,chanel);
}

void OuvrirCapot(TIM_TypeDef * timer, int chanel){
	PWM_Set_Valeur(timer,chanel,108);
}

void FermerCapot (TIM_TypeDef * timer, int chanel){
	PWM_Set_Valeur(timer,chanel,50);
}
