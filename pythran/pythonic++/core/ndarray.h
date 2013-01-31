#ifndef PYTHONIC_ARRAY_H
#define PYTHONIC_ARRAY_H
#include <cassert>
#include <iostream>
#include <iterator>
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

        template<class T, unsigned long N>
            struct ndarray;

        template<class T, unsigned long N, unsigned long V>
            struct apply_to_tuple;

        template<class T, unsigned long N>
            struct ndarray_iterator: std::iterator< std::random_access_iterator_tag, typename ndarray_helper<T,N>::result_type >
            {
                ndarray<T,N> const& ref_array;
                long value;
                long step;

                ndarray_iterator() {}
                ndarray_iterator(long v, ndarray<T,N> const& ref, long s) : value(v), step(s), ref_array(ref) {}
                typename ndarray_helper<T,N>::result_type operator*() { return ref_array[value]; }

                ndarray_iterator<T,N>& operator++() { value+=step; return *this; }
                ndarray_iterator<T,N> operator++(int) { ndarray_iterator<T,N> self(*this); value+=step; return self; }
                ndarray_iterator<T,N>& operator+=(long n) { value+=step*n; return *this; }
                bool operator!=(ndarray_iterator<T,N> const& other) { return value != other.value; }
                bool operator<(ndarray_iterator<T,N> const& other) { return value < other.value; }
                long operator-(ndarray_iterator<T,N> const& other) { return (value - other.value)/step; }
            };

        template<class T, unsigned long N>
            struct ndarray_flat_iterator: std::iterator< std::random_access_iterator_tag, T >
            {
                ndarray<T,N> const& ref_array;
                long value;
                long step;

                ndarray_flat_iterator() {}
                ndarray_flat_iterator(long v, ndarray<T,N> const& ref, long s) : value(v), step(s), ref_array(ref) {}
                T& operator*() { return ref_array.data->data[value + *(ref_array.offset_data)]; }

                ndarray_flat_iterator<T,N>& operator++() { value+=step; return *this; }
                ndarray_flat_iterator<T,N> operator++(int) { ndarray_iterator<T,N> self(*this); value+=step; return self; }
                ndarray_flat_iterator<T,N>& operator+=(long n) { value+=step*n; return *this; }
                bool operator!=(ndarray_flat_iterator<T,N> const& other) { return value != other.value; }
                bool operator<(ndarray_flat_iterator<T,N> const& other) { return value < other.value; }
                long operator-(ndarray_flat_iterator<T,N> const& other) { return (value - other.value)/step; }
            };

        template<class T, unsigned long N>
            struct ndarray_flat
            {
                ndarray<T,N> const& ref_array;

                //types
                typedef ndarray_flat_iterator<T,N> iterator;
                typedef T& value_type;

                ndarray_flat() {}
                ndarray_flat(ndarray<T,N> const& ref) : ref_array(ref) {}

                iterator begin() const
                {
                    return ndarray_flat_iterator<T,N>(0,ref_array,1);
                }

                iterator end() const
                {
                    return ndarray_flat_iterator<T,N>(
                            std::accumulate(ref_array.shape->begin(), ref_array.shape->end(), 1, std::multiplies<int>()),
                            ref_array,
                            1);
                }
            };

        template<class T, unsigned long N>
            struct ndarray
            {
                impl::shared_ref< raw_array<T> > data;
                impl::shared_ref<size_t> offset_data;
                impl::shared_ref<std::array<long,N>> shape;

                //  types
                typedef typename ndarray_helper<T,N>::const_result_type value_type;
                typedef ndarray_iterator<T,N> iterator;

                ndarray(std::initializer_list<size_t> s): offset_data(impl::shared_ref<size_t>(0))
                {
                    size_t r = 1;
                    shape = impl::shared_ref<std::array<long,N>>();
                    auto is = shape->begin();
                    for(auto v :s )
                        r*=(*is++=v);
                    data = impl::shared_ref< raw_array<T> >(r);
                }

                ndarray(std::initializer_list<size_t> s, T value): offset_data(impl::shared_ref<size_t>(0))
                {
                    size_t r = 1;
                    auto is = shape->begin();
                    for(auto v :s )
                        r*=(*is++=v);
                    data = impl::shared_ref< raw_array<T> >(r);
                    std::fill(data->data, data->data+r, value);
                }

                ndarray(std::array<long, N> const& s): offset_data(impl::shared_ref<size_t>(0))
                {
                    size_t r = 1;
                    auto is = shape->begin();
                    for(auto v :s )
                        r*=(*is++=v);
                    data = impl::shared_ref< raw_array<T> >(r);
                }

                ndarray(T* d, long const* shp, long const size): offset_data(impl::shared_ref<size_t>(0))
                {
                    std::copy(shp, shp + N, shape->begin());
                    data = impl::shared_ref< raw_array<T> >(size, d);
                }

                ndarray(impl::shared_ref< raw_array<T> > const& d, size_t ofs, long const* shp): offset_data(impl::shared_ref<size_t>(ofs))
                {
                    std::copy(shp, shp + N, shape->begin());
                    data = impl::shared_ref< raw_array<T> >(d);
                }

                ndarray(): data(impl::no_memory()), offset_data(impl::shared_ref<size_t>(0)), shape(impl::no_memory()) {}

                ndarray(core::ndarray<T,N>&& array): data(std::move(array.data)), offset_data(std::move(array.offset_data)), shape(std::move(array.shape)) {}

                ndarray(const core::ndarray<T,N>& array): data(array.data), offset_data(array.offset_data), shape(array.shape) {}

                ndarray<T,N>& operator=(ndarray<T,N> && other) {
                    if(*offset_data>0 || (shape->data() && std::accumulate(shape->begin(), shape->end(), 0)!=data->n))
                    {
                        std::copy(other.data->data + *other.offset_data, other.data->data + *other.offset_data + std::accumulate(other.shape->begin(), other.shape->end(), 0), data->data + *offset_data);

                    }
                    else
                    {
                        data=std::move(other.data);
                        offset_data=std::move(other.offset_data);
                        shape=std::move(other.shape);
                    }
                    return *this;
                }

                ndarray<T,N>& operator=(ndarray<T,N> const & other) {
                    if(*offset_data>0 || (shape->data() && std::accumulate(shape->begin(), shape->end(), 0)!=data->n))
                    {
                        std::copy(other.data->data + *other.offset_data, other.data->data + *other.offset_data + std::accumulate(other.shape->begin(), other.shape->end(), 0), data->data + *offset_data);

                    }
                    else
                    {
                        shape=other.shape;
                        data=other.data;
                        offset_data=other.offset_data;
                    }
                    return *this;
                }

                template<class... Types>
                    typename ndarray_helper<T,N-sizeof...(Types)+1>::result_type operator()(Types ... t)
                    {
                        return ndarray_helper<T,N-sizeof...(Types)+1>::at(*this, t...);
                    }

                template<class... Types>
                    typename ndarray_helper<T,N-sizeof...(Types)+1>::const_result_type operator()(Types ... t) const
                    {
                        return ndarray_helper<T,N-sizeof...(Types)+1>::at(*this, t...);
                    }

                typename ndarray_helper<T, N>::result_type operator[](size_t t)
                {
                    if(t>=(*shape)[0])
                        throw IndexError("index out of bounds");
                    return ndarray_helper<T, N>::get(*this, t);
                }

                typename ndarray_helper<T, N>::const_result_type operator[](const size_t t) const
                {
                    if(t>=(*shape)[0])
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

                iterator begin() const
                {
                    return ndarray_iterator<T,N>(0,*this,1);
                }

                iterator end() const
                {
                    return ndarray_iterator<T,N>((*shape)[0],*this,1);
                }
            };

        template<class T, unsigned long V>
            struct ndarray_helper
            {
                typedef core::ndarray<T,V-1> result_type;
                typedef const core::ndarray<T,V-1> const_result_type;

                static result_type get(ndarray<T,V>& array, size_t t)
                {
                    long offset = std::accumulate(array.shape->begin() + 1, array.shape->begin() + V, 0);
                    return core::ndarray<T,V-1>(array.data, *array.offset_data + t*offset, array.shape->begin() + 1);
                }

                static const_result_type get(ndarray<T,V> const& array, const size_t t)
                {
                    long offset = std::accumulate(array.shape->begin() + 1, array.shape->begin() + V, 0);
                    return core::ndarray<T,V-1>(array.data, *array.offset_data + t*offset, array.shape->begin() + 1);
                }

                template<unsigned long W>
                    static result_type at(ndarray<T,W> & array, unsigned long t1)
                    {
                        long r = std::accumulate(array.shape->begin() +W-V+1, array.shape->begin() + W, 1, std::multiplies<int>());
                        return core::ndarray<T,V-1>(array.data, t1*r, array.shape->begin() + W - V + 1);
                    }

                template<unsigned long W>
                    static result_type at(ndarray<T,W> & array, unsigned long t1, unsigned long t2)
                    {
                        long r = std::accumulate(array.shape->begin() +W-V+1, array.shape->begin() + W, 1, std::multiplies<int>());
                        return core::ndarray<T,V-1>(array.data, (t1 * (*array.shape)[W-V] + t2)*r, array.shape->begin() + W - V);
                    }

                template<unsigned long W, class... C>
                    static result_type at(ndarray<T,W> & array, unsigned long t1, unsigned long t2, C... t)
                    {
                        return at(array, t1 * (*array.shape)[W-sizeof...(C)-V] + t2, t...);
                    }

                template<unsigned long W>
                    static const_result_type at(ndarray<T,W> const& array, unsigned long t1)
                    {
                        long r = std::accumulate(array.shape->begin() +W-V+1, array.shape->begin() + W, 1, std::multiplies<int>());
                        return core::ndarray<T,V-1>(array.data, t1*r, array.shape->begin() + W - V +1);
                    }

                template<unsigned long W>
                    static const_result_type at(ndarray<T,W> const& array, unsigned long t1, unsigned long t2)
                    {
                        long r = std::accumulate(array.shape->begin() +W-V+1, array.shape->begin() + W, 1, std::multiplies<int>());
                        return core::ndarray<T,V-1>(array.data, (t1 * (*array.shape)[W-V] + t2)*r, array.shape->begin() + W - V +1);
                    }

                template<unsigned long W, class... C>
                    static const_result_type at(ndarray<T,W> const& array, unsigned long t1, unsigned long t2, C... t)
                    {
                        return at(array, t1 * (*array.shape)[W-sizeof...(C)-V] + t2, t...);
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
                static result_type at(ndarray<T,W>& array, unsigned long t)
                {
                    return *(array.data->data + *array.offset_data + t);
                }

                template<unsigned long W>
                static result_type at(ndarray<T,W>& array, unsigned long t1, unsigned long t2)
                {
                    return *(array.data->data + *array.offset_data + t1 * (*array.shape)[W-1] + t2);
                }

                template<unsigned long W, class... C>
                static result_type at(ndarray<T,W>& array, unsigned long t1, unsigned long t2, C... t)
                {
                    return at(array, t1 * (*array.shape)[W-sizeof...(C)-1] + t2, t...);
                }

                template<unsigned long W>
                static const_result_type at(ndarray<T,W> const& array, unsigned long t)
                {
                    return *(array.data->data + t);
                }

                template<unsigned long W>
                static const_result_type at(ndarray<T,W> const& array, unsigned long t1, unsigned long t2)
                {
                    return *(array.data->data + t1 * (*array.shape)[W-1] + t2);
                }

                template<unsigned long W, class... C>
                static const_result_type at(ndarray<T,W> const& array, unsigned long t1, unsigned long t2, C... t)
                {
                    return at(array, t1 * (*array.shape)[W-sizeof...(C)-1] + t2, t...);
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
