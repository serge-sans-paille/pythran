#ifndef PYTHONIC_ARRAY_H
#define PYTHONIC_ARRAY_H
#include <cassert>
#include <iostream>
#include <initializer_list>
#include "shared_ref.h"

namespace  pythonic {

    namespace core {

        template<class T>
            class raw_array {
                raw_array(raw_array<T> const& );

                public:

                T* data;
                size_t n;
                raw_array() : data(nullptr), n(0) {}
                raw_array(size_t n) : data(new T[n]), n(n) {
                }
                raw_array(raw_array<T>&& d) : data(d.data), n(d.n) {
                    d.data = nullptr;
                }

                ~raw_array() {
                    if(data)
                        delete [] data;
                }
            };

        template<class T, int N>
            struct ndarray
            {
                impl::shared_ref< raw_array<T> > data;
                long shape[N];

                ndarray(std::initializer_list<int> s)
                {
                    long r = 1;
                    long * is = shape;
                    for(auto v :s )
                        r*=(*is++=v);
                    data = impl::shared_ref< raw_array<T> >(r);
                }

                ndarray(): data(impl::no_memory()) {}
                ndarray(core::ndarray<T,N>&& array): data(std::move(array.data))
                {
                    std::copy(array.shape, array.shape + N, shape);
                }
                ndarray(const core::ndarray<T,N>& array): data(array.data)
                {
                    std::copy(array.shape, array.shape + N, shape);
                }

                template<class... Types>
                    T& operator()(Types... t)
                    {
                        return *at(data->data, t...);
                    }

                template<class... Types>
                    int offset(int t0, int t1, Types... tn)
                    {
                        return offset(t0 * shape[N - sizeof...(Types) - 1] + t1, tn...); 
                    }

                int offset(int t0, int t1)
                {
                    return t0 * shape[N-1] + t1;
                }

                T* at(T* from, int t)
                {
                    return from +t;
                }

                template<class... Types>
                    T* at(T* from, Types... tn)
                    {
                        return at(from, offset(tn...));
                    }
            };
    }
}
#endif
