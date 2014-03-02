#ifndef _CDOG_H_
#define _CDOG_H_

#include "CEntity.h"

//=======================================
class CDog : public CEntity {
	public:
		
		CDog();//constructer

		bool OnLoad(char* File, int Width, int Height, int MaxFrames);//on load of object init some things

        void OnLoop();//every loop update the data

        void OnRender(SDL_Surface* Surf_Display);//display things to screen

        void OnCleanup();//clean up the object 

        void OnAnimate();//animate the dog

        bool OnCollision(CEntity* Entity);//check to see if the dog has collided with something
        
        float playerPos;//player position
        float yPlayerPos;//player position
        
        bool moving;//is the dog moving?

	int dogGrowlSound;//declare dog growl
	int soundTimer;//make sure it dosent growl to often

};

#endif
