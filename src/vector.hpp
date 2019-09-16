#ifndef HLS_VECTOR_HPP
#define HLS_VECTOR_HPP

#include<iostream>
#include<functional>
#include<assert.h>

namespace hls{

    // vector element id type
    // we limit the vector size to 16384
    typedef unsigned short vid_t;

    // vector with static memory allocation
    // T: element type
    // N: vector size
    template<typename T, vid_t N>
    class StaticVector {
    protected:
        T _data[N];

    public:
        // blank constructor
        StaticVector() {};
        // copy constructor
        StaticVector(const StaticVector<T, N> &vec);
        // initialize all the elements with a same constant
        StaticVector(const T &v);

        // get elements
        T &operator[](const vid_t &id);

        // vector-scalar operators
        StaticVector<T, N> operator+(const T &v);
        StaticVector<T, N> operator-(const T &v);
        StaticVector<T, N> operator*(const T &v);
        StaticVector<T, N> operator/(const T &v);

        // vector-vector operators
        StaticVector<T, N> operator=(const StaticVector<T, N> &vec);
        StaticVector<T, N> operator+(const StaticVector<T, N> &vec);
        StaticVector<T, N> operator-(const StaticVector<T, N> &vec);
        StaticVector<T, N> operator*(const StaticVector<T, N> &vec);
        StaticVector<T, N> operator/(const StaticVector<T, N> &vec);

        // logic function
        bool operator==(const StaticVector<T, N> &vec);
        bool operator!=(const StaticVector<T, N> &vec);

        // aggregate function
        T sum();
        T average();
        T max();
        T min();
    };

    // iterators to save the words for writing for loops
    template<typename T, vid_t N>
    inline void unary_iterator(StaticVector<T, N> &v, std::function<void(T &)> f)
    {
        for (vid_t i = 0; i < N; i++)
            f(v[i]);
    }

    template<typename T, vid_t N>
    inline void binary_iterator(StaticVector<T, N> &v1, StaticVector<T, N> &v2,
        std::function<void(T &, T &)> f)
    {
        for (vid_t i = 0; i < N; i++)
            f(v1[i], v2[i]);
    }

    template<typename T, vid_t N>
    inline void binary_iterator(StaticVector<T, N> &v1, StaticVector<T, N> &v2,
        StaticVector<T, N> &v3, std::function<void(T &, T &, T &)> f)
    {
        for (vid_t i = 0; i < N; i++)
            f(v1[i], v2[i], v3[i]);
    }

    template<typename T, vid_t N>
    StaticVector<T, N>::StaticVector(const StaticVector<T, N> &vec)
    {
        binary_iterator<T, N>(*this, vec, [](T &a, T &b){a = b;});
    }

    template<typename T, vid_t N>
    StaticVector<T, N>::StaticVector(const T &v)
    {
        unary_iterator(*this, [](T &a){a = v;});
    }

    template<typename T, vid_t N>
    T &StaticVector<T, N>::operator[](const vid_t &id)
    {
        assert(id < N);
        return _data[id];
    }

    template<typename T, vid_t N>
    StaticVector<T, N> StaticVector<T, N>::operator+(const T &v)
    {
        StaticVector<T, N> res;
        binary_iterator(res, *this, [](T &a, T &b){a = b + v;});
    }
}

#endif