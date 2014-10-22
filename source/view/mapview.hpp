#ifndef MAPVIEW_HPP
#define MAPVIEW_HPP

#include<vector>

#include<model/map.hpp>

#include<4u/gl/vertexbuffer.hpp>

#include"renderprogram.hpp"
#include"regionview.hpp"
#include"spectator.hpp"

#include"config.hpp"

class MapView
{
private:
	MapReaderHandle &map_handle;
	HexArray<RegionView*,Map::SIZE> regions;
	unsigned int hash;
	
	/* Buffers for region */
	fvec2 *coord = nullptr;
	fvec3 *color = nullptr;
	fvec2 *texcoord = nullptr;
	VertexBuffer coord_buffer;

public:
	typedef Region::Locator Locator;
	MapView(MapReaderHandle &mh) :
		map_handle(mh),
		coord(new fvec2[RegionView::BUFFER_SIZE]),
		color(new fvec3[RegionView::BUFFER_SIZE]),
		texcoord(new fvec2[RegionView::BUFFER_SIZE])
	{
		/* Creates coord buffer */
		Region temp;
		int buffer_pos = 0;
		for(auto i = temp.begin(); i != temp.end(); ++i)
		{
			ivec2 p = ~i;
			vec2 c = Locator::getTileCenterPos(p);

			for(int j = 0; j < 6; ++j)
			{
				coord[buffer_pos] = Locator::getVertex(j) + c;
				coord[buffer_pos + 1] = Locator::getVertex((j+1)%6) + c;
				coord[buffer_pos + 2] = c;
				
				buffer_pos += 3;
			}
		}
		coord_buffer.buffer(coord,RegionView::BUFFER_SIZE);
		
		map_handle.read([this](MapReader &map){
			mini_init(map);
			// tex_init();
			// tex_update(map);
			for(auto i = map.begin(); i != map.end(); ++i)
			{
				regions.get(~i) = new RegionView(color,texcoord);
				// regions.get(~i)->update(*i);
			}
		});
	}
	~MapView()
	{
		for(RegionView *reg : regions)
		{
			delete reg;
			reg = nullptr;
		}
		delete[] coord;
		delete[] color;
		delete[] texcoord;
		
		mini_delete();
		// tex_delete();
	}

	void update()
	{
		map_handle.read([this](MapReader &map){
			mini_update(map);
			// tex_update(map);
			if(hash != map.getHash())
			{
				for(auto i = map.begin(); i != map.end(); ++i)
				{
					regions.get(~i)->update(*i);
				}
			}
			hash = map.getHash();
		});
	}
	
	void draw(RenderProgram *prog, const Spectator &spect, const mat2 &proj)
	{
		if(1.0/spect.getOri().det() < _sqr(vconfig::MINIATURE_THRESHOLD*config::TILE_SIZE))
		{
			vec2 safe_zone = proj*(spect.getOri()*(Region::SIZE*config::TILE_SIZE*vec2(2.0,2.0)));
			/* Draw detailed regions */
			for(auto i = begin(); i != end(); ++i)
			{
				vec2 view_pos = spect.getPos() + MapView::Locator::getTileCenterPos(MapView::Locator::getRegionCenterTile(~i),config::TILE_SIZE);
				vec2 screen_pos = proj*(spect.getOri()*view_pos);
				if(_abs(screen_pos.x()) < 1.0 + _abs(safe_zone.x()) && _abs(screen_pos.y()) < 1.0 + _abs(safe_zone.y()))
				{
					prog->setTranslation(view_pos);
					prog->pointCoord(coord_buffer);
					prog->pointColor((*i)->getColorBuffer());
					prog->pointTexCoord((*i)->getTexCoordBuffer());
					glDrawArrays(GL_TRIANGLES,0,RegionView::BUFFER_SIZE);
				}
			}
		}
		else
		{
			/* Draw miniature */
			// glBindTexture(GL_TEXTURE_2D, texture);
			prog->setTranslation(spect.getPos());
			prog->pointCoord(mini_coord_buffer);
			prog->pointColor(mini_color_buffer);
			prog->pointTexCoord(mini_texcoord_buffer);
			glDrawArrays(GL_TRIANGLES,0,BUFFER_SIZE);
		}
	}
	
	HexArray<RegionView*,Map::SIZE>::iterator begin()
	{
		return regions.begin();
	}
	HexArray<RegionView*,Map::SIZE>::iterator end()
	{
		return regions.end();
	}
	HexArray<RegionView*,Map::SIZE>::const_iterator begin() const
	{
		return static_cast<const HexArray<RegionView*,Map::SIZE>&>(regions).begin();
	}
	HexArray<RegionView*,Map::SIZE>::const_iterator end() const
	{
		return static_cast<const HexArray<RegionView*,Map::SIZE>&>(regions).end();
	}
	
public:
	static const int BUFFER_SIZE = 18*(3*Map::SIZE*(Map::SIZE + 1) + 1);
	
private:
	/* Map miniature */
	fvec2 *mini_coord;
	fvec3 *mini_color;
	fvec2 *mini_texcoord;
	VertexBuffer mini_coord_buffer, mini_color_buffer, mini_texcoord_buffer;
	void mini_init(MapReader &map)
	{
		mini_coord = new fvec2[BUFFER_SIZE];
		mini_color = new fvec3[BUFFER_SIZE];
		mini_texcoord = new fvec2[BUFFER_SIZE];
		
		static const ivec2 vertex[6] =
		{
			ivec2(Region::SIZE, 0),
			ivec2(0, Region::SIZE),
			ivec2(-Region::SIZE, Region::SIZE),
			ivec2(-Region::SIZE, 0),
			ivec2(0, -Region::SIZE),
			ivec2(Region::SIZE, -Region::SIZE),
		};
		
		int buffer_pos = 0;
		for(auto i = map.begin(); i != map.end(); ++i)
		{
			ivec2 p = ~i;
			vec2 c = Locator::getTileCenterPos(Locator::getRegionCenterTile(p));
			for(int j = 0; j < 6; ++j)
			{
				mini_coord[buffer_pos] = (Locator::getTileCenterPos(vertex[j]) + Locator::getVertex(((5-j)+2)%6) + c);
				mini_coord[buffer_pos + 1] = (Locator::getTileCenterPos(vertex[(j+1)%6]) + Locator::getVertex(((5-j)+1)%6) + c);
				mini_coord[buffer_pos + 2] = (c);

				buffer_pos += 3;
			}
		}
		mini_coord_buffer.buffer(mini_coord,BUFFER_SIZE);
	}
	void mini_update(MapReader &map)
	{
		int buffer_pos = 0;
		for(auto i = map.begin(); i != map.end(); ++i)
		{
			fvec2 tdev(0.0f,(float)(*i)->type/Tile::TYPES_NUM);
			for(int j = 0; j < 6; ++j)
			{
				fvec3 col = __getVertexColorMultiplier(**i);
				mini_color[buffer_pos] = col;
				mini_color[buffer_pos + 1] = col;
				mini_color[buffer_pos + 2] = col;
				
				mini_texcoord[buffer_pos] = __vertex_texcoords[j] + tdev;
				mini_texcoord[buffer_pos + 1] = __vertex_texcoords[(j+1)%6] + tdev;
				mini_texcoord[buffer_pos + 2] = __vertex_texcoords[6] + tdev;
				
				buffer_pos += 3;
			}
		}
		mini_color_buffer.buffer(mini_color,BUFFER_SIZE);
		mini_texcoord_buffer.buffer(mini_texcoord,BUFFER_SIZE);
	}
	void mini_delete()
	{
		delete[] mini_coord;
		delete[] mini_color;
		delete[] mini_texcoord;
	}

	/*
private:
	GLuint texture;
	fvec3 *tex_bitmap;
	
	static const int TEX_REG_SIZE = 2*Region::SIZE + 1;
	static const int TEX_MAP_SIZE = 2*Map::SIZE + 1;
	
	void tex_init()
	{
		tex_bitmap = new fvec3[_sqr(TEX_REG_SIZE*TEX_MAP_SIZE)];
		glGenTextures(1,&texture);
	}
	
	void tex_update(MapReader &map)
	{
		int pitch = TEX_REG_SIZE*TEX_MAP_SIZE;
		for(auto i = map.begin(); i != map.end(); ++i)
		{
			const Region *reg = *i;
			ivec2 bm_map_coord = ~i + ivec2(Map::SIZE,Map::SIZE);
			for(auto j = reg->begin(); j != reg->end(); ++j)
			{
				ivec2 bm_reg_coord = ~j + ivec2(Region::SIZE,Region::SIZE);
				tex_bitmap[
				  (bm_map_coord.y()*TEX_MAP_SIZE + bm_map_coord.x())*TEX_REG_SIZE + 
				  (bm_reg_coord.y()*pitch + bm_reg_coord.x())
				] = __getVertexColorMultiplier(**i);
			}
		}

		glBindTexture(GL_TEXTURE_2D, texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEX_REG_SIZE*TEX_MAP_SIZE, TEX_REG_SIZE*TEX_MAP_SIZE, 0, GL_RGB, GL_FLOAT, tex_bitmap);

		glBindTexture(GL_TEXTURE_2D, 0);
	}
	
	void tex_delete()
	{
		glDeleteTextures(1,&texture);
	}
	*/
};

#endif // MAPVIEW_HPP
