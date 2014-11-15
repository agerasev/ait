#ifndef HEXARRAY_HPP
#define HEXARRAY_HPP

/* TODO:
 * Avoid calling T() when allocates memory
 * maybe like this: "reinterpret_cast<T*>(new char[n*sizeof(T)])"
 */

#include<functional>

#include<4u/la/vec.hpp>

#include"hexlocator.hpp"

template <class T, int N>
class HexArray
{
public:
	class iterator : public HexLocator<N>::iterator
    {
    private:
		HexArray<T,N> *_map;
    public:
		iterator(HexArray<T,N> *c_map, ivec2 c_pos) :
			HexLocator<N>::iterator(c_pos),
            _map(c_map)
        {
			
        }
        T &operator *()
        {
            return _map->get(HexLocator<N>::iterator::pos());
        }
		T *operator ->()
		{
			return &_map->get(HexLocator<N>::iterator::pos());
		}
		iterator &operator ++ ()
        {
            HexLocator<N>::iterator::next();
            return (*this);
        }
	};
	class const_iterator : public HexLocator<N>::iterator
    {
    private:
		const HexArray<T,N> *_map;
    public:
		const_iterator(const HexArray<T,N> *c_map, ivec2 c_pos) :
			HexLocator<N>::iterator(c_pos),
            _map(c_map)
        {
			
        }
        const T &operator *() const
        {
            return _map->get(HexLocator<N>::iterator::pos());
        }
		const T *operator ->() const
		{
			return &_map->get(HexLocator<N>::iterator::pos());
		}
		const_iterator &operator ++ ()
        {
            HexLocator<N>::iterator::next();
            return (*this);
        }
	};
private:
    T **_elem;
public:
	HexArray():
        _elem(nullptr)
    {
		_elem = new T*[1+2*N];
		_elem += N;
		for(int i=-N;i<0;i++)
		{
			_elem[i] = new T[2*N+1+i];
			_elem[i] += N + i;
        }
        for(int i=0;i<=N;i++)
		{
			_elem[i] = new T[2*N+1-i];
			_elem[i] += N;
		}
    }
    ~HexArray()
	{
        for(int i=-N;i<0;i++)
		{
			_elem[i] -= N + i;
			delete[] _elem[i];
        }
        for(int i=0;i<=N;i++)
		{
			_elem[i] -= N;
            delete[] _elem[i];
		}
		_elem -= N;
		delete[] _elem;\
    }
    T &get(ivec2 p)
    {
        return _elem[p.y()][p.x()];
    }
	const T &get(ivec2 p) const
    {
        return _elem[p.y()][p.x()];
    }
    T &operator()(ivec2 p)
    {
        return _elem[p.y()][p.x()];
    }
	const T &operator()(ivec2 p) const
    {
        return _elem[p.y()][p.x()];
    }
    int size() const
    {
        return N;
    }
    iterator begin()
    {
		return iterator(this,ivec2(0,-N));
    }
    iterator end()
    {
		return iterator(this,ivec2(-N,N+1));
    }
	const_iterator begin() const
	{
		return const_iterator(this,ivec2(0,-N));
	}
	const_iterator end() const
	{
		return const_iterator(this,ivec2(-N,N+1));
	}
	void for_each(std::function<void(const T&, const ivec2 &p)> func) const
	{
		for(const_iterator i = begin(); i != end(); ++i)
		{
			func(*i,~i);
		}
	}
	void for_each(std::function<void(T&, const ivec2 &p)> func)
	{
		for(iterator i = begin(); i != end(); ++i)
		{
			func(*i,~i);
		}
	}
};

#endif // HEXARRAY_HPP
