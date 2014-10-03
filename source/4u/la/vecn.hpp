#ifndef VECN_HPP
#define VECN_HPP

template<typename T, int N>
struct tvecn {
    T data[N];
	inline tvecn() {

    }
    template <typename S>
	inline tvecn(const tvecn<S,N> &av) {
        for(int i = 0; i < N; ++i) {
            data[i] = static_cast<T>(av.data[i]);
        }
    }
	inline tvecn(const T *p, int d = 1) {
        for(int i = 0; i < N; ++i) {
            data[i] = p[d*i];
        }
    }
	template <typename S>
	inline tvecn<T,N> &operator = (const tvecn<S,N> &av) {
		for(int i = 0; i < N; ++i) {
			data[i] = static_cast<T>(av.data[i]);
		}
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
};

// Basic operations
  // Addition
template<typename T, int N>
inline tvecn<T,N> operator +(const tvecn<T,N> &a, const tvecn<T,N> &b) {
    tvecn<T,N> c;
    for(int i = 0; i < N; ++i) {
        c.data[i] = a.data[i] + b.data[i];
    }
    return c;
}
  // Multiplication by constatnt
template<typename T, int N>
inline tvecn<T,N> operator *(T a, const tvecn<T,N> &b) {
    tvecn<T,N> c;
    for(int i = 0; i < N; ++i) {
		c.data[i] = a*b.data[i];
    }
    return c;
}

// Component product
template<typename T, int N>
inline tvecn<T,N> operator &(const tvecn<T,N> &a, const tvecn<T,N> &b) {
  tvecn<T,N> c;
  for(int i = 0; i < N; ++i) {
	  c.data[i] = a.data[i]*b.data[i];
  }
  return c;
}

  // Scalar product
template<typename T, int N>
inline T operator *(const tvecn<T,N> &a, const tvecn<T,N> &b) {
    T c = static_cast<T>(0);
    for(int i = 0; i < N; ++i) {
        c += a.data[i]*b.data[i];
    }
    return c;
}

// Derivative operations
template<typename T, typename S, int N>
inline tvecn<T,N> operator *(const tvecn<T,N> &b, S a) {
	return static_cast<T>(a)*b;
}
template<typename T, int N>
inline tvecn<T,N> operator -(const tvecn<T,N> &a) {
    return static_cast<T>(-1)*a;
}
template<typename T, int N>
inline tvecn<T,N> operator -(const tvecn<T,N> &a, const tvecn<T,N> &b) {
    return a+(-b);
}
template<typename T, typename S, int N>
inline tvecn<T,N> operator /(const tvecn<T,N> &b, S a) {
	return b*(static_cast<T>(1)/static_cast<T>(a));
}

// Assign operations
template<typename T, typename S, int N>
inline tvecn<T,N> &operator +=(tvecn<T,N> &a, const tvecn<S,N> &b) {
    return a = a + b;
}
template<typename T, typename S, int N>
inline tvecn<T,N> &operator -=(tvecn<T,N> &a, const tvecn<S,N> &b) {
    return a = a - b;
}
template<typename T, typename S, int N>
inline tvecn<T,N> &operator *=(tvecn<T,N> &a, S b) {
    return a = a*b;
}
template<typename T, typename S, int N>
inline tvecn<T,N> &operator /=(tvecn<T,N> &a, S b) {
    return a = a/b;
}

// Math
#include<cmath>
template<typename T, int N>
inline T sqr(const tvecn<T,N> &v) {
	return v*v;
}
template<typename T, int N>
inline T length(const tvecn<T,N> &v) {
	return sqrt(sqr(v));
}
template<typename T, int N>
inline tvecn<T,N> norm(const tvecn<T,N> &v) {
	return v/length(v);
}

// Comparisons
template<typename T, int N>
inline bool operator ==(const tvecn<T,N> &a, const tvecn<T,N> &b) {
    for(int i = 0; i < N; ++i) {
        if(a.data[i] != b.data[i]) {
            return false;
        }
    }
    return true;
}
template<typename T, int N>
inline bool operator !=(const tvecn<T,N> &a, const tvecn<T,N> &b) {
    return !(a==b);
}

#endif // VECN_HPP
