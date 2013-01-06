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
                raw_array(size_t n) : data(new T[n]), n(n) { }
                raw_array(size_t n, T* d) : data(d), n(n) { }
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
                size_t offset_data;
                long shape[N];

                //  types
                typedef T value_type;

                ndarray(std::initializer_list<size_t> s): offset_data(0)
                {
                    size_t r = 1;
                    long * is = shape;
                    for(auto v :s )
                        r*=(*is++=v);
                    data = impl::shared_ref< raw_array<T> >(r);
                }

                ndarray(T* d, long const* shp, long const size): offset_data(0)
                {
                    std::copy(shp, shp + N, shape);
                    data = impl::shared_ref< raw_array<T> >(size, d);
                }

                ndarray(impl::shared_ref< raw_array<T> > const& d, size_t ofs, long const* shp): offset_data(ofs)
                {
                    std::copy(shp, shp + N, shape);
                    data = impl::shared_ref< raw_array<T> >(d);
                }

                ndarray(): data(impl::no_memory()), offset_data(0) {}
                ndarray(core::ndarray<T,N>&& array): data(std::move(array.data)), offset_data(array.offset_data)
                {
                    std::copy(array.shape, array.shape + N, shape);
                }
                ndarray(const core::ndarray<T,N>& array): data(array.data), offset_data(array.offset_data)
                {
                    std::copy(array.shape, array.shape + N, shape);
                }

                template<class... Types>
                    T& operator()(Types const... t)
                    {
                        return *at(data->data + offset_data, t...);
                    }

                template<class... Types>
                    T& operator()(Types const... t) const
                    {
                        return *at(data->data + offset_data, t...);
                    }

                template<class... Types>
                    size_t offset(int const t0, int const t1, Types const... tn)
                    {
                        return offset(t0 * shape[N - sizeof...(Types) - 1] + t1, tn...); 
                    }

                size_t offset(int const t0, int const t1)
                {
                    return t0 * shape[N-1] + t1;
                }

                T* at(T* from, size_t const t)
                {
                    return from + t;
                }

                template<class... Types>
                    T* at(T* from, Types const... tn)
                    {
                        return at(from, offset(tn...));
                    }

                T* at(T* from, size_t const t) const
                {
                    return from + t;
                }

                template<class... Types>
                    T* at(T* from, Types const... tn) const
                    {
                        return at(from, offset(tn...));
                    }
            };
    }
}
#endif
