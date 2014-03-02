//=============================================================================
#include "CShot.h"
#include "CApp.h"
#include "CSamus.h"
#include "CEntity.h"
#include <vector>
//=============================================================================
CShot::CShot(){
	Flags = ENTITY_FLAG_NONE;
	Type = ENTITY_TYPE_BULLET;
	MaxSpeedX = 15;
	MaxSpeedY = 15;
}

//-----------------------------------------------------------------------------
bool CShot::OnLoad(char* File, int Width, int Height, int MaxFrames){
	if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false) {//entity version
   	     return false;
	}
	
	return true;
}
//-----------------------------------------------------------------------------
void CShot::OnLoop() {
	CEntity::OnLoop();//entity version
}


//-----------------------------------------------------------------------------
void CShot::OnRender(SDL_Surface* Surf_Display) {
	CEntity::OnRender(Surf_Display);//entity version
}

//------------------------------------------------------------------------------
void CShot::OnCleanup() {
	CEntity::OnCleanup();//entity version
}

//------------------------------------------------------------------------------
void CShot::OnAnimate() {
	CEntity::OnAnimate();//entity version
	Anim_Control.MaxFrames = 0;
	CurrentFrameRow = 0;
	CurrentFrameCol = 0;
}

//------------------------------------------------------------------------------
bool CShot::OnCollision(CEntity* Entity) {
	return true;//do nothing
}

//===============================================================
