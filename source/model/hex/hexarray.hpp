#ifndef HEXARRAY_HPP
#define HEXARRAY_HPP

/* TODO:
 * Avoid calling T() when allocates memory
 * maybe like this: "reinterpret_cast<T*>(new char[n*sizeof(T)])"
 */

#include<functional>

#include<4u/la/vec.hpp>

template <class T, int N>
class HexArray
{
public:
	class iterator
    {
    private:
		HexArray<T,N> *_map;
        ivec2 _pos;
        int _end_x;
        int _get_end_x(int f_y)
        {
            return (f_y<0)?(N):(N - f_y);
        }
        int _get_begin_x(int f_y)
        {
            return (f_y>0)?(-N):(-N - f_y);
        }
    public:
		iterator(HexArray<T,N> *c_map, ivec2 c_pos):
            _map(c_map),
            _pos(c_pos)
        {
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
		T *operator ->()
		{
			//std::cout << _pos.x << ',' << _pos.y << std::endl;
			return &_map->get(_pos);
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
		const HexArray<T,N> *_map;
		ivec2 _pos;
		int _end_x;
		int _get_end_x(int f_y)
		{
			return (f_y<0)?(N):(N - f_y);
		}
		int _get_begin_x(int f_y)
		{
			return (f_y>0)?(-N):(-N - f_y);
		}
	public:
		const_iterator(const HexArray<T,N> *c_map, ivec2 c_pos):
			_map(c_map),
			_pos(c_pos)
		{
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
		const T *operator ->() const
		{
			//std::cout << _pos.x << ',' << _pos.y << std::endl;
			return &_map->get(_pos);
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
public:
	HexArray():
        _elem(nullptr)
    {
		//std::cout << "HexArray created" << std::endl;
		_elem = new T*[1+2*N];
		_elem += N;
		for(int i=-N;i<0;i++){
			_elem[i] = new T[2*N+1+i];
			_elem[i] += N + i;
        }
        for(int i=0;i<=N;i++){
			_elem[i] = new T[2*N+1-i];
			_elem[i] += N;
		}
		//std::cout << "end." << std::endl;
    }
    ~HexArray()
	{
        for(int i=-N;i<0;i++){
		_elem[i] -= N + i;
        delete[] _elem[i];
        }
        for(int i=0;i<=N;i++){
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
