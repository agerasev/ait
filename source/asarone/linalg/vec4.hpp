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
    using z = comp<2>;
    using w = comp<3>;
};

#endif // VEC4_HPP
