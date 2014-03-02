//==============================================================================
// Surface functions
//==============================================================================
#ifndef _CSURFACE_H_
    #define _CSURFACE_H_

#include <SDL.h>
#include <SDL_image.h>

//==============================================================================
class CSurface {
	public:
		CSurface();//constructer

	public:
		static SDL_Surface* OnLoad(char* File);//load the surface

		static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y);//draw the surface

		static bool OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y, int X2, int Y2, int W, int H);//draw parts of the surface

		static bool Transparent(SDL_Surface* Surf_Dest, int R, int G, int B);//make it transperent
};

//==============================================================================

#endif
