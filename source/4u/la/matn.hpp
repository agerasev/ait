#ifndef MATN_HPP
#define MATN_HPP

#include"matnm.hpp"

// Square matrix struct
template <typename T, int N>
struct tmatnm<T,N,N> {
    T data[N*N];
    inline tmatnm() {}
    template <typename S>
    inline tmatnm(const tmatnm<S,N,N> &m) {
        for(int i = 0; i < N*N; ++i) {
            data[i] = static_cast<T>(m.data[i]);
        }
    }
    template <typename S>
    inline tmatnm(const S *p, int dy = 0, int dx = 1) {
        for(int i = 0; i < N; ++i) {
            for(int j = 0; j < N; ++j) {
                data[i*N + j] = static_cast<T>(p[(dx*N + dy)*i + dx*j]);
            }
        }
    }
    template <typename S>
    inline tmatnm<T,N,N> &operator =(const tmatnm<S,N,N> &m) {
        for(int i = 0; i < N*N; ++i) {
            data[i] = static_cast<T>(m.data[i]);
        }
        return *this;
    }
	template <typename S>
	inline tmatnm(std::initializer_list<S> list) {
		auto il = list.begin();
		for(int i = 0; i < N*N && il != list.end(); ++i, ++il) {
				data[i] = static_cast<T>(*il);
		}
	}
private:
	template <int Len, typename _T, int _N>
	struct __Unroller__
	{
		template <typename S, typename ... Args>
		inline static void unroll(tmatnm<_T,_N,_N> &mat, S &arg, Args &... args)
		{
			mat.data[_N*_N - Len] = static_cast<_T>(arg);
			__Unroller__<Len-1,_T,_N>::unroll(mat, args ...);
		}
	};
	template<typename _T, int _N>
	struct __Unroller__<1,_T,_N>
	{
		template <typename S>
		inline static void unroll(tmatnm<_T,_N,_N> &mat, S &arg)
		{
			mat.data[_N*_N - 1] = static_cast<_T>(arg);
		}
	};
public:
	template <typename ... Args>
	inline tmatnm(Args ... args) {
		__Unroller__<N*N,T,N>::unroll(*this,args...);
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
    inline tvecn<T,N> col(int n) const {
        return tvecn<T,N>(data + n, N);
    }
    inline tmatnm<T,N,N> t() const {
        return tmatnm<T,N,N>(data,-N*N+1,N);
    }
    //Submatrix
    inline tmatnm<T,N-1,N-1> sub(int x, int y) const {
        tmatnm<T,N-1,N-1> c;
        for(int ix = 0, jx = 0; ix < N; ++ix,++jx) {
            if(ix == x) {
                --jx;
                continue;
            }
            for(int iy = 0, jy = 0; iy < N; ++iy,++jy) {
                if(iy == y) {
                    --jy;
                    continue;
                }
                c(jx,jy) = (*this)(ix,iy);
            }
        }
        return c;
    }
	//Determinant
	inline T cofactor(int x, int y) const {
		return (1 - 2*((x+y)%2))*this->sub(x,y).det();
	}

	/* I need to create struct here because function
	 * template partial specialization is not allowed */
private:
	template <typename _T, int _N>
	struct __Determinator__
	{
		inline static _T det(const tmatnm<_T,_N,_N> &mat)
		{
			_T c = static_cast<_T>(0);
			const int rc = 0;
			for(int i = 0; i < N; ++i) {
				c += mat(i,rc)*mat.cofactor(i,rc);
			}
			return c;
		}
	};
	template <typename _T>
	struct __Determinator__<_T,1>
	{
		inline static _T det(const tmatnm<_T,1,1> &mat)
		{
			return mat.data[0];
		}
	};
public:
	inline T det() const {
		return __Determinator__<T,N>::det(*this);
	}
	/* Adjugate matrix */
	inline tmatnm<T,N,N> adj() const
	{
		tmatnm<T,N,N> ret;
		for(int i = 0; i < N; ++i)
		{
			for(int j = 0; j < N; ++j)
			{
				ret(j,i) = cofactor(i,j);
			}
		}
		return ret;
	}
	/* Inverse matrix */
	inline tmatnm<T,N,N> invert() const
	{
		return this->adj()/this->det();
	}
};

// Diagonal matrix creation
template <typename T, typename S, int N>
inline tmatnm<T,N,N> diag(S diag) {
	tmatnm<T,N,N> ret;
    for(int iy = 0; iy < N; ++iy) {
        for(int ix = 0; ix < N; ++ix) {
            if(ix == iy) {
				ret(ix,iy) = static_cast<T>(diag);
            } else {
				ret(ix,iy) = static_cast<T>(0);
            }
        }
    }
	return ret;
}


#endif // MATN_HPP
