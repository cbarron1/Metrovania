//=============================================================================
#include "CWhip.h"
#include "CApp.h"
#include "CSimon.h"
#include "CEntity.h"
#include <vector>
#include <iostream>
//=============================================================================
CWhip::CWhip(){
	Flags = ENTITY_FLAG_NONE;
	Type = ENTITY_TYPE_WHIP;
	MaxSpeedX = 0;
	MaxSpeedY = 0;
}

//-----------------------------------------------------------------------------
bool CWhip::OnLoad(char* File, int Width, int Height, int MaxFrames){
	if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false) {//entity version
   	     return false;
	}
	
	return true;
}
//-----------------------------------------------------------------------------
void CWhip::OnLoop() {
	CEntity::OnLoop();//entity version
}


//-----------------------------------------------------------------------------
void CWhip::OnRender(SDL_Surface* Surf_Display) {
	CEntity::OnRender(Surf_Display);//entity version
}

//------------------------------------------------------------------------------
void CWhip::OnCleanup() {
	CEntity::OnCleanup();//entity version
}

//------------------------------------------------------------------------------
void CWhip::OnAnimate() {
	//reference spritesheet
	Anim_Control.MaxFrames = 0;
	CurrentFrameRow = 0;
	CEntity::OnAnimate();//entity version
	OnCleanup();//clean it up after every animation attempt
}

//------------------------------------------------------------------------------
bool CWhip::OnCollision(CEntity* Entity) {
	return true;//do nothing if it collides with something
}

//===============================================================
