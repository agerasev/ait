#ifndef REGION_H
#define REGION_H

#include<4u/la/vec.hpp>

#include"hex/hexarray.hpp"
#include"hex/hexlocator.hpp"

#include"tile.hpp"

#include<model/config.hpp>

class Region
{
public:
	static const int SIZE = config::REGION_SIZE;
	typedef HexLocator<SIZE> Locator;

	Tile::Type type = Tile::NONE;
	int height = 0;

private:
	HexArray<Tile,SIZE> tiles;

public:
	Region()
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
	HexArray<Tile,SIZE>::const_iterator begin() const
	{
		return tiles.begin();
	}
	HexArray<Tile,SIZE>::const_iterator end() const
	{
		return tiles.end();
	}
	HexArray<Tile,SIZE>::iterator begin()
	{
		return tiles.begin();
	}
	HexArray<Tile,SIZE>::iterator end()
	{
		return tiles.end();
	}
};

#endif // REGION_H
