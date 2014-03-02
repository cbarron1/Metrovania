//=============================================================================
#ifndef _CINSECT_H_
#define _CINSECT_H_

#include "CEntity.h"

//=============================================================================
class CInsect : public CEntity {
	public:
	
	int jumpTimer;//variable helps with jump timing

	CInsect();//constructer

	bool OnLoad(char* File, int Width, int Height, int MaxFrames);//load image

        void OnLoop();//update data

        void OnRender(SDL_Surface* Surf_Display);//render image

        void OnCleanup();//clean up insect

        void OnAnimate();//animate the insect

        bool OnCollision(CEntity* Entity);//when the insect collides

};
//=============================================================================

#endif
