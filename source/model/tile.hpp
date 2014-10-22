#ifndef TILE_H
#define TILE_H

#include"config.hpp"

struct Tile
{
public:
	enum Type
	{
		NONE = 0,
		OCEAN,
		FRESH,
		SAND,
		GRASS,
		ROCK,
		MARSH,
		SNOW
	};
	static const int TYPES_NUM = 8;

	static bool isWater(Type t)
	{
		return t == OCEAN || t == FRESH;
	}
	
	static bool isLand(Type t)
	{
		return !isWater(t) && t != NONE;
	}
	
public:
	Type type;
	int height;

public:
	Tile()
	{
		type = NONE;
		height = 0;
	}
};

#endif // TILE_H
