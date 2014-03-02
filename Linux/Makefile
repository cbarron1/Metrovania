
CC=g++

# Objects
OBJECTS=CAnimation.o CApp.o CApp_OnCleanup.o CApp_OnEvent.o CApp_OnInit.o CApp_OnLoop.o CApp_OnRender.o CArea.o CCamera.o CEntity.o CEvent.o CFPS.o CMap.o CSamus.o CSurface.o CTile.o CEntityCol.o CTurtle.o CInsect.o CSimon.o CApp_OnTitle.o CApp_OnGameOver.o CShot.o CExplode.o CSkeleton.o CWhip.o CSword.o CDog.o CSoundBank.o CApp_OnVictory.o CApp_OnPosReset.o

# Compiler flags
CPPFLAGS=-Wall -g `sdl-config --cflags`

# Linker flags
LDFLAGS=`sdl-config --libs` -lSDL -lSDL_image -lSDL_mixer

main: CApp.cpp
	$(CC) $(CPPFLAGS) -c CAnimation.cpp CApp.cpp CApp_OnCleanup.cpp CApp_OnEvent.cpp CApp_OnInit.cpp CApp_OnLoop.cpp CApp_OnRender.cpp CArea.cpp CCamera.cpp CEntity.cpp CEvent.cpp CFPS.cpp CMap.cpp CSamus.cpp CSurface.cpp CTile.cpp CEntityCol.cpp CTurtle.cpp CInsect.cpp CSimon.cpp CApp_OnTitle.cpp CApp_OnGameOver.cpp CShot.cpp CExplode.cpp CSkeleton.cpp CWhip.cpp CSword.cpp  CDog.cpp CSoundBank.cpp CApp_OnVictory.cpp CApp_OnPosReset.cpp
	$(CC) $(OBJECTS) $(CPPFLAGS) $(LDFLAGS) -o metrovania

# cleanup
clean:
	rm -rf $(OBJECTS) *~

