#ifndef LINKIN_HPP
#define LINKIN_HPP

#include"image.hpp"

class LinkIn
{
public:
    virtual void receive(Image *img) = 0;
};

#endif // LINKIN_HPP
