//==============================================================================
#include "CAnimation.h"

//==============================================================================
//constructer for animation class
CAnimation::CAnimation() {
    CurrentFrame    = 0;
    MaxFrames       = 0;
    FrameInc        = 1;

    FrameRate       = 100; //Milliseconds
    OldTime         = 0;

    Oscillate       = false;
}

//animates the entity
//------------------------------------------------------------------------------
void CAnimation::OnAnimate() {
    if(OldTime + FrameRate > SDL_GetTicks()) { //if it finishes looping through the frame then return
        return;
    }

    OldTime = SDL_GetTicks(); //returns the number of milliseconds the program has been running

    CurrentFrame += FrameInc; //change to the correct frame

    if(Oscillate) {//if the animation oscillates go to the max number of frames and then snake back down
        if(FrameInc > 0) {
            if(CurrentFrame >= MaxFrames - 1) {
                FrameInc = -FrameInc;
            }
        }else{
            if(CurrentFrame <= 0) {
                FrameInc = -FrameInc;
            }
        }
    }else{//otherwise go to the max number of frames and then go back to start
        if(CurrentFrame >= MaxFrames - 1) {
            CurrentFrame = 0;
        }
    }
}

//sets the frame rate
//==============================================================================
void CAnimation::SetFrameRate(int Rate) {
    FrameRate = Rate;
}

//if the passed in frame is not valid then return. otherwise set it to current frame
//------------------------------------------------------------------------------
void CAnimation::SetCurrentFrame(int Frame) {
    if(Frame < 0 || Frame >= MaxFrames) return;

    CurrentFrame = Frame;
}

//return currentframe
//------------------------------------------------------------------------------
int CAnimation::GetCurrentFrame() {
    return CurrentFrame;
}

//==============================================================================
