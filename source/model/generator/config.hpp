#ifndef GCONFIG_HPP
#define GCONFIG_HPP

#include<model/config.hpp>

/* Generator */
namespace gconfig
{

const float
  LAND_FREQUENCY = 0.36,
  LAND_RADIUS = 0.75;
const int
  GAME_OF_LIFE_ITERS = 8,
  LAND_MAX_HEIGHT = 100,
  OCEAN_DEPTH = -50;

const int
  GRASS_THRESHOLD = 2,
  SNOW_THRESHOLD = 75;

const int
  BLUR_RADIUS = 2; // config::REGION_SIZE;
const double
  BLUR_FACTOR = -0.01;

}

#endif // GCONFIG_HPP
