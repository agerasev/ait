#ifndef CONFIG_HPP
#define CONFIG_HPP

namespace config
{

/* Size */
const int 
  MAP_SIZE = 12,
  REGION_SIZE = 12;
const double
  TILE_SIZE = 0.6f;

/* Generator */
namespace gen
{

const float 
  LAND_FREQUENCY = 0.36,
  LAND_RADIUS = 0.75;
const int 
  GAME_OF_LIFE_ITERS = 16,
  LAND_MAX_HEIGHT = 100,
  OCEAN_DEPTH = -50;

const int 
  GRASS_THRESHOLD = 2,
  SNOW_THRESHOLD = 75;

const int 
  BLUR_RADIUS = REGION_SIZE;
const double 
  BLUR_FACTOR = -0.01;

}

}

#endif // CONFIG_HPP
