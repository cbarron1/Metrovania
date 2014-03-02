	//==============================================================================
#ifndef _CENTITY_H_
    #define _CENTITY_H_

#include <vector>

#include "CArea.h"
#include "CAnimation.h"
#include "CCamera.h"
#include "CFPS.h"
#include "CSurface.h"

//==============================================================================
enum {//all our entity types
	ENTITY_TYPE_GENERIC = 0,

	ENTITY_TYPE_PLAYER,
	ENTITY_TYPE_INSECT,
	ENTITY_TYPE_BULLET,
	ENTITY_TYPE_EFFECT,
	ENTITY_TYPE_SKELETON,
	ENTITY_TYPE_WHIP,
	ENTITY_TYPE_SWORD1,
	ENTITY_TYPE_SWORD2,
	ENTITY_TYPE_BOMB,
	ENTITY_TYPE_DOG
};

//==============================================================================
enum {//all our entity flags
	ENTITY_FLAG_NONE 	= 0,

	ENTITY_FLAG_GRAVITY	= 0x00000001,
	ENTITY_FLAG_GHOST	= 0x00000002,
	ENTITY_FLAG_MAPONLY	= 0x00000004
};

//==============================================================================
class CEntity {
	public:
		static std::vector<CEntity*>    EntityList;//vector of entitys

	protected:
		CAnimation      Anim_Control;//instance of animation

		SDL_Surface*    Surf_Entity;//declare the surface of the entity

	public:
		float	X;//X pos
		float	Y;//Y pos

		int		Width;//entity width
		int		Height;//entity height

		bool	MoveLeft;//are we moving to the left?
		bool	MoveRight;//are we moving to the right?
		bool	faceLeft;//are we facing left?
		bool	faceRight;//are we facing right?

	public:
		int		Type;//entity type

		bool	Dead;//are we dead?
		int		Flags;//entity flags
		int	health;//entitys health
		int	healthTimer;//entitys health timer
		int	collisionTimer;//entitys collision timer

	public:
		float	SpeedX;//current X speed
		float	SpeedY;//current Y speed

		float	AccelX;//current X acceleration
		float	AccelY;//current Y acceleration

	public:
		float	MaxSpeedX;//max X speed
		float	MaxSpeedY;//max Y speed

	public:
		int		CurrentFrameCol;//what frame col is being animated
		int		CurrentFrameRow;//what frame row is being animated

	protected:
		int		Col_X;//the collision X
		int		Col_Y;//the collision Y
		int		Col_Width;//the collision width
		int		Col_Height;//the collision height

	public:
		CEntity();//entity constructer

		virtual ~CEntity();//entity deconstructer

	public:
		virtual bool OnLoad(char* File, int Width, int Height, int MaxFrames);//load the entity

		virtual void OnLoop();//every loop update data

		virtual void OnRender(SDL_Surface* Surf_Display);//render the entity

		virtual void OnCleanup();//clean the entity up

		virtual void OnAnimate();//animate the entity

		virtual bool OnCollision(CEntity* Entity);//check to see if the entity has collided

	public:
		void    OnMove(float MoveX, float MoveY);//when the entity moves

		void 	StopMove();

	public:
		bool    Collides(int oX, int oY, int oW, int oH);
		//bool    CanJump; //made it public for the bomb jump functionality

	public:
		bool 	PosValid(int NewX, int NewY);//check to see if the position its moving to is valid

		bool 	PosValidTile(CTile* Tile);//check to see if theres a tile in the way

		bool 	PosValidEntity(CEntity* Entity, int NewX, int NewY);//check to see if theres an entity in the way

        protected:
                bool    CanJump;//check to see if the entity can currently jump
 
        public:
                bool     Jump();//make the entity jump
};

//==============================================================================
class CEntityCol {
	public:
		static std::vector<CEntityCol>	EntityColList;//this vector will hold all entity collisions

	public:
		CEntity* EntityA;//entity A that collided
		CEntity* EntityB;//entity B that collided

	public:
		CEntityCol();//push both the entitys in to the vector
};

//==============================================================================

#endif
