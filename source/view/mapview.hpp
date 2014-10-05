#ifndef MAPVIEW_HPP
#define MAPVIEW_HPP

#include<vector>

#include<model/map.hpp>

#include<4u/gl/vertexbuffer.hpp>

#include"regionview.hpp"

class MapView
{
private:
	MapReaderHandle &map_handle;
	HexArray<RegionView*> *regions = nullptr;

public:
	MapView(MapReaderHandle &mh) :
		map_handle(mh)
	{
		map_handle.read([this](MapReader &map){
			regions = new HexArray<RegionView*>(map.getSize());
			for(auto i = map.begin(); i != map.end(); ++i)
			{
				regions->get(~i) = new RegionView(*i);
			}
		});
	}
	HexArray<RegionView*>::iterator begin()
	{
		return regions->begin();
	}
	HexArray<RegionView*>::iterator end()
	{
		return regions->end();
	}
	HexArray<RegionView*>::const_iterator begin() const
	{
		return static_cast<const HexArray<RegionView*> * const>(regions)->begin();
	}
	HexArray<RegionView*>::const_iterator end() const
	{
		return static_cast<const HexArray<RegionView*> * const>(regions)->end();
	}
};

#endif // MAPVIEW_HPP
