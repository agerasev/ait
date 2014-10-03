#ifndef HEXLOCATOR_HPP
#define HEXLOCATOR_HPP

#include<4u/util/const.hpp>
#include<4u/util/op.hpp>
#include<4u/la/vec.hpp>

#define _floor floor

class HexLocator
{
private:
    const int
        AX, AY, AD,
        BX, BY, BD,
        CX, CY, CD;

public:
    const double tile_size; //half_width
	const int region_size;

	const vec2 tile_vertex[6];

	HexLocator(const double ts, const int rs) :

		AX( 1 ),        AY( -(3*rs + 1) ),  AD( rs - (3*rs + 1)*(rs + 1) ),
		BX( 3*rs + 2 ), BY( 1 ),            BD( -(3*rs + 2)*(rs + 1) + (2*rs + 1) ),
		CX( 3*rs + 1 ), CY( 3*rs + 2 ),     CD( -(3*rs + 1)*(rs + 1) + (3*rs + 2)*(2*rs + 1) ),

		tile_size(ts), region_size(rs),

		tile_vertex{
			vec2(   0.0,        ts      ),
			vec2(   ts*S32,     0.5*ts  ),
			vec2(   ts*S32,     -0.5*ts ),
			vec2(   0.0,        -ts     ),
			vec2(   -ts*S32,    -0.5*ts ),
			vec2(   -ts*S32,    0.5*ts  )
		}

    {

    }

	inline ivec2 getTileByPos(const vec2 &p) const
    {
		int a = _floor(p.x()/(S32*tile_size));
		int b = _floor((p.x()/S3 + p.y())/tile_size);
		int c = _floor((-p.x()/S3 + p.y())/tile_size);
        return ivec2(_div(a - c + 1, 3),_div(b + c + 2, 3));
    }
	inline ivec2 getRegionByTile(const ivec2 &p) const
    {
        int A = _div(AX*p.x() + AY*p.y(), AD);
        int B = _div(BX*p.x() + BY*p.y(), BD);
        int C = _div(CX*p.x() + CY*p.y(), CD);
        return ivec2(_div(C-B+1,3),_div(A+B+2,3));
    }
	inline ivec2 getRegionCenterTile(const ivec2 &reg) const
    {
		return ivec2(reg.x()*region_size - reg.y()*(region_size+1), reg.x()*(region_size+1) + reg.y()*(2*region_size+1));
    }
	inline vec2 getTileCenterPos(const ivec2 &pos) const
    {
		return vec2(S3*tile_size*(pos.x() + 0.5*pos.y()),1.5*tile_size*pos.y());
    }
};

#endif // HEXLOCATOR_HPP
