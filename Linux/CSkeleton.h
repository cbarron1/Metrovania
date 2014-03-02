//=============================================================================
#ifndef _CSKELETON_H_
#define _CSKELETON_H_

#include "CEntity.h"
#include "CSword.h"

//=============================================================================
class CSkeleton : public CEntity {
	public:

	CSkeleton();//constructer

	bool OnLoad(char* File, int Width, int Height, int MaxFrames);//load image

        void OnLoop();//update data

        void OnRender(SDL_Surface* Surf_Display);//render images

        void OnCleanup();//clean up object

        void OnAnimate();//animate

        bool OnCollision(CEntity* Entity);//do things when collision happens
        
    bool swordOut;//is his sword out?
    int AttackTimer;//timer used for timing
    
    float playerPos;//players x position
    float yPlayerPos;//players y position
    
    bool moving;//is he moving?
    
    CSword upSword;//composition (sword class for when he is brandishing it)
    CSword outSword;//composition (sword class for when he is stabbing)


};
//=============================================================================

#endif
