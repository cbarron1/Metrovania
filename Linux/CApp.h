//==============================================================================
// SDL Tutorial 8
//==============================================================================
#ifndef _CAPP_H_
    #define _CAPP_H_

#define _CRT_SECURE_NO_DEPRECATE
#include <SDL.h>

#include "Define.h"

#include "CFPS.h"

#include "CArea.h"
#include "CCamera.h"
#include "CEntity.h"
#include "CEvent.h"
#include "CSurface.h"
#include "CSoundBank.h"

#include "CSamus.h"
#include "CSimon.h"
#include "CTurtle.h"
#include "CInsect.h"
#include "CShot.h"
#include "CExplode.h"
#include "CSkeleton.h"
#include "CWhip.h"
#include "CSword.h"
#include "CDog.h"

//==============================================================================
class CApp : public CEvent {
    private:
        bool            Running;//is the game running?

        SDL_Surface*    Surf_Display;//the main display
	SDL_Surface*	Surf_Counter;

        CSamus		Samus;//declaration of power suit wearing samus
	CSimon		Simon;//declaration of whip wielding simon
	
	//instantiate all turtles
	CTurtle		Adrian;
	CTurtle		Barney;
	CTurtle		Cynthia;
	CTurtle		Doug;
	CTurtle		Ethan;
	CTurtle		Fernando;
	CTurtle		Greg;
	CTurtle		Heidi;
	CTurtle		Ingrid;
	CTurtle		Justin;
	CTurtle		Kayla;
	CTurtle		Louis;
	CTurtle		Marc;
	CTurtle		Nolan;
	CTurtle		Oscar;
	CTurtle		Peter;
	CTurtle		Quincy;
	CTurtle		Robert;
	
	//instantiate all insects
	CInsect		Atlas;
	CInsect		Odin;
	CInsect		Bacchus;
	CInsect		Cthulhu;
	CInsect		Lucifer;
	CInsect		Venus;
	CInsect		Daedalus;
	CInsect		Quetzlcoatl;
	CInsect		Shiva;
	
	//instantiate all skeletons
	CSkeleton	Alpha;
	CSkeleton	Bravo;
	CSkeleton	Charlie;
	CSkeleton	Delta;
	CSkeleton	Echo;
	CSkeleton	Foxtrot;
	CSkeleton	Golf;
	CSkeleton	Hotel;
	CSkeleton	India;
	
	//instantiate all dogs
	CDog		Ramza;
	CDog		Firion;
	CDog		Luneth;
	CDog		Cecil;
	CDog		Bartz;
	CDog		Terra;
	CDog		Cloud;
	CDog		Squall;
	CDog		Zidane;
	CDog		Tidus;
	CDog		Mog;
	CDog		Vaan;
	CDog		Lightning;
	
	
	
	int		attackSound;//declaration of either a gun firing or a whip snapping
	int		enemyCounter;//counts the number of enemys
	int		waitingCounter; //counter for adding delay between killing last enemy and victory screen

    public:
        CApp();//constructer

        int OnExecute();//executes all other functions
        
        int OnTitle();//title screen declaration
        
        int OnGameOver();//game over screen declaration
        
        int OnVictory();
        
        void OnPosReset();
        
        int count;

    public:
        bool OnInit();//initializes all objects

        void OnEvent(SDL_Event* Event);//takes input

        	void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);//when a key is pressed down

        	void OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);//when a key is depressed

            void OnExit();//when the game exits

        void OnLoop();//function that updates all data

        void OnRender();//draws all images to screen

        void OnCleanup();//cleans up all objects
        
        
        
	bool metroid;//are we playing with samus?
	bool castlevania;//are we playing with simon?
};

//==============================================================================

#endif
