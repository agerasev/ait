#ifndef REGION_H
#define REGION_H

#include<4u/la/vec.hpp>

#include"hex/hexarray.hpp"
#include"hex/hexlocator.hpp"

#include"tile.hpp"

class Region
{
public:
	static const int SIZE = 0;
	typedef HexLocator<SIZE> Locator;

	Tile::Type type;
	float height;

private:
	HexArray<Tile> tiles;

public:
	Region() :
		tiles(SIZE)
	{

	}
	Tile &getTile(const ivec2 &pos)
	{
		return tiles(pos);
	}
	const Tile &getTile(const ivec2 &pos) const
	{
		return tiles(pos);
	}
	HexArray<Tile>::const_iterator begin() const
	{
		return tiles.begin();
	}
	HexArray<Tile>::const_iterator end() const
	{
		return tiles.end();
	}
	HexArray<Tile>::iterator begin()
	{
		return tiles.begin();
	}
	HexArray<Tile>::iterator end()
	{
		return tiles.end();
	}
};

#endif // REGION_H
