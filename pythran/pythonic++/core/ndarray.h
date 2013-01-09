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
                raw_array() : data(nullptr), n(0), foreign(false){}
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

        template<class T, unsigned long V>
            struct ndarray_helper;

        template<class T, unsigned long N, unsigned long V>
            struct apply_to_tuple;

        template<class T, unsigned long N>
            struct ndarray
            {
                impl::shared_ref< raw_array<T> > data;
                size_t offset_data;
                std::array<long,N> shape;

                //  types
                typedef typename ndarray_helper<T,N>::const_result_type value_type;

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

                ndarray(std::array<long, N> const& s): offset_data(0)
                {
                    size_t r = 1;
                    auto is = shape.begin();
                    for(auto v :s )
                        r*=(*is++=v);
                    data = impl::shared_ref< raw_array<T> >(r);
                }

                ndarray(T* d, long const* shp, long const size): offset_data(0)
                {
                    std::copy(shp, shp + N, shape.begin());
                    data = impl::shared_ref< raw_array<T> >(size, d);
                }

                ndarray(impl::shared_ref< raw_array<T> > const& d, size_t ofs, long const* shp): offset_data(ofs)
                {
                    std::copy(shp, shp + N, shape.begin());
                    data = impl::shared_ref< raw_array<T> >(d);
                }

                ndarray(): data(impl::no_memory()), offset_data(0) {}

                ndarray(core::ndarray<T,N>&& array): data(std::move(array.data)), offset_data(array.offset_data), shape(array.shape) {}

                ndarray(const core::ndarray<T,N>& array): data(array.data), offset_data(array.offset_data), shape(array.shape) {}

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


                template<class... Types>
                    typename ndarray_helper<T,N-sizeof...(Types)+1>::result_type operator()(Types ... t)
                    {
                        return ndarray_helper<T,N-sizeof...(Types)+1>::at(*this, offset(t...));
                    }

                template<class... Types>
                    typename ndarray_helper<T,N-sizeof...(Types)+1>::const_result_type operator()(Types ... t) const
                    {
                        return ndarray_helper<T,N-sizeof...(Types)+1>::at(*this, offset(t...));
                    }

                template<class... Types>
                    size_t offset(int t0, int t1, Types ... tn) const
                    {
                        return offset(t0 * shape[N - sizeof...(Types) - 1] + t1, tn...); 
                    }

                size_t offset(int t0, int t1) const
                {
                    return offset_data + t0 * shape[N-1] + t1;
                }

                size_t offset(int t0) const
                {
                    return offset_data + t0 * shape[N-1];
                }

                typename ndarray_helper<T, N>::result_type operator[](size_t t)
                {
                    if(t>=shape[0])
                        throw IndexError("index out of bounds");
                    return ndarray_helper<T, N>::get(*this, t);
                }

                typename ndarray_helper<T, N>::const_result_type operator[](const size_t t) const
                {
                    if(t>=shape[0])
                        throw IndexError("index out of bounds");
                    return ndarray_helper<T, N>::get(*this, t);
                }

        template<class... C>
                typename core::ndarray_helper<T, N-sizeof...(C) +1>::result_type operator[](std::tuple<C...> t)
                {
                    return apply_to_tuple<T,N,sizeof...(C)-1>::builder(*this, t, std::get<sizeof...(C)-1>(t));
                }

        template<class... C>
                typename core::ndarray_helper<T, N-sizeof...(C) +1>::const_result_type operator[](std::tuple<C...> t) const
                {
                    return apply_to_tuple<T,N,sizeof...(C)-1>::builder(*this, t, std::get<sizeof...(C)-1>(t));
                }
            };

        template<class T, unsigned long V>
            struct ndarray_helper
            {
                typedef core::ndarray<T,V-1> result_type;
                typedef const core::ndarray<T,V-1> const_result_type;

                static result_type get(ndarray<T,V>& array, size_t t)
                {
                    auto iter = array.shape.begin() + 1;
                    long offset = 0;
                    while(iter!= array.shape.begin() + V)
                        offset += *iter++;
                    return core::ndarray<T,V-1>(array.data, array.offset_data + t*offset, array.shape.begin() + 1);
                }

                static const_result_type get(ndarray<T,V> const& array, const size_t t)
                {
                    auto iter = array.shape.begin() + 1;
                    long offset = 0;
                    while(iter!= array.shape.begin() + V)
                        offset += *iter++;
                    return core::ndarray<T,V-1>(array.data, array.offset_data + t*offset, array.shape.begin() + 1);
                }

                template<unsigned long W>
                    static result_type at(ndarray<T,W> & array, size_t offset)
                    {
                        return core::ndarray<T,V-1>(array.data, offset, array.shape.begin() + 1);
                    }

                template<unsigned long W>
                    static const_result_type at(ndarray<T,W> const& array, size_t offset)
                    {
                        return core::ndarray<T,V-1>(array.data, offset, array.shape.begin() + 1);
                    }
            };


        template<class T>
            struct ndarray_helper<T,1>
            {
                typedef T& result_type;
                typedef const T& const_result_type;

                static result_type get(ndarray<T,1>& array, size_t t)
                {
                    return array(t);
                }

                static const_result_type get(ndarray<T,1> const& array, const size_t t)
                {
                    return array(t);
                }

                template<unsigned long W>
                static result_type at(ndarray<T,W>& array, size_t t)
                {
                    return *(array.data->data + t);
                }

                template<unsigned long W>
                static const_result_type at(ndarray<T,W> const& array, size_t const t)
                {
                    return *(array.data->data + t);
                }

            };

        template<class T, unsigned long N, unsigned long V>
            struct apply_to_tuple
            {
                template<typename... C, typename... S>
                    static typename core::ndarray_helper<T, N-sizeof...(C) +1>::result_type builder(ndarray<T,N>& array, std::tuple<C...>& t, S... s)
                    {
                        return apply_to_tuple<T,N,V-1>::builder(array, t, std::get<V-1>(t), s...);
                    }

                template<typename... C, typename... S>
                    static typename core::ndarray_helper<T, N-sizeof...(C) +1>::const_result_type builder(ndarray<T,N> const& array, std::tuple<C...> const& t, S... s)
                    {
                        return apply_to_tuple<T,N,V-1>::builder(array, t, std::get<V-1>(t), s...);
                    }
            };

        template<class T, unsigned long N>
            struct apply_to_tuple<T,N,0>
            {
                template<typename... C, typename... S>
                    static typename core::ndarray_helper<T, N-sizeof...(C) +1>::result_type builder(ndarray<T,N>& array, std::tuple<C...>& t, S... s)
                    {
                        return array(s...);
                    }

                template<typename... C, typename... S>
                    static typename core::ndarray_helper<T, N-sizeof...(C) +1>::const_result_type builder(ndarray<T,N> const& array, std::tuple<C...> const& t, S... s)
                    {
                        return array(s...);
                    }
            };


    }
}
#endif
