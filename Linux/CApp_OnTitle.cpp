#include "CApp.h"
#include "CSurface.h"

int CApp::OnTitle() {

	int introSound;//declare the intro sound
		
	SDL_Surface* title;//declare title surface
	if ((title = CSurface::OnLoad("./images/titleScreen/TitleScreen.png")) == false) return -1;//load the title image
	SDL_Surface* arrow;//declare arrow surface
	if ((arrow = CSurface::OnLoad("./images/titleScreen/arrow.png")) == false) return -1;//load the arrow image
	SDL_Surface* intro;//declare the intro surface
	SDL_Surface* instructions;//declare the instructions
	if ((instructions = CSurface::OnLoad("./images/titleScreen/instructions.png")) == false) return -1;//load the instructions image


	CSurface::OnDraw(Surf_Display, title, 0,0);//draw the title screen
	CSurface::OnDraw(Surf_Display, arrow, 240,230);//draw the arrow
	
	SDL_Flip(Surf_Display);//flip the surface
	
	SDL_Event event;//declare events
	bool titleRunning = true;//declare variables
	bool choice1 = true;
	bool choice2 = false;
	
	while (titleRunning) {//while the title screen is still running
		while (SDL_PollEvent(&event)) {
			switch(event.type) {
				case SDL_KEYDOWN://if a key is pressed
					switch(event.key.keysym.sym) {
						case SDLK_UP://up arrow
							if (choice1) {//if the first choice is the current choice
								CSurface::OnDraw(Surf_Display, title, 0,0);//switch to the second choice
								choice1=false;
								choice2=true;
								CSurface::OnDraw(Surf_Display,arrow,240,270);
								SDL_Flip(Surf_Display);
							}	
							else if (choice2) {//if the second choice is the current choice
								CSurface::OnDraw(Surf_Display, title, 0,0);//swich to the first choice
								choice1=true;
								choice2=false;
								CSurface::OnDraw(Surf_Display,arrow,240,230);
								SDL_Flip(Surf_Display);
							}	
							break;
						case SDLK_DOWN://down arrow
							if (choice1) {//if the first choic is the current choice
								CSurface::OnDraw(Surf_Display, title, 0,0);//switch to the second choice
								choice1=false;
								choice2=true;
								CSurface::OnDraw(Surf_Display,arrow,240,270);
								SDL_Flip(Surf_Display);
							}	
							else if (choice2) {//if the second choice is the current choice
								CSurface::OnDraw(Surf_Display, title, 0,0);//switch to the first choice
								choice1=true;
								choice2=false;
								CSurface::OnDraw(Surf_Display,arrow,240,230);
								SDL_Flip(Surf_Display);
							}	
							break;
						case SDLK_RETURN://enter key
							if (choice1) {//if the first choice is the current choice
								if (( introSound = CSoundBank::SoundControl.OnLoad("./sounds/samusIntro.wav")) == -1) return -1;//load the samus intro sound
								CSoundBank::SoundControl.Play(-1, introSound, 0);//play it
								if (( intro = CSurface::OnLoad("./images/titleScreen/samusintro.png")) == false) return -1;//load the samus intro image
								CSurface::OnDraw(Surf_Display, title, 0,0);//draw everything
								CSurface::OnDraw(Surf_Display, arrow, 240, 230);
								CSurface::OnDraw(Surf_Display, intro, 360, 220, 0, 0, 30, 30);
								SDL_Flip(Surf_Display);//flip screen
								SDL_Delay(1000);//delay
								CSurface::OnDraw(Surf_Display, title, 0,0);
								CSurface::OnDraw(Surf_Display, arrow, 240, 230);
								CSurface::OnDraw(Surf_Display, intro, 360, 220, 0, 30, 30, 30);
								SDL_Flip(Surf_Display);
								SDL_Delay(200);
								CSurface::OnDraw(Surf_Display, title, 0,0);
								CSurface::OnDraw(Surf_Display, arrow, 240, 230);
								CSurface::OnDraw(Surf_Display, intro, 360, 220, 0, 60, 30, 30);
								SDL_Flip(Surf_Display);
								SDL_Delay(200);
								CSurface::OnDraw(Surf_Display, title, 0,0);
								CSurface::OnDraw(Surf_Display, arrow, 240, 230);
								CSurface::OnDraw(Surf_Display, intro, 360, 220, 0, 90, 30, 30);
								SDL_Flip(Surf_Display);
								SDL_Delay(200);
								CSurface::OnDraw(Surf_Display, title, 0,0);
								CSurface::OnDraw(Surf_Display, arrow, 240, 230);
								CSurface::OnDraw(Surf_Display, intro, 360, 220, 0, 120, 30, 30);
								SDL_Flip(Surf_Display);
								SDL_Delay(200);
								CSurface::OnDraw(Surf_Display, title, 0,0);
								CSurface::OnDraw(Surf_Display, arrow, 240, 230);
								CSurface::OnDraw(Surf_Display, intro, 360, 220, 0, 150, 30, 30);
								SDL_Flip(Surf_Display);
								SDL_Delay(200);
								CSurface::OnDraw(Surf_Display, title, 0,0);
								CSurface::OnDraw(Surf_Display, arrow, 240, 230);
								CSurface::OnDraw(Surf_Display, intro, 360, 220, 0, 180, 30, 30);
								SDL_Flip(Surf_Display);
								SDL_Delay(200);
								CSurface::OnDraw(Surf_Display, title, 0,0);
								CSurface::OnDraw(Surf_Display, arrow, 240, 230);
								CSurface::OnDraw(Surf_Display, intro, 360, 220, 0, 210, 30, 30);
								SDL_Flip(Surf_Display);
								SDL_Delay(200);
								CSurface::OnDraw(Surf_Display, title, 0,0);
								CSurface::OnDraw(Surf_Display, arrow, 240, 230);
								CSurface::OnDraw(Surf_Display, intro, 360, 220, 0, 240, 30, 30);
								SDL_Flip(Surf_Display);
								SDL_Delay(500);
								metroid=true;//we are playing samus
								castlevania=false;
								titleRunning=false;
							} else { //do the same as above but for simon
								if (( introSound = CSoundBank::SoundControl.OnLoad("./sounds/simonIntro.wav")) == -1) return -1;
								CSoundBank::SoundControl.Play(-1, introSound, 0);
								if (( intro = CSurface::OnLoad("./images/titleScreen/simonintro.png")) == false) return -1;
								CSurface::OnDraw(Surf_Display, title, 0,0);
								CSurface::OnDraw(Surf_Display, arrow, 240, 270);
								CSurface::OnDraw(Surf_Display, intro, 360, 230, 0, 0, 80, 80);
								SDL_Flip(Surf_Display);
								SDL_Delay(1000);
								CSurface::OnDraw(Surf_Display, title, 0,0);
								CSurface::OnDraw(Surf_Display, arrow, 240, 270);
								CSurface::OnDraw(Surf_Display, intro, 360, 230, 0, 80, 80, 80);
								SDL_Flip(Surf_Display);
								SDL_Delay(200);
								CSurface::OnDraw(Surf_Display, title, 0,0);
								CSurface::OnDraw(Surf_Display, arrow, 240, 270);
								CSurface::OnDraw(Surf_Display, intro, 360, 230, 0, 160, 80, 80);
								SDL_Flip(Surf_Display);
								SDL_Delay(200);
								CSurface::OnDraw(Surf_Display, title, 0,0);
								CSurface::OnDraw(Surf_Display, arrow, 240, 270);
								CSurface::OnDraw(Surf_Display, intro, 360, 230, 0, 240, 80, 80);
								SDL_Flip(Surf_Display);
								SDL_Delay(200);
								CSurface::OnDraw(Surf_Display, title, 0,0);
								CSurface::OnDraw(Surf_Display, arrow, 240, 270);
								CSurface::OnDraw(Surf_Display, intro, 360, 230, 0, 320, 80, 80);
								SDL_Flip(Surf_Display);
								SDL_Delay(200);
								CSurface::OnDraw(Surf_Display, title, 0,0);
								CSurface::OnDraw(Surf_Display, arrow, 240, 270);
								CSurface::OnDraw(Surf_Display, intro, 360, 230, 0, 400, 80, 80);
								SDL_Flip(Surf_Display);
								SDL_Delay(200);
								CSurface::OnDraw(Surf_Display, title, 0,0);
								CSurface::OnDraw(Surf_Display, arrow, 240, 270);
								CSurface::OnDraw(Surf_Display, intro, 360, 230, 0, 480, 80, 80);
								SDL_Flip(Surf_Display);
								SDL_Delay(200);
								CSurface::OnDraw(Surf_Display, title, 0,0);
								CSurface::OnDraw(Surf_Display, arrow, 240, 270);
								CSurface::OnDraw(Surf_Display, intro, 360, 230, 0, 560, 80, 80);
								SDL_Flip(Surf_Display);
								SDL_Delay(1500);
								castlevania=true;
								metroid=false;
								titleRunning=false;
							}
							break;
						case SDLK_r://if r is pressed do nothing
							break;		
						default://if anything else is pressed end teh game
						     	return -1;
							break;	
					}	
					break;
			}	
		}	
	}	
	
	SDL_FreeSurface(title);//free the title
	SDL_FreeSurface(arrow);//free the arrow
	
	CSurface::OnDraw(Surf_Display, instructions, 0,0);//draw the instructions
	SDL_Flip(Surf_Display);//flip screen
	SDL_Delay(2000);//wait 2 seconds
	SDL_FreeSurface(instructions);//free the instructions
	
	return 0;	
	
}
