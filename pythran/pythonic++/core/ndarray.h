#ifndef PYTHONIC_ARRAY_H
#define PYTHONIC_ARRAY_H
#include <cassert>
#include <iostream>
#include <array>
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
                raw_array() : data(nullptr), n(0), foreign(false) {}
                raw_array(size_t n) : data(new T[n]), n(n), foreign(false) { }
                raw_array(size_t n, T* d) : data(d), n(n), foreign(true) { }
                raw_array(raw_array<T>&& d) : data(d.data), n(d.n), foreign(false) {
                    d.data = nullptr;
                }

                ~raw_array() {
                    if(data and not foreign)
                        delete [] data;
                }
                private:
                bool foreign;
            };

        template<class T, unsigned long N>
            struct ndarray
            {
                impl::shared_ref< raw_array<T> > data;
                size_t offset_data;
                std::array<long,N> shape;

                //  types
                typedef typename std::conditional<N==1, const T&, const ndarray<T,N-1> >::type value_type;

                ndarray(std::initializer_list<size_t> s): offset_data(0)
                {
                    size_t r = 1;
                    auto is = shape.begin();
                    for(auto v :s )
                        r*=(*is++=v);
                    data = impl::shared_ref< raw_array<T> >(r);
                }

                ndarray(std::initializer_list<size_t> s, T value): offset_data(0)
                {
                    size_t r = 1;
                    auto is = shape.begin();
                    for(auto v :s )
                        r*=(*is++=v);
                    data = impl::shared_ref< raw_array<T> >(r);
                    std::fill(data->data, data->data+r, value);
                }
                ndarray(std::array<long, N> s): offset_data(0)
                {
                    size_t r = 1;
                    auto is = shape.begin();
                    for(auto v :s )
                        r*=(*is++=v);
                    data = impl::shared_ref< raw_array<T> >(r);
                }

                ndarray(T* d, long const* shp): offset_data(0)
                {
                    size_t r = 1;
                    long * is = shape.data();
                    long const* v = shp;
                    while(v!=shp+N)
                        r*=(*is++=*v++);
                    data = impl::shared_ref< raw_array<T> >(r, d);
                }
                ndarray<T,N>& operator=(ndarray<T,N> && other) {
                    data=std::move(other.data);
                    shape=std::move(other.shape);
                    return *this;
                }
                ndarray<T,N>& operator=(ndarray<T,N> const & other) {
                    data=other.data;
                    shape=other.shape;
                    return *this;
                }

                ndarray(impl::shared_ref< raw_array<T> > const& d, size_t ofs, long const* shp): offset_data(ofs)
                {
                    std::copy(shp, shp + N, shape.begin());
                    data = impl::shared_ref< raw_array<T> >(d);
                }

                ndarray(): data(impl::no_memory()), offset_data(0) {}
                ndarray(core::ndarray<T,N>&& array): data(std::move(array.data)), offset_data(array.offset_data), shape(array.shape)
                {
                }
                ndarray(const core::ndarray<T,N>& array): data(array.data), offset_data(array.offset_data), shape(array.shape)
                {
                }

                template<class... Types>
                    T& operator()(Types ... t)
                    {
                        return *at(data->data + offset_data, t...);
                    }

                template<class... Types>
                    T& operator()(Types ... t) const
                    {
                        return *at(data->data + offset_data, t...);
                    }

                template<class... Types>
                    size_t offset(int t0, int t1, Types ... tn) const
                    {
                        return offset(t0 * shape[N - sizeof...(Types) - 1] + t1, tn...); 
                    }

                size_t offset(int t0, int t1) const
                {
                    return t0 * shape[N-1] + t1;
                }

                T* at(T* from, size_t t)
                {
                    return from + t;
                }

                template<class... Types>
                    T* at(T* from, Types ... tn)
                    {
                        return from + offset(tn...);
                    }

                T* at(T* from, size_t t) const
                {
                    return from + t;
                }

                template<class... Types>
                    T* at(T* from, long t0, long t1) const
                    {
                        return from + t0 * shape[N-1] + t1;
                    }
                template<class... Types>
                    T* at(T* from, long t0, long t1, Types ... tn) const
                    {
                        return at(from, t0 * shape[N - sizeof...(Types) - 1] + t1, tn...);
                    }

            };

    }
}
#endif
