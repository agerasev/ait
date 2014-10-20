#ifndef TILE_H
#define TILE_H

struct Tile
{
public:
	enum Type
	{
		NONE = 0,
		OCEAN,
		SHELF,
		SAND,
		GRASS
	};

public:
	Type type;
	float height;

public:
	Tile()
	{
		type = NONE;
		height = 0.0f;
	}
};

#endif // TILE_H
