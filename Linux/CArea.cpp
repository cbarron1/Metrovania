//=============================================================================
#include "CArea.h"

//=============================================================================
CArea CArea::AreaControl;
//=============================================================================
//constructer
CArea::CArea() {
    AreaSize = 0;
}

//=============================================================================
//on loadi of area
bool CArea::OnLoad(char* File) {
    OnCleanup();//clean up the area to make sure nothing from  previous areas cross over

    FILE* FileHandle = fopen(File, "r");//open the file

    if(FileHandle == NULL) {//if it does not open then return
        return false;
    }

    char TilesetFile[255];//take in the tileset file

    fscanf(FileHandle, "%s\n", TilesetFile);//parse it

    if((Surf_Tileset = CSurface::OnLoad(TilesetFile)) == false) {//if it does not load then return
        fclose(FileHandle);

        return false;
    }

    fscanf(FileHandle, "%d\n", &AreaSize);//parse in the number of areas

    for(int X = 0;X < AreaSize;X++) {//for the number of areas
        for(int Y = 0;Y < AreaSize;Y++) {
            char MapFile[255];

            fscanf(FileHandle, "%s ", MapFile);//parse the map files

            CMap tempMap;
            if(tempMap.OnLoad(MapFile) == false) {//open them
                fclose(FileHandle);

                return false;
            }

            tempMap.Surf_Tileset = Surf_Tileset;//set the map to a surface

            MapList.push_back(tempMap);//push it back to a maplist
        }
        fscanf(FileHandle, "\n");
    }

    fclose(FileHandle);

    return true;
}

//-----------------------------------------------------------------------------
//render the map
void CArea::OnRender(SDL_Surface* Surf_Display, int CameraX, int CameraY) {
	//declare a few variables
	int MapWidth  = MAP_WIDTH * TILE_SIZE;
	int MapHeight = MAP_HEIGHT * TILE_SIZE;

	int FirstID = -CameraX / MapWidth;
		FirstID = FirstID + ((-CameraY / MapHeight) * AreaSize);

	for(int i = 0;i < 4;i++) {
		int ID = FirstID + ((i / 2) * AreaSize) + (i % 2);//get the ID of the tile

		if(ID < 0 || ID >= MapList.size()) continue;

		int X = ((ID % AreaSize) * MapWidth) + CameraX;//get its X location
		int Y = ((ID / AreaSize) * MapHeight) + CameraY;//get its Y location

		MapList[ID].OnRender(Surf_Display, X, Y);//render the tile
	}
}

//-----------------------------------------------------------------------------
void CArea::OnCleanup() {//on cleanup clear the maplist and free the surface
	if(Surf_Tileset) {
		SDL_FreeSurface(Surf_Tileset);
	}

	MapList.clear();
}

//=============================================================================
//get map gets the map x, y, and ID of a tile in a map
CMap* CArea::GetMap(int X, int Y) {
	int MapWidth  = MAP_WIDTH * TILE_SIZE;
	int MapHeight = MAP_HEIGHT * TILE_SIZE;

    int ID = X / MapWidth;
        ID = ID + ((Y / MapHeight) * AreaSize);

    if(ID < 0 || ID >= MapList.size()) {
        return NULL;
    }

    return &MapList[ID];
}

//-----------------------------------------------------------------------------
//get tile is called by get map after a map has been chosen to get the specific tile
CTile* CArea::GetTile(int X, int Y) {
	int MapWidth  = MAP_WIDTH * TILE_SIZE;
	int MapHeight = MAP_HEIGHT * TILE_SIZE;

	CMap* Map = GetMap(X, Y);

	if(Map == NULL) return NULL;

	X = X % MapWidth;
	Y = Y % MapHeight;

    return Map->GetTile(X, Y);
}

//=============================================================================
