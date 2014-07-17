#ifndef VEC2_HPP
#define VEC2_HPP

#include"vecn.hpp"

template <typename T>
struct tvecn<T,2> {
    T data[2];
    inline tvecn() {

	}
	template <typename S>
    inline tvecn(const tvecn<S,2> &av) {
		this->data[0] = static_cast<T>(av.data[0]);
		this->data[1] = static_cast<T>(av.data[1]);
	}
    inline tvecn(const T *p, int d = 1) {
        for(int i = 0; i < 2; ++i) {
            data[i] = p[d*i];
        }
    }
    inline tvecn(T ax, T ay) {
		this->data[0] = ax;
		this->data[1] = ay;
	}
	template <typename S>
    inline tvecn<T,2> &operator = (const tvecn<S,2> &av) {
		this->data[0] = static_cast<T>(av.data[0]);
		this->data[1] = static_cast<T>(av.data[1]);
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
};

// Pseudo cross product
template <typename T>
inline T operator ^(const tvecn<T,2> &a, const tvecn<T,2> &b) {
	return a(0)*b(1) - a(1)*b(0);
}

#endif // VEC2_HPP
