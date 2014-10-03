#ifndef MAP_HPP
#define MAP_HPP

#include<functional>

#include<4u/la/vec.hpp>
#include<4u/thread/mutex.hpp>

#include"hex/hexarray.hpp"
#include"hex/hexlocator.hpp"

#include"region.hpp"

class Map;

class MapReader;
class MapWriter;

/* Interfaces */

class MapReaderHandle
{
public:
	virtual void read(std::function<void(MapReader&)>) = 0;
};

class MapWriterHandle
{
public:
	virtual void write(std::function<void(MapWriter&)>) = 0;
};

class MapReader : public MapReaderHandle
{
public:
	/* Iteration */
	virtual HexArray<Region*>::const_iterator begin() const = 0;
	virtual HexArray<Region*>::const_iterator end() const = 0;
	/* Direct access */
	virtual const Region *getRegion(const ivec2 &rpos) const = 0;
	virtual const Tile &getTile(const ivec2 &pos) const = 0;
	/* Size */
	virtual int getSize() const = 0;
};

class MapWriter : public MapReader, public MapWriterHandle
{
public:
	/* Iteration */
	virtual HexArray<Region*>::iterator begin() = 0;
	virtual HexArray<Region*>::iterator end() = 0;
	/* Direct access */
	virtual Region *getRegion(const ivec2 &rpos) = 0;
	virtual Tile &getTile(const ivec2 &pos) = 0;
};

/* Implementation */

class Map : public MapWriter
{
private:
	const int map_size;
	const int reg_size;
	HexArray<Region*> regions;
	HexLocator locator;
	Mutex mutex; /* TODO: Replce Mutex with RWCond */

public:
	Map(int ms, int rs) :
		map_size(ms),
		reg_size(rs),
		regions(map_size),
		locator(1.0,map_size)
	{
		for(Region *&reg : regions)
		{
			reg = new Region(reg_size);
		}
	}

	virtual ~Map()
	{
		for(Region *&reg : regions)
		{
			delete reg;
			reg = nullptr;
		}
	}

	/* MapReaderHandle */
	virtual void read(std::function<void(MapReader&)> func) override
	{
		mutex.lock();
		{
			func(static_cast<MapReader&>(*this));
		}
		mutex.unlock();
	}
	/* MapWriterHandle */
	virtual void write(std::function<void(MapWriter&)> func) override
	{
		mutex.lock();
		{
			func(static_cast<MapWriter&>(*this));
		}
		mutex.unlock();
	}

	/* MapReader */
	virtual HexArray<Region*>::const_iterator begin() const override
	{
		return regions.begin();
	}
	virtual HexArray<Region*>::const_iterator end() const override
	{
		return regions.end();
	}
	virtual const Region *getRegion(const ivec2 &rpos) const override
	{
		return regions(rpos);
	}
	virtual const Tile &getTile(const ivec2 &pos) const override
	{
		ivec2 rpos = locator.getRegionByTile(pos);
		ivec2 tpos = pos - locator.getRegionCenterTile(rpos);
		return getRegion(rpos)->getTile(tpos);
	}
	virtual int getSize() const override
	{
		return map_size;
	}

	/* MapWriter */
	virtual HexArray<Region*>::iterator begin() override
	{
		return regions.begin();
	}
	virtual HexArray<Region*>::iterator end() override
	{
		return regions.end();
	}
	virtual Region *getRegion(const ivec2 &rpos) override
	{
		return regions(rpos);
	}
	virtual Tile &getTile(const ivec2 &pos) override
	{
		ivec2 rpos = locator.getRegionByTile(pos);
		ivec2 tpos = pos - locator.getRegionCenterTile(rpos);
		return getRegion(rpos)->getTile(tpos);
	}
};

#endif // MAP_HPP
