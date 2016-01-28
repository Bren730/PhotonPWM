# PhotonPWM
Sets the Particle Photon's resolution to 16-Bit and the highest frequency 

To use the library, copy the PhotonPWM.h and PhotonPWM.cpp into your project folder. Then put #include "PhotonPWM.h" at the top of your code. After that you can create a new instance of  PhotonPWM by calling "PhotonPWM [name you want to use]". In your setup(); run [name you want to use].initTimers();, this initialises all the Photon's PWM pins (D0, D1, D2, D3, WKP, TX, RX) and enables 16-Bit PWM output.
Now just call [name you want to use].analogWrite16(pin, value); and it should work.