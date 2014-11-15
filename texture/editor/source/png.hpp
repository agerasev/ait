#pragma once

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include<png.h>

#include<SDL2/SDL.h>

SDL_Surface *loadPNG(const char* file_name)
{

	int width, height;
	png_byte color_type;
	png_byte bit_depth;

	png_structp png_ptr;
	png_infop info_ptr;
	png_bytep * row_pointers;

	png_byte header[8];    // 8 is the maximum size that can be checked

	/* open file and test for it being a png */
	FILE *fp = fopen(file_name, "rb");
	if (!fp)
		fprintf(stderr,"[read_png_file] File %s could not be opened for reading", file_name);
	fread(header, 1, 8, fp);
	if (png_sig_cmp(header, 0, 8))
		fprintf(stderr,"[read_png_file] File %s is not recognized as a PNG file", file_name);


	/* initialize stuff */
	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

	if (!png_ptr)
		fprintf(stderr,"[read_png_file] png_create_read_struct failed");

	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr)
		fprintf(stderr,"[read_png_file] png_create_info_struct failed");

	if (setjmp(png_jmpbuf(png_ptr)))
		fprintf(stderr,"[read_png_file] Error during init_io");

	png_init_io(png_ptr, fp);
	png_set_sig_bytes(png_ptr, 8);

	png_read_info(png_ptr, info_ptr);

	width = png_get_image_width(png_ptr, info_ptr);
	height = png_get_image_height(png_ptr, info_ptr);
	color_type = png_get_color_type(png_ptr, info_ptr);
	bit_depth = png_get_bit_depth(png_ptr, info_ptr);

	png_set_interlace_handling(png_ptr);
	png_read_update_info(png_ptr, info_ptr);

	if(bit_depth != 8)
	{
		fprintf(stderr,"[read_png_file] bit depth must be 8 (is %d)",bit_depth);
	}

	SDL_Surface *surface = NULL;
	if(color_type == PNG_COLOR_TYPE_RGB)
	{
		surface = SDL_CreateRGBSurface(SDL_SWSURFACE,width,height,24,0x0000ff,0x00ff00,0xff0000,0x000000);
	}
	else if(color_type == PNG_COLOR_TYPE_RGBA)
	{
		surface = SDL_CreateRGBSurface(SDL_SWSURFACE,width,height,32,0x000000ff,0x0000ff00,0x00ff0000,0xff000000);
	}
	else
	{
		fprintf(stderr,"[read_png_file] color_type of input file must be PNG_COLOR_TYPE_RGBA (%d) or PNG_COLOR_TYPE_RGB (%d) (is %d)",
			PNG_COLOR_TYPE_RGBA, PNG_COLOR_TYPE_RGB, png_get_color_type(png_ptr, info_ptr));
	}

	/* read file */
	if (setjmp(png_jmpbuf(png_ptr)))
		fprintf(stderr,"[read_png_file] Error during read_image");

	row_pointers = (png_bytep*)malloc(sizeof(png_bytep)*height);
	int iy;
	for(iy = 0; iy < height; ++iy)
		row_pointers[iy] = (png_bytep)surface->pixels + iy*surface->pitch;

	png_read_image(png_ptr, row_pointers);

	free(row_pointers);

	if(color_type == PNG_COLOR_TYPE_RGB)
	{
		SDL_Surface *new_surface = SDL_CreateRGBSurface(SDL_SWSURFACE,width,height,32,0x000000ff,0x0000ff00,0x00ff0000,0xff000000);
		int iy;
		for(iy = 0; iy < height; ++iy)
		{
			int ix;
			for(ix = 0; ix < width; ++ix)
			{
				Uint8 *pixel = (Uint8*)surface->pixels + iy*surface->pitch + 3*ix;
				Uint8 *new_pixel = (Uint8*)new_surface->pixels + iy*new_surface->pitch + 4*ix;
				new_pixel[0] = pixel[0];
				new_pixel[1] = pixel[1];
				new_pixel[2] = pixel[2];
				new_pixel[3] = 0xff;
			}
		}
		SDL_FreeSurface(surface);
		surface = new_surface;
	}

	fclose(fp);

	return surface;
}


void savePNG(const char* file_name, const SDL_Surface *image)
{
	int width = image->w, height = image->h;
	png_byte color_type = PNG_COLOR_TYPE_RGBA;
	png_byte bit_depth = 8;

	png_structp png_ptr;
	png_infop info_ptr;
	png_bytep *row_pointers;

	/* create file */
	FILE *fp = fopen(file_name, "wb");
	if (!fp)
		fprintf(stderr,"[write_png_file] File %s could not be opened for writing", file_name);


	/* initialize stuff */
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

	if (!png_ptr)
		fprintf(stderr,"[write_png_file] png_create_write_struct failed");

	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr)
		fprintf(stderr,"[write_png_file] png_create_info_struct failed");

	if (setjmp(png_jmpbuf(png_ptr)))
		fprintf(stderr,"[write_png_file] Error during init_io");

	png_init_io(png_ptr, fp);


	/* write header */
	if (setjmp(png_jmpbuf(png_ptr)))
		fprintf(stderr,"[write_png_file] Error during writing header");

	png_set_IHDR(png_ptr, info_ptr, width, height,
							 bit_depth, color_type, PNG_INTERLACE_NONE,
							 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

	png_write_info(png_ptr, info_ptr);

	/* write bytes */
	if (setjmp(png_jmpbuf(png_ptr)))
		fprintf(stderr,"[write_png_file] Error during writing bytes");

	row_pointers = (png_bytep*)malloc(sizeof(png_bytep)*height);
	int iy;
	for(iy = 0; iy < height; ++iy)
		row_pointers[iy] = (png_bytep)image->pixels + iy*image->pitch;

	png_write_image(png_ptr, row_pointers);

	free(row_pointers);

	/* end write */
	if (setjmp(png_jmpbuf(png_ptr)))
		fprintf(stderr,"[write_png_file] Error during end of write");

	png_write_end(png_ptr, NULL);

	fclose(fp);
}
