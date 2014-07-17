#ifndef HEXLOCATOR_HPP
#define HEXLOCATOR_HPP

#include<asarone/util/const.hpp>
#include<asarone/util/op.hpp>
#include<asarone/linalg/vec.hpp>

class HexLocator
{
private:

    const int
        AX, AY, AD,
        BX, BY, BD,
        CX, CY, CD;

public:

    const double tile_size; //half_width
    const int land_size;

    const vec2 tile_vertex[6];

    HexLocator(const double ts, const int ls) :

        btile_size(ts), land_size(ls),

        AX( 1 ),        AY( -(3*ls + 1) ),  AD( ls - (3*ls + 1)*(ls + 1) ),
        BX( 3*ls + 2 ), BY( 1 ),            BD( -(3*ls + 2)*(ls + 1) + (2*ls + 1) ),
        CX( 3*ls + 1 ), CY( 3*ls + 2 ),     CD( -(3*ls + 1)*(ls + 1) + (3*ls + 2)*(2*ls + 1) ),

        tile_vert({
            vec2(   0.0,        ts      ),
            vec2(   ts*S32,     0.5*ts  ),
            vec2(   ts*S32,     -0.5*ts ),
            vec2(   0.0,        -ts     ),
            vec2(   -ts*S32,    -0.5*ts ),
            vec2(   -ts*S32,    0.5*ts  )
        })

    {

    }

    inline ivec2 getTileByPos(vec2 p) const
    {
        int a = _floor(p.x()/(S32*block_size));
        int b = _floor((p.x()/S3 + p.y())/block_size);
        int c = _floor((-p.x()/S3 + p.y())/block_size);
        return ivec2(_div(a - c + 1, 3),_div(b + c + 2, 3));
    }
    inline ivec2 getLandByTile(ivec2 p) const
    {
        int A = _div(AX*p.x() + AY*p.y(), AD);
        int B = _div(BX*p.x() + BY*p.y(), BD);
        int C = _div(CX*p.x() + CY*p.y(), CD);
        return ivec2(_div(C-B+1,3),_div(A+B+2,3));
    }
    inline ivec2 getTileByLand(ivec2 l) const
    {
        return ivec2(p.x()*land_size - p.y()*(land_size+1), p.x()*(land_size+1) + p.y()*(2*land_size+1));
    }
    inline vec2 getPosByTile(ivec2) const
    {
        return vec3(S3*tile_size*(pos.x() + 0.5*pos.y()),1.5*tile_size*pos.y());
    }
};

#endif // HEXLOCATOR_HPP
