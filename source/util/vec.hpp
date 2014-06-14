#ifndef TVECN_H
#define TVECN_H

template<typename T, int N>
struct tvecn {
    T data[N];
    tvecn() {

    }
    template <typename S>
    tvecn(const tvecn<S,N> &av) {
        for(int i = 0; i < N; ++i) {
            data[i] = static_cast<T>(av.data[i]);
        }
    }
    tvecn(const T *p, int d = 1) {
        for(int i = 0; i < N; ++i) {
            data[i] = p[d*i];
        }
    }
    T &operator ()(int n) {
        return data[n];
    }
    T operator ()(int n) const {
        return data[n];
    }
};

// Basic operations
  // Addition
template<typename T, int N>
tvecn<T,N> operator +(const tvecn<T,N> &a, const tvecn<T,N> &b) {
    tvecn<T,N> c;
    for(int i = 0; i < N; ++i) {
        c.data[i] = a.data[i] + b.data[i];
    }
    return c;
}
  // Multiplication by constatnt
template<typename T, typename S, int N>
tvecn<T,N> operator *(S a, const tvecn<T,N> &b) {
    tvecn<T,N> c;
    for(int i = 0; i < N; ++i) {
        c.data[i] = static_cast<T>(a)*b.data[i];
    }
    return c;
}
  // Scalar product
template<typename T, int N>
T operator *(const tvecn<T,N> &a, const tvecn<T,N> &b) {
    T c = static_cast<T>(0);
    for(int i = 0; i < N; ++i) {
        c += a.data[i]*b.data[i];
    }
    return c;
}

// Derivative operations
template<typename T, typename S, int N>
tvecn<T,N> operator *(const tvecn<T,N> &b, S a) {
    return a*b;
}
template<typename T, int N>
tvecn<T,N> operator -(const tvecn<T,N> &a) {
    return static_cast<T>(-1)*a;
}
template<typename T, int N>
tvecn<T,N> operator -(const tvecn<T,N> &a, const tvecn<T,N> &b) {
    return a+(-b);
}

template <typename T>
struct tvec2 : tvecn<T,2> {
    tvec2() : tvecn<T,2>() {}
    template <typename S>
    tvec2(const tvecn<S,2> &av) : tvecn<T,2>(av) {}
    tvec2(const T *p, int d = 1) : tvecn<T,2>(p,d) {}
    tvec2(T ax, T ay) {
        this->data[0] = ax;
        this->data[1] = ay;
    }
    T &x() {return this->data[0];}
    T &y() {return this->data[1];}
    T x() const {return this->data[0];}
    T y() const {return this->data[1];}
};

// Pseudo cross product
template <typename T>
T operator ^(const tvecn<T,2> &a, const tvecn<T,2> &b) {
    return a(0)*b(1) - a(1)*b(0);
}

template <typename T>
struct tvec3 : tvecn<T,3> {
    tvec3() : tvecn<T,3>() {}
    template <typename S>
    tvec3(const tvecn<S,3> &av) : tvecn<T,3>(av) {}
    tvec3(const T *p, int d = 1) : tvecn<T,3>(p,d) {}
    tvec3(T ax, T ay, T az) {
        this->data[0] = ax;
        this->data[1] = ay;
        this->data[2] = az;
    }
    T &x() {return this->data[0];}
    T &y() {return this->data[1];}
    T &z() {return this->data[2];}
    T x() const {return this->data[0];}
    T y() const {return this->data[1];}
    T z() const {return this->data[2];}
};

// Cross product
template <typename T>
tvecn<T,3> operator ^(const tvecn<T,3> &a, const tvecn<T,3> &b) {
    return a(0)*b(1) - a(1)*b(0);
}

template <typename T>
struct tvec4 : tvecn<T,4> {
    tvec4() : tvecn<T,4>() {}
    template <typename S>
    tvec4(const tvecn<S,4> &av) : tvecn<T,4>(av) {}
    tvec4(const T *p, int d = 1) : tvecn<T,4>(p,d) {}
    tvec4(T ax, T ay, T az, T aw) {
        this->data[0] = ax;
        this->data[1] = ay;
        this->data[2] = az;
        this->data[3] = aw;
    }
    T &x() {return this->data[0];}
    T &y() {return this->data[1];}
    T &z() {return this->data[2];}
    T &w() {return this->data[3];}
    T x() const {return this->data[0];}
    T y() const {return this->data[1];}
    T z() const {return this->data[2];}
    T w() const {return this->data[3];}
};

typedef tvec2<double> vec2;
typedef tvec2<int> ivec2;
typedef tvec3<double> vec3;
typedef tvec3<int> ivec3;
typedef tvec4<double> vec4;
typedef tvec4<int> ivec4;

#ifdef UNITTEST
void unittestTVECN() {

}
#endif // UNITTEST

#endif // TVECN_H
