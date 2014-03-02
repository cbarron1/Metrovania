//==============================================================================
#include "CApp.h"
#include <iostream>
//==============================================================================
bool CApp::OnInit() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {//init SDL
        return false;
    }

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {//init sound
        return false;
    }

    if((Surf_Display = SDL_SetVideoMode(WWIDTH, WHEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {//init the window
        return false;
    }
    
    if (OnTitle() != 0) Running = false;//check to see if the title screen is still going
    
    SDL_Delay(2000);// do nothing

    if(CArea::AreaControl.OnLoad("./maps/test.area") == false) {//load the map
    	return false;
    }

    SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);//make it so that a button repeats if held down
    
    int backgroundMusic;//declare background sound

	if(metroid){//if we are playing samus
		if(Samus.OnLoad("images/samusanim.png", 30, 40, 11) == false) {//load samus image
			return false;
		}
		if((attackSound = CSoundBank::SoundControl.OnLoad("./sounds/shot.wav")) == -1) {//load her shot sound
			return false;
		}
		if((backgroundMusic = CSoundBank::SoundControl.OnLoad("./sounds/samusBackground.wav")) == -1) {//load her background music
			return false;
		}	
		CSoundBank::SoundControl.Play(-1,backgroundMusic, -1);//play her background music
	}

	if(castlevania){//if we are playing simon
		if(Simon.OnLoad("images/simonanim.png", 30, 50, 13) == false){//load his image
			return false;
		}
		if((attackSound = CSoundBank::SoundControl.OnLoad("./sounds/whip.wav")) == -1) {//load his whip sound
			return false;
		}
		if((backgroundMusic = CSoundBank::SoundControl.OnLoad("./sounds/simonBackground.wav")) == -1) {//loadload his background music
			return false;
		}	
		CSoundBank::SoundControl.Play(-1,backgroundMusic, -1);//play his background music
	}

	//load all the turtles
	if(Adrian.OnLoad("images/Enemy1.png", 40, 17, 6) == false) return false; 
	if(Barney.OnLoad("images/Enemy1.png", 40, 17, 6) == false) return false;
	if(Cynthia.OnLoad("images/Enemy1.png", 40, 17, 6) == false) return false;
	if(Doug.OnLoad("images/Enemy1.png", 40, 17, 6) == false) return false;
	if(Ethan.OnLoad("images/Enemy1.png", 40, 17, 6) == false) return false;
	if(Fernando.OnLoad("images/Enemy1.png", 40, 17, 6) == false) return false;
	if(Greg.OnLoad("images/Enemy1.png", 40, 17, 6) == false) return false;
	if(Heidi.OnLoad("images/Enemy1.png", 40, 17, 6) == false) return false;
	if(Ingrid.OnLoad("images/Enemy1.png", 40, 17, 6) == false) return false;
	if(Justin.OnLoad("images/Enemy1.png", 40, 17, 6) == false) return false;
	if(Kayla.OnLoad("images/Enemy1.png", 40, 17, 6) == false) return false;
	if(Louis.OnLoad("images/Enemy1.png", 40, 17, 6) == false) return false;
	if(Marc.OnLoad("images/Enemy1.png", 40, 17, 6) == false) return false;
	if(Nolan.OnLoad("images/Enemy1.png", 40, 17, 6) == false) return false;
	if(Oscar.OnLoad("images/Enemy1.png", 40, 17, 6) == false) return false;
	if(Peter.OnLoad("images/Enemy1.png", 40, 17, 6) == false) return false;
	if(Quincy.OnLoad("images/Enemy1.png", 40, 17, 6) == false) return false;
	if(Robert.OnLoad("images/Enemy1.png", 40, 17, 6) == false) return false;
	
	
	//load all insects
	if(Atlas.OnLoad("images/Enemy2.png",58,49,3) == false) return false;
	if(Odin.OnLoad("images/Enemy2.png",58,49,3) == false) return false;
	if(Bacchus.OnLoad("images/Enemy2.png",58,49,3) == false) return false;
	if(Cthulhu.OnLoad("images/Enemy2.png",58,49,3) == false) return false;
	if(Lucifer.OnLoad("images/Enemy2.png",58,49,3) == false) return false;
	if(Venus.OnLoad("images/Enemy2.png",58,49,3) == false) return false;
	if(Daedalus.OnLoad("images/Enemy2.png",58,49,3) == false) return false;
	if(Quetzlcoatl.OnLoad("images/Enemy2.png",58,49,3) == false) return false;
	if(Shiva.OnLoad("images/Enemy2.png",58,49,3) == false) return false;

	//load all skeletons
	if(Alpha.OnLoad("images/skeleton.png", 33, 52, 3) == false) return false;
	if(Bravo.OnLoad("images/skeleton.png", 33, 52, 3) == false) return false;
	if(Charlie.OnLoad("images/skeleton.png", 33, 52, 3) == false) return false;
	if(Delta.OnLoad("images/skeleton.png", 33, 52, 3) == false) return false;
	if(Echo.OnLoad("images/skeleton.png", 33, 52, 3) == false) return false;
	if(Foxtrot.OnLoad("images/skeleton.png", 33, 52, 3) == false) return false;
	if(Golf.OnLoad("images/skeleton.png", 33, 52, 3) == false) return false;
	if(Hotel.OnLoad("images/skeleton.png", 33, 52, 3) == false) return false;
	if(India.OnLoad("images/skeleton.png", 33, 52, 3) == false) return false; 
	
	//load all dogs
	if(Ramza.OnLoad("images/dog.png",43,26, 5) == false) return false;
	if(Firion.OnLoad("images/dog.png",43,26, 5) == false) return false;
	if(Luneth.OnLoad("images/dog.png",43,26, 5) == false) return false;
	if(Cecil.OnLoad("images/dog.png",43,26, 5) == false) return false;
	if(Bartz.OnLoad("images/dog.png",43,26, 5) == false) return false;
	if(Terra.OnLoad("images/dog.png",43,26, 5) == false) return false;
	if(Cloud.OnLoad("images/dog.png",43,26, 5) == false) return false;
	if(Squall.OnLoad("images/dog.png",43,26, 5) == false) return false;
	if(Zidane.OnLoad("images/dog.png",43,26, 5) == false) return false;
	if(Tidus.OnLoad("images/dog.png",43,26, 5) == false) return false;
	if(Mog.OnLoad("images/dog.png",43,26, 5) == false) return false;
	if(Vaan.OnLoad("images/dog.png",43,26, 5) == false) return false;
	if(Lightning.OnLoad("images/dog.png",43,26, 5) == false) return false;

	//load the image for the enemy counter
	if((Surf_Counter = CSurface::OnLoad("./images/numberChart.png")) == false ) return false;

	//push all the entitys into the entity list
	if(metroid) CEntity::EntityList.push_back(&Samus);
	if(castlevania) CEntity::EntityList.push_back(&Simon);
	CEntity::EntityList.push_back(&Adrian);
	CEntity::EntityList.push_back(&Barney);
	CEntity::EntityList.push_back(&Cynthia);
	CEntity::EntityList.push_back(&Doug);
	CEntity::EntityList.push_back(&Ethan);
	CEntity::EntityList.push_back(&Fernando);
	CEntity::EntityList.push_back(&Greg);
	CEntity::EntityList.push_back(&Heidi);
	CEntity::EntityList.push_back(&Ingrid);
	CEntity::EntityList.push_back(&Justin);
	CEntity::EntityList.push_back(&Kayla);
	CEntity::EntityList.push_back(&Louis);
	CEntity::EntityList.push_back(&Marc);
	CEntity::EntityList.push_back(&Nolan);
	CEntity::EntityList.push_back(&Oscar);
	CEntity::EntityList.push_back(&Peter);
	CEntity::EntityList.push_back(&Quincy);
	CEntity::EntityList.push_back(&Robert);
	CEntity::EntityList.push_back(&Atlas);
	CEntity::EntityList.push_back(&Odin);
	CEntity::EntityList.push_back(&Bacchus);
	CEntity::EntityList.push_back(&Cthulhu);
	CEntity::EntityList.push_back(&Lucifer);
	CEntity::EntityList.push_back(&Venus);
	CEntity::EntityList.push_back(&Daedalus);
	CEntity::EntityList.push_back(&Quetzlcoatl);
	CEntity::EntityList.push_back(&Shiva);
	CEntity::EntityList.push_back(&Alpha);
	CEntity::EntityList.push_back(&Bravo);
	CEntity::EntityList.push_back(&Charlie);
	CEntity::EntityList.push_back(&Delta);
	CEntity::EntityList.push_back(&Echo);
	CEntity::EntityList.push_back(&Foxtrot);
	CEntity::EntityList.push_back(&Golf);
	CEntity::EntityList.push_back(&Hotel);
	CEntity::EntityList.push_back(&India);
	CEntity::EntityList.push_back(&Ramza);
	CEntity::EntityList.push_back(&Firion);
	CEntity::EntityList.push_back(&Luneth);
	CEntity::EntityList.push_back(&Cecil);
	CEntity::EntityList.push_back(&Bartz);
	CEntity::EntityList.push_back(&Terra);
	CEntity::EntityList.push_back(&Cloud);
	CEntity::EntityList.push_back(&Squall);
	CEntity::EntityList.push_back(&Zidane);
	CEntity::EntityList.push_back(&Tidus);
	CEntity::EntityList.push_back(&Mog);
	CEntity::EntityList.push_back(&Vaan);
	CEntity::EntityList.push_back(&Lightning);
	
		//init samus position if we are playing her
	if(metroid){
		Samus.X = 50;
		Samus.Y = 50;
	}

	//init simon posiiton if we are playing him
	if(castlevania){
		Simon.X = 50;
		Simon.Y = 50;
	}

	//init enemy positions
	
	//turtles
	Adrian.X = 416;
	Adrian.Y = 96;
	Barney.X = 928;
	Barney.Y = 96;
	Cynthia.X = 1600;
	Cynthia.Y = 96;
	Doug.X = 352;
	Doug.Y = 288;
	Ethan.X = 864;
	Ethan.Y = 320;
	Fernando.X = 1472;
	Fernando.Y = 288;
	Greg.X = 768;
	Greg.Y = 384;
	Heidi.X = 992;
	Heidi.Y = 416;
	Ingrid.X = 960;
	Ingrid.Y = 480;
	Justin.X = 1472;
	Justin.Y = 512;
	Kayla.X = 1472;
	Kayla.Y = 576;
	Louis.X = 96;
	Louis.Y = 1312;
	Marc.X = 896;
	Marc.Y = 1408;
	Nolan.X = 1408;
	Nolan.Y = 1472;
	Oscar.X = 448;
	Oscar.Y = 1536;
	Peter.X = 1590;
	Peter.Y = 1632;
	Quincy.X = 800;
	Quincy.Y = 1664;
	Robert.X = 992;
	Robert.Y = 1760;

	//insects
	Atlas.X = 1728;
	Atlas.Y = 128;
	Odin.X = 128;
	Odin.Y = 544;
	Bacchus.X = 416;
	Bacchus.Y = 544;
	Cthulhu.X = 1792;
	Cthulhu.Y = 544;
	Lucifer.X = 768;
	Lucifer.Y = 1504;
	Venus.X = 992;
	Venus.Y = 1536;
	Daedalus.X = 1504;
	Daedalus.Y = 1632;
	Quetzlcoatl.X = 280;
	Quetzlcoatl.Y = 1696;
	Shiva.X = 640;
	Shiva.Y = 1728;

	//skeletons
	Alpha.X = 832;
	Alpha.Y = 864;
	Bravo.X = 1088;
	Bravo.Y = 864;
	Charlie.X = 1440;
	Charlie.Y = 864;
	Delta.X = 288;
	Delta.Y = 1184;
	Echo.X = 416;
	Echo.Y = 1184;
	Foxtrot.X = 1696;
	Foxtrot.Y = 1184;
	Golf.X = 288;
	Golf.Y = 1408;
	Hotel.X = 1472;
	Hotel.Y = 1632;
	India.X = 1568;
	India.Y = 1632;

	//dogs
	Ramza.X = 1400;
	Ramza.Y =  1440;
	Firion.X = 384;
	Firion.Y = 864;
	Luneth.X = 544;
	Luneth.Y = 864;
	Cecil.X = 1600;
	Cecil.Y = 864;
	Bartz.X = 1728;
	Bartz.Y = 864;
	Terra.X = 192;
	Terra.Y = 1184;
	Cloud.X = 480;
	Cloud.Y = 1184;
	Squall.X = 800;
	Squall.Y = 1184;
	Zidane.X = 960;
	Zidane.Y = 1184;
	Tidus.X = 1088;
	Tidus.Y = 1184;
	Mog.X = 448;
	Mog.Y = 1632;
	Vaan.X = 1440;
	Vaan.Y = 1184;
	Lightning.X = 1344;
	Lightning.Y = 1440;


	//set camera to follow the player
	CCamera::CameraControl.TargetMode = TARGET_MODE_CENTER;
   	if(metroid) CCamera::CameraControl.SetTarget(&Samus.X, &Samus.Y);
	if(castlevania) CCamera::CameraControl.SetTarget(&Simon.X, &Simon.Y);

    return true;
}

//==============================================================================
