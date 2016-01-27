void initTimers(){
    
    //Without this setup 16-Bit output does not work
    pinMode(D0, OUTPUT);
    pinMode(D1, OUTPUT);
    pinMode(D2, OUTPUT);
    pinMode(D3, OUTPUT);
    pinMode(WKP, OUTPUT);
    pinMode(TX, OUTPUT);
    pinMode(RX, OUTPUT);
    
    analogWrite(D0, 0);
    analogWrite(D1, 0);
    analogWrite(D2, 0);
    analogWrite(D3, 0);
    analogWrite(WKP, 0);
    analogWrite(TX, 0);
    analogWrite(RX, 0);
    
    //GPIO clocks enable
    //Initialise GPIO for PWM function
    GPIO_InitTypeDef        GPIO_InitStructure;    //GPIO Initialisation Structure
    
    //Sets the AHB clock to the system clock (prescaler to 1), then sets PCLK1 and PCLK2 (APB1 and APB2) to the AHB clock (prescalers to 1), and thus to the system clock.
    //These lines of code make sure the PWM signals are as fast as possible and equal to each other
    //http://www.han-ese.nl/STM32/stm32f0stdlibrary/html/group___r_c_c___group2.html
    RCC_HCLKConfig(RCC_SYSCLK_Div1);
    RCC_PCLK1Config(RCC_HCLK_Div1);
    RCC_PCLK2Config(RCC_HCLK_Div1);
    
    //Enable GPIO
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    
    //Initialize D0/PB7, Alternative Function, 100Mhz, Output, Push-pull
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
    
    GPIO_Init(GPIOB, &GPIO_InitStructure); // Note the GPIOB. 
    GPIO_Init(GPIOA, &GPIO_InitStructure); // Note the GPIOB. 
    
    // Consult https://docs.particle.io/datasheets/photon-datasheet/#pin-out-diagrams for pinout, pay attention to the STM32 Pin column, ie PB7
    // the 'B' in PB7 means you should use the 'B' GPIO, GPIOB.  PA4 would use GPIOA.
    
    //The APB1Periph identifies the timer peripheral (clock). Note that TIM1 has APB2 as an identifier
    //http://www.han-ese.nl/STM32/stm32f2stdlibrary/html/group___r_c_c.html#gaee7cc5d73af7fe1986fceff8afd3973e
    //Both APB1 and APB2 are derived from the AHB clock which, in turn is derived from the system clock. 
    //Earlier we set all prescalers to 1, essentially coupling all timers to the system clock
    // /https://sites.google.com/site/learningeclipsearm/5-using-stm32-std-lib/a-clocks
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
    
    
    /* Timer Base configuration */
    TIM_TimeBaseStructure.TIM_Prescaler = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; // count up PWM
    //TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseStructure.TIM_Period = 65535;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); // TIM4 = Timer 4
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); // TIM4 = Timer 4
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure); // TIM4 = Timer 4
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); // TIM4 = Timer 4
    
    //Some PWM Output Compare structure
    TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    
    //Setting up timer 1, channel 2 (TX) and 3 (RX)
    TIM_OC3Init(TIM1, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
    TIM_OC2Init(TIM1, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
    
    //Setting up timer 3, channel 1 (D3) and 2 (D2)
    TIM_OC1Init(TIM3, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
    TIM_OC2Init(TIM3, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
    
    //Setting up timer 4, channel 1 (D1) and 2 (D0)
    TIM_OC1Init(TIM4, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
    TIM_OC2Init(TIM4, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
    
    //Setting up timer 5, channel 1 (WKP)
    TIM_OC1Init(TIM5, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);
    //TIM_ARRPreloadConfig(TIM4, ENABLE); // don't seem to need this

    Serial.println("Finished setting up PWMs");
}

void analogWrite16(int pin, unsigned int dutyCycle){
    STM32_Pin_Info* PIN_MAP = HAL_Pin_Map();
    
    TIM_OCInitStructure.TIM_Pulse = 65535 - dutyCycle;
    
    //PIN_MAP[pin].timer_peripheral-> CCR2 = TIM_OCInitStructure.TIM_Pulse;
    
    if (PIN_MAP[pin].timer_ch == TIM_Channel_1) {
        //Serial.println("modifying TIM1");
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