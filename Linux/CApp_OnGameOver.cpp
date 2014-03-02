#include "CApp.h"

//function for gameover screen
int CApp::OnGameOver() {
	
	int gameOverSound;//declare gameover background music
	
	CSoundBank::SoundControl.OnCleanup();//clean up all previous game music

	SDL_Surface* gameover;//declare gameover screen surface
	if ((gameover = CSurface::OnLoad("./images/gameOver/gameOver.png")) == false) return -1;//load the gameover image
	
	SDL_Surface* simonDeath;//declare simon death animation
	if ((simonDeath = CSurface::OnLoad("./images/simondeath.png")) == false) return -1;//if we are playing with simon then load the death animation
	SDL_Surface* samusDeath;//declare samus death animatio
	if ((samusDeath = CSurface::OnLoad("./images/samusdeath.png")) == false) return -1;//if we are playing with samus then load th death animation
	
	CSurface::OnDraw(Surf_Display, gameover, 0,0);//draw the game over screen
	
	if (metroid) {//if we are playing samus
		if (( gameOverSound = CSoundBank::SoundControl.OnLoad("./sounds/samusDeathSound.wav")) == -1) return -1;//load the background music for samus
		CSoundBank::SoundControl.Play(-1, gameOverSound, -1);//play the music
		CSurface::OnDraw(Surf_Display, samusDeath, 285, 232, 0, 0, 70, 90);//draw the first frame of samus death
		SDL_Flip(Surf_Display);//flip the screen
		SDL_Delay(1000);//do nothing
		CSurface::OnDraw(Surf_Display, gameover, 0, 0);//draw the gameover screen
		CSurface::OnDraw(Surf_Display, samusDeath, 285, 232, 0, 90, 70, 90);//draw the second frame of samus death
		SDL_Flip(Surf_Display);//flip the screen
		SDL_Delay(200);//do nothing
		CSurface::OnDraw(Surf_Display, gameover, 0, 0);//draw the gameover screen
		CSurface::OnDraw(Surf_Display, samusDeath, 285, 232, 0, 180, 70, 90);//draw the third frame of samus death
		SDL_Flip(Surf_Display);//flip screen
		SDL_Delay(200);//do nothing
		CSurface::OnDraw(Surf_Display, gameover, 0, 0);//draw the gameover screen
		CSurface::OnDraw(Surf_Display, samusDeath, 285, 232, 0, 270, 70, 90);//draw the fourth frame of samus death
		SDL_Flip(Surf_Display);//flip the screen
		SDL_Delay(200);//do nothing
		CSurface::OnDraw(Surf_Display, gameover, 0, 0);//draw the gameover screen
		CSurface::OnDraw(Surf_Display, samusDeath, 285, 232, 0, 360, 70, 90);//draw the fifth frame of samus death
		SDL_Flip(Surf_Display);//flip the screen
		SDL_Delay(200);//do nothing
		CSurface::OnDraw(Surf_Display, gameover, 0, 0);//draw the gameover screen
		CSurface::OnDraw(Surf_Display, samusDeath, 285, 232, 0, 450, 70, 90);//draw the sixth frame of samus death
		SDL_Flip(Surf_Display);//flip the screen
		SDL_Delay(200);//do nothing
		CSurface::OnDraw(Surf_Display, gameover, 0, 0);//draw the gameover screen
		CSurface::OnDraw(Surf_Display, samusDeath, 285, 232, 0, 540, 70, 90);//draw the seventh frame of samus death
		SDL_Flip(Surf_Display);//flip the screen
		SDL_Delay(1000);//do nothing
	} else if (castlevania) {//if we are playing simon
		if (( gameOverSound = CSoundBank::SoundControl.OnLoad("./sounds/simonDeathSound.wav")) == -1) return -1;//load the background music for simon
		CSoundBank::SoundControl.Play(-1, gameOverSound, -1);
		CSurface::OnDraw(Surf_Display, simonDeath, 285, 220, 0, 0, 65,50);
		SDL_Flip(Surf_Display);
		SDL_Delay(1000);
		CSurface::OnDraw(Surf_Display, gameover, 0, 0);
		CSurface::OnDraw(Surf_Display, simonDeath, 285,220, 0,50, 65, 50);
		SDL_Flip(Surf_Display);
		SDL_Delay(500);
		CSurface::OnDraw(Surf_Display, gameover, 0, 0);
		CSurface::OnDraw(Surf_Display, simonDeath, 285,220, 0, 100, 65, 50);
		SDL_Flip(Surf_Display);
		SDL_Delay(500);
		CSurface::OnDraw(Surf_Display, gameover, 0, 0);
		CSurface::OnDraw(Surf_Display, simonDeath, 285, 220, 0, 150, 65, 50);
		SDL_Flip(Surf_Display);
		SDL_Delay(1500);
	}		
	
	bool gameOverRunning = true;
	
	SDL_Event event;
	while(gameOverRunning) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym) {
						case SDLK_ESCAPE:
							SDL_FreeSurface(simonDeath);
							SDL_FreeSurface(samusDeath);
							SDL_FreeSurface(gameover);
							gameOverRunning = false;
							Running=false;
							break;
						default:
							break;
					}
					break;	
			}	
		}		
	}	
	

}	
