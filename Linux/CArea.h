//=============================================================================
#ifndef _CAREA_H_
    #define _CAREA_H_

#define _CRT_SECURE_NO_DEPRECATE
#include "CMap.h"

//=============================================================================
class CArea {
    public:
        static CArea            AreaControl;//make area a static

    public:
        std::vector<CMap>       MapList;//a vector of maps

    private:
        int                     AreaSize;//size of area

        SDL_Surface*			Surf_Tileset;//surface on tileset

    public:
        CArea();//constructer

        bool    OnLoad(char* File);//load the area file

        void    OnRender(SDL_Surface* Surf_Display, int CameraX, int CameraY);//render the area

        void    OnCleanup();//clear the area

    public:
        CMap*	GetMap(int X, int Y);//get the specific map in area

		CTile*	GetTile(int X, int Y);//get the specific tile in area
};

//=============================================================================

#endif

