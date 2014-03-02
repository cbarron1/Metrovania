#ifndef CWHIP_H
#define CWHIP_H

#include "CEntity.h"

class CWhip : public CEntity
{
	public:
		//this first function is the constructor
		CWhip();
		
		bool OnLoad(char* File, int Width, int Height, int MaxFrames);//load image

     		void OnLoop();//update data

		void OnRender(SDL_Surface* Surf_Display);//render image

		void OnCleanup();//clean up object

		void OnAnimate();//animate whip

		bool OnCollision(CEntity* Entity);//do things if it collides with something

};

#endif
