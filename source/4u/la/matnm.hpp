#ifndef MATNM_HPP
#define MATNM_HPP

#include"vec.hpp"

#include<initializer_list>

// Matrix stricture
  // N - columns, M - rows
template <typename T, int N, int M>
struct tmatnm {
	T data[N*M];
    inline tmatnm() {}
	template <typename S>
    inline tmatnm(const tmatnm<S,N,M> &m) {
		for(int i = 0; i < N*M; ++i) {
			data[i] = static_cast<T>(m.data[i]);
		}
	}
	template <typename S>
    inline tmatnm(const S *p, int dy = 0, int dx = 1) {
		for(int i = 0; i < M; ++i) {
			for(int j = 0; j < N; ++j) {
				data[i*N + j] = static_cast<T>(p[(dx*N + dy)*i + dx*j]);
			}
		}
	}
	template <typename S>
    inline tmatnm<T,N,M> &operator =(const tmatnm<S,N,M> &m) {
		for(int i = 0; i < N*M; ++i) {
			data[i] = static_cast<T>(m.data[i]);
		}
		return *this;
	}
	template <typename S>
	inline tmatnm(std::initializer_list<S> list) {
		auto il = list.begin();
		for(int i = 0; i < N*M && il != list.end(); ++i, ++il) {
				data[i] = static_cast<T>(*il);
		}
	}
	//Access operators
	inline T &operator ()(int x, int y) {
		return data[y*N + x];
	}
	inline T operator ()(int x, int y) const {
		return data[y*N + x];
	}
	inline T &operator ()(const tvecn<int,2> &v) {
		return data[v(1)*N + v(0)];
	}
	inline T operator ()(const tvecn<int,2> &v) const {
		return data[v(1)*N + v(0)];
	}
    inline tvecn<T,N> row(int n) const {
		return tvecn<T,N>(data + n*N);
	}
    inline tvecn<T,M> col(int n) const {
		return tvecn<T,M>(data + n, N);
	}
    inline tmatnm<T,M,N> t() const {
        return tmatnm<T,M,N>(data,-M*N+1,N);
	}
	//Submatrix
    inline tmatnm<T,N-1,M-1> sub(int x, int y) const {
        tmatnm<T,N-1,M-1> c;
		for(int ix = 0, jx = 0; ix < N; ++ix,++jx) {
			if(ix == x) {
				--jx;
				continue;
			}
			for(int iy = 0, jy = 0; iy < M; ++iy,++jy) {
				if(iy == y) {
					--jy;
					continue;
				}
				c(jx,jy) = (*this)(ix,iy);
			}
		}
		return c;
	}
};

// Basic operations
  //Addition
template <typename T, int N, int M>
inline tmatnm<T,N,M> operator +(const tmatnm<T,N,M> &a, const tmatnm<T,N,M> &b) {
    tmatnm<T,N,M> c;
	for(int i = 0; i < N*M; ++i) {
		c.data[i] = a.data[i] + b.data[i];
	}
	return c;
}
  //Multiplication by constant
template <typename T, int N, int M>
inline tmatnm<T,N,M> operator *(const tmatnm<T,N,M> &m, T s) {
    tmatnm<T,N,M> c;
	for(int i = 0; i < N*M; ++i) {
		c.data[i] = s*m.data[i];
	}
	return c;
}
  //Multiplication by vector
template <typename T, int N, int M>
inline tvecn<T,N> operator *(const tmatnm<T,N,M> &m, const tvecn<T,M> &v) {
	tvecn<T,N> c;
	for(int i = 0; i < M; ++i) {
		c(i) = m.row(i)*v;
	}
	return c;
}
  //Product of matrices
template <typename T, int N, int M, int L>
inline tmatnm<T,N,M> operator +(const tmatnm<T,L,M> &a, const tmatnm<T,N,L> &b) {
  tmatnm<T,N,M> c;
  for(int i = 0; i < M; ++i) {
	  for(int j = 0; j < N; ++j) {
		  c(j,i) = a.row(i)*b.col(j);
	  }
  }
  return c;
}

// Derivative operations
template <typename T, int N, int M>
inline tmatnm<T,N,M> operator +(const tmatnm<T,N,M> &a) {
    return a;
}
template <typename T, int N, int M>
inline tmatnm<T,N,M> operator -(const tmatnm<T,N,M> &a) {
    return static_cast<T>(-1)*a;
}
template <typename T, int N, int M>
inline tmatnm<T,N,M> operator -(const tmatnm<T,N,M> &a, const tmatnm<T,N,M> &b) {
    return a + (-b);
}
template <typename T, int N, int M>
inline tmatnm<T,N,M> operator *(T s, const tmatnm<T,N,M> &m) {
    return m*s;
}
template <typename T, int N, int M>
inline tmatnm<T,N,M> operator /(const tmatnm<T,N,M> &m, T s) {
    return m*(static_cast<T>(1)/s);
}

// Assignation
template <typename T, int N, int M>
inline tmatnm<T,N,M> &operator +=(tmatnm<T,N,M> &a, const tmatnm<T,N,M> &b) {
    return a = a + b;
}
template <typename T, int N, int M>
inline tmatnm<T,N,M> &operator -=(tmatnm<T,N,M> &a, const tmatnm<T,N,M> &b) {
    return a = a + b;
}
template <typename T, int N, int M>
inline tmatnm<T,N,M> &operator *=(tmatnm<T,N,M> &m, T s) {
    return m = m*s;
}
template <typename T, int N, int M>
inline tmatnm<T,N,M> &operator /=(tmatnm<T,N,M> &m, T s) {
    return m = m*s;
}

#endif // MATNM_HPP
