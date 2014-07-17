#ifndef LAND_H
#define LAND_H

#include<hextiling/hexarray.hpp>
#include<hextiling/hexlocator.hpp>

#include"tile.h"

class Land
{
private:
	HexArray<Tile> array;
public:
	Land() {

	}
};

#endif // LAND_H
