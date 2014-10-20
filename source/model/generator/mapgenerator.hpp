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

	
	const float life_density_factor = 0.32;
	struct LifeState
	{
	public:
		bool alive = false;
		bool pre_alive = false;
		bool track = false;
	};
	
	HexArray<LifeState> life;
	
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
		seed(time(NULL)), rand(seed),
		life(Map::SIZE)
	{

	}

	void generate(MapWriterHandle &map_handle)
	{
		/* Generate life */
		for(int i = 0; i < life_density_factor*Map::SIZE*Map::SIZE; ++i)
		{
			ivec2 p = random<(3*Map::SIZE)/4>();
			life.get(p).alive = true;
			life.get(p).track = true;
		}
		
		copyToMap(map_handle);
		
		/*
		genSoil(map_handle);
		genMoisture(map_handle);
		genVegetation(map_handle);
		*/
	}
	
	void step(MapWriterHandle &map_handle)
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
			Map::Locator::getNeighbours(~i,[&count,this](const ivec2 &p){
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
		
		copyToMap(map_handle);
	}
	
	void copyToMap(MapWriterHandle &map_handle)
	{
		map_handle.write([this](MapWriter &_map){
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
		map_handle.write([this](MapWriter &_map){
			MapWriter &map = _map; // because qtcreator can't see _map
			HexArray<RegionParams> params(Map::SIZE);
			for(auto i = params.begin(); i != params.end(); ++i)
			{
				(*i).pos = ~i;
			}

			/* Flood map */
			for(Region *reg : map)
			{
				reg->type = Tile::OCEAN;
			}

			/* Drop seed */
			int edge_num = 0;
			map.getRegion(nullivec2)->type = Tile::SAND;
			Map::Locator::getNeighbours(nullivec2,[&params,&map,&edge_num](const ivec2 &p){
				if(map.getRegion(p)->type == Tile::OCEAN)
				{
					params.get(p).edge = true;
					++edge_num;
				}
			});

			/* Grow soil */
			for(int i = 0; i < grow_factor*Map::SIZE*Map::SIZE; ++i)
			{
				/* Counting points */
				int j = 0;
				int r = rand.get()%edge_num;
				for(RegionParams &p : params)
				{
					if(p.edge)
					{
						if(j == r)
						{
							map.getRegion(p.pos)->type = Tile::SAND;
							p.edge = false;
							--edge_num;
							Map::Locator::getNeighbours(p.pos,[&params,&map,&edge_num](const ivec2 &p){
								if(map.getRegion(p)->type == Tile::OCEAN)
								{
									params.get(p).edge = true;
									++edge_num;
								}
							});
							break;
						}
						++j;
					}
				}
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
