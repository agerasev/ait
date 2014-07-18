#ifndef VEC3_HPP
#define VEC3_HPP

#include"vecn.hpp"

template <typename T>
struct tvecn<T,3> {
    T data[3];
    inline tvecn() {

	}
	template <typename S>
    inline tvecn(const tvecn<S,3> &av) {
		this->data[0] = static_cast<T>(av.data[0]);
		this->data[1] = static_cast<T>(av.data[1]);
		this->data[2] = static_cast<T>(av.data[2]);
	}
    inline tvecn(const T *p, int d = 1) {
        for(int i = 0; i < 3; ++i) {
            data[i] = p[d*i];
        }
    }
    inline tvecn(T ax, T ay, T az) {
		this->data[0] = ax;
		this->data[1] = ay;
		this->data[2] = az;
	}
	template <typename S>
    inline tvecn<T,3> &operator = (const tvecn<S,3> &av) {
		this->data[0] = static_cast<T>(av.data[0]);
		this->data[1] = static_cast<T>(av.data[1]);
		this->data[2] = static_cast<T>(av.data[2]);
		return *this;
	}
    inline T &operator ()(int n) {
        return data[n];
    }
    inline T operator ()(int n) const {
        return data[n];
    }
    template <int P>
    inline T comp() const {return data[P];}
    template <int P>
    inline T &comp() {return data[P];}
    using x = comp<0>;
    using y = comp<1>;
    using z = comp<2>;
};

// Cross product
template <typename T>
inline tvecn<T,3> operator ^(const tvecn<T,3> &a, const tvecn<T,3> &b) {
	return a(0)*b(1) - a(1)*b(0);
}

#endif // VEC3_HPP
