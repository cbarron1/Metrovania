//==============================================================================
#include <iostream>
#include "CEntity.h"
//==============================================================================
std::vector<CEntity*> 	CEntity::EntityList;//entity vector that will hold all of the active entitys

//constructer
//==============================================================================
CEntity::CEntity() {

	CanJump = false;

	Surf_Entity = NULL;

	X = 0;
	Y = 0;

	Width 	= 0;
	Height 	= 0;

	Dead = false;

	SpeedX = 0;
	SpeedY = 0;

	AccelX = 0;
	AccelY = 0;

	MaxSpeedX = 10;
	MaxSpeedY = 10;

	CurrentFrameCol = 0;
	CurrentFrameRow = 0;

	Col_X = 0;
	Col_Y = 0;

	Col_Width  = 0;
	Col_Height = 0;
}

//deconstructer
//------------------------------------------------------------------------------
CEntity::~CEntity() {
}

//==============================================================================
bool CEntity::OnLoad(char* File, int Width, int Height, int MaxFrames) {
	if((Surf_Entity = CSurface::OnLoad(File)) == NULL) {//load the surface of the entity
		return false;
	}

	CSurface::Transparent(Surf_Entity, 255, 0, 255);//make it transparent

	this->Width = Width;//its width is equal to the width passed in
	this->Height = Height;//its height is equal to the height passed in

	Anim_Control.MaxFrames = MaxFrames;//its maxframes is equal to the maxframes passed in

    return true;
}

//------------------------------------------------------------------------------
void CEntity::OnLoop() {
	//We're not Moving
	if(MoveLeft == false && MoveRight == false ) {
		StopMove();
	}

	if(MoveLeft) {//moving left
		AccelX = -0.5;
	}else

	if(MoveRight) {//moving right
		AccelX = 0.5;
	}

	if(Flags & ENTITY_FLAG_GRAVITY) {//moving down due to gravity
		AccelY = 0.75f;
	}

	SpeedX += AccelX * CFPS::FPSControl.GetSpeedFactor();//match the speed to the acceleration times the frames per second
	SpeedY += AccelY * CFPS::FPSControl.GetSpeedFactor();

	if(SpeedX > MaxSpeedX)  SpeedX =  MaxSpeedX;//make sure the speeds never exceed their max
	if(SpeedX < -MaxSpeedX) SpeedX = -MaxSpeedX;
	if(SpeedY > MaxSpeedY)  SpeedY =  MaxSpeedY;
	if(SpeedY < -MaxSpeedY) SpeedY = -MaxSpeedY;

	OnAnimate();//animate the movement
	OnMove(SpeedX, SpeedY);//move with the speed
}

//draw the entity
//------------------------------------------------------------------------------
void CEntity::OnRender(SDL_Surface* Surf_Display) {
    if(Surf_Entity == NULL || Surf_Display == NULL) return;

    CSurface::OnDraw(Surf_Display, Surf_Entity, X - CCamera::CameraControl.GetX(), Y - CCamera::CameraControl.GetY(), CurrentFrameCol * Width,(CurrentFrameRow + Anim_Control.GetCurrentFrame()) * Height, Width, Height);
}

//clean up the enemy. If its a bullet then turn its death flag on
//------------------------------------------------------------------------------
void CEntity::OnCleanup() {

	if(Surf_Entity) SDL_FreeSurface(Surf_Entity);
	Surf_Entity = NULL;
	if(Type == ENTITY_TYPE_BULLET) Dead = true;
}

//animate the entity
//------------------------------------------------------------------------------
void CEntity::OnAnimate() {
	
	Anim_Control.OnAnimate();
}

//when an entity collides with another
//------------------------------------------------------------------------------
bool CEntity::OnCollision(CEntity* Entity) {
	return true;
}

//move the entity
//==============================================================================
void CEntity::OnMove(float MoveX, float MoveY) {

	CanJump = false;//it cannot jump while moving

	if(MoveX == 0 && MoveY == 0) return;//if its not moving the return

	double NewX = 0;//declare variables
	double NewY = 0;

	MoveX *= CFPS::FPSControl.GetSpeedFactor();//get its movement speed and multiply by the frames per second
	MoveY *= CFPS::FPSControl.GetSpeedFactor();

	if(MoveX != 0) {//if the entity is moving in the x direction
		if(MoveX >= 0) 	NewX =  CFPS::FPSControl.GetSpeedFactor();//and if the movement is to the right
		else 			NewX = -CFPS::FPSControl.GetSpeedFactor();//else its moving to the left
	}

	if(MoveY != 0) {//if the entity is moving in the y direction
		if(MoveY >= 0) 	NewY =  CFPS::FPSControl.GetSpeedFactor();
		else 			NewY = -CFPS::FPSControl.GetSpeedFactor();
	}

	while(true) {
		if(Flags & ENTITY_FLAG_GHOST) {//if the entity is a ghost
			PosValid((int)(X + NewX), (int)(Y + NewY)); //We don't care about collisions, but we need to send events to other entities

			X += NewX;//move its X 
			Y += NewY;//move its Y


		}else if (Type == ENTITY_TYPE_INSECT){//if the entity is a insect
			if(PosValid((int)(X + NewX), (int)(Y))) {//check to see if its new X position is valid
				X += NewX;//if it is then move it's X
			}else{//if not
				if (faceLeft && collisionTimer > 100) {//if its facing to the left and it hasent collided with anthing in 100 cycles then
					faceLeft = false;//make it face to the right
					faceRight = true;
					collisionTimer = 0;//reset its collision timer
				} else if (faceRight && collisionTimer > 100) {//if its facing to the right and it hasent collided in 100 cycles
					faceRight = false;//make it face to the left and reset its collision timer
					faceLeft = true;
					collisionTimer = 0;
				}		
				SpeedX = 0;//its speed in the X direction is now 0
			}

			if(PosValid((int)(X), (int)(Y + NewY))) {//check to see if its new Y position is valid
				Y += NewY;//if it is then move it's Y
			}else{//if not
    				if(MoveY > 0) {//and its currently moving downwards
    				    CanJump = true;//make it able to jump
 			        }
				SpeedY = 0;//but make its speed 0
			}
		} else if (Type == ENTITY_TYPE_PLAYER) {//if the entity is a player
			if(PosValid((int)(X + NewX), (int)(Y))) {//check to see if its new X position is valid
				X += NewX;// if it is then move its X
			}else{
				SpeedX = 0;//if not make its speed in the x direction 0
			}

			if(PosValid((int)(X), (int)(Y + NewY))) {//check to see if its new Y position is valid
				Y += NewY;//if it is then move its Y
			}else{//otherwise
    				if(MoveY > 0) {//if it is moving downwards
    				    CanJump = true;//make it able to jump again
 			        }
				
				SpeedY = 0;//but make its speed 0
			}		
		}else if (Type == ENTITY_TYPE_BULLET){//if the entity is a bullet
			if(PosValid((int)(X + NewX), (int)(Y))) {//check to see if its new X position is valid
				X += NewX;//if it is then move its X
			}else{
				OnCleanup();//other wise run cleanup
			}

			if(PosValid((int)(X), (int)(Y + NewY))) {//same as above but for the Y
				Y += NewY;
			}else{
				OnCleanup();
			}
		}else if (Type == ENTITY_TYPE_SKELETON){//if the entity is a skeleton
			if(PosValid((int)(X + NewX), (int)(Y))) {//check to see if its new X position is valid
				X += NewX;//if it is then move its X
			}else{//otherwise
				if(faceRight && collisionTimer > 200){//if its facing to the right and its collision timer is larger then 200 cycles
					faceLeft = true;//make it face and the oppisote direction
					faceRight = false;
					MoveLeft = true;
					MoveRight = false;
					collisionTimer = 0;
					SpeedX = -MaxSpeedX;
				}
				else if(faceLeft && collisionTimer > 200){//same as above but vice-versa
					faceLeft = false;
					faceRight = true;
					MoveLeft = false;
					MoveRight = true;
					collisionTimer = 0;
					SpeedX = MaxSpeedX;
				}
			}

			if(PosValid((int)(X), (int)(Y + NewY))) {//check to see if its new Y position is valid
				Y += NewY;//if it is then move its Y
			}else{//otherwise
    				if(MoveY > 0) {//if its moving downwards
    				    CanJump = true;//allow it to jump again
 			        }
				
				SpeedY = 0;//but make its speed in the Y direction 0
			}		
		} else if (Type == ENTITY_TYPE_DOG) {//if the entity is of type dog
			if(PosValid((int)(X + NewX), (int)(Y))) {//check to see if its new X position is valid
				X += NewX;//if it is then move its X
			}else{//otherwise
				if(faceRight && collisionTimer > 200){//do teh samething you did for the skeleton
					faceLeft = true;
					faceRight = false;
					MoveLeft = true;
					MoveRight = false;
					collisionTimer = 0;
					SpeedX = -MaxSpeedX;
				}
				else if(faceLeft && collisionTimer > 200){
					faceLeft = false;
					faceRight = true;
					MoveLeft = false;
					MoveRight = true;
					collisionTimer = 0;
					SpeedX = MaxSpeedX;
				}
			}

			if(PosValid((int)(X), (int)(Y + NewY))) {//all the same logic as skeleton
				Y += NewY;
			}else{
    				if(MoveY > 0) {
    				    CanJump = true;
 			        }
				
				SpeedY = 0;
			}	
		} else {//if its any other type of entity
			if(PosValid((int)(X + NewX), (int)(Y))) {//check its new x
				X += NewX;//set it if its valid
			}else{
				if(faceRight && collisionTimer > 100){//same logic as dog/skeleton but with less cycles
					faceLeft = true;
					faceRight = false;
					MoveLeft = true;
					MoveRight = false;
					collisionTimer = 0;
					SpeedX = -MaxSpeedX;
				}
				else if(faceLeft && collisionTimer > 100){
					faceLeft = false;
					faceRight = true;
					MoveLeft = false;
					MoveRight = true;
					collisionTimer = 0;
					SpeedX = MaxSpeedX;
				}
			}

			if(PosValid((int)(X), (int)(Y + NewY))) {//same as alwats
				Y += NewY;
			}else{//if its new Y is not valid then make it stop moving in the y direction
    				if(MoveY > 0) {
    				    CanJump = true;
 			        }
				
				SpeedY = 0;
			}		
		}	
		

		MoveX += -NewX;//subtract its desired position from its current position
		MoveY += -NewY;

		if(NewX > 0 && MoveX <= 0) NewX = 0;//set the new x and y 0 after everything is carried out
		if(NewX < 0 && MoveX >= 0) NewX = 0;

		if(NewY > 0 && MoveY <= 0) NewY = 0;
		if(NewY < 0 && MoveY >= 0) NewY = 0;

		if(MoveX == 0) NewX = 0;
		if(MoveY == 0) NewY = 0;

		if(MoveX == 0 && MoveY 	== 0) 	break;
		if(NewX  == 0 && NewY 	== 0) 	break;
	}
}

//make the entity stop moving slowly
//------------------------------------------------------------------------------
void CEntity::StopMove() {
	if(SpeedX > 0) {//if its speed in the x is greater then 0 them make its acceleration -1
		AccelX = -1;
	}

	if(SpeedX < 0) {//if its speed in the x is less then 0 then make its acceleration positive 1
		AccelX =  1;
	}

	if(SpeedX < 2.0f && SpeedX > -2.0f) {//if the speed in the X direction is close to 0 then set it to 0
		AccelX = 0;
		SpeedX = 0;
	}
}

//check to see if it has collided
//==============================================================================
bool CEntity::Collides(int oX, int oY, int oW, int oH) {
    int left1, left2;
    int right1, right2;
    int top1, top2;
    int bottom1, bottom2;

	int tX = (int)X + Col_X;//get its target X and target Y
	int tY = (int)Y + Col_Y;

    left1 = tX;//set the left edge of the target
    left2 = oX;//set the left edge of the origin

    right1 = left1 + Width - 1 - Col_Width;//set the right edge of the target
    right2 = oX + oW - 1;//set the right edge of the origin

    top1 = tY;//set the top edge of the target
    top2 = oY;//top edge of origin

    bottom1 = top1 + Height - 1 - Col_Height;//bot edge of target
    bottom2 = oY + oH - 1;//bot edge of origin


    if (bottom1 < top2) return false;//if the target bottem edge is touching the top origin then they are colliding so return false
    if (top1 > bottom2) return false;//if the target top edge is touching the bottem origin return false

    if (right1 < left2) return false;//etc
    if (left1 > right2) return false;

    return true;
}

//check to see if its new position is valid
//==============================================================================
bool CEntity::PosValid(int NewX, int NewY) {
	bool Return = true;

	int StartX 	= (NewX + Col_X) / TILE_SIZE;//get its initial X and Y
	int StartY 	= (NewY + Col_Y) / TILE_SIZE;

	int EndX	= ((NewX + Col_X) + Width - Col_Width - 1) 		/ TILE_SIZE;//get its ending X and Y
	int EndY	= ((NewY + Col_Y) + Height - Col_Height - 1)	/ TILE_SIZE;

	for(int iY = StartY;iY <= EndY;iY++) {//for every pixel between the start and end positions check to see if there is a tile that will get in the way
		for(int iX = StartX;iX <= EndX;iX++) {
			CTile* Tile = CArea::AreaControl.GetTile(iX * TILE_SIZE, iY * TILE_SIZE);

			if(PosValidTile(Tile) == false) {
				Return = false;
			}
		}
	}

	if(Flags & ENTITY_FLAG_MAPONLY) {//if it can only collide with the map dont do anthing
	}else{//otherwise check to see if there is an entity in the way between the start and end positions
		for(int i = 0;i < EntityList.size();i++) {
			if(PosValidEntity(EntityList[i], NewX, NewY) == false) {
				Return = false;
			}
		}
	}

	return Return;
}

//check to see if the tile passed in is valid
//------------------------------------------------------------------------------
bool CEntity::PosValidTile(CTile* Tile) {
	if(Tile == NULL) {//if there is no tile then no collision
		return true;
	}

	if(Tile->TypeID == TILE_TYPE_BLOCK) {//if the tile is a block then collision
		return false;
	}
	
	if (Tile->TypeID == TILE_TYPE_DAMAGE) {//if the tile is a damaging block
		if (healthTimer >= 100)	{//and the player hasent been hurt withen 100 cycles
			health++;//increment its health
			healthTimer=0;//reset its health timer
		}
		return false;	
	}	

	return true;
}

//check to see if their is an entity in the way
//------------------------------------------------------------------------------
bool CEntity::PosValidEntity(CEntity* Entity, int NewX, int NewY) {
	if(this != Entity && Entity != NULL && Entity->Dead == false &&//if the entity being collided with is not itself, exists, is not dead, does not collide with only the map, and is in fact colliding with you
		Entity->Flags ^ ENTITY_FLAG_MAPONLY &&
		Entity->Collides(NewX + Col_X, NewY + Col_Y, Width - Col_Width - 1, Height - Col_Height - 1) == true) {

		if(this->Type == ENTITY_TYPE_PLAYER && Entity->Type == ENTITY_TYPE_BULLET) return true;//samus wont collide with bullets
		if(Entity->Type == ENTITY_TYPE_PLAYER && this->Type == ENTITY_TYPE_BULLET) return true;//bullets wont collide with samus
		if(this->Type == ENTITY_TYPE_BULLET && Entity->Type == ENTITY_TYPE_BULLET) return true;//bullets wont collide with bullets

		if(Entity->Type == ENTITY_TYPE_EFFECT) return true;//effects wont collide with anything whether they are the source or target
		if(this->Type == ENTITY_TYPE_EFFECT) return true;

		if(Entity->Type == ENTITY_TYPE_WHIP && this->Type == ENTITY_TYPE_PLAYER) return true;//simon wont collide with the whip
		if(Entity->Type == ENTITY_TYPE_PLAYER && this->Type == ENTITY_TYPE_WHIP) return true;//the whip wont collide with simon
		
		if((Entity->Type == ENTITY_TYPE_SWORD1 || Entity->Type == ENTITY_TYPE_SWORD2) && this->Type == ENTITY_TYPE_SKELETON) return true;//the skeleton wont collide with either version of his sword
		if(Entity->Type == ENTITY_TYPE_SKELETON && (this->Type == ENTITY_TYPE_SWORD1 || this->Type == ENTITY_TYPE_SWORD2)) return true;//either version of the skeleton's sword wont collide with the skeleton
		if(Entity->Type == ENTITY_TYPE_SKELETON && this->Type == ENTITY_TYPE_DOG) return true;//dogs wont collide with skeletons
		if(Entity->Type == ENTITY_TYPE_DOG && this->Type == ENTITY_TYPE_SKELETON) return true;//skeletons wont collide with dogs
		if(Entity->Type == ENTITY_TYPE_DOG && this->Type == ENTITY_TYPE_DOG) return true;//dogs wont collide dogs
		if(Entity->Type == ENTITY_TYPE_SKELETON && this->Type == ENTITY_TYPE_SKELETON) return true;//skeletons wont collide with skeletons
		
		if(this->Type == ENTITY_TYPE_PLAYER && Entity->Type == ENTITY_TYPE_BOMB) return true;//bombs wont collide with samus
		if(Entity->Type == ENTITY_TYPE_PLAYER && this->Type == ENTITY_TYPE_BOMB) return true;//Samus won't collide with bombs
		if(this->Type == ENTITY_TYPE_BOMB && Entity->Type == ENTITY_TYPE_BOMB) return true;//bombs wont collide with bombs

		CEntityCol EntityCol;//declare a class to take in both entitys if all checks have been passed

		EntityCol.EntityA = this;//set them equal to colliding entitys
		EntityCol.EntityB = Entity;

		CEntityCol::EntityColList.push_back(EntityCol);//push back the colliding entity's

		return false;//there was a collision
	}

	return true;//otherwise there was not one
}

//make the entity jump
//==============================================================================
bool CEntity::Jump() {
    if(CanJump == false) return false;//if you cant jump then dont do anything

    	Anim_Control.MaxFrames = 0; //otherwise make the frames of jumping 0
    SpeedY = -MaxSpeedY;//make its speed negative its max speed
    return true;
}
