#ifndef REGIONVIEW_HPP
#define REGIONVIEW_HPP

#include<vector>

#include<4u/gl/vertexbuffer.hpp>

#include<model/hex/hexarray.hpp>
#include<model/hex/hexlocator.hpp>
#include<model/region.hpp>

static const fvec3 __vertex_color = fvec3(1.0f,1.0f,1.0f);
static const int __types_num = 5;
static const fvec2 __vertex_texcoords[7] = {
	fvec2(1.0,0.5/__types_num),
	fvec2(0.5,0.99999/__types_num),
	fvec2(0.0,0.99999/__types_num),
	fvec2(0.0,0.5/__types_num),
	fvec2(0.5,0.0/__types_num),
	fvec2(1.0,0.0/__types_num),
	fvec2(0.5,0.5/__types_num)
};

class RegionView
{
private:
	std::vector<fvec2> coord;
	std::vector<fvec3> color;
	std::vector<fvec2> texcoord;
	VertexBuffer coord_buffer, color_buffer, texcoord_buffer;
	int buffers_length = 0;
	typedef Region::Locator Locator;

public:
	RegionView(const Region *reg)
	{
		for(auto i = reg->begin(); i != reg->end(); ++i)
		{
			ivec2 p = ~i;
			vec2 c = Locator::getTileCenterPos(p);
			fvec2 tdev(0.0f,(float)i->type/__types_num);

			for(int i = 0; i < 6; ++i)
			{
				coord.push_back(Locator::getVertex(i) + c);
				coord.push_back(Locator::getVertex((i+1)%6) + c);
				coord.push_back(c);

				color.push_back(__vertex_color);
				color.push_back(__vertex_color);
				color.push_back(__vertex_color);

				texcoord.push_back(__vertex_texcoords[i] + tdev);
				texcoord.push_back(__vertex_texcoords[(i+1)%6] + tdev);
				texcoord.push_back(__vertex_texcoords[6] + tdev);

				buffers_length += 3;
			}
		}
		coord_buffer.buffer(coord.data(),coord.size());
		color_buffer.buffer(color.data(),color.size());
		texcoord_buffer.buffer(texcoord.data(),texcoord.size());
	}
	
	void update(const Region *reg)
	{
		int buffer_pos = 0;
		for(auto i = reg->begin(); i != reg->end(); ++i)
		{
			fvec2 tdev(0.0f,(float)i->type/__types_num);
			for(int i = 0; i < 6; ++i)
			{
				texcoord[buffer_pos++] = __vertex_texcoords[i] + tdev;
				texcoord[buffer_pos++] = __vertex_texcoords[(i+1)%6] + tdev;
				texcoord[buffer_pos++] = __vertex_texcoords[6] + tdev;
			}
		}
		texcoord_buffer.buffer(texcoord.data(),texcoord.size());
	}

	VertexBuffer &getCoordBuffer()
	{
		return coord_buffer;
	}
	VertexBuffer &getColorBuffer()
	{
		return color_buffer;
	}
	VertexBuffer &getTexCoordBuffer()
	{
		return texcoord_buffer;
	}
	int getBuffersLength() const
	{
		return buffers_length;
	}
};

#endif // REGIONVIEW_HPP
