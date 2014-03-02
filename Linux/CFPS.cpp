//=============================================================================
#include "CFPS.h"

//=============================================================================
CFPS CFPS::FPSControl;

//constructer
//=============================================================================
CFPS::CFPS() {
	OldTime     = 0;
	LastTime    = 0;

	SpeedFactor	= 0;

	Frames      = 0;
	NumFrames   = 0;
}


//=============================================================================
void CFPS::OnLoop() {
	if(OldTime + 1000 < SDL_GetTicks()) {//if the old time + 1000 is less then the time the program has been running
		OldTime = SDL_GetTicks();//make old time equal to the time the program has been running

		NumFrames = Frames;//set the number of frames to the frame variable

		Frames = 0;//set frame variable to 0
	}

	SpeedFactor = ((SDL_GetTicks() - LastTime) / 1000.0f) * 32.0f;//calculates how much we should scale everthing by to match frame rate

	LastTime = SDL_GetTicks();//set last time to the time the program has been running

	Frames++;//increement frames
}

//=============================================================================
int CFPS::GetFPS() {
    return NumFrames;//simply return the number of frames
}

//------------------------------------------------------------------------------
float CFPS::GetSpeedFactor() {
    return SpeedFactor;//return speedfactor
}

//==============================================================================
