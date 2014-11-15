#ifndef TEXTURES_HPP
#define TEXTURES_HPP

#include<4u/gl/texture.hpp>

class Textures
{
private:
	Texture *tree;
	
public:
	Textures()
	{
		
	}
	~Textures()
	{
		
	}

	void load()
	{
		tree = new Texture();
        tree->loadFromFile("../texture/tree.bmp");
	}

	Texture *get(unsigned int)
	{
		return tree;
	}
	
	void free()
	{
		delete tree;
	}
	
} textures;

#endif // TEXTURES_HPP
