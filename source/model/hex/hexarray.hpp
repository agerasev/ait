#ifndef HEXARRAY_HPP
#define HEXARRAY_HPP

/* TODO:
 * Avoid calling T() when allocates memory
 * maybe like this: "reinterpret_cast<T*>(new char[n*sizeof(T)])"
 */

#include<4u/la/vec.hpp>

template <class T>
class HexArray
{
public:
	class iterator
    {
    private:
		HexArray<T> *_map;
        ivec2 _pos;
        int _width;
        int _end_x;
        int _get_end_x(int f_y)
        {
            return (f_y<0)?(_width):(_width - f_y);
        }
        int _get_begin_x(int f_y)
        {
            return (f_y>0)?(-_width):(-_width - f_y);
        }
    public:
		iterator(HexArray<T> *c_map, ivec2 c_pos):
            _map(c_map),
            _pos(c_pos)
        {
            _width = _map->width();
            _end_x = _get_end_x(_pos.y());
        }
		~iterator()
        {

        }
        T &operator *()
        {
            //std::cout << _pos.x << ',' << _pos.y << std::endl;
            return _map->get(_pos);
        }
		const T &operator *() const
        {
            //std::cout << _pos.x << ',' << _pos.y << std::endl;
            return _map->get(_pos);
        }
		iterator &operator ++ ()
        {
            ++_pos.x();
            if(_pos.x() > _end_x)
            {
                ++_pos.y();
                _pos.x() = _get_begin_x(_pos.y());
                _end_x = _get_end_x(_pos.y());
            }
            return (*this);
        }
		ivec2 getPos() const
        {
            return _pos;
        }
        ivec2 operator ~ () const
        {
            return _pos;
        }
		bool operator == (const iterator &f_iter)
        {
            return (f_iter.getPos()==_pos)?true:false;
        }
		bool operator != (const iterator &f_iter)
        {
            return (f_iter.getPos()!=_pos)?true:false;
        }
	};
	class const_iterator
	{
	private:
		const HexArray<T> *_map;
		ivec2 _pos;
		int _width;
		int _end_x;
		int _get_end_x(int f_y)
		{
			return (f_y<0)?(_width):(_width - f_y);
		}
		int _get_begin_x(int f_y)
		{
			return (f_y>0)?(-_width):(-_width - f_y);
		}
	public:
		const_iterator(const HexArray<T> *c_map, ivec2 c_pos):
			_map(c_map),
			_pos(c_pos)
		{
			_width = _map->width();
			_end_x = _get_end_x(_pos.y());
		}
		~const_iterator()
		{

		}
		const T &operator *() const
		{
			//std::cout << _pos.x << ',' << _pos.y << std::endl;
			return _map->get(_pos);
		}
		const_iterator &operator ++ ()
		{
			++_pos.x();
			if(_pos.x() > _end_x)
			{
				++_pos.y();
				_pos.x() = _get_begin_x(_pos.y());
				_end_x = _get_end_x(_pos.y());
			}
			return (*this);
		}
		ivec2 getPos() const
		{
			return _pos;
		}
		ivec2 operator ~ () const
		{
			return _pos;
		}
		bool operator == (const const_iterator &f_iter)
		{
			return (f_iter.getPos()==_pos)?true:false;
		}
		bool operator != (const const_iterator &f_iter)
		{
			return (f_iter.getPos()!=_pos)?true:false;
		}
	};
private:
    T **_elem;
	int _width;
public:
	HexArray(int c_width):
        _elem(nullptr),
		_width(c_width)
    {
		//std::cout << "HexArray created" << std::endl;
		_elem = new T*[1+2*_width];
		_elem += _width;
		for(int i=-_width;i<0;i++){
			_elem[i] = new T[2*_width+1+i];
			_elem[i] += _width + i;
        }
        for(int i=0;i<=_width;i++){
			_elem[i] = new T[2*_width+1-i];
			_elem[i] += _width;
		}
		//std::cout << "end." << std::endl;
    }
    ~HexArray()
	{
        for(int i=-_width;i<0;i++){
		_elem[i] -= _width + i;
        delete[] _elem[i];
        }
        for(int i=0;i<=_width;i++){
			_elem[i] -= _width;
            delete[] _elem[i];
		}
		_elem -= _width;
		delete[] _elem;\
    }
    bool inside(ivec2 p)
    {
        if( p.x()>_width || -p.x()>_width || p.y()>_width || -p.y()>_width || p.x()+p.y()>_width || -p.x()-p.y()>_width )
        {
            return false;
        }
        return true;
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
    int width() const
    {
        return _width;
    }
    iterator begin()
    {
		return iterator(this,ivec2(0,-_width));
    }
    iterator end()
    {
		return iterator(this,ivec2(-_width,_width+1));
    }
	const_iterator begin() const
	{
		return const_iterator(this,ivec2(0,-_width));
	}
	const_iterator end() const
	{
		return const_iterator(this,ivec2(-_width,_width+1));
	}
};


#endif // HEXARRAY_HPP
