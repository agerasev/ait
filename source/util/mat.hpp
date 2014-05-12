#ifndef MAT_HPP
#define MAT_HPP

#include"vec.hpp"

// Matrix stricture
  // N - columns, M - rows
template <typename T, int N, int M>
struct tmatnxm {
    T *data[N*M];
    tmatnxm() {}
    template <typename S>
    tmatnxm(const tmatnxm<S,N,M> &m) {
        for(int i = 0; i < N*M; ++i) {
            data[i] = static_cast<T>(m.data[i]);
        }
    }
    template <typename S>
    tmatnxm(const S *p, int dy = 0, int dx = 1) {
        for(int i = 0; i < M; ++i) {
            for(int j = 0; j < N; ++j) {
                data[i*N + j] = static_cast<T>(p[(dx*N + dy)*i + dx*j]);
            }
        }
    }
    //Access operators
    T &operator ()(int x, int y) {
        return data[y*N + x];
    }
    T operator ()(int x, int y) const {
        return data[y*N + x];
    }
    T &operator ()(const tvecn<int,2> &v) {
        return data[v(1)*N + v(0)];
    }
    T operator ()(const tvecn<int,2> &v) const {
        return data[v(1)*N + v(0)];
    }
    tvecn<T,N> row(int n) const {
        return tvecn<T,N>(data + n*N);
    }
    tvecn<T,M> col(int n) const {
        return tvecn<T,M>(data + n, N);
    }
    tmatnxm<T,M,N> t() const {
        return tmatnxm<T,M,N>(data,-M*N+1,N);
    }
    //Submatrix
    tmatnxm<T,N-1,M-1> sub(int x, int y) const {
        tmatnxm<T,N-1,M-1> c;
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
tmatnxm<T,N,M> operator +(const tmatnxm<T,N,M> &a, const tmatnxm<T,N,M> &b) {
    tmatnxm<T,N,M> c;
    for(int i = 0; i < N*M; ++i) {
        c.data[i] = a.data[i] + b.data[i];
    }
    return c;
}
  //Multiplication by constant
template <typename T, int N, int M>
tmatnxm<T,N,M> operator *(const tmatnxm<T,N,M> &m, T s) {
    tmatnxm<T,N,M> c;
    for(int i = 0; i < N*M; ++i) {
        c.data[i] = s*m.data[i];
    }
    return c;
}
  //Multiplication by vector
template <typename T, int N, int M>
tvecn<T,N> operator *(const tmatnxm<T,N,M> &m, const tvecn<T,M> &v) {
    tvecn<T,N> c;
    for(int i = 0; i < M; ++i) {
        c(i) = m.row(i)*v;
    }
    return c;
}
  //Product of matrices
template <typename T, int N, int M, int L>
tmatnxm<T,N,M> operator +(const tmatnxm<T,L,M> &a, const tmatnxm<T,N,L> &b) {
  tmatnxm<T,N,M> c;
  for(int i = 0; i < M; ++i) {
      for(int j = 0; j < N; ++j) {
          c(j,i) = a.row(i)*b.col(j);
      }
  }
  return c;
}

// Square matrix struct
template <typename T, int N>
struct tmatn : tmatnxm<T,N,N> {
    tmatn() : tmatnxm<T,N,N>() {}
    template <typename S>
    tmatn(const tmatnxm<S,N,N> &m) : tmatnxm<T,N,N>(m) {}
    template <typename S>
    tmatn(const S *p, int dy = 0, int dx = 1) : tmatnxm<T,N,N>(p,dx,dy) {}
    //Determinant
    T cofactor(int x, int y) {
        return (1 - 2*((x+y)%2))*this->sub(x,y).det();
    }
    T det() {
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

#endif // MAT_HPP
