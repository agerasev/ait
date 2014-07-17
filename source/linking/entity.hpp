#ifndef ENTITY_HPP
#define ENTITY_HPP

typedef unsigned int EntityKind;
namespace EntityKindMask {}

class Entity
{
private:

public:
    const EntityKind kind;
    virtual void proceed() = 0;
};

#endif // ENTITY_HPP
