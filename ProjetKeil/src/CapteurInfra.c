#include "CapteurInfra.h"
#include "GPIO.h"

void initADC(void){
	
	// Initialisation de l'ADC1 (GPIOB0)
	GPIO_Struct_TypeDef adc;
	adc.GPIO = GPIOB;
	adc.GPIO_Pin = 0;
	adc.GPIO_Techno = In_Analog;
	GPIO_Init(&adc);
	
	// Activation de l'horloge associée
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	// Division de la fréquence par 6 (72/6 < 14)
	RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;
	
	// Allumage de l'ADC
	ADC1->CR2|= ADC_CR2_ADON;
	
	// Sélection de la voie
	ADC1->SQR1 &= ADC_SQR1_L;
	ADC1->SQR3 |= 8;
	
	// Calibration
	ADC1->CR2 |= ADC_CR2_CAL;
	while(ADC1->CR2 & ADC_CR2_CAL);
	
}


int getVoltage(void){
	
	// Lancement de la conversation
	ADC1->CR2 |= ADC_CR2_ADON; // Déjà initialisé donc lance
	
	// Attente de la fin de la conversion
	while(!(ADC1->SR & ADC_SR_EOC));
	
	// On peut reprendre une autre mesure
	ADC1->SR &= ~ADC_SR_EOC;
	
	// Valeur stockée dans les 12 premiers bits
	return ADC1->DR & 0xFFF;
}

int getDistance(void){
	/*
		>= 0xA80 --> trop près (moins de 6 cm)
		<= 0x200 --> trop loin (plus de 36 cm)
	
		Valeur min : 0x200 = 512
		Valeur max : 0xA80 = 2688
		
		Valeur x mesurée entre 512 et 2688
		
		Il faut utiliser l'inverse de la distance ! (Pas linéaire sinon)

		2688 --> 1/6
		x --> A = (x/6)/2688
		
		==> distance = 1/A = 2688*6/x
	*/
	
	int voltage = getVoltage();
	
	int distance = 2688*6/voltage;
	
	return distance;
}
