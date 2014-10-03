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
	inline T z() const {return data[2];}
	inline T &z() {return data[2];}
};

// Basic operations
  // Addition
template<typename T>
inline tvecn<T,3> operator +(const tvecn<T,3> &a, const tvecn<T,3> &b) {
	return tvecn<T,3>(
				a.x() + b.x(),
				a.y() + b.y(),
				a.z() + b.z()
				);
}
  // Multiplication by constatnt
template<typename T>
inline tvecn<T,3> operator *(T a, const tvecn<T,3> &b) {
	return tvecn<T,3>(
				a*b.x(),
				a*b.y(),
				a*b.z()
				);
}
  // Scalar product
template<typename T>
inline T operator *(const tvecn<T,3> &a, const tvecn<T,3> &b) {
	return
			a.x()*b.x() +
			a.y()*b.y() +
			a.z()*b.z();
}

// Derivative operations
template<typename T>
inline tvecn<T,3> operator *(const tvecn<T,3> &b, T a) {
	return a*b;
}
template<typename T>
inline tvecn<T,3> operator -(const tvecn<T,3> &a) {
	return static_cast<T>(-1)*a;
}
template<typename T>
inline tvecn<T,3> operator -(const tvecn<T,3> &a, const tvecn<T,3> &b) {
	return a+(-b);
}
template<typename T>
inline tvecn<T,3> operator /(const tvecn<T,3> &b, T a) {
	return b*(static_cast<T>(1)/a);
}

// Cross product
template <typename T>
inline tvecn<T,3> operator ^(const tvecn<T,3> &a, const tvecn<T,3> &b) {
    return tvecn<T,3>(
                a[1]*b[2] - b[1]*a[2],
                a[2]*b[0] - b[2]*a[0],
                a[0]*b[1] - b[0]*a[1]
                );
}

typedef tvecn<double,3>     dvec3;
typedef tvecn<float,3>      fvec3;
typedef tvecn<int,3>		ivec3;

const dvec3 nulldvec3(0.0,0.0,0.0);
const fvec3 nullfvec3(0.0f,0.0f,0.0f);
const ivec3 nullivec3(0,0,0);

typedef dvec3 vec3;
const vec3 nullvec3 = nulldvec3;

#endif // VEC3_HPP
