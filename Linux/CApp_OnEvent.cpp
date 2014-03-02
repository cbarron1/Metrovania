//==============================================================================
#include "CApp.h"

//takes in an event
//==============================================================================
void CApp::OnEvent(SDL_Event* Event) {
    CEvent::OnEvent(Event);
}

//when a key is pressed
//==============================================================================
void CApp::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {

	if(metroid){//if we are playing samus
		switch(sym) {//case statement for key pressed


			case SDLK_e: {//if e is pressed
				SDL_EnableKeyRepeat(0, 10000);//holding the button does nohting
				Samus.health--;//increment health
				break;
			}

			case SDLK_LEFT: {//left arrow
				Samus.MoveLeft = true;//move to the left
				Samus.Crouch = false;//uncrouch
				break;
			}
	
			case SDLK_RIGHT: {//right arrow
				Samus.MoveRight = true;//move to the right
				Samus.Crouch = false;//uncrouch
				break;
			}
	
			case SDLK_SPACE: {//space bar
				SDL_EnableKeyRepeat(0, 10000);//holding it down does nothing
	   			Samus.Jump();//make samus jump
		        break;
			}
	
			case SDLK_UP: {//up arrow
				SDL_EnableKeyRepeat(0, 10000);//holding it down does nothing
				if (Samus.morphBall) {//if samus is already in morphball
					Samus.morphBall = false;//take her out of morphball
					Samus.Crouch = true;//crouch
				} else if (Samus.Crouch) {//if samus is already crouching
					Samus.Crouch = false;//uncrouch
				}
				else Samus.PointUp = true;//otherwise make her point up
				break;
			}
	
			case SDLK_DOWN: {//down arrow
				SDL_EnableKeyRepeat(0, 10000);//holding it down does nothing
				if (Samus.Crouch) {//if samus is crouching
					Samus.morphBall = true;//put her in morphball
					Samus.Crouch = false;//uncrouch
				}else if(!Samus.morphBall) {//if samus not not in morphball and crouching
					Samus.Crouch = true;//crouch
					Samus.morphBall = false;//take her out of morphball
				}
				break;
			}
	
			case SDLK_w: {//w key
				Samus.PointUpDiagonal = true;//make her point diagonally up
				break;
			}  
	
			case SDLK_s: {//s key
				Samus.PointDownDiagonal = true;//make her point diagonally down
				break;
			}

			case SDLK_q: {//q key
				if (!Samus.morphBall) //as long as she is not in a ball, she can shoot
				{
					SDL_EnableKeyRepeat(0, 10000);//holding it down does nothing (semi-auto!)
					Samus.shotTimer = 0;//reset the timer keeping track of her shots
					CSoundBank::SoundControl.Play(-1, attackSound, 0);//play the shoot sound
					CShot* Bullet = new CShot;//make a pointer to a bullet object
					Bullet->OnLoad("./images/shot.png", 8, 8, 0);//load the image for the bullet
					if(Samus.faceRight){//if she is facing right shoot it towards the right
						Bullet->faceRight = true;
						Bullet->faceLeft = false;
						Bullet->MoveRight = true;
						Bullet->MoveLeft = false;
						Bullet->X = Samus.X+30;
						Bullet->Y = Samus.Y+15;
						Bullet->SpeedX = 15;
					}
					if(Samus.faceLeft){//if she is facing left shoot it left
						Bullet->faceRight = false;
						Bullet->faceLeft = true;
						Bullet->MoveRight = false;
						Bullet->MoveLeft = true;
						Bullet->X = Samus.X;
						Bullet->Y = Samus.Y+15;
						Bullet->SpeedX = -15;
					}
					if(Samus.faceRight && Samus.PointUpDiagonal){//right diagonally up
						Bullet->faceRight = true;
						Bullet->faceLeft = false;
						Bullet->MoveRight = true;
						Bullet->MoveLeft = false;
						Bullet->X = Samus.X+30;
						Bullet->Y = Samus.Y-4;
						Bullet->SpeedX = 10.605; //net velocity is 12
						Bullet->SpeedY = -10.605;
					}
					if(Samus.faceLeft && Samus.PointUpDiagonal){//left diagonally up
						Bullet->faceRight = false;
						Bullet->faceLeft = true;
						Bullet->MoveRight = false;
						Bullet->MoveLeft = true;
						Bullet->X = Samus.X;
						Bullet->Y = Samus.Y;
						Bullet->SpeedX = -10.605;
						Bullet->SpeedY = -10.605;
					}
					if(Samus.faceRight && Samus.PointDownDiagonal){//right diagonally down
						Bullet->faceRight = true;
						Bullet->faceLeft = false;
						Bullet->MoveRight = true;
						Bullet->MoveLeft = false;
						Bullet->X = Samus.X+30;
						Bullet->Y = Samus.Y+25;
						Bullet->SpeedX = 10.605;
						Bullet->SpeedY = 10.605;
					}
					if(Samus.faceLeft && Samus.PointDownDiagonal){//left diagonally down
						Bullet->faceRight = false;
						Bullet->faceLeft = true;
						Bullet->MoveRight = false;
						Bullet->MoveLeft = true;
						Bullet->X = Samus.X;
						Bullet->Y = Samus.Y+18;
						Bullet->SpeedX = -10.605;
						Bullet->SpeedY = 10.605;
					}
					if(Samus.PointUp && !(Samus.PointUpDiagonal||Samus.MoveLeft||Samus.MoveRight)){ //trap the up shots
						if(Samus.faceRight){//up and facing right
							Bullet->faceRight = true;
							Bullet->faceLeft = false;
							Bullet->MoveRight = false;
							Bullet->MoveLeft = false;
							Bullet->X = Samus.X+8;
							Bullet->Y = Samus.Y-5;
							Bullet->SpeedX = 0;
							Bullet->SpeedY = -15;
						}
						if(Samus.faceLeft){//up and facing left
							Bullet->faceRight = false;
							Bullet->faceLeft = true;
							Bullet->MoveRight = false;
							Bullet->MoveLeft = false;
							Bullet->X = Samus.X+8;
							Bullet->Y = Samus.Y-5;
							Bullet->SpeedX = 0;
							Bullet->SpeedY = -15;
						}
					}
					if(Samus.Crouch){ //trap the crouching
						if(Samus.faceRight){//crouched and right
							Bullet->faceRight = true;
							Bullet->faceLeft = false;
							Bullet->MoveRight = true;
							Bullet->MoveLeft = false;
							Bullet->X = Samus.X+30;
							Bullet->Y = Samus.Y+22;
							Bullet->SpeedX = 15;
						}
						if(Samus.faceLeft){//crouched and left
							Bullet->faceRight = false;
							Bullet->faceLeft = true;
							Bullet->MoveRight = false;
							Bullet->MoveLeft = true;
							Bullet->X = Samus.X;
							Bullet->Y = Samus.Y+22;
							Bullet->SpeedX = -15;
						}
						if(Samus.faceRight && Samus.PointUpDiagonal){//crouched and right diagonally up
							Bullet->faceRight = true;
							Bullet->faceLeft = false;
							Bullet->MoveRight = true;
							Bullet->MoveLeft = false;
							Bullet->X = Samus.X+30;
							Bullet->Y = Samus.Y+3;
							Bullet->SpeedX = 10.605;
							Bullet->SpeedY = -10.605;
						}
						if(Samus.faceLeft && Samus.PointUpDiagonal){//crouched and left diagonally up
							Bullet->faceRight = false;
							Bullet->faceLeft = true;
							Bullet->MoveRight = false;
							Bullet->MoveLeft = true;
							Bullet->X = Samus.X;
							Bullet->Y = Samus.Y+8;
							Bullet->SpeedX = -10.605;
							Bullet->SpeedY = -10.605;
						}
						if(Samus.faceRight && Samus.PointDownDiagonal){//crouched and right diagonally down
							Bullet->faceRight = true;
							Bullet->faceLeft = false;
							Bullet->MoveRight = true;
							Bullet->MoveLeft = false;
							Bullet->X = Samus.X+30;
							Bullet->Y = Samus.Y+30;
							Bullet->SpeedX = 10.605;
							Bullet->SpeedY = 10.605;
						}
						if(Samus.faceLeft && Samus.PointDownDiagonal){//crouched and left diagonally down
							Bullet->faceRight = false;
							Bullet->faceLeft = true;
							Bullet->MoveRight = false;
							Bullet->MoveLeft = true;
							Bullet->X = Samus.X;
							Bullet->Y = Samus.Y+25;
							Bullet->SpeedX = -10.605;
							Bullet->SpeedY = 10.605;
						}
					}
					CEntity::EntityList.push_back(Bullet);//push the bullet into the entity list
				}
				if (Samus.morphBall){ //if Samus is in her morphball
					SDL_EnableKeyRepeat(0, 10000);//holding the button down does nothing
					CExplode* bomb = new CExplode; //a new pointer to a bomb
					bomb->OnLoad("./images/Bomb.png", 28, 28, 5);
					if (Samus.faceLeft){
						bomb->X = Samus.X+3; //make the bomb match the position of Samus
						bomb->Y = Samus.Y+18;
					}
					if (Samus.faceRight){
						bomb->X = Samus.X+3; //make the bomb match the position of Samus
						bomb->Y = Samus.Y+18;
					}
					bomb->isbomb = 1; //make the effect an actual bomb
					bomb->fm = 5; //main bomb animation
					bomb->altframemax = 9; //explosion animation
					bomb->cyclelimit = 220;
					CEntity::EntityList.push_back(bomb); //push back the bomb into the list
				}
				break;
				case SDLK_d: { //bomb button
					if (Samus.morphBall){ //if Samus is in her morphball
						SDL_EnableKeyRepeat(0, 10000);
						CExplode* bomb = new CExplode; //a new pointer to a bomb
						bomb->OnLoad("./images/Bomb.png", 28, 28, 5);
						if (Samus.faceLeft){
							bomb->X = Samus.X+3; //make the bomb match the position of Samus
							bomb->Y = Samus.Y+18;
						}
						if (Samus.faceRight){
							bomb->X = Samus.X+3; //make the bomb match the position of Samus
							bomb->Y = Samus.Y+18;
						}
						bomb->isbomb = 1; //make the effect an actual bomb
						bomb->fm = 5; //main bomb animation
						bomb->altframemax = 9; //explosion animation
						bomb->cyclelimit = 220;
						CEntity::EntityList.push_back(bomb); //push back the bomb into the list
					}
					break;
				}
			}
			
			case SDLK_r: {//reset the position of everything
				Samus.X = 50;
				Samus.Y = 50;
				OnPosReset();
				break;
			}

			case SDLK_z: {//reset the position of samus
				Samus.X = 100;
				Samus.Y = 500;
				break;
			}

			case SDLK_x: {//reset the position of the enemys

				break;
			}
				

			case SDLK_ESCAPE: {//if esc is pressed exit
				OnExit();
			break;
			}

			default: {//other wise do nothing
			}
		}
	}
	if(castlevania){//if simon is being played
		switch(sym) {

			case SDLK_e: {//if e is pressed
				SDL_EnableKeyRepeat(0, 10000);//holding the button does nohting
				Simon.health--;//increment health
				break;
			}

			case SDLK_q: {//if q is pressed
				if(Simon.Attack == false){//if simon is already not attacking
					SDL_EnableKeyRepeat(0, 10000);//holding the button does nohting
					CSoundBank::SoundControl.Play(-1, attackSound, 0);//play a whipping noise
					Simon.Attack = true;//simon is attacking
					Simon.MoveRight = false;//simon is not moving right
					Simon.MoveLeft = false;//simon is not moving left
				}
				break;
			}

			case SDLK_LEFT: {//left arrow
				if(Simon.Attack == false){//if simon is not attacking
					Simon.MoveLeft = true;//move left
					Simon.Crouch = false;//uncrouch
				}
				break;
			}
	
			case SDLK_RIGHT: {//right arrow
				if(Simon.Attack == false){//if simon is not attacking
					Simon.MoveRight = true;//move right
					Simon.Crouch = false;//uncrouch
				}
				break;
			}

			case SDLK_a: {//a key
				Simon.Taunt = true;//do the stupid taunt animation
				break;
			}
	
			case SDLK_SPACE: {//space bar
				SDL_EnableKeyRepeat(0, 10000);//holding it down does nothing
	   			Simon.Jump();//make simon jump
		        	break;
			}

			case SDLK_UP: {//up arrow
				Simon.PointUp = true;//simon is facing up
				break;
			}

			case SDLK_DOWN: {//down arrow
				Simon.Crouch = true;//crouch
				break;
			}

			
			case SDLK_r: {//reset the position of everything
				Simon.X = 100;
				Simon.Y = 500;
				OnPosReset();
				break;
			}


			case SDLK_z: {//reset simons position
				Simon.X = 50;
				Simon.Y = 50;
				break;
			}

			case SDLK_x: {//reset enemy positions

				break;
			}

			case SDLK_ESCAPE: {//esc key ends game
				OnExit();
			break;
			}

			default: {
			}
		}
	}
}

//------------------------------------------------------------------------------
void CApp::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {//if a key is depressed
	if(metroid){//if samus is being played
		switch(sym) {
			case SDLK_LEFT: {//left arrow depressed
				Samus.MoveLeft = false;//stop moving left
				break;
			}

			case SDLK_RIGHT: {//right arrow depressed
				Samus.MoveRight = false;//stop moving right
				break;
			}

			case SDLK_UP: {//up arrow depressed
				Samus.PointUp = false;//stop pointing up
				break;
			}

			case SDLK_DOWN: {//down arrow depressed
				break;//do nothing
			}

			case SDLK_w: {//w key depressed
				Samus.PointUpDiagonal = false;//stop pointing diagonally up
				break;
			}

			case SDLK_s: {//s key depressed
				Samus.PointDownDiagonal = false;//stop pointing diagonally down
				break;
			}


			default: {
			}
		}
	}
	if(castlevania){//if simon is being played
		switch(sym) {
			case SDLK_LEFT: {//left arrow depressed
				Simon.MoveLeft = false;//stop moving left
				break;
			}

			case SDLK_RIGHT: {//right arrow depressed
				Simon.MoveRight = false;//stop moving right
				break;
			}

			case SDLK_a: {//a key depressed
				Simon.Taunt = false;//stop taunting
				break;
			}

			case SDLK_UP: {//up arrow depressed
				Simon.PointUp = false;//stop pointing up
				break;
			}

			case SDLK_DOWN: {//down arrow depressed
				Simon.Crouch = false;//stop crouching
				break;
			}

			default: {//otherwise do nothing
			}
		}
	}
}

//if the game wants to exit then make running false
//------------------------------------------------------------------------------
void CApp::OnExit() {
	Running = false;
}

//==============================================================================
