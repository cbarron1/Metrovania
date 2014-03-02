//==============================================================================
#include "CApp.h"

//constructer
//==============================================================================
CApp::CApp() {
    Surf_Display = NULL;

    Running = true;
    
    waitingCounter = 0;
}

//main program loop, puts all the pieces together
//------------------------------------------------------------------------------
int CApp::OnExecute() {
    if(OnInit() == false) {//initialize everything. if something fails exit
        return -1;
    }

    SDL_Event Event;
    
    Samus.X = 50;
	Samus.Y = 50;
	
	count = 0;
    while(Running) {//while the game is running
        while(SDL_PollEvent(&Event)) {
            OnEvent(&Event);//get inputs and pass into OnEvent
        }

        OnLoop();//update all the data
        if (!Running) break;//if the game is not running break out of the loop
        OnRender();//render all images onto screen
    }

    OnCleanup();//once game stops running clean everything up

    return 0;
}

//creates a CApp program and runs onExecute();
//==============================================================================
int main(int argc, char* argv[]) {
    CApp theApp;
    return theApp.OnExecute();
}

//==============================================================================
