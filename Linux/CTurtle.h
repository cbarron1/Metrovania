//=============================================================================
#ifndef _CTURTLE_H_
#define _CTURTLE_H_

#include "CEntity.h"

//=============================================================================
class CTurtle : public CEntity {
	public:

	CTurtle();//constructer

	bool OnLoad(char* File, int Width, int Height, int MaxFrames);//load image

        void OnLoop();//update data

        void OnRender(SDL_Surface* Surf_Display);//render image

        void OnCleanup();//clean  up object

        void OnAnimate();//animate turtle

        bool OnCollision(CEntity* Entity);//do things when it collides with other entitys

};
//=============================================================================

#endif
