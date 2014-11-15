#ifndef VIEWCONFIG_HPP
#define VIEWCONFIG_HPP

#include<model/config.hpp>

#include<4u/la/mat.hpp>

namespace vconfig
{

const int MINIATURE_THRESHOLD = 32;
mat2 ISOMETRY = mat2(1.0,0.0,0.0,1.0);

double MAX_ZOOM = 2.0*config::MAP_SIZE*config::REGION_SIZE*config::TILE_SIZE;
double MIN_ZOOM = config::TILE_SIZE;

}

#endif // VIEWCONFIG_HPP
