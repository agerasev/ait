#ifndef LINKOUT_HPP
#define LINKOUT_HPP

#include"image.hpp"

class LinkOut
{
public:
    virtual void send(Image *img) = 0;
};

#endif // LINKOUT_HPP
