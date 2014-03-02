#include "CApp.h"

int CApp::OnVictory() {
	
	int victorySound;//declare sound
	
	CSoundBank::SoundControl.OnCleanup();//clean up all previous sound
	
	SDL_Surface* victoryScreen;//declare the surface
	if (( victoryScreen = CSurface::OnLoad("./images/gameOver/victoryScreen.png")) == false) return -1;//load the victory
	
	if (( victorySound = CSoundBank::SoundControl.OnLoad("./sounds/victory.wav")) == -1) return -1;//load the victory music
	CSoundBank::SoundControl.Play(-1, victorySound, -1);//play the music
	
	CSurface::OnDraw(Surf_Display,victoryScreen,0,0);
	SDL_Flip(Surf_Display);

	bool gameOverRunning = true;
	
	SDL_Event event;
	while(gameOverRunning) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_KEYDOWN://when a key is pressed
					switch(event.key.keysym.sym) {
						case SDLK_ESCAPE://escape key
							SDL_FreeSurface(victoryScreen);//free the surface
							gameOverRunning = false;//stop running the screen
							Running=false;//stop running the game
							break;
						default://anything else do nothing
							break;
					}
					break;	
			}	
		}		
	}	
	
	
}	
