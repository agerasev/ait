#ifndef HEXLOCATOR_HPP
#define HEXLOCATOR_HPP

#include<functional>

#include<4u/util/const.hpp>
#include<4u/util/op.hpp>
#include<4u/la/vec.hpp>

#include<model/config.hpp>

#define _floor floor

static const vec2 __tile_vertex[6] = {
	vec2(0.0,1.0),
	vec2(S32,0.5),
	vec2(S32,-0.5),
	vec2(0.0,-1.0),
	vec2(-S32,-0.5),
	vec2(-S32,0.5)
};

static const ivec2 __neighbours[6] = {
	ivec2(1,0),
	ivec2(0,1),
	ivec2(-1,1),
	ivec2(-1,0),
	ivec2(0,-1),
	ivec2(1,-1)
};

template <int N>
class HexLocator
{
private:
	static const int
		AX = 1,	      AY = -(3*N + 1), AD = N - (3*N + 1)*(N + 1),
		BX = 3*N + 2, BY = 1,          BD = -(3*N + 2)*(N + 1) + (2*N + 1),
		CX = 3*N + 1, CY = 3*N + 2,    CD = -(3*N + 1)*(N + 1) + (3*N + 2)*(2*N + 1);

private:
	HexLocator() {}

public:
	inline static ivec2 getTileByPos(const vec2 &p, double tile_size = config::TILE_SIZE)
    {
		int a = _floor(p.x()/(S32*tile_size));
		int b = _floor((p.x()/S3 + p.y())/tile_size);
		int c = _floor((-p.x()/S3 + p.y())/tile_size);
        return ivec2(_div(a - c + 1, 3),_div(b + c + 2, 3));
    }
	inline static ivec2 getRegionByTile(const ivec2 &p)
    {
        int A = _div(AX*p.x() + AY*p.y(), N - (3*N + 1)*(N + 1));
        int B = _div(BX*p.x() + BY*p.y(), -(3*N + 2)*(N + 1) + (2*N + 1));
        int C = _div(CX*p.x() + CY*p.y(), -(3*N + 1)*(N + 1) + (3*N + 2)*(2*N + 1));
        return ivec2(_div(C-B+1,3),_div(A+B+2,3));
    }
	inline static ivec2 getRegionCenterTile(const ivec2 &reg)
    {
		return ivec2(reg.x()*N - reg.y()*(N+1), reg.x()*(N+1) + reg.y()*(2*N+1));
    }
	inline static vec2 getTileCenterPos(const ivec2 &pos, double tile_size = config::TILE_SIZE)
    {
		return vec2(S3*tile_size*(pos.x() + 0.5*pos.y()),1.5*tile_size*pos.y());
    }
	inline static vec2 getVertex(int n, double tile_size = config::TILE_SIZE)
	{
		return __tile_vertex[n]*tile_size;
	}
	inline static void getNeighbours(ivec2 p, std::function<void(const ivec2 &)> h)
	{
		unsigned char mask = 0x3f;
		mask &= ~((p.x() <= -N)*(0x0c));
		mask &= ~((p.x() >=  N)*(0x21));
		mask &= ~((p.y() <= -N)*(0x30));
		mask &= ~((p.y() >=  N)*(0x06));
		mask &= ~((p.x() + p.y() <= -N)*(0x18));
		mask &= ~((p.x() + p.y() >=  N)*(0x03));
		for(int i = 0; i < 6; ++i)
		{
			if(mask&(1<<i))
			{
				h(p + __neighbours[i]);
			}
		}
	}
};

#endif // HEXLOCATOR_HPP
