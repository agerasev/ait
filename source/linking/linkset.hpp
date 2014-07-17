#ifndef LINKSET_HPP
#define LINKSET_HPP

template <typename TLink>
class LinkSet
{
public:
    virtual void add(TLink *lnk) = 0;
    virtual void remove(TLink *lnk) = 0;
    class iterator
    {
    public:
        virtual iterator &operator ++ () = 0;
        virtual TLink *operator * () = 0;
    };
    virtual iterator begin() = 0;
    virtual iterator end() = 0;
};

#endif // LINKSET_HPP
