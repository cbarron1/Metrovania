//==============================================================================
// FPS Class
//==============================================================================
#ifndef _CFPS_H_
    #define _CFPS_H_

#include <SDL.h>

//==============================================================================
class CFPS {
	public:
		static CFPS FPSControl;//class is static

	private:
		int     OldTime;//time variables
		int     LastTime;

		float 	SpeedFactor;//variable to decide how much we multiply to match framerate

		int		NumFrames;//frame variables
		int     Frames;

	public:
		CFPS();//constructer

		void    OnLoop();//update data

	public:
		int     GetFPS();//get frames per second

		float   GetSpeedFactor();//get speed factor
};

//==============================================================================
#endif
