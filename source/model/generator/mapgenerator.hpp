#ifndef MAPGENERATOR_HPP
#define MAPGENERATOR_HPP

#include<functional>
#include<vector>

#include<model/map.hpp>

#include<4u/random/contrand.hpp>

#include<ctime>

class MapGenerator
{
private:
	unsigned int seed;
	ContRandInt rand;

	
	const float life_density_factor = 0.36;
	struct LifeState
	{
	public:
		bool alive = false;
		bool pre_alive = false;
		bool track = false;
	};
	
	/* Params */
	const float grow_factor = 4.0;
	struct RegionParams
	{
	public:
		ivec2 pos;
		bool edge = false;
	};

public:
	MapGenerator(unsigned int /*s*/) :
		seed(time(NULL)), rand(seed)
	{

	}

	void generate(MapWriterHandle &map_handle)
	{
		genSoil(map_handle);
		genMoisture(map_handle);
		genVegetation(map_handle);
	}
	
	void step(MapWriterHandle &map_handle)
	{
		
	}
	
	void copyToMap(MapWriterHandle &map_handle, HexArray<LifeState> &life)
	{
		map_handle.write([&life](MapWriter &_map){
			MapWriter &map = _map; // because qtcreator can't see _map
			
			/* Copy life to map */
			for(auto i = life.begin(); i != life.end(); ++i)
			{
				Tile::Type type = Tile::OCEAN;
				if((*i).alive)
				{
					type = Tile::SAND;
				}
				else if((*i).track)
				{
					type = Tile::GRASS;
				}
				
				map.getRegion(~i)->type = type;
			}
			
			/* Apply to tiles */
			for(Region *reg : map)
			{
				for(Tile &til : *reg)
				{
					til.type = reg->type;
				}
			}
		});
	}

	void genSoil(MapWriterHandle &map_handle)
	{
		HexArray<LifeState> life(Map::SIZE);
		
		/* Generate life */
		for(int i = 0; i < life_density_factor*Map::SIZE*Map::SIZE; ++i)
		{
			ivec2 p = random<(3*Map::SIZE)/4>();
			life.get(p).alive = true;
			life.get(p).track = true;
		}
		
		/* Life step */
		for(int j = 0; j < 16; ++j)
		{
			/* Copy previous state */
			for(LifeState &ls : life)
			{
				ls.pre_alive = ls.alive;
				ls.track = ls.track || ls.alive;
				ls.alive = false;
			}
			
			/* Life step */
			for(auto i = life.begin(); i != life.end(); ++i)
			{
				int count = 0;
				Map::Locator::getNeighbours(~i,[&count,&life](const ivec2 &p){
					if(life(p).pre_alive)
					{
						++count;
					}
				});
				if(i->pre_alive)
				{
					i->alive = (count == 3);
				}
				else
				{
					i->alive = (count == 2);
				}
			}
		}
		
		copyToMap(map_handle,life);
	}

	void genMoisture(MapWriterHandle &)
	{

	}

	void genVegetation(MapWriterHandle &)
	{

	}

	template <int N>
	ivec2 random()
	{
		ivec2 point;
		point.x() = rand.get()%(2*N + 1) - N;
		point.y() = rand.get()%(2*N + 1) - N;
		if(abs(point.x() + point.y()) > N)
		{
			return random<N>();
			/* 1/3 longer than true continuous */
		}
		return point;
	}
};

#endif // MAPGENERATOR_HPP
