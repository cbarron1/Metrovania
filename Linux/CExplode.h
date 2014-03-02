#ifndef CEXPLODE_H
#define CEXPLODE_H

#include "CEntity.h"

class CExplode : public CEntity
{
	public:
		//this first function is the constructor
		CExplode();
		
		bool OnLoad(char* File, int Width, int Height, int MaxFrames);//load the image of the effect

     		void OnLoop();//update data

		void OnRender(SDL_Surface* Surf_Display);//draw effect

		void OnCleanup();//clean up effect

		void OnAnimate();//animate effect

		bool OnCollision(CEntity* Entity);//check to see if effect has collided

		bool isbomb;//is it a bomb?
		int cycle;//important for timing
		int fm; //max frames
		int cyclelimit; //how many iterations
		int altframemax; //alternate max frames

};

#endif
