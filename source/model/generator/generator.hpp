#ifndef MAPGENERATOR_HPP
#define MAPGENERATOR_HPP

#include<functional>
#include<vector>

#include<model/map.hpp>

#include<ctime>

#include"landscape.hpp"

class Generator
{
private:
	unsigned int seed;
	
	/* Params */
	const float grow_factor = 4.0;
	struct RegionParams
	{
	public:
		ivec2 pos;
		bool edge = false;
	};

public:
	Generator(unsigned int s) :
		seed(s)
	{

	}

	void generate(MapWriterHandle &map_handle)
	{
		Landscape(seed).generate(map_handle);
	}
	
	void step(MapWriterHandle &map_handle)
	{
		seed = time(NULL);
		generate(map_handle);
	}
};

#endif // MAPGENERATOR_HPP
