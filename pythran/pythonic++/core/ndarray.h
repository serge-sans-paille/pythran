#ifndef PYTHONIC_ARRAY_H
#define PYTHONIC_ARRAY_H
#include <cassert>
#include <iostream>
#include <iterator>
#include <array>
#include <initializer_list>
#include "shared_ref.h"

#include <boost/simd/sdk/simd/native.hpp>
#ifdef __SSE__
#include <boost/simd/include/functions/unaligned_load.hpp>
#include <boost/simd/include/functions/unaligned_store.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/include/functions/store.hpp>
#endif

#include <mm_malloc.h>

#ifdef __SSE__
namespace std {

template <>
  void fill<double*, double> (double* first, double* last, const double& val) {
      size_t n = last - first;
      if(val == 0.) memset(first, sizeof(*first)*n, 0);
      else {
          typedef boost::simd::native<double, BOOST_SIMD_DEFAULT_EXTENSION> vS;
          static const std::size_t vN = boost::simd::meta::cardinal_of< vS >::value;
          static const size_t unroll_factor = 2;
          double *bound = first + n/(unroll_factor*vN) * (unroll_factor*vN);
          vS xval = boost::simd::splat<vS>(val);

          while(first< bound) {
              boost::simd::store<vS>( xval, first, 0);
              boost::simd::store<vS>( xval, first, vN);
              first+= vN * unroll_factor;
          }
          while(first<last)
              *first++=val;
      }
  }
}

#endif

namespace  pythonic {

    namespace core {

        template<class T>
            class raw_array {
                raw_array(raw_array<T> const& );

                public:

                T* data;
                size_t n;
                raw_array() : data(nullptr), n(0), foreign(false){}
                raw_array(size_t n) : data((T*)_mm_malloc(sizeof(T)*n, 32)), n(n), foreign(false) { }
                raw_array(size_t n, T* d) : data(d), n(n), foreign(true) { }
                raw_array(raw_array<T>&& d) : data(d.data), n(d.n), foreign(false) {
                    d.data = nullptr;
                }

                ~raw_array() {
                    if(data and not foreign)
                        _mm_free(data);
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

        template<class T>
        struct vectorized {
            typedef T type;
            static type broadcast(T v) { return v;}
        };
#ifdef __AVX__
        template<>
            struct vectorized<double> {
                typedef boost::simd::native<double, BOOST_SIMD_DEFAULT_EXTENSION> type;
                static type broadcast(double v) {
                    static const std::size_t N = boost::simd::meta::cardinal_of< type >::value;
                    return boost::simd::splat<type> (v);
                }
            };
#endif

        template<class T>
            struct broadcast {

                long size() const { return 0; }
                T __value;
                typename vectorized<T>::type _value;
                static constexpr unsigned long value = 0;
                broadcast(T v) : __value(v), _value(vectorized<T>::broadcast(v)) {}
#ifdef __AVX__
                typename vectorized<T>::type load(long ) const { return _value;}
#endif
                T operator[](long ) const {
                    return __value;
                }
            };

        template<class Op, class Arg0>
            struct numpy_uexpr {
                Arg0 arg0;
                typedef decltype(Op()(arg0[std::declval<long>()])) value_type;
                static constexpr unsigned long value = Arg0::value;
                numpy_uexpr(Arg0 const& arg0) : arg0(arg0) {
                }
#ifdef __AVX__
                auto load(long i) const -> decltype(Op()(arg0.load(i))) {
                    return Op()(arg0.load(i));
                }
#endif
                auto operator[](long i) const -> decltype(Op()(arg0[i])) {
                    return Op()(arg0[i]);
                }
                long size() const { return arg0.size(); }
            };
        template <class Op, class T0, unsigned long N0>
            struct numpy_uexpr<Op, ndarray<T0,N0>> {
                T0 *arg0;
                typedef decltype(Op()(arg0[std::declval<long>()])) value_type;
                static constexpr unsigned long value = N0;
                long _size;
                numpy_uexpr(ndarray<T0,N0> const& arg0 ) : arg0(arg0.data->data + *arg0.offset_data), _size(arg0.size()) {
                }
#ifdef __AVX__
                auto load(long i) const -> decltype(Op()( boost::simd::unaligned_load<boost::simd::native<T0, BOOST_SIMD_DEFAULT_EXTENSION>>(arg0,i) )) {
                    return Op()(boost::simd::unaligned_load<boost::simd::native<T0, BOOST_SIMD_DEFAULT_EXTENSION>>(arg0,i));
                }
#endif
                auto operator[](long i) const -> decltype(Op()(arg0[i])) {
                    return Op()(arg0[i]);
                }
                long size() const { return _size; }
            };

        template<class Op, class Arg0, class Arg1>
            struct numpy_expr {
                Arg0 arg0;
                Arg1 arg1;
                typedef decltype(Op()(arg0[std::declval<long>()], arg1[std::declval<long>()])) value_type;
                static constexpr unsigned long value = Arg0::value>Arg1::value?Arg0::value: Arg1::value;
                numpy_expr(Arg0 const& arg0, Arg1 const& arg1) : arg0(arg0), arg1(arg1) {
                }
#ifdef __AVX__
                auto load(long i) const -> decltype(Op()(arg0.load(i), arg1.load(i))) {
                    return Op()(arg0.load(i), arg1.load(i));
                }
#endif
                auto operator[](long i) const -> decltype(Op()(arg0[i], arg1[i])) {
                    return Op()(arg0[i], arg1[i]);
                }
                long size() const { return std::max(arg0.size(), arg1.size()); }
            };
        template<class Op, class T0, unsigned long N0, class T1, unsigned long N1>
            struct numpy_expr<Op, ndarray<T0,N0>, ndarray<T1,N1>> {
                T0* arg0;
                T1* arg1;
                long _size;
                typedef decltype(Op()(arg0[std::declval<long>()], arg1[std::declval<long>()])) value_type;
                static constexpr unsigned long value = N0>N1?N0:N1;
                numpy_expr(ndarray<T0,N0> const& arg0, ndarray<T1,N1> const& arg1) :
                    arg0(arg0.data->data + *arg0.offset_data),
                    arg1(arg1.data->data + *arg1.offset_data),
                    _size(std::max(arg0.size(), arg1.size())) {
                }
#ifdef __AVX__
                auto load(long i) const -> decltype(Op()(boost::simd::unaligned_load<boost::simd::native<T0, BOOST_SIMD_DEFAULT_EXTENSION>>(arg0,i), boost::simd::unaligned_load<boost::simd::native<T1, BOOST_SIMD_DEFAULT_EXTENSION>>(arg1,i))) {
                    return Op()(boost::simd::unaligned_load<boost::simd::native<T0, BOOST_SIMD_DEFAULT_EXTENSION>>(arg0,i), boost::simd::unaligned_load<boost::simd::native<T1, BOOST_SIMD_DEFAULT_EXTENSION>>(arg1,i));
                }
#endif
                auto operator[](long i) const -> decltype(Op()(arg0[i], arg1[i])) {
                    return Op()(arg0[i], arg1[i]);
                }
                long size() const { return _size; }
            };

        template<class Op, class T0, unsigned long N0, class Arg1>
            struct numpy_expr<Op, ndarray<T0,N0>, Arg1> {
                T0* arg0;
                Arg1 arg1;
                long _size;
                typedef decltype(Op()(arg0[std::declval<long>()], arg1[std::declval<long>()])) value_type;
                static constexpr unsigned long value = N0>Arg1::value?N0:Arg1::value;
                numpy_expr(ndarray<T0,N0> const& arg0, Arg1 const& arg1) :
                    arg0(arg0.data->data + *arg0.offset_data),
                    arg1(arg1),
                    _size(std::max(arg0.size(), arg1.size())) {
                }
#ifdef __AVX__
                auto load(long i) const -> decltype(Op()(boost::simd::unaligned_load<boost::simd::native<T0, BOOST_SIMD_DEFAULT_EXTENSION>>(arg0,i), arg1.load(i))) {
                    return Op()(boost::simd::unaligned_load<boost::simd::native<T0, BOOST_SIMD_DEFAULT_EXTENSION>>(arg0,i), arg1.load(i));
                }
#endif
                auto operator[](long i) const -> decltype(Op()(arg0[i], arg1[i])) {
                    return Op()(arg0[i], arg1[i]);
                }
                long size() const { return _size; }
            };

        template<class Op, class Arg0, class T1, unsigned long N1>
            struct numpy_expr<Op, Arg0, ndarray<T1,N1>> {
                Arg0 arg0;
                T1* arg1;
                long _size;
                typedef decltype(Op()(arg0[std::declval<long>()], arg1[std::declval<long>()])) value_type;
                static constexpr unsigned long value = Arg0::value>N1?Arg0::value:N1;
                numpy_expr(Arg0 const& arg0, ndarray<T1,N1> const& arg1) :
                    arg0(arg0),
                    arg1(arg1.data->data + *arg1.offset_data),
                    _size(std::max(arg0.size(), arg1.size())) {
                }
#ifdef __AVX__
                auto load(long i) const -> decltype(Op()(arg0.load(i), _mm256_loadu_pd(arg1+i))) {
                    return Op()(arg0.load(i), _mm256_loadu_pd(arg1+i));
                }
#endif
                auto operator[](long i) const -> decltype(Op()(arg0[i], arg1[i])) {
                    return Op()(arg0[i], arg1[i]);
                }
                long size() const { return _size; }
            };


        template<class T, unsigned long N>
            struct ndarray_iterator: std::iterator< std::random_access_iterator_tag, typename std::remove_reference<typename ndarray_helper<T,N>::result_type>::type >
            {
                ndarray<T,N> & ref_array;
                long value;
                long step;

                ndarray_iterator() {}
                ndarray_iterator(long v, ndarray<T,N> & ref, long s) : value(v), step(s), ref_array(ref) {}
                typename ndarray_helper<T,N>::result_type operator*() { return ref_array[value]; }

                ndarray_iterator<T,N>& operator++() { value+=step; return *this; }
                ndarray_iterator<T,N> operator++(int) { ndarray_iterator<T,N> self(*this); value+=step; return self; }
                ndarray_iterator<T,N>& operator+=(long n) { value+=step*n; return *this; }
                bool operator!=(ndarray_iterator<T,N> const& other) { return value != other.value; }
                bool operator==(ndarray_iterator<T,N> const& other) { return value == other.value; }
                bool operator<(ndarray_iterator<T,N> const& other) { return value < other.value; }
                long operator-(ndarray_iterator<T,N> const& other) { return (value - other.value)/step; }
                ndarray_iterator<T,N> operator-(long i) { return ndarray_iterator<T,N>(value - i*step, ref_array, step); }
                ndarray_iterator<T,N> operator+(long i) { return ndarray_iterator<T,N>(value + i*step, ref_array, step); }
            };

        template<class T, unsigned long N>
            struct ndarray_const_iterator: std::iterator< std::random_access_iterator_tag, typename std::remove_reference<typename ndarray_helper<T,N>::const_result_type>::type >
            {
                ndarray<T,N> const& ref_array;
                long value;
                long step;

                ndarray_const_iterator(long v, ndarray<T,N> const& ref, long s) : value(v), step(s), ref_array(ref) {}
                typename ndarray_helper<T,N>::const_result_type operator*() { return ref_array[value]; }

                ndarray_const_iterator<T,N>& operator++() { value+=step; return *this; }
                ndarray_const_iterator<T,N> operator++(int) { ndarray_const_iterator<T,N> self(*this); value+=step; return self; }
                ndarray_const_iterator<T,N>& operator+=(long n) { value+=step*n; return *this; }
                bool operator!=(ndarray_const_iterator<T,N> const& other) { return value != other.value; }
                bool operator==(ndarray_const_iterator<T,N> const& other) { return value == other.value; }
                bool operator<(ndarray_const_iterator<T,N> const& other) { return value < other.value; }
                long operator-(ndarray_const_iterator<T,N> const& other) { return (value - other.value)/step; }
                ndarray_const_iterator<T,N> operator-(long i) { return ndarray_const_iterator<T,N>(value - i*step, ref_array, step); }
                ndarray_const_iterator<T,N> operator+(long i) { return ndarray_const_iterator<T,N>(value + i*step, ref_array, step); }
            };

        template<class T, unsigned long N>
            struct ndarray_flat_iterator: std::iterator< std::random_access_iterator_tag, T >
            {
                ndarray<T,N> & ref_array;
                long value;
                long step;

                ndarray_flat_iterator(long v, ndarray<T,N> & ref, long s) : value(v), step(s), ref_array(ref) {}
                T& operator*() { return ref_array.data->data[value + *(ref_array.offset_data)]; }

                ndarray_flat_iterator<T,N>& operator++() { value+=step; return *this; }
                ndarray_flat_iterator<T,N> operator++(int) { ndarray_flat_iterator<T,N> self(*this); value+=step; return self; }
                ndarray_flat_iterator<T,N>& operator+=(long n) { value+=step*n; return *this; }
                bool operator!=(ndarray_flat_iterator<T,N> const& other) { return value != other.value; }
                bool operator==(ndarray_flat_iterator<T,N> const& other) { return value == other.value; }
                bool operator<(ndarray_flat_iterator<T,N> const& other) { return value < other.value; }
                long operator-(ndarray_flat_iterator<T,N> const& other) { return (value - other.value)/step; }
                ndarray_flat_iterator<T,N> operator+(long i) { return ndarray_flat_iterator<T,N>(value + i*step, ref_array, step); }
            };

        template<class T, unsigned long N>
            struct ndarray_flat_const_iterator: std::iterator< std::random_access_iterator_tag, const T >
            {
                ndarray<T,N> const& ref_array;
                long value;
                long step;

                ndarray_flat_const_iterator(long v, ndarray<T,N> const& ref, long s) : value(v), step(s), ref_array(ref) {}
                T const& operator*() { return ref_array.data->data[value + *(ref_array.offset_data)]; }

                ndarray_flat_const_iterator<T,N>& operator++() { value+=step; return *this; }
                ndarray_flat_const_iterator<T,N> operator++(int) { ndarray_flat_const_iterator<T,N> self(*this); value+=step; return self; }
                ndarray_flat_const_iterator<T,N>& operator+=(long n) { value+=step*n; return *this; }
                bool operator!=(ndarray_flat_const_iterator<T,N> const& other) { return value != other.value; }
                bool operator==(ndarray_flat_const_iterator<T,N> const& other) { return value == other.value; }
                bool operator<(ndarray_flat_const_iterator<T,N> const& other) { return value < other.value; }
                long operator-(ndarray_flat_const_iterator<T,N> const& other) { return (value - other.value)/step; }
                ndarray_flat_const_iterator<T,N> operator+(long i) { return ndarray_flat_const_iterator<T,N>(value + i*step, ref_array, step); }
            };

        template<class T, unsigned long N>
            struct ndarray_flat_const
            {
                ndarray<T,N> const& ref_array;

                //types
                typedef ndarray_flat_const_iterator<T,N> iterator;
                typedef T& value_type;

                ndarray_flat_const(ndarray<T,N> const& ref) : ref_array(ref) {}

                iterator begin() const
                {
                    return ndarray_flat_const_iterator<T,N>(0,ref_array,1);
                }

                iterator end() const
                {
                    return ndarray_flat_const_iterator<T,N>(
                            std::accumulate(ref_array.shape->begin(), ref_array.shape->end(), 1, std::multiplies<long>()),
                            ref_array,
                            1);
                }
            };

        template<class T, unsigned long N>
            struct ndarray_flat
            {
                ndarray<T,N> & ref_array;

                //types
                typedef ndarray_flat_iterator<T,N> iterator;
                typedef T& value_type;

                ndarray_flat() {}
                ndarray_flat(ndarray<T,N> & ref) : ref_array(ref) {}

                iterator begin()
                {
                    return ndarray_flat_iterator<T,N>(0,ref_array,1);
                }

                iterator end()
                {
                    return ndarray_flat_iterator<T,N>(
                            std::accumulate(ref_array.shape->begin(), ref_array.shape->end(), 1, std::multiplies<long>()),
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
                typedef ndarray_const_iterator<T,N> const_iterator;

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

                //Check if InputIterator is not a fundamental type to avoid conflict with ndarray(initializer_list, int)
                template<class InputIterator>
                    ndarray(typename std::enable_if<!std::is_fundamental<InputIterator>::value, InputIterator>::type start, InputIterator stop) : offset_data(impl::shared_ref<size_t>(0))
                    {
                        shape = impl::shared_ref<std::array<long,1>>();
                        (*shape)[0] = (stop - start);
                        data = impl::shared_ref< raw_array<T> >((*shape)[0]);
                        std::copy(start, stop, data->data);
                    }

                template<class Op, class U>
                    ndarray(const core::ndarray<U,N>& array, Op op) : offset_data(impl::shared_ref<size_t>(0)), shape(array.shape)
                    {
                        ndarray_flat_const<U,N> iter(array);
                        data = impl::shared_ref< raw_array<T> >(array.data->n);
                        std::transform(iter.begin(), iter.end(), data->data, op);
                    }
                template<class E>
                    void initialize(E const & expr) {
                        long n = expr.size();
                        shape = impl::shared_ref<std::array<long,1>>();
                        (*shape)[0] = n;
                        T* iter = data->data;
                        typedef typename boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION> vT;
                        static const std::size_t vN = boost::simd::meta::cardinal_of< vT >::value;
                        long i;
#ifdef __AVX__
                        const long bound = n/vN*vN;
#else
                        const long bound = n/8*8;
#endif
#pragma omp parallel for if(n>1000)
#ifdef __AVX__
                        for(i=0;i< bound; i+= vN) {
                            boost::simd::unaligned_store<vT>( expr.load(i), iter, i);
                        }
#else
                        for(i=0 ;i< bound; i+=8) {
                            iter[i+0] = expr[i+0];
                            iter[i+1] = expr[i+1];
                            iter[i+2] = expr[i+2];
                            iter[i+3] = expr[i+3];
                            iter[i+4] = expr[i+4];
                            iter[i+5] = expr[i+5];
                            iter[i+6] = expr[i+6];
                            iter[i+7] = expr[i+7];
                        }
#endif
                        for(i=bound;i< n; ++i)
                            iter[i] = expr[i];
                    }

                template<class Op, class Arg0, class Arg1>
                    ndarray(numpy_expr<Op, Arg0, Arg1> const & expr) : offset_data(impl::shared_ref<size_t>(0)), shape(), data(expr.size()) {
                        initialize(expr);
                    }
                template<class Op, class Arg0>
                    ndarray(numpy_uexpr<Op, Arg0> const & expr) : offset_data(impl::shared_ref<size_t>(0)), shape(), data(expr.size()) {
                        initialize(expr);

                    }

                long size() const {
                    return std::accumulate(shape->begin(), shape->end(), 1, std::multiplies<long>());
                }

                ndarray<T,N>& operator=(ndarray<T,N> && other) {
                    if(*offset_data>0 || (shape->data() && std::accumulate(shape->begin(), shape->end(), 1, std::multiplies<long>())!=data->n))
                    {
                        std::copy(other.data->data + *other.offset_data, other.data->data + *other.offset_data + std::accumulate(other.shape->begin(), other.shape->end(), 1, std::multiplies<long>()), data->data + *offset_data);

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
                    if(*offset_data>0 || (shape->data() && std::accumulate(shape->begin(), shape->end(), 1, std::multiplies<long>())!=data->n))
                    {
                        std::copy(other.data->data + *other.offset_data, other.data->data + *other.offset_data + std::accumulate(other.shape->begin(), other.shape->end(), 1, std::multiplies<long>()), data->data + *offset_data);

                    }
                    else
                    {
                        shape=other.shape;
                        data=other.data;
                        offset_data=other.offset_data;
                    }
                    return *this;
                }

                template<class Op, class Arg0, class Arg1>
                    ndarray<T,N>& operator=(numpy_expr<Op, Arg0, Arg1> & expr) {
                        initialize(expr);
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

                typename ndarray_helper<T, N>::const_result_type operator[](size_t t) const
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

                iterator begin() { return ndarray_iterator<T,N>(0,*this,1); }
                iterator end() { return ndarray_iterator<T,N>((*shape)[0],*this,1); }
                const_iterator begin() const { return ndarray_const_iterator<T,N>(0,*this,1); }
                const_iterator end() const { return ndarray_const_iterator<T,N>((*shape)[0],*this,1); }
            };

        template<class T, unsigned long V>
            struct ndarray_helper
            {
                typedef core::ndarray<T,V-1> result_type;
                typedef const core::ndarray<T,V-1> const_result_type;

                static result_type get(ndarray<T,V>& array, size_t t)
                {
                    long offset = std::accumulate(array.shape->begin() + 1, array.shape->end(), 1, std::multiplies<long>());
                    return core::ndarray<T,V-1>(array.data, *array.offset_data + t*offset, array.shape->begin() + 1);
                }

                static const_result_type get(ndarray<T,V> const& array, size_t t)
                {
                    long offset = std::accumulate(array.shape->begin() + 1, array.shape->end(), 1, std::multiplies<long>());
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
                        long r = std::accumulate(array.shape->begin() +W-V+1, array.shape->begin() + W, 1, std::multiplies<long>());
                        return core::ndarray<T,V-1>(array.data, t1*r, array.shape->begin() + W - V +1);
                    }

                template<unsigned long W>
                    static const_result_type at(ndarray<T,W> const& array, unsigned long t1, unsigned long t2)
                    {
                        long r = std::accumulate(array.shape->begin() +W-V+1, array.shape->begin() + W, 1, std::multiplies<long>());
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

                static const_result_type get(ndarray<T,1> const& array, size_t t)
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
                    return *(array.data->data + t + *array.offset_data);
                }

                template<unsigned long W>
                static const_result_type at(ndarray<T,W> const& array, unsigned long t1, unsigned long t2)
                {
                    return *(array.data->data + t1 * (*array.shape)[W-1] + t2 + *array.offset_data);
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
