//=============================================================================
#ifndef _CSAMUS_H_
    #define _CSAMUS_H_

#include "CEntity.h"

//=============================================================================
class CSamus : public CEntity {
    public:
        CSamus();//constructer

	bool OnLoad(char* File, int Width, int Height, int MaxFrames);//load samus

        void OnLoop();//update her data

        void OnRender(SDL_Surface* Surf_Display);//render her

        void OnCleanup();//clean her up

        void OnAnimate();//animate her

        bool OnCollision(CEntity* Entity);//if she collides with something

	void BulletDeincrement();//timer

	bool	Crouch;//is she crouching?
	bool	PointUpDiagonal;//is she pointing up diagonally?
	bool	PointDownDiagonal;//is she pointing down diagonally?
	bool	morphBall;//is she in morphball?
	bool	PointUp;//is she pointing up?

	int 	shotTimer;//timer for shots

	SDL_Surface*	Surf_Health;//surface that health is blited to
};

//=============================================================================

#endif


