//=============================================================================
#include "CSkeleton.h"
#include <iostream>
//=============================================================================

CSkeleton::CSkeleton() {

	Type = 	ENTITY_TYPE_SKELETON;
	Flags = ENTITY_FLAG_GRAVITY;

	MoveRight = true;
	faceRight = true;
	MoveLeft = false;
	faceLeft = false;
	swordOut = false;

	collisionTimer = 0;
	AttackTimer = 0;
	MaxSpeedX = 4;
	SpeedX = 4;
	health = 0;
	Dead = false;
	moving = true;
	
	upSword.Dead = true;
	outSword.Dead = true;
	
	upSword.Type = ENTITY_TYPE_SWORD1;
	outSword.Type = ENTITY_TYPE_SWORD2;
}

//=============================================================================

bool CSkeleton::OnLoad(char* File, int Width, int Height, int MaxFrames) {
	if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false){//entity version
	return false;
	}
	
	upSword.OnLoad("./images/sword1.png", 17, 16, 2);//call upsword on load function
	outSword.OnLoad("./images/sword2.png", 25, 8, 2);//call outsword on load function

	return true;
}

//=============================================================================
void CSkeleton::OnLoop(){
	CEntity::OnLoop();//entity version


	if (X-playerPos > 30) {//if player is near and to the left make him face left
		faceLeft = true;
		faceRight = false;
	} else if (X-playerPos < -30) {//if player is near and to the right make him face right
		faceRight = true;
		faceLeft = false;
	}

	if (Y-yPlayerPos > 80 || Y-yPlayerPos < -80) {//if player is far in the y direction make it not do anything
		moving = false;
		MoveRight = false;
		MoveLeft = false;
	} else if (X-playerPos > 320 || X-playerPos < -320) {//if player is far in the x direction make it not do anything
		moving = false;
		MoveRight = false;
		MoveLeft = false;
	}	
	else {//if player is not far
		moving = true;//make him move
		if (X-playerPos <=50 && X-playerPos >= -50) {//if hes withen range pull out your sword
			swordOut = true;
		} else {//otherwise dont
			swordOut = false;		
		}	
	}
	
	if (swordOut && AttackTimer <= 90) {//if his sword is out and attack timer is less then 90 increment attack timer
		AttackTimer++;
	}
	else if (swordOut && AttackTimer > 90) {//if his sword is out and his attack timer is more then 90
		AttackTimer = 0;//reset attack timer
		swordOut = false;//but his sword away
	}		
	
	if (!moving) {
		MoveRight = false;//if hes not moving then dont move
		MoveLeft = false;
	}
	else if (swordOut) {//if his sword is out and hes moving
		if (faceRight) {//and hes facing to the right
			MoveRight = false;//make him stop moving to the right
		}	
		else if (faceLeft) {//if hes facing to the left
			MoveLeft = false;//make him stop moving to the left
		}	
	}
	else if(faceRight) {//if his sword is not out and hes moving and hes facing to the right make him move in that direction
		MoveRight = true;
		MoveLeft = false;
	}
	else if (faceLeft){//if his sword is not out and hes moving and hes facing to the left make him move in that direction
		MoveLeft = true;
		MoveRight = false;
	}


	if(collisionTimer <= 200) collisionTimer++;//increment collision timer if its less then 200
	
	if (swordOut && AttackTimer > 30 && AttackTimer <=60) {//if his sword is out and his attack timer is between 30 and 60
		upSword.Dead = false;//"kill" his upsword
		outSword.Dead = true;//his outsword is now "alive"
		if (faceRight) {//depending on what direction hes facing choose the right coordinats and the right sprite sheet column
			upSword.X = X + 7;
			upSword.Y = Y - 16;
			upSword.CurrentFrameCol = 1;
		}	
		else if (faceLeft) {
			upSword.X = X + 7;
			upSword.Y = Y - 16;
			upSword.CurrentFrameCol = 0;
		}	
	} 
	else if (swordOut && AttackTimer > 60 && AttackTimer <= 90) {//if his sword is out and his attack timer is between 60 and 90
		upSword.Dead = true;//make his upsword "alive"
		outSword.Dead = false;//"kill" his outsword
		if (faceRight) {//animation and X and Y choosing
			outSword.X = X + 30;
			outSword.Y = Y + 15;
			outSword.CurrentFrameCol = 0;
		}
		else if (faceLeft) {
			outSword.X = X - 20;
			outSword.Y = Y + 15;
			outSword.CurrentFrameCol = 1;
		}		
	}

	if(!swordOut || AttackTimer < 30){//if his sword is not out OR his attack timer is less then 30
		upSword.Dead = true;//make both his swords "dead"
		outSword.Dead = true;
	}

	
	outSword.OnLoop();//outsword data
	upSword.OnLoop();//upsword data
	outSword.PosValid(outSword.X,outSword.Y);//check to see if outsword is colliding
	upSword.PosValid(upSword.X,upSword.Y);//check to see if upsword is colliding
}

//=============================================================================
void CSkeleton::OnRender(SDL_Surface* Surf_Display) {
	CEntity::OnRender(Surf_Display);//entity version
	if (!upSword.Dead) upSword.OnRender(Surf_Display);//if upsword is "alive" render it
	if (!outSword.Dead) outSword.OnRender(Surf_Display);//if outsword is "alive" render it
}

//=============================================================================
void CSkeleton::OnCleanup() {
	CEntity::OnCleanup();//entity version
	upSword.OnCleanup();//clean up upsword
	outSword.OnCleanup();//clena up outsword
}

//=============================================================================
void CSkeleton::OnAnimate() {
	//animation stuff (check sprite sheet for reference)
	CurrentFrameRow = 0;
	if (!moving) {
		Anim_Control.MaxFrames = 0;
		CurrentFrameRow = 1;	
	} else {
		CurrentFrameRow = 0;
		if (swordOut) {
			Anim_Control.MaxFrames = 0;
			if(AttackTimer < 30) CurrentFrameRow = 0;
			else if (AttackTimer < 60) CurrentFrameRow = 1;
			else CurrentFrameRow = 2;	
			if (faceRight) {
				CurrentFrameCol = 2;
			} else if (faceLeft) {
				CurrentFrameCol = 3;
			}		
		} else {
			CurrentFrameRow = 0;
			Anim_Control.MaxFrames = 3;
			if (faceRight) {
				CurrentFrameCol = 0;
			} else {
				CurrentFrameCol = 1;
			}
		}
	}	
	CEntity::OnAnimate();//entity version
	
	upSword.OnAnimate();//animate upsword
	outSword.OnAnimate();//animate outsword
		
}
//=============================================================================
bool CSkeleton::OnCollision(CEntity* Entity) {

	if(Entity->Type == ENTITY_TYPE_PLAYER && Entity->healthTimer >= 100){//if the skeleton collides with a player and the palyers health timer is above 100
		Entity->health++;//increment players health
		Entity->healthTimer = 0;//reset players health timer
	}
	if(Entity->Type == ENTITY_TYPE_BULLET){//if skeleton collides witha  bullet
		health++;//increment his health
	}
	if(Entity->Type == ENTITY_TYPE_BOMB){//if skeleton collides with a bomb
		health+=20;//incrment his health by 20
	}
	if(Entity->Type == ENTITY_TYPE_WHIP) Dead = true;//if skeleton collides with a whip kill him
	if (health >= 50) Dead = true;//if his health is greater then 50 kill him
	
	return true;
}
