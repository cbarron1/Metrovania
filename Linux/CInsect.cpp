//=============================================================================
#include "CInsect.h"
#include "CSamus.h"

//=============================================================================

CInsect::CInsect() {

	Type = 	ENTITY_TYPE_INSECT;//its of type insect

	Flags = ENTITY_FLAG_GRAVITY;//its effected by gravity

	MoveRight = false;
	faceRight = false;
	MoveLeft = true;
	faceLeft = true;
	jumpTimer = 0;
	collisionTimer = 0;
	SpeedX = 10;
	health = 0;
	MaxSpeedY = 15;
	Dead = false;
}

//=============================================================================

bool CInsect::OnLoad(char* File, int Width, int Height, int MaxFrames) {
	if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false){//call entity version of onload
	return false;
	}

	return true;
}

//=============================================================================
void CInsect::OnLoop(){
	CEntity::OnLoop();//entity version

	if(faceRight && SpeedY != 0) {//if its facing to the right and its moving in the y direction
		MoveRight = true;//make it move to the right
		MoveLeft = false;
	}
	else if (faceLeft && SpeedY != 0){//if its facing to the left and its moving in the y dirction
		MoveLeft = true;//make it move to the left
		MoveRight = false;
	}
	
	if (SpeedY == 0) {//if its not moving in the y direction
		MoveLeft = false;//make it stop moving in the x direction
		MoveRight = false;
	}	
	
	if(CanJump && jumpTimer >= 100) {//if it can jump and its jump timer is greater then 100 cycles
		jumpTimer = 0;//reset its jump timer
		Jump();//make it jump
	}	

	if(collisionTimer <= 100) collisionTimer++;//if its collision timer is less then 100 increment it
	
}

//=============================================================================
void CInsect::OnRender(SDL_Surface* Surf_Display) {
	CEntity::OnRender(Surf_Display);//entity version
}

//=============================================================================
void CInsect::OnCleanup() {
	CEntity::OnCleanup();//entity version
}

//=============================================================================
void CInsect::OnAnimate() {
	CurrentFrameCol = 0;//animation columns and rows set according to image
	if (CanJump && jumpTimer < 100) {
		CurrentFrameRow = 0;
		Anim_Control.MaxFrames = 3;
		jumpTimer++;
	} else {
		CurrentFrameRow = 2;
		Anim_Control.MaxFrames = 0;
	}
	CEntity::OnAnimate();
		
}
//=============================================================================
bool CInsect::OnCollision(CEntity* Entity) {

	if(Entity->Type == ENTITY_TYPE_PLAYER) SpeedY = MaxSpeedY;//if it collides with a player then set its speed in the y direction to its maximum

	if(Entity->Type == ENTITY_TYPE_PLAYER && Entity->healthTimer >= 100) {//if it collides with a player and the players health timer is greater then 100
		Entity->health++;//increment player health
		Entity->healthTimer = 0;//reset health timer
	}
	if(Entity->Type == ENTITY_TYPE_BULLET){//if it collides with a bullet
		health++;//increment insect health
	}
	if(Entity->Type == ENTITY_TYPE_BOMB){//if it collides with a bomb
		health+=20;//increment insect health by 20
	}
	if(Entity->Type == ENTITY_TYPE_WHIP) Dead = true;//if it collides with a whip then kill the insect
	if (health >= 50) Dead = true; //general death scenario

	return true;
}
