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
	inline T &operator [](int n) {
		return data[n];
	}
	inline T operator [](int n) const {
		return data[n];
	}
	inline T &operator ()(int n) {
		return data[n];
	}
	inline T operator ()(int n) const {
		return data[n];
	}
	inline T x() const {return data[0];}
	inline T &x() {return data[0];}
	inline T y() const {return data[1];}
	inline T &y() {return data[1];}
};

// Basic operations
  // Addition
template<typename T>
inline tvecn<T,2> operator +(const tvecn<T,2> &a, const tvecn<T,2> &b) {
	return tvecn<T,2>(
				a.x() + b.x(),
				a.y() + b.y()
				);
}
  // Multiplication by constatnt
template<typename T>
inline tvecn<T,2> operator *(T a, const tvecn<T,2> &b) {
	return tvecn<T,2>(
				a*b.x(),
				a*b.y()
				);
}
  // Scalar product
template<typename T>
inline T operator *(const tvecn<T,2> &a, const tvecn<T,2> &b) {
	return
			a.x()*b.x() +
			a.y()*b.y();
}

// Derivative operations
template<typename T>
inline tvecn<T,2> operator *(const tvecn<T,2> &b, T a) {
	return a*b;
}
template<typename T>
inline tvecn<T,2> operator +(const tvecn<T,2> &a) {
	return a;
}
template<typename T>
inline tvecn<T,2> operator -(const tvecn<T,2> &a) {
	return static_cast<T>(-1)*a;
}
template<typename T>
inline tvecn<T,2> operator -(const tvecn<T,2> &a, const tvecn<T,2> &b) {
	return a+(-b);
}
template<typename T>
inline tvecn<T,2> operator /(const tvecn<T,2> &b, T a) {
	return b*(static_cast<T>(1)/a);
}

// Pseudo cross product
template <typename T>
inline T operator ^(const tvecn<T,2> &a, const tvecn<T,2> &b) {
	return a(0)*b(1) - a(1)*b(0);
}

typedef tvecn<double,2>     dvec2;
typedef tvecn<float,2>      fvec2;
typedef tvecn<int,2>		ivec2;

const dvec2 nulldvec2(0.0,0.0);
const fvec2 nullfvec2(0.0f,0.0f);
const ivec2 nullivec2(0,0);

typedef dvec2 vec2;
const vec2 nullvec2 = nulldvec2;

#endif // VEC2_HPP
