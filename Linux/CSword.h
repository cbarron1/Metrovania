#ifndef _CSWORD_H_
#define _CSWORD_H_

#include "CEntity.h"

class CSword : public CEntity {

	public:
		
		CSword();//constructer
		
		bool OnLoad(char* File, int Width, int Height, int MaxFrames);//load image

     	void OnLoop();//update data

		void OnRender(SDL_Surface* Surf_Display);//render image

		void OnCleanup();//clean up object

		void OnAnimate();//animate image

		bool OnCollision(CEntity* Entity);//when it collides with something

};

#endif
