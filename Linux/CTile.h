//==============================================================================
#ifndef _CTILE_H_
	#define _CTILE_H_

#include "Define.h"

//enumeration for the different tile types
//==============================================================================
enum {
    TILE_TYPE_NONE = 0,

    TILE_TYPE_NORMAL,//background
    TILE_TYPE_BLOCK,//foreground
    TILE_TYPE_DIAGONAL,//this one dident work out and is actually never used
    TILE_TYPE_DAMAGE//damaging
};

//==============================================================================
class CTile {
    public:
        int     TileID;//tile has 2 variables its ID and its type
        int     TypeID;

    public:
        CTile();//constructer
};

//==============================================================================
#endif
