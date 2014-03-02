//=============================================================================
#include "CSimon.h"
#include "CApp.h"
#include <iostream>
//=============================================================================
CSimon::CSimon() {
	Flags = ENTITY_FLAG_GRAVITY;
	Type = 	ENTITY_TYPE_PLAYER;
	Crouch = false;
	Taunt = false;
	Attack = false;
	MoveLeft  = false;
	MoveRight = false;
	PointUp = false;
	AttackTimer = 0;
	MaxSpeedY = 12;
	MaxSpeedX = 5;

	health = 0;
	healthTimer = 0;

}
//=============================================================================
bool CSimon::OnLoad(char* File, int Width, int Height, int MaxFrames) {
    if(CEntity::OnLoad(File, Width, Height, MaxFrames) == false) {//entity version
        return false;
    }
	if((Surf_Health = CSurface::OnLoad("./images/hearts.png")) == false ) return false;//load health bar image
	if((Surf_Whip = CSurface::OnLoad("./images/whipBrandish.png")) == false) return false;//load whip brandish image

    return true;
}

//-----------------------------------------------------------------------------
void CSimon::OnLoop() {
	CEntity::OnLoop();//entity version
	if(CurrentFrameCol == 0 || CurrentFrameCol == 3 || CurrentFrameCol == 5){//columns 0 3 and 5 of sprite sheet are him facking to the right
		faceRight = true;
		faceLeft = false;
	}
	else{//everything else is to the left
		faceRight = false;
		faceLeft = true;
	}

	if(AttackTimer <= 90 && Attack) AttackTimer++;//if hes attacking and his attacktimer is less then 90 increment attacktimer

	if(AttackTimer >= 90 && Attack){//if his attack timer is greater then 90 and hes attacking
		Attack = false;//make him stop attacking
		AttackTimer = 0;//reset attack timer
	}


	if(healthTimer < 100)healthTimer++;//increment health timer if its less then 100

	if(health >= 10) Dead = true;//if he has more then 10 health make him die

}

//-----------------------------------------------------------------------------
void CSimon::OnRender(SDL_Surface* Surf_Display) {
	CEntity::OnRender(Surf_Display);//entity version
	CSurface::OnDraw(Surf_Display, Surf_Health, 0, 0, 0, health*60, 160, 60);//health bar render
	if(AttackTimer < 30 && PointUp && faceRight && Attack) CSurface::OnDraw(Surf_Display, Surf_Whip, 260, 240, 0, 120, 60, 60);//whip brandish render if hes facing right and pointing up
	else if(AttackTimer < 30 && PointUp && faceLeft && Attack) CSurface::OnDraw(Surf_Display, Surf_Whip, 350, 240, 60, 120, 60, 60);//whip brandish render if hes pointing up and facing left
	if(AttackTimer < 30 && !PointUp && faceRight && Attack) CSurface::OnDraw(Surf_Display, Surf_Whip, 260, 240, 0, 0, 60, 60);//whip brandish render if hes not pointing up and hes facing right and its the first part of this animation
	else if(AttackTimer < 60 && !PointUp && faceRight && Attack) CSurface::OnDraw(Surf_Display, Surf_Whip, 265, 235, 0, 60, 60, 60);//whip brandish render if hes not pointing up and hes facing right and its the second part of this animation
	else if(AttackTimer < 30 && !PointUp && faceLeft && Attack) CSurface::OnDraw(Surf_Display, Surf_Whip, 350, 240, 60, 0, 60, 60);//whip brandish render if hes not pointing up and hes facing left and its the first part of this animation
	else if(AttackTimer < 60 && !PointUp && faceLeft && Attack) CSurface::OnDraw(Surf_Display, Surf_Whip, 345, 235, 60, 60, 60, 60);//whip brandish render if hes not pointing up and hes facing left and its the second part of this animation
}

//------------------------------------------------------------------------------
void CSimon::OnCleanup() {
	CEntity::OnCleanup();//entity version
	SDL_FreeSurface(Surf_Health);//free health bar image
	SDL_FreeSurface(Surf_Whip);//free whip brandish image
}

//------------------------------------------------------------------------------
void CSimon::OnAnimate() {
	//animation stuff (refrence sprite sheet)
	if(SpeedX != 0) {
		Anim_Control.MaxFrames = 13;
	}else{
		Anim_Control.MaxFrames = 0;
	}

	if(Attack) {
		Anim_Control.MaxFrames = 0;
		if(AttackTimer < 30) CurrentFrameRow = 0;
		else if (AttackTimer < 60) CurrentFrameRow = 1;
		else CurrentFrameRow = 2;		
		if(faceRight) {
			if(PointUp) CurrentFrameCol = 5;
			if(!PointUp) CurrentFrameCol = 3;
		}
		if(faceLeft) {
			if(PointUp) CurrentFrameCol = 6;
			if(!PointUp) CurrentFrameCol = 4;
		}
	}

	else if(Taunt){
		Anim_Control.MaxFrames = 9;
		CurrentFrameCol = 2;
		CurrentFrameRow = 0;
	}
	
	else if(!CanJump) {
		if(faceRight) CurrentFrameCol = 0;
		else CurrentFrameCol = 1;
		CurrentFrameRow = 13;
		Anim_Control.MaxFrames = 0;
	}
	
	else if(MoveLeft) {
		CurrentFrameRow = 0;
		CurrentFrameCol = 1;
	}
	
	else if(MoveRight) {
		CurrentFrameRow = 0;
		CurrentFrameCol = 0;
	}

	else {
		if (faceLeft && Crouch) {
			CurrentFrameCol = 1;
			CurrentFrameRow = 14;
		}
		else if (faceRight && Crouch) {
			CurrentFrameCol = 0;
			CurrentFrameRow = 14;
		}
		else if (faceRight) {
			CurrentFrameCol = 0;
			CurrentFrameRow = 12;
		}
		else {
			CurrentFrameCol = 1;
			CurrentFrameRow = 12;
		}	
		Anim_Control.MaxFrames = 0;
	}	

	CEntity::OnAnimate();//entity version
}

//------------------------------------------------------------------------------
bool CSimon::OnCollision(CEntity* Entity) {
	return true;//do nothing if he collides with anything
}

//=============================================================================
