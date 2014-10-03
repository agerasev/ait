#ifndef VEC4_HPP
#define VEC4_HPP

#include"vecn.hpp"

template <typename T>
struct tvecn<T,4> {
    T data[4];
    inline tvecn() {

	}
	template <typename S>
    inline tvecn(const tvecn<S,4> &av) {
		this->data[0] = static_cast<T>(av.data[0]);
		this->data[1] = static_cast<T>(av.data[1]);
		this->data[2] = static_cast<T>(av.data[2]);
		this->data[3] = static_cast<T>(av.data[3]);
	}
    inline tvecn(const T *p, int d = 1) {
        for(int i = 0; i < 4; ++i) {
            data[i] = p[d*i];
        }
    }
    inline tvecn(T ax, T ay, T az, T aw = static_cast<T>(1)) {
		this->data[0] = ax;
		this->data[1] = ay;
		this->data[2] = az;
		this->data[3] = aw;
	}
	template <typename S>
    inline tvecn<T,4> &operator = (const tvecn<S,4> &av) {
		this->data[0] = static_cast<T>(av.data[0]);
		this->data[1] = static_cast<T>(av.data[1]);
		this->data[2] = static_cast<T>(av.data[2]);
		this->data[3] = static_cast<T>(av.data[3]);
		return *this;
	}
	inline T &operator [](int n) {
        return data[n];
	}
	inline T operator [](int n) const {
        return data[n];
	}
	inline T x() const {return data[0];}
	inline T &x() {return data[0];}
	inline T y() const {return data[1];}
	inline T &y() {return data[1];}
	inline T z() const {return data[2];}
	inline T &z() {return data[2];}
	inline T w() const {return data[3];}
	inline T &w() {return data[3];}
};

// Basic operations
  // Addition
template<typename T>
inline tvecn<T,4> operator +(const tvecn<T,4> &a, const tvecn<T,4> &b) {
	return tvecn<T,4>(
				a.x() + b.x(),
				a.y() + b.y(),
				a.z() + b.z(),
				a.w() + b.w()
				);
}
  // Multiplication by constatnt
template<typename T>
inline tvecn<T,4> operator *(T a, const tvecn<T,4> &b) {
	return tvecn<T,4>(
				a*b.x(),
				a*b.y(),
				a*b.z(),
				a*b.w()
				);
}
  // Scalar product
template<typename T>
inline T operator *(const tvecn<T,4> &a, const tvecn<T,4> &b) {
	return
			a.x()*b.x() +
			a.y()*b.y() +
			a.z()*b.z() +
			a.w()*b.w();
}

// Derivative operations
template<typename T>
inline tvecn<T,4> operator *(const tvecn<T,4> &b, T a) {
	return a*b;
}
template<typename T>
inline tvecn<T,4> operator -(const tvecn<T,4> &a) {
	return static_cast<T>(-1)*a;
}
template<typename T>
inline tvecn<T,4> operator -(const tvecn<T,4> &a, const tvecn<T,4> &b) {
	return a+(-b);
}
template<typename T>
inline tvecn<T,4> operator /(const tvecn<T,4> &b, T a) {
	return b*(static_cast<T>(1)/a);
}

typedef tvecn<double,4>     dvec4;
typedef tvecn<float,4>      fvec4;
typedef tvecn<int,4>		ivec4;

const dvec4 nulldvec4(0.0,0.0,0.0,0.0);
const fvec4 nullfvec4(0.0f,0.0f,0.0f,0.0f);
const ivec4 nullivec4(0,0,0,0);

typedef dvec4 vec4;
const vec4 nullvec4 = nulldvec4;

#endif // VEC4_HPP
