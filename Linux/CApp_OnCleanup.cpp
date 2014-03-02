//==============================================================================
#include "CApp.h"

//when the game ends this cleans up all the objects
//==============================================================================
void CApp::OnCleanup() {
	//cleans up the areas (map)	
	CArea::AreaControl.OnCleanup();

    //--------------------------------------------------------------------------
    // Entities
    //--------------------------------------------------------------------------
    //loops through all the entitys and cleans them up.
    for(int i = 0;i < CEntity::EntityList.size();i++) {
        if(!CEntity::EntityList[i]) continue;

        CEntity::EntityList[i]->OnCleanup();
    }

    //clears the list
    CEntity::EntityList.clear();
    //cleans up the sound bank
    CSoundBank::SoundControl.OnCleanup();
    //closes audio stuff
    Mix_CloseAudio();
    //frees the main window
    SDL_FreeSurface(Surf_Display);
    //closes all the SDL stuff
    SDL_Quit();
}

//==============================================================================
