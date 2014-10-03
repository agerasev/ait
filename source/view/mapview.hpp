#ifndef MAPVIEW_HPP
#define MAPVIEW_HPP

#include<vector>

#include<model/map.hpp>

#include<4u/gl/vertexbuffer.hpp>

class MapView
{
private:
	MapReaderHandle &map_handle;
	HexArray<VertexBuffer> coord,color,texcoord;
public:
	MapView(MapReaderHandle &mh, int size) :
		map_handle(mh),
		coord(size),
		color(size),
		texcoord(size)
	{
		map_handle.read([this](MapReader &map){
			for(auto i = map.begin(); i != map.end(); ++i)
			{
				std::vector<float> coord_buffer, color_buffer, texcoord_buffer;
				/*
				for(const Tile &t : **i)
				{
					// copy coords to buffer
				}
				*/
				coord(~i).buffer(coord_buffer.data(),coord_buffer.size());
				color(~i).buffer(color_buffer.data(),color_buffer.size());
				texcoord(~i).buffer(texcoord_buffer.data(),texcoord_buffer.size());
			}
		});
	}
};

#endif // MAPVIEW_HPP
