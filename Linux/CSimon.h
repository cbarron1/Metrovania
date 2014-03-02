//=============================================================================
#ifndef _CSIMON_H_
    #define _CSIMON_H_

#include "CEntity.h"

//=============================================================================
class CSimon : public CEntity {
    public:
        CSimon();//constructer

	bool OnLoad(char* File, int Width, int Height, int MaxFrames);//load the image

        void OnLoop();//loop the data

        void OnRender(SDL_Surface* Surf_Display);//render the image

        void OnCleanup();//clean him up

        void OnAnimate();//animate simon

        bool OnCollision(CEntity* Entity);//when he collides with something

	bool	Crouch;//is simon crouching?

	bool	Taunt;//is he taunting?

	bool	Attack;//is he attacking?

	int	AttackTimer;//helps time attacks

	SDL_Surface*	Surf_Health;//surface for health bar

	SDL_Surface*	Surf_Whip;//surface for the brandishing part of whip

	bool	PointUp;//is he pointing up?
};

//=============================================================================

#endif
