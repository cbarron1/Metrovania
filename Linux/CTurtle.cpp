//=============================================================================
#include "CTurtle.h"
#include "CSamus.h"

//=============================================================================

CTurtle::CTurtle() {

	Type = 	ENTITY_TYPE_GENERIC;

	Flags = ENTITY_FLAG_NONE;

	MoveRight = false;
	faceRight = false;
	MoveLeft = true;
	faceLeft = true;
	collisionTimer = 0;

	SpeedX = 10;
}

//=============================================================================

bool CTurtle::OnLoad(char* File, int Width, int Height, int MaxFrames) {
	if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false){//entity version
	return false;
	}

	return true;
}

//=============================================================================
void CTurtle::OnLoop(){
	CEntity::OnLoop();//entity version
	if(faceRight) {//find the direction its facing and make it move that way
		MoveRight = true;
		MoveLeft = false;
	}
	else{
		MoveLeft = true;
		MoveRight = false;
	}


	if(collisionTimer <= 100) collisionTimer++;//increment its collision timer
}

//=============================================================================
void CTurtle::OnRender(SDL_Surface* Surf_Display) {
	CEntity::OnRender(Surf_Display);//entity version
}

//=============================================================================
void CTurtle::OnCleanup() {
	CEntity::OnCleanup();//entity version
}

//=============================================================================
void CTurtle::OnAnimate() {
	//reference sprite sheet
	Anim_Control.MaxFrames = 6;
	CurrentFrameRow = 0;
	if(MoveLeft) {
		CurrentFrameCol = 1;
	} else {
		CurrentFrameCol = 0;
	}
	CEntity::OnAnimate();//entity version
}
//=============================================================================
bool CTurtle::OnCollision(CEntity* Entity) {

	if(Entity->Type == ENTITY_TYPE_PLAYER && Entity->healthTimer >= 100){//if the turtle collides with a player whos health tiemr is greater then 100
		Entity->health++;//increment player health
		Entity->healthTimer = 0;//reset player healh timer
	}

	return true;
}
