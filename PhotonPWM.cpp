/*
  PhotonPWM.cpp - Library for enabling 16-Bit PWM output on the Particle Photon
  Created by Brendan Spijkerman, Januari 26, 2016.
  Released into the public domain.
*/

#include "application.h"
#include "PhotonPWM.h"
#include "math.h"

TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; //Time base structure for timers
TIM_OCInitTypeDef       TIM_OCInitStructure;   //Output compare init structure for PWM

//Constructor
PhotonPWM::PhotonPWM()
{
    //Sets the AHB clock to the system clock (prescaler to 1)
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	
	//Timer Base configuration
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // count up PWM
	TIM_TimeBaseStructure.TIM_Period = 65535;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	
	//Some PWM Output Compare structure
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
}

void PhotonPWM::initTimer(byte timerToInitiate){
    
    switch (timerToInitiate){
        case 1:
        
            //Without this setup 16-Bit output does not work
            pinMode(TX, OUTPUT);
    	    pinMode(RX, OUTPUT);
    	    analogWrite(TX, 0);
    	    analogWrite(RX, 0);
    	    
    	    //Sets PCLK2 (APB2) to the AHB clock (prescalers to 1), and thus to the system clock.
    	    //This makes sure the PWM signals are as fast as possible
    	    //http://www.han-ese.nl/STM32/stm32f0stdlibrary/html/group___r_c_c___group2.html
    	    RCC_PCLK2Config(RCC_HCLK_Div1);
    	    
    	    //The APB1Periph identifies the timer peripheral (clock). Note that TIM1 has APB2 as an identifier
	        //http://www.han-ese.nl/STM32/stm32f2stdlibrary/html/group___r_c_c.html#gaee7cc5d73af7fe1986fceff8afd3973e
    	    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    	    
    	    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
    	    
    	    //Setting up timer 1, channel 2 (TX) and 3 (RX)
        	TIM_OC2Init(TIM1, &TIM_OCInitStructure);
        	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
        	TIM_OC3Init(TIM1, &TIM_OCInitStructure);
        	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
        	
        	analogWrite16(TX, 0);
	        analogWrite16(RX, 0);
    	    
            break;
        
        case 3:
            
            //Without this setup 16-Bit output does not work
            pinMode(D2, OUTPUT);
	        pinMode(D3, OUTPUT);
	        analogWrite(D2, 0);
	        analogWrite(D3, 0);
	        
	        //Sets PCLK1 (APB1) to the AHB clock (prescalers to 1), and thus to the system clock.
	        //This makes sure the PWM signals are as fast as possible
	        //http://www.han-ese.nl/STM32/stm32f0stdlibrary/html/group___r_c_c___group2.html
	        RCC_PCLK1Config(RCC_HCLK_Div1);
	        
	        //The APB1Periph identifies the timer peripheral (clock)
	        //http://www.han-ese.nl/STM32/stm32f2stdlibrary/html/group___r_c_c.html#gaee7cc5d73af7fe1986fceff8afd3973e
	        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	        
	        TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	        
	        //Setting up timer 3, channel 1 (D3) and 2 (D2)
        	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
        	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
        	TIM_OC2Init(TIM3, &TIM_OCInitStructure);
        	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
        	
    		analogWrite16(D2, 0);
	        analogWrite16(D3, 0);
	        
            break;
        
        case 4:
            
            //Without this setup 16-Bit output does not work
            pinMode(D0, OUTPUT);
    	    pinMode(D1, OUTPUT);
	    	analogWrite(D0, 0);
	        analogWrite(D1, 0);
        
            //Sets PCLK1 (APB1) to the AHB clock (prescalers to 1), and thus to the system clock.
            //This makes sure the PWM signals are as fast as possible
            //http://www.han-ese.nl/STM32/stm32f0stdlibrary/html/group___r_c_c___group2.html
	        RCC_PCLK1Config(RCC_HCLK_Div1);
	        
	        //The APB1Periph identifies the timer peripheral (clock)
	        //http://www.han-ese.nl/STM32/stm32f2stdlibrary/html/group___r_c_c.html#gaee7cc5d73af7fe1986fceff8afd3973e
        	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
        	
        	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
        	
    		//Setting up timer 4, channel 1 (D1) and 2 (D0)
        	TIM_OC1Init(TIM4, &TIM_OCInitStructure);
        	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
        	TIM_OC2Init(TIM4, &TIM_OCInitStructure);
        	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
        	
        	analogWrite16(D0, 0);
	        analogWrite16(D1, 0);
            
            break;
        
        case 5:
            
            //Without this setup 16-Bit output does not work
        	pinMode(WKP, OUTPUT);
	        analogWrite(WKP, 0);
        
            //Sets PCLK1 (APB1) to the AHB clock (prescalers to 1), and thus to the system clock.
            //This makes sure the PWM signals are as fast as possible
            //http://www.han-ese.nl/STM32/stm32f0stdlibrary/html/group___r_c_c___group2.html
	        RCC_PCLK1Config(RCC_HCLK_Div1);
	        
	        //The APB1Periph identifies the timer peripheral (clock)
	        //http://www.han-ese.nl/STM32/stm32f2stdlibrary/html/group___r_c_c.html#gaee7cc5d73af7fe1986fceff8afd3973e
	        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	        
	        TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
	        
        	//Setting up timer 5, channel 1 (WKP)
        	TIM_OC1Init(TIM5, &TIM_OCInitStructure);
        	TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);

	        analogWrite16(WKP, 0);
            
            break;
            
        default:
            Serial.println("Timer " + String(timerToInitiate) + " can not be configured");
    }
    
}

void PhotonPWM::initAllTimers(){
    initTimer(1);
    initTimer(3);
    initTimer(4);
    initTimer(5);
}

bool PhotonPWM::timerInitiated(byte timerNr){
    
    if(timersInitiated[timerNr]){
        return true;
    } else {
        return false;
    }
    
}

void PhotonPWM::analogWrite16(byte pin, unsigned int dutyCycle){
	STM32_Pin_Info* PIN_MAP = HAL_Pin_Map();

	//Invert the dutyCycle so the output corresponds to the user's expectations (0 = low, 65535 = high)
	TIM_OCInitStructure.TIM_Pulse = 65535 - dutyCycle;
	
	if(PIN_MAP[pin].timer_peripheral == TIM1){
	    Serial.println("modifying TIM1");
	    if (PIN_MAP[pin].timer_ch == TIM_Channel_2) {
	        
	    }
	}

	if (PIN_MAP[pin].timer_ch == TIM_Channel_1 && PIN_MAP[pin].timer_peripheral == TIM1) {
        Serial.println("modifying TIM1");
		PIN_MAP[pin].timer_peripheral-> CCR1 = TIM_OCInitStructure.TIM_Pulse;
	} else if (PIN_MAP[pin].timer_ch == TIM_Channel_2) {
        //Serial.println("modifying TIM2");
		PIN_MAP[pin].timer_peripheral-> CCR2 = TIM_OCInitStructure.TIM_Pulse;
	} else if (PIN_MAP[pin].timer_ch == TIM_Channel_3) {
        //Serial.println("modifying TIM3");
		PIN_MAP[pin].timer_peripheral-> CCR3 = TIM_OCInitStructure.TIM_Pulse;
	} else if (PIN_MAP[pin].timer_ch == TIM_Channel_4) {
        //Serial.println("modifying TIM4");
		PIN_MAP[pin].timer_peripheral-> CCR4 = TIM_OCInitStructure.TIM_Pulse;
	} else {
        //Serial.println("did not find a TIM match");
		Serial.println(PIN_MAP[pin].timer_ch);
	}

}

void PhotonPWM::analogWrite16GC(byte pin, unsigned int dutyCycle){
    
    float gamma   = 2.8; // Correction factor
    int   max_in  = 65535, // Top end of INPUT range
          max_out = 65535; // Top end of OUTPUT range
          
    unsigned int val = (int)(pow((float)dutyCycle / (float)max_in, gamma) * max_out + 0.5);
    analogWrite16(pin, val);
}



























