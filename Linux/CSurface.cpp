//==============================================================================
#include "CSurface.h"

//==============================================================================
CSurface::CSurface() {
}

//==============================================================================
SDL_Surface* CSurface::OnLoad(char* File) {
	SDL_Surface* Surf_Temp = NULL;
	SDL_Surface* Surf_Return = NULL;

	if((Surf_Temp = IMG_Load(File)) == NULL) {//if it dosent load then exit
		return NULL;
	}

	Surf_Return = SDL_DisplayFormatAlpha(Surf_Temp);//make the surface that is returned
	SDL_FreeSurface(Surf_Temp);//free the temp surface

	return Surf_Return;//return the right sruface
}

//==============================================================================
bool CSurface::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y) {
	if(Surf_Dest == NULL || Surf_Src == NULL) {//if the source or the destination dont exist then exit
		return false;
	}

	SDL_Rect DestR;//make a rectangle for the destination

	DestR.x = X;//set it equal to the X and Y desired
	DestR.y = Y;

	SDL_BlitSurface(Surf_Src, NULL, Surf_Dest, &DestR);//blit it

	return true;
}

//------------------------------------------------------------------------------
bool CSurface::OnDraw(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y, int X2, int Y2, int W, int H) {
	if(Surf_Dest == NULL || Surf_Src == NULL) {//everything is the same except its for only parts of the source
		return false;
	}

	SDL_Rect DestR;

	DestR.x = X;
	DestR.y = Y;

	SDL_Rect SrcR;//declare a source rectrangle

	SrcR.x = X2;//set its X and Y and width and height
	SrcR.y = Y2;
	SrcR.w = W;
	SrcR.h = H;

	SDL_BlitSurface(Surf_Src, &SrcR, Surf_Dest, &DestR);//blit it

	return true;
}

//------------------------------------------------------------------------------
bool CSurface::Transparent(SDL_Surface* Surf_Dest, int R, int G, int B) {
	if(Surf_Dest == NULL) {
		return false;
	}

	SDL_SetColorKey(Surf_Dest, SDL_SRCCOLORKEY | SDL_RLEACCEL, SDL_MapRGB(Surf_Dest->format, R, G, B));//make it transparent

	return true;
}

//==============================================================================
