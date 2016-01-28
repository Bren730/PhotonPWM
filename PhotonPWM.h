/*
  PhotonPWM.h - Library for enabling 16-Bit PWM output on the Particle Photon
  Created by Brendan Spijkerman, Januari 26, 2016.
  Released into the public domain.
*/

#ifndef PhotonPWM_h
#define PhotonPWM_h

#include "application.h"

#if !defined(STM32F2XX) && !defined(PLATFORM_ID)	//Photon
	#error "*** This device is not supported by this library. Platform should be Particle Photon ***"
#endif

class PhotonPWM {
	public:
		PhotonPWM();
		void initTimers();
		void analogWrite16(byte pin, unsigned int dutyCycle);
		void analogWrite16GC(byte pin, unsigned int dutyCycle);
};

#endif