//=============================================================================
#include "CSamus.h"
#include "CApp.h"
#include <iostream>
//constructer
//=============================================================================
CSamus::CSamus() {
	Flags = ENTITY_FLAG_GRAVITY;
	Type = 	ENTITY_TYPE_PLAYER;
	Crouch = false;
	PointUpDiagonal = false;
	PointDownDiagonal = false;
	PointUp = false;
	morphBall = false;
	MoveLeft  = false;
	MoveRight = false;
	MaxSpeedY = 12;

	health = 0;
	healthTimer = 0;

}

//=============================================================================
bool CSamus::OnLoad(char* File, int Width, int Height, int MaxFrames) {
    if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false) {//entity version of onload
        return false;
    }
	if((Surf_Health = CSurface::OnLoad("./images/hearts.png")) == false ) return false;//load the hearts image

    return true;
}

//-----------------------------------------------------------------------------
void CSamus::OnLoop() {
	CEntity::OnLoop();//entity version
	if(CurrentFrameCol == 0 || CurrentFrameCol == 2 || CurrentFrameCol == 4 || CurrentFrameCol == 6 || CurrentFrameCol == 8 || CurrentFrameCol == 10){//check if her column is a column that is facing to the right
		faceRight = true;
		faceLeft = false;
	}
	else{//otherwise she is facing to the left
		faceRight = false;
		faceLeft = true;
	}

	if(healthTimer < 100)healthTimer++;//if her health timer is less then 100 increment

	if(health >= 10) Dead = true;//if she has more then 10 health turn her death flag on

	if(shotTimer < 50) shotTimer++;//if her shot timer is less then 50 increment

}

//-----------------------------------------------------------------------------
void CSamus::OnRender(SDL_Surface* Surf_Display) {
	CEntity::OnRender(Surf_Display);//entity version
	CSurface::OnDraw(Surf_Display, Surf_Health, 0, 0, 0, health*60, 160, 60);//draw her health bar on to the screen
}

//------------------------------------------------------------------------------
void CSamus::OnCleanup() {
	CEntity::OnCleanup();//entity version
	SDL_FreeSurface(Surf_Health);//free the health surface
}

//------------------------------------------------------------------------------
void CSamus::OnAnimate() {
	if(SpeedX != 0) {//if she is moving her frames is 11
		Anim_Control.MaxFrames = 11;
	}else{
		Anim_Control.MaxFrames = 0;//otherwise she has one frame
	}
	
	//the below is all sprite sheet related animation stuff. It simply chooses the right frame row and column for each state
	if(MoveLeft) {
		CurrentFrameRow = 0;
		if (!CanJump && !morphBall) {
			if(shotTimer < 50){
				CurrentFrameRow = 10;
				CurrentFrameCol = 1;
				Anim_Control.MaxFrames = 0;
			}
			else {
				CurrentFrameCol = 9;
				Anim_Control.MaxFrames = 9;
			}
		} else if (morphBall) {
			CurrentFrameCol = 3;
			Anim_Control.MaxFrames = 9;
		} else if (PointUpDiagonal) {
			CurrentFrameCol = 5;
		} else if (PointDownDiagonal) {
			CurrentFrameCol = 7;
		} else {
			if(shotTimer < 50) CurrentFrameCol = 11;
			else CurrentFrameCol = 1;
		}
	}
	
	else if(MoveRight) {
		CurrentFrameRow = 0;
		if (!CanJump && !morphBall) {
			if(shotTimer < 50){
				CurrentFrameRow = 10;
				CurrentFrameCol = 0;
				Anim_Control.MaxFrames = 0;
			}
			else{
				CurrentFrameCol = 8;
				Anim_Control.MaxFrames = 9;
			}
		} else if (morphBall) {
			CurrentFrameCol = 2;
			Anim_Control.MaxFrames = 9;
		}
		else if (PointUpDiagonal) {
			CurrentFrameCol = 4;
		}
		else if (PointDownDiagonal) {
			CurrentFrameCol = 6;
		}
		else {
			if(shotTimer < 50) CurrentFrameCol = 10;
			else CurrentFrameCol = 0;
		}
	}

	else if(PointUpDiagonal && !morphBall){
		if (faceRight) CurrentFrameCol = 4;
		if (faceLeft) CurrentFrameCol = 5;
		if (!Crouch) CurrentFrameRow = 10;
		else CurrentFrameRow = 11;
		Anim_Control.MaxFrames = 0;
	}

	else if(PointDownDiagonal && !morphBall){
		if (faceRight) CurrentFrameCol = 6;
		if (faceLeft) CurrentFrameCol = 7;
		if (!Crouch) CurrentFrameRow = 10;
		else CurrentFrameRow = 11;
		Anim_Control.MaxFrames = 0;
	}

	else if(Crouch) {
		if (faceRight) CurrentFrameCol = 0;
		if (faceLeft) CurrentFrameCol = 1;
		CurrentFrameRow = 11;
		Anim_Control.MaxFrames = 0;
	}


	else if (morphBall) {
		if (faceRight) CurrentFrameCol = 2;
		if (faceLeft) CurrentFrameCol = 3;
		CurrentFrameRow = 0;
		Anim_Control.MaxFrames = 9;	
	}	

	else {
		if (faceRight) {
			CurrentFrameCol = 0;
			if(PointUp) CurrentFrameRow = 12;
			else CurrentFrameRow = 10;
		}
		else {
			CurrentFrameCol = 1;
			if(PointUp) CurrentFrameRow = 12;
			else CurrentFrameRow = 10;
		}	
		Anim_Control.MaxFrames = 0;
	}	

	CEntity::OnAnimate();//entity version
}

//------------------------------------------------------------------------------
bool CSamus::OnCollision(CEntity* Entity) {//if she collides with something do nothing
	return true;
}


