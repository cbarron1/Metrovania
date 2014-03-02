//==============================================================================
#include "CApp.h"

//==============================================================================
void CApp::OnRender() {
	SDL_Rect Rect;//make a rectangle that will hold the window images
	Rect.x = 0;
	Rect.y = 0;
	Rect.w = WWIDTH;
	Rect.h = WHEIGHT;

	SDL_FillRect(Surf_Display, &Rect, 0);//fill it with nothing

	CArea::AreaControl.OnRender(Surf_Display, -CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY());//get the camera cooridants and draw the area

    //--------------------------------------------------------------------------
    // Entities
    //--------------------------------------------------------------------------
    for(int i = 0;i < CEntity::EntityList.size();i++) {//draw all the entitys
        if(!CEntity::EntityList[i]) continue;

        CEntity::EntityList[i]->OnRender(Surf_Display);
    }

	CSurface::OnDraw(Surf_Display, Surf_Counter, 510, -20, (enemyCounter/10)*100, 0, 100, 100);//draw the counter
	CSurface::OnDraw(Surf_Display, Surf_Counter, 560, -20, (enemyCounter%10)*100, 0, 100, 100);

	SDL_Flip(Surf_Display);//flip the screen
}

//==============================================================================
