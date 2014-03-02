#ifndef CSHOT_H
#define CSHOT_H

#include "CEntity.h"

class CShot : public CEntity
{
	public:
		//this first function is the constructor
		CShot();
		
		bool OnLoad(char* File, int Width, int Height, int MaxFrames);//load the shot image

     		void OnLoop();//loop through the data

		void OnRender(SDL_Surface* Surf_Display);//render the shot

		void OnCleanup();//clean the shot up

		void OnAnimate();//animate the shot

		bool OnCollision(CEntity* Entity);//when the shot collides with something

};

#endif
