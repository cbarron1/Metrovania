#include <iostream>
#include "CSword.h"
//-----------------------------------------------------------------------------
CSword::CSword() {
	Flags = ENTITY_FLAG_NONE;
	MaxSpeedX = 0;
	MaxSpeedY = 0;
}	
//-----------------------------------------------------------------------------

bool CSword::OnLoad(char* File, int Width, int Height, int MaxFrames){
	if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false) {//entity version
   	     return false;
	}
	
	return true;
}
//-----------------------------------------------------------------------------
void CSword::OnLoop() {
	CEntity::OnLoop();//entity version
}


//-----------------------------------------------------------------------------
void CSword::OnRender(SDL_Surface* Surf_Display) {
	CEntity::OnRender(Surf_Display);//entity version
}

//------------------------------------------------------------------------------
void CSword::OnCleanup() {
	CEntity::OnCleanup();//entity version
}

//------------------------------------------------------------------------------
void CSword::OnAnimate() {
	Anim_Control.MaxFrames = 0;//no animation
	CurrentFrameRow = 0;//only the column matters
	CEntity::OnAnimate();//entity versions
}

//------------------------------------------------------------------------------
bool CSword::OnCollision(CEntity* Entity) {
	if (Entity->Type == ENTITY_TYPE_PLAYER && Entity->healthTimer >=100) {//if the sword collides with a player and the players health timer is greater then 100 then increment the players health and reset the players health timer
		Entity->health++;
		Entity->healthTimer = 0;
	}	
	
	return true;
}
