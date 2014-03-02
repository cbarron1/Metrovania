//=============================================================================
#include "CMap.h"

//=============================================================================
CMap::CMap() {
	Surf_Tileset = NULL;
}

//=============================================================================
bool CMap::OnLoad(char* File) {
    TileList.clear();//clear the vector

    FILE* FileHandle = fopen(File, "r");//read in the file

    if(FileHandle == NULL) {
        return false;
    }

    for(int Y = 0;Y < MAP_HEIGHT;Y++) {
        for(int X = 0;X < MAP_WIDTH;X++) {
            CTile tempTile;

            fscanf(FileHandle, "%d:%d ", &tempTile.TileID, &tempTile.TypeID);//scan in the text map

            TileList.push_back(tempTile);//push the tile list back
        }
        fscanf(FileHandle, "\n");
    }

    fclose(FileHandle);

    return true;
}

//-----------------------------------------------------------------------------
void CMap::OnRender(SDL_Surface* Surf_Display, int MapX, int MapY) {
	if(Surf_Tileset == NULL) return;
	//find the width and height of the tiles
	int TilesetWidth  = Surf_Tileset->w / TILE_SIZE;
	int TilesetHeight = Surf_Tileset->h / TILE_SIZE;

	int ID = 0;

	for(int Y = 0;Y < MAP_HEIGHT;Y++) {
		for(int X = 0;X < MAP_WIDTH;X++) {
			if(TileList[ID].TypeID == TILE_TYPE_NONE) {//if the tile is of type none increment ID and continue
				ID++;
				continue;
			}

			int tX = MapX + (X * TILE_SIZE);//get the target X
			int tY = MapY + (Y * TILE_SIZE);//get the target Y

			int TilesetX = (TileList[ID].TileID % TilesetWidth) * TILE_SIZE;//get the X in terms of tiles
			int TilesetY = (TileList[ID].TileID / TilesetWidth) * TILE_SIZE;//get the Y in terms of tiles

			CSurface::OnDraw(Surf_Display, Surf_Tileset, tX, tY, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);//draw the tile

			ID++;//increment ID
		}
	}
}

//=============================================================================
CTile* CMap::GetTile(int X, int Y) {
    int ID = 0;

    //find the tile ID
    ID = X / TILE_SIZE;
    ID = ID + (MAP_WIDTH * (Y / TILE_SIZE));

    //make sure its valid
    if(ID < 0 || ID >= TileList.size()) {
    	return NULL;
    }

    return &TileList[ID];
}

//=============================================================================
