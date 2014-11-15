#ifndef LANDSCAPE_HPP
#define LANDSCAPE_HPP

#include<4u/random/contrand.hpp>
#include<4u/util/op.hpp>

#include<model/map.hpp>
#include"config.hpp"

#include<queue>

#include<cmath>

class Landscape
{
private:
	unsigned int seed;
	ContRandInt rand;
	
	/* Life */
    const float life_density_factor = gconfig::LAND_FREQUENCY;
	struct LifeState
	{
	public:
		bool alive = false;
		bool pre_alive = false;
		bool track = false;
	};
	
	struct DistanceState
	{
	public:
		bool mark = false;
		int dist = 0;
		bool open = false;
	};
	
public:
	Landscape(unsigned int s) :
		seed(s), rand(seed)
	{
		
	}

	void generate(MapWriterHandle &map_handle)
	{
		genLand(map_handle);
	}
	
	void genLand(MapWriterHandle &map_handle)
	{
		HexArray<LifeState,Map::SIZE> life;
		
		/* Generate life */
		for(int i = 0; i < life_density_factor*Map::SIZE*Map::SIZE; ++i)
		{
            ivec2 p = random<static_cast<int>(gconfig::LAND_RADIUS*Map::SIZE)>();
			life.get(p).alive = true;
			life.get(p).track = true;
		}
		
		/* Life step */
        for(int j = 0; j < gconfig::GAME_OF_LIFE_ITERS; ++j)
		{
			/* Copy previous state */
			for(LifeState &ls : life)
			{
				ls.pre_alive = ls.alive;
				ls.track = ls.track || ls.alive;
				ls.alive = false;
			}
			
			/* Life step */
			life.for_each([&](LifeState &ls, const ivec2 &p) 
			{
				int count = 0;
				Map::Locator::getNeighbours(p,[&count,&life](const ivec2 &np)
				{
					if(life(np).pre_alive)
					{
						++count;
					}
				});
				if(ls.pre_alive)
				{
					ls.alive = (count == 3);
				}
				else
				{
					ls.alive = (count == 2);
				}
			});
		}
		/* Remove land from map borders */
		life.for_each([&](LifeState &ls, const ivec2 &p)
		{
			if(_abs(p.x()) == Map::SIZE || _abs(p.y()) == Map::SIZE || _abs(p.x() + p.y()) == Map::SIZE)
			{
				ls.track = false;
			}
		});
		
		copyToMap(map_handle,life);
		
		HexArray<DistanceState,Map::SIZE> dist;
		/* Computes distance from the coastline */
		std::queue<ivec2> queue;
		/* Land */
		dist.for_each([&](DistanceState &d, const ivec2 &p)
		{
			if(_abs(p.x()) == Map::SIZE || _abs(p.y()) == Map::SIZE || _abs(p.x() + p.y()) == Map::SIZE)
			{
				queue.push(p);
				d.mark = true;
			}
		});
		while(!queue.empty())
		{
			ivec2 p = queue.front();
			queue.pop();
			Map::Locator::getNeighbours(p,[&](const ivec2 &np)
			{
				if(!dist(np).mark)
				{
					dist(np).dist = dist(p).dist + life(np).track;
					dist(np).mark = true;
					queue.push(np);
				}
				else if(dist(np).dist > dist(p).dist + life(np).track)
				{
					dist(np).dist = dist(p).dist + life(np).track;
					queue.push(np);
				}
			});
		}
		/* Water */
		dist.for_each([&queue,&life](DistanceState &d, const ivec2 &p)
		{
			d.mark = false;
			if(!life(p).track)
			{
				int ncount = 0;
				Map::Locator::getNeighbours(p,[&](const ivec2 &np)
				{
					if(life(np).track)
					{
						++ncount;
					}
				});
				if(ncount > 0)
				{
					queue.push(p);
					d.mark = true;
				}
			}
		});
		while(!queue.empty())
		{
			ivec2 p = queue.front();
			queue.pop();
			Map::Locator::getNeighbours(p,[&](const ivec2 &np)
			{
				if(!life(np).track)
				{
					if(!dist(np).mark)
					{
						dist(np).dist = dist(p).dist - 1;
						dist(np).mark = true;
						queue.push(np);
					}
					else if(dist(np).dist < dist(p).dist - 1)
					{
						dist(np).dist = dist(p).dist - 1;
						queue.push(np);
					}
				}
			});
		}
		
		/* Salt and fresh water */
		dist.for_each([&](DistanceState &d, const ivec2 &p)
		{
			d.mark = false;
			if(_abs(p.x()) == Map::SIZE || _abs(p.y()) == Map::SIZE || _abs(p.x() + p.y()) == Map::SIZE)
			{
				queue.push(p);
				d.open = true;
				d.mark = true;
			}
		});
		while(!queue.empty())
		{
			ivec2 p = queue.front();
			queue.pop();
			Map::Locator::getNeighbours(p,[&](const ivec2 &np)
			{
				if(!dist(np).mark && !life(np).track)
				{
					dist(np).open = dist(p).open;
					dist(np).mark = true;
					queue.push(np);
				}
			});
		}
		
		/* Elevates regions */
		copyToMap(map_handle,dist);
		
		applyToTiles(map_handle);
	}
	
	void copyToMap(MapWriterHandle &map_handle, HexArray<LifeState,Map::SIZE> &life)
	{
		map_handle.write([&](MapWriter &_map){
			MapWriter &map = _map; // because qtcreator can't see _map
			
			/* Copy life to map */
			life.for_each([&](LifeState &ls, const ivec2 &p)
			{
				Tile::Type type = Tile::OCEAN;
				if(ls.track)
				{
					type = Tile::SAND;
				}
				
				map.getRegion(p)->type = type;
			});
		});
	}
	
	void copyToMap(MapWriterHandle &map_handle, HexArray<DistanceState,Map::SIZE> &dist)
	{
		map_handle.write([&](MapWriter &_map){
			MapWriter &map = _map; // because qtcreator can't see _map
			dist.for_each([&](DistanceState &ds, const ivec2 &p)
			{
				Region *reg = map.getRegion(p);
                reg->height = ds.dist/(Map::SIZE*gconfig::LAND_RADIUS/2)*gconfig::LAND_MAX_HEIGHT;
				if(reg->type == Tile::OCEAN && !ds.open)
				{
					reg->type = Tile::FRESH;
				}
				if(Tile::isLand(reg->type))
				{
                    if(ds.dist >= gconfig::GRASS_THRESHOLD)
					{
						reg->type = Tile::GRASS;
					}
					/*
                    if(reg->height >= gconfig::SNOW_THRESHOLD)
					{
						reg->type = Tile::SNOW;
					}
					*/
				}
				else if(Tile::isWater(reg->type))
				{
                    if(reg->height < gconfig::OCEAN_DEPTH)
					{
                        reg->height = gconfig::OCEAN_DEPTH;
					}
				}
			});
		});
	}
	
	void applyToTiles(MapWriterHandle &map_handle)
	{
        typedef HexLocator<gconfig::BLUR_RADIUS> Brush;
        HexArray<double,gconfig::BLUR_RADIUS> brush;
		double norm = 0.0;
		brush.for_each([&](double &weight, const ivec2 &dp)
		{
            norm += (weight = exp(gconfig::BLUR_FACTOR*_sqr(Region::Locator::getTileCenterPos(dp))));
		});
		brush.for_each([&](double &weight, const ivec2 &)
		{
			weight /= norm;
		});
		map_handle.write([&](MapWriter &_map)
		{
			MapWriter &map = _map; // because qtcreator can't see _map
			for(auto i = map.begin(); i != map.end(); ++i)
			{
				ivec2 r = ~i;
				for(auto j = (*i)->begin(); j != (*i)->end(); ++j)
				{
					ivec2 t = ~j + Region::Locator::getRegionCenterTile(r);
					double rating[Tile::TYPES_NUM] = {0};
					double height = 0;
					Tile &dst = *j;
					brush.for_each([&](double &weight, const ivec2 &dp)
					{
						ivec2 np = dp + t;
						ivec2 nr = Region::Locator::getRegionByTile(np);
						Region *src = nullptr;
						if(Map::Locator::isInside(nr))
						{
							src = map.getRegion(nr);
						}
						else
						{
							src = *i;
						}
						rating[src->type] += weight;
						height += weight*src->height;
					});
					dst.height = height;
					Tile::Type type = Tile::NONE;
					double max_type_weight = 0.0;
					for(int i = 0; i < Tile::TYPES_NUM; ++i)
					{
						if(rating[i] > max_type_weight)
						{
							max_type_weight = rating[i];
							type = static_cast<Tile::Type>(i);
						}
					}
					dst.type = type;
				}
			}
		});
	}
	
	template <int N>
	ivec2 random()
	{
		ivec2 point;
		point.x() = rand.get()%(2*N + 1) - N;
		point.y() = rand.get()%(2*N + 1) - N;
		if(_abs(point.x() + point.y()) > N)
		{
			return random<N>();
			/* 1/3 longer than true continuous */
		}
		return point;
	}
};

#endif // LANDSCAPE_HPP
