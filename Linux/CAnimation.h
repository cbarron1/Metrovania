//==============================================================================
// Animation Class
//==============================================================================
#ifndef _CANIMATION_H_
    #define _CANIMATION_H_

#include <SDL.h>

//==============================================================================
class CAnimation {
	public:
		int	CurrentFrame;//keeps track of the current frame number

		int     FrameInc;//keeps track of the incoming frame

    private:
        int     FrameRate; //Milliseconds

		long    OldTime;//time since animation started

	public:
        int	    MaxFrames;//max number of frames in animation

		bool	Oscillate;//how we want to loop through frames

	public:
		CAnimation();//constructer

		void OnAnimate();//animates entity

	public:
        void SetFrameRate(int Rate);//sets the frame rate equal to computer

		void SetCurrentFrame(int Frame);//sets the frame of the animation 

		int GetCurrentFrame();//returns the current frame
};

//==============================================================================

#endif
