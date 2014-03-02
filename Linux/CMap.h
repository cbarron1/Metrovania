	//==============================================================================
#ifndef _CMAP_H_
    #define _CMAP_H_

#define _CRT_SECURE_NO_DEPRECATE
#include <SDL.h>
#include <vector>

#include "CTile.h"
#include "CSurface.h"

//==============================================================================
class CMap {
	public:
		SDL_Surface*			Surf_Tileset;//surface of the tileset source

	private:
		std::vector<CTile>      TileList;//vector of tiles in map

	public:
		CMap();//constructer

	public:
		bool OnLoad(char* File);//load in the file for the map

		void OnRender(SDL_Surface* Surf_Display, int MapX, int MapY);//render the map

    public:
        CTile*	GetTile(int X, int Y);//get the tile ID at the X and Y location
};

//==============================================================================

#endif
