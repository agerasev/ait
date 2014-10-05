#ifndef REGIONVIEW_HPP
#define REGIONVIEW_HPP

#include<vector>

#include<4u/gl/vertexbuffer.hpp>

#include<model/hex/hexarray.hpp>
#include<model/hex/hexlocator.hpp>
#include<model/region.hpp>

class RegionView
{
private:
	std::vector<fvec2> coord;
	std::vector<fvec3> color;
	std::vector<fvec2> texcoord;
	VertexBuffer coord_buffer, color_buffer, texcoord_buffer;
	int buffers_length = 0;
public:
	RegionView(const Region *reg)
	{
		const HexLocator &loc = reg->getLocator();

		fvec3 vertex_colors[7] = {
			fvec3(1.0,0.0,0.0),
			fvec3(1.0,1.0,0.0),
			fvec3(0.0,1.0,0.0),
			fvec3(0.0,1.0,1.0),
			fvec3(0.0,0.0,1.0),
			fvec3(1.0,0.0,1.0),
			fvec3(1.0,1.0,1.0)
		};
		fvec2 vertex_texcoords[7] = {
			fvec2(1.0,0.5),
			fvec2(0.5,1.0),
			fvec2(0.0,1.0),
			fvec2(0.0,0.5),
			fvec2(0.5,0.0),
			fvec2(1.0,0.0),
			fvec2(0.5,0.5)
		};

		for(auto i = reg->begin(); i != reg->end(); ++i)
		{
			ivec2 p = ~i;
			vec2 c = loc.getTileCenterPos(p);

			for(int i = 0; i < 6; ++i)
			{
				coord.push_back(loc.tile_vertex[i] + c);
				coord.push_back(loc.tile_vertex[(i+1)%6] + c);
				coord.push_back(c);

				color.push_back(vertex_colors[i]);
				color.push_back(vertex_colors[(i+1)%6]);
				color.push_back(vertex_colors[6]);

				texcoord.push_back(vertex_texcoords[i]);
				texcoord.push_back(vertex_texcoords[(i+1)%6]);
				texcoord.push_back(vertex_texcoords[6]);

				buffers_length += 3;
			}
		}
		coord_buffer.buffer(coord.data(),coord.size());
		color_buffer.buffer(color.data(),color.size());
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
