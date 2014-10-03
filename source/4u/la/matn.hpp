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
    inline T cofactor(int x, int y) {
		return (1 - 2*((x+y)%2))*this->sub(x,y).det();
	}
    inline T det() {
		if(N <= 1) {
			return *(this->data);
		} else {
			T c = static_cast<T>(0);
			const int rc = 0;
			for(int i = 0; i < N; ++i) {
				c += cofactor(i,rc);
			}
			return c;
		}
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
