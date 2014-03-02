//==============================================================================
#ifndef _CCAMERA_H_
    #define _CCAMERA_H_

#include <SDL.h>

#include "Define.h"

//to camera types (center on player or just dont move)
//==============================================================================
enum {
	TARGET_MODE_NORMAL = 0,
	TARGET_MODE_CENTER
};

//==============================================================================
class CCamera {
	public:
		static CCamera CameraControl;//static declaration

	private:
		int X;//X of camera
		int Y;//Y of camera

		float* TargetX;//if we are targeting a player his X
		float* TargetY;//and Y

	public:
		int TargetMode;//how is the camera moving?

	public:
		CCamera();//Constructer

	public:
		void OnMove(int MoveX, int MoveY);//move the X and Y of camera

	public:
		int GetX();//return X camera
		int GetY();//return Y camera

	public:
		void SetPos(int X, int Y);//set the X and Y of camera

		void SetTarget(float* X, float* Y);//set the X and Y of target
};

//==============================================================================

#endif
