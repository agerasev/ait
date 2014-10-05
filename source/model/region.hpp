#ifndef REGION_H
#define REGION_H

#include<4u/la/vec.hpp>

#include"hex/hexarray.hpp"
#include"hex/hexlocator.hpp"

#include"tile.hpp"

class Region
{
private:
	HexArray<Tile> tiles;
	HexLocator locator;
	const int size;
public:
	Region(int s) :
		tiles(s),
		locator(1.0,s),
		size(s)
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
	int getSize() const
	{
		return size;
	}
	const HexLocator &getLocator() const
	{
		return locator;
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
