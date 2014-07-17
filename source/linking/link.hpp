#ifndef LINK_HPP
#define LINK_HPP

#include"linkin.hpp"
#include"linkout.hpp"

typedef unsigned int LinkID;

class Link : public LinkIn, public LinkOut
{
public:
    const LinkID id;
};

#endif // LINK_HPP
