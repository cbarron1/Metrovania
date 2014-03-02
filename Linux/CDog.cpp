#include "CDog.h"
#include "CSamus.h"
#include "CSimon.h"
#include "CApp.h"
#include "CSoundBank.h"
#include <iostream>
//constructer
CDog::CDog() {

	Type = ENTITY_TYPE_DOG;

	Flags = ENTITY_FLAG_GRAVITY;

	MoveRight = false;
	faceRight = false;
	MoveLeft = true;
	faceLeft = true;
	collisionTimer = 0;
	
	MaxSpeedX = 12;
	MaxSpeedY = 6;
	SpeedX = 12;
	health = 0;
	Dead = false;
	moving = true;


}

//when the dog is loaded do the following
//==================================================================
bool CDog::OnLoad(char* File, int Width, int Height, int MaxFrames) {
	if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false) {//call the entity version of onload
		return false;
	}
	if((dogGrowlSound = CSoundBank::SoundControl.OnLoad("./sounds/dogGrowl.wav")) == -1) {//load the dog growl sound
		return false;
	}
	return true;
}

//===================================================================
void CDog::OnLoop() {
	CEntity::OnLoop();//run the entity version of onloop

	if (X-playerPos > 50) {//if the player is far and to the left face that direction
		faceLeft = true;
		faceRight = false;
	} else if (X-playerPos < -50) {//if the player is far and to the right face that direction
		faceRight = true;
		faceLeft = false;
	}
	if (Y-yPlayerPos > 100 || Y-yPlayerPos < -100) {//if the player is very far dont move
		moving = false;
		MoveRight = false;
		MoveLeft = false;
	} else if (X-playerPos > 320 || X-playerPos < -320) {//same as above
		moving = false;
		MoveRight = false;
		MoveLeft = false;
	}
	else {//if the player is near start moving depending on what direction your facing
		moving = true;
		if(faceRight) {
			MoveRight = true;
			MoveLeft = false;
		} else {
			MoveLeft = true;
			MoveRight = false;
		}
	}

	if(X-playerPos <=50 && X-playerPos >= -50 && CanJump && moving) {//if your really really close and your moving and you can jump, do a small leap and growl
		Jump();
		if(soundTimer > 500){
			CSoundBank::SoundControl.Play(-1, dogGrowlSound, 0);
			soundTimer = 0;
		}
	}	

	if(soundTimer <= 500) soundTimer++;//increment the sound timer

	if(collisionTimer <= 100) collisionTimer++;//increment the collision timer
}

//===================================================================
void CDog::OnRender(SDL_Surface* Surf_Display) {
	CEntity::OnRender(Surf_Display);//call the entity version of onrender
}

//===================================================================
void CDog::OnCleanup() {
	CEntity::OnCleanup();//call the entity version of oncleanup
}

//===================================================================
void CDog::OnAnimate() {
	if(MoveLeft) {//if hes moving to the left then grab the right col
		CurrentFrameCol = 1;
	} else {//otherwise grab the other one
		CurrentFrameCol = 0;
	}
	
	if (!moving) {//if hes not moving then dont animate him
		Anim_Control.MaxFrames = 0;
		CurrentFrameRow = 0;
	} else {//otherwise animate him
		Anim_Control.MaxFrames = 5;
		CurrentFrameRow = 0;
	}		
	CEntity::OnAnimate();//call the entity version of onanimate
}

//===================================================================
bool CDog::OnCollision(CEntity* Entity) {
	if (Entity->Type == ENTITY_TYPE_PLAYER && Entity->healthTimer >=100) {//if a dog collides with a player and his health timer is large enough
		Entity->health++;//increment health
		Entity->healthTimer = 0;//reset health timer
	}
	if(Entity->Type == ENTITY_TYPE_BULLET){//if a dog collides with a bullet
		health++;//increment the dogs health
	}
	if(Entity->Type == ENTITY_TYPE_BOMB){//if a dog collides with a bomb
		health+=20;//increment his health by alot
	}
	if(Entity->Type == ENTITY_TYPE_WHIP) Dead = true;//if a dog collides with a whip then kill it
	if (health >= 50) Dead = true;//if the dog has more then 50 health kill it

	return true;
}

