//==============================================================================
#include "CCamera.h"

//==============================================================================
CCamera CCamera::CameraControl;

//constructer
//==============================================================================
CCamera::CCamera() {
	X = Y = 0;

	TargetX = TargetY = NULL;

	TargetMode = TARGET_MODE_NORMAL;
}

//move the camera by MoveX and MoveY pixels
//==============================================================================
void CCamera::OnMove(int MoveX, int MoveY) {
	X += MoveX;
	Y += MoveY;
}

//return the X
//==============================================================================
int CCamera::GetX() {
	if(TargetX != NULL) {
		if(TargetMode == TARGET_MODE_CENTER) {
			return *TargetX - (WWIDTH / 2);
		}

		return *TargetX;
	}

	return X;
}

//return the Y
//------------------------------------------------------------------------------
int CCamera::GetY() {
	if(TargetY != NULL) {
		if(TargetMode == TARGET_MODE_CENTER) {
			return *TargetY - (WHEIGHT / 2);
		}

		return *TargetY;
	}

	return Y;
}

//set the position of the X and Y
//==============================================================================
void CCamera::SetPos(int X, int Y) {
	this->X = X;
	this->Y = Y;
}

//set the target position X and Y
//------------------------------------------------------------------------------
void CCamera::SetTarget(float* X, float* Y) {
	TargetX = X;
	TargetY = Y;
}

//==============================================================================
