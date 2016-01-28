# PhotonPWM
Sets the Particle Photon's resolution to 16-Bit and the highest frequency 

To use the library, copy the PhotonPWM.h and PhotonPWM.cpp into your project folder. Then put #include "PhotonPWM.h" at the top of your code. After that you can create a new instance of  PhotonPWM by calling "PhotonPWM [name you want to use]". In your setup(); run [name you want to use].initTimer([timer you want to use]);, this initialises the Photon's PWM pins of the timer you selected (D0, D1, D2, D3, WKP, TIM1: TX, RX) and enables 16-Bit PWM output.

| Timer | Pins |
|---|---|
| TIM1 | TX, RX |
| TIM3 | D2, D3 |
| TIM4 | D0, D1 |
| TIM5 | WKP	|

Now just call [name you want to use].analogWrite16(pin, value); and it should work, if the pin is initialised.

Note that this branch is the development branch and as such likely contains bugs.

##Known issues:##

*Timer initialisation screws with the normal analogWrite. Initialising only one timer works, but breaks PWM output on all other pins