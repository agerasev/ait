#ifndef REGIONVIEW_HPP
#define REGIONVIEW_HPP

#include<vector>
#include<functional>

#include<4u/gl/vertexbuffer.hpp>
#include<4u/gl/texture.hpp>
#include<4u/util/op.hpp>
#include<4u/random/contrand.hpp>

#include<model/hex/hexarray.hpp>
#include<model/hex/hexlocator.hpp>
#include<model/region.hpp>

static const fvec2 __vertex_texcoords[7] = {
	fvec2(1.0,0.5/Tile::TYPES_NUM),
	fvec2(0.5,0.99999/Tile::TYPES_NUM),
	fvec2(0.0,0.99999/Tile::TYPES_NUM),
	fvec2(0.0,0.5/Tile::TYPES_NUM),
	fvec2(0.5,0.0/Tile::TYPES_NUM),
	fvec2(1.0,0.0/Tile::TYPES_NUM),
	fvec2(0.5,0.5/Tile::TYPES_NUM)
};

template <typename T>
fvec3 __getVertexColorMultiplier(const T &t)
{
	float mul = static_cast<float>(t.height)/config::gen::LAND_MAX_HEIGHT;
	switch(t.type)
	{
	case Tile::GRASS:
		return fvec3(1.0f,1.2f - 0.6f*mul,1.0f);
	case Tile::SNOW:
		return fvec3(1.0f,1.0f,1.0f)*(1.0f - mul + static_cast<float>(config::gen::SNOW_THRESHOLD)/config::gen::LAND_MAX_HEIGHT);
	case Tile::OCEAN:
		return fvec3(1.0f,1.0f,1.0f)*(1.0f + mul);
	// case Tile::FRESH:
		// return fvec3(1.0f,1.0f,1.0f)*(0.8f + mul);
	default:
		return fvec3(1.0f,1.0f,1.0f);
	}
}

static ContRandInt __rand(0xabcdef);

class RegionView
{
public:
	static const int BUFFER_SIZE = 18*(3*Region::SIZE*(Region::SIZE + 1) + 1);
	
private:
	fvec3 *color;
	fvec2 *texcoord;
	VertexBuffer color_buffer, texcoord_buffer;
	
	typedef Region::Locator Locator;

public:
	RegionView(fvec3 *c, fvec2 *t) :
		color(c), texcoord(t)
	{
		
	}
	
	~RegionView()
	{
		
	}
	
	void update(const Region *reg)
	{
		/* Loads buffers in video memory */
		int buffer_pos = 0;
		for(auto i = reg->begin(); i != reg->end(); ++i)
		{
			fvec2 tdev(0.0f,(float)i->type/Tile::TYPES_NUM);
			int r = __rand.get()%6;
			fvec2 n = 0.5f*fvec2(__rand.get()%2,(float)(__rand.get()%2)/Tile::TYPES_NUM);
			for(int j = 0; j < 6; ++j)
			{
				fvec3 col = __getVertexColorMultiplier(*i);
				color[buffer_pos] = col;
				color[buffer_pos + 1] = col;
				color[buffer_pos + 2] = col;
				
				texcoord[buffer_pos] = __vertex_texcoords[(j+r)%6]/2 + n + tdev;
				texcoord[buffer_pos + 1] = __vertex_texcoords[(j+1+r)%6]/2 + n + tdev;
				texcoord[buffer_pos + 2] = __vertex_texcoords[6]/2 + n + tdev;
				
				buffer_pos += 3;
			}
		}
		color_buffer.buffer(color, BUFFER_SIZE);
		texcoord_buffer.buffer(texcoord, BUFFER_SIZE);
	}

	VertexBuffer &getColorBuffer()
	{
		return color_buffer;
	}
	VertexBuffer &getTexCoordBuffer()
	{
		return texcoord_buffer;
	}
};

#endif // REGIONVIEW_HPP
