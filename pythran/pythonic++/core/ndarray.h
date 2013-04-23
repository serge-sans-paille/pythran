#ifndef PYTHONIC_ARRAY_H
#define PYTHONIC_ARRAY_H
#include <cassert>
#include <iostream>
#include <iterator>
#include <array>
#include <initializer_list>
#include "shared_ref.h"
#if 0
#include "shared_ref.h"

#include <boost/simd/sdk/simd/native.hpp>
#ifdef __SSE__
#include <boost/simd/include/functions/unaligned_load.hpp>
#include <boost/simd/include/functions/unaligned_store.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/include/functions/store.hpp>
#endif

#include <mm_malloc.h>
#endif

namespace  pythonic {
    namespace __builtin__ {
        template <class T>
            long len(T const &t);
    }

    namespace core {

        template<class T>
            class raw_array {
                raw_array(raw_array<T> const& );

                public:
                typedef T* pointer_type;

                T* data;
                raw_array() : data(nullptr) {}
                raw_array(size_t n) : data(new T[n]) {}
                raw_array(T* d) : data(d) {}
                raw_array(raw_array<T>&& d) : data(d.data) { d.data = nullptr; }

                ~raw_array() {
                    if(data)
                        delete [] data;
                }
            };

        template<class T, size_t N>
            struct ndarray;

        template<class T>
            struct type_helper;

        template<class T, size_t N>
            struct type_helper<ndarray<T,N>> {
                typedef ndarray<T,N-1> type;
                typedef std::vector<type> holder;
                typedef typename holder::iterator iterator;
                typedef typename holder::const_iterator const_iterator;
                typedef impl::shared_ref<raw_array<T>> memory;

                static iterator begin(ndarray<T,N>& self) { return self.data.begin(); }
                static iterator end(ndarray<T,N>& self) { return self.data.end(); }
                static const_iterator begin(ndarray<T,N> const& self) { return self.data.begin(); }
                static const_iterator end(ndarray<T,N> const& self) { return self.data.end(); }
                template<class Iterable>
                static long initialize_from_iterable(ndarray<T,N>& self, memory& shared, T* mem_iter, Iterable&& iterable) {
                    self.mem = shared;
                    self.size = iterable.size();
                    self.data.resize(self.size);
                    self.buffer = mem_iter;
                    long offset = 0;
                    auto content_iter = self.data.begin();
                    for(auto & iterable_content : iterable)
                        offset += type_helper<ndarray<T,N-1>>::initialize_from_iterable(*content_iter++, shared, mem_iter + offset, iterable_content);
                    return offset;
                }
                template<class ShapeIterator>
                static long initialize_from_shape(ndarray<T,N>& self, memory& shared, T* mem_iter, ShapeIterator& shape_iterator) {
                    self.mem = shared;
                    self.size = *shape_iterator;
                    self.data.resize(self.size);
                    self.buffer = mem_iter;
                    auto next_shape_iterator = ++shape_iterator;
                    long offset = 0;
                    for(auto & content : self.data)
                        offset += type_helper<ndarray<T,N-1>>::initialize_from_shape(content, shared, mem_iter + offset, next_shape_iterator);
                    return offset;
                }
            };

        template<class T>
            struct type_helper<ndarray<T,1>> {
                typedef T type;
                typedef T* holder;
                typedef holder iterator;
                typedef const holder const_iterator;
                typedef impl::shared_ref<raw_array<T>> memory;

                static iterator begin(ndarray<T,1>& self) { return self.data; }
                static iterator end(ndarray<T,1>& self) { return self.data + self.size; }
                static const_iterator begin(ndarray<T,1> const& self) { return self.data; }
                static const_iterator end(ndarray<T,1> const& self) { return self.data + self.size; }
                template<class Iterable>
                static long initialize_from_iterable(ndarray<T,1>& self, memory& shared, T* mem_iter, Iterable&& iterable) {
                    self.mem = shared;
                    self.data = mem_iter;
                    self.size = iterable.size();
                    self.buffer = mem_iter;
                    auto data_end = std::copy(iterable.begin(), iterable.end(), self.data);
                    return data_end - self.data;
                }
                template<class ShapeIterator>
                static long initialize_from_shape(ndarray<T,1>& self, memory& shared, T* mem_iter, ShapeIterator& shape_iterator) {
                    self.mem = shared;
                    self.data = mem_iter;
                    self.size = *shape_iterator;
                    self.buffer = mem_iter;
                    return self.size;
                }
            };

        template<class T>
            struct sliced_ndarray : slice {
                typedef typename T::value_type value_type;
                typedef typename T::reference reference;
                typedef typename T::const_reference const_reference;

                T& data;

                sliced_ndarray(T& data, slice const& s) : slice(s), data(data) {}

                reference operator[](long i) { return data[lower+i*step]; }
                const_reference operator[](long i) const { return data[lower+i*step]; }
                sliced_ndarray<T> operator[](slice const& s) const { return sliced_ndarray(data, slice(lower + step*s.lower, std::min(upper, lower + step*s.upper), step*s.step)); }
                sliced_ndarray<T> operator[](slice const& s) { return sliced_ndarray(data, slice(lower + step*s.lower, std::min(upper, lower + step*s.upper), step*s.step)); }

                sliced_ndarray<T>& operator=(value_type v) {
                    for(size_t i=lower; i<upper; i+=step)
                        data[i] = v;
                    return *this;
                }
            };

        /* a few helpers */
        long product(long t) { return t; }
        template<class... Types>
            long product(long t, Types... types) { return t * product(types...); }

        template<class T, size_t N>
            struct _get_shape {
                template<class Iter>
                void operator()(ndarray<T,N> const& array, Iter iter) {
                    *iter++ = array.size;
                    _get_shape<T, N-1>()(array.data[0], iter);
                }
            };
        template<class T>
            struct _get_shape<T,1> {
                template<class Iter>
                void operator()(ndarray<T,1> const& array, Iter iter) {
                    *iter = array.size;
                }
            };

        template<class T, size_t N>
            ltuple<long, N> get_shape( ndarray<T,N> const& array) {
                ltuple<long, N> v(N);
                _get_shape<T,N>()(array, v.begin());
                return v;
            }

        template<class T, size_t N>
            struct ndarray {

                /* types */
                typedef typename type_helper<ndarray<T, N>>::type value_type;
                typedef value_type& reference;
                typedef value_type const & const_reference;
                typedef typename type_helper<ndarray<T, N>>::iterator iterator;
                typedef typename type_helper<ndarray<T, N>>::const_iterator const_iterator;

                /* members */
                size_t size;
                typename type_helper<ndarray<T, N>>::memory mem;
                typename type_helper<ndarray<T, N>>::holder data;
                T* buffer;

                /* constructors */
                ndarray() : size(0), mem(impl::no_memory()), data(), buffer(nullptr) {}


                /* from a sequence */
                template<class Iterable>
                    ndarray(Iterable&& iterable, typename std::enable_if< // prevent destruction of copy constructor
                            !std::is_same<typename std::remove_cv<typename std::remove_reference<Iterable>::type>::type, ndarray<T,N>>::value, bool>::type = false):
                        size(nested_container_size<Iterable>()(std::forward<Iterable>(iterable))),
                        mem(size),
                        data()
                {
                    type_helper<ndarray<T,N>>::initialize_from_iterable(*this, mem, mem->data, std::forward<Iterable>(iterable));
                }

                /* from a shape */
                template<class Shape>
                    ndarray(Shape&& shape, T value):
                        size(0),
                        mem(std::accumulate(shape.begin(), shape.end(), 1, std::multiplies<long>())),
                        data()
                {
                    auto shape_iterator = shape.begin();
                    long offset = type_helper<ndarray<T,N>>::initialize_from_shape(*this, mem, mem->data, shape_iterator);
                    std::fill(mem->data, mem->data + offset, value);
                }

                /* from a shape without setting values */
                template<class Shape>
                    ndarray(Shape&& shape, none_type):
                        size(0),
                        mem(std::accumulate(shape.begin(), shape.end(), 1, std::multiplies<long>())),
                        data()
                {
                    auto shape_iterator = shape.begin();
                    long offset = type_helper<ndarray<T,N>>::initialize_from_shape(*this, mem, mem->data, shape_iterator);
                }

                /* from a foreign pointer */
                ndarray(T* data, long int* shape, size_t size):
                    size(size),
                    mem(data),
                    data()
                {
                    mem.external(); // make sure we do not releas the pointer
                    auto shape_iterator = shape;
                    type_helper<ndarray<T,N>>::initialize_from_shape(*this, mem, mem->data, shape_iterator);
                }

                /* attributes */
                ltuple<long, N> shape() const { 
                    return get_shape(*this);
                }

                /* assignment */
                ndarray<T,N>& operator=(ndarray<T,N> const& other) {
                    if(size == other.size) // maybe a subarray copy ?
                        std::copy(other.begin(), other.end(), begin());
                    else { // just an init ?
                        size = other.size;
                        mem = other.mem;
                        data = other.data;
                        buffer = other.buffer;
                    }
                    return *this;
                }

                /* accessors */
                reference operator[](long i) { return data[i]; }
                template<class U, size_t M>
                    typename ndarray<T, N-M+1>::reference operator[](ltuple<U,M> const& l) { return at<typename ndarray<T, N-M+1>::reference>(l.begin(), int_<M>()); }
                const_reference operator[](long i) const { return data[i]; }
                sliced_ndarray<ndarray<T,N>> operator[](slice const& s) const { return sliced_ndarray<ndarray<T,N>>(*this, s); }
                sliced_ndarray<ndarray<T,N>> operator[](slice const& s) { return sliced_ndarray<ndarray<T,N>>(*this, s); }

                typename type_helper<ndarray<T, N>>::iterator begin() { return type_helper<ndarray<T, N>>::begin(*this); }
                typename type_helper<ndarray<T, N>>::iterator end() { return type_helper<ndarray<T, N>>::end(*this); }
                typename type_helper<ndarray<T, N>>::const_iterator begin() const { return type_helper<ndarray<T, N>>::begin(*this); }
                typename type_helper<ndarray<T, N>>::const_iterator end() const { return type_helper<ndarray<T, N>>::end(*this); }

                /* helpers */
                template<class R, class U, size_t M>
                    R at(U&& iter, int_<M>) {
                        return (*this)[*iter].at<R>(iter+1, int_<M-1>());
                    }
                template<class R, class U>
                    R at(U&& iter, int_<1>) {
                        return (*this)[*iter];
                    }
                size_t count() const {
                    auto shape = this->shape();
                    return std::accumulate(shape.begin(), shape.end(), 1, std::multiplies<int>());
                }
                ndarray<T,1> flat() const {
                    ndarray<T, 1> flatty;
                    flatty.size = count();
                    flatty.mem = mem;
                    flatty.data = flatty.buffer = buffer;
                    return flatty;
                }
            };

#if 0

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
                auto shape() const -> decltype(arg0.shape()) { return arg0.shape(); }
            };
        template <class Op, class T0, unsigned long N0>
            struct numpy_uexpr<Op, ndarray<T0,N0>> {
                T0 *arg0;
                typedef decltype(Op()(arg0[std::declval<long>()])) value_type;
                static constexpr unsigned long value = N0;
                long _size;
                ndarray<T0,N0> a0;
                numpy_uexpr(ndarray<T0,N0> const& arg0 ) : arg0(arg0.data->data + *arg0.offset_data), _size(arg0.size()), a0(arg0) {
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
                std::array<long, N0> const & shape() const { return *a0.shape; }
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
                auto shape() const -> decltype(arg0.shape()) { return arg0.shape(); }
            };
        template<class Op, class T0, unsigned long N0, class T1, unsigned long N1>
            struct numpy_expr<Op, ndarray<T0,N0>, ndarray<T1,N1>> {
                T0* arg0;
                T1* arg1;
                long _size;
                typedef decltype(Op()(arg0[std::declval<long>()], arg1[std::declval<long>()])) value_type;
                static constexpr unsigned long value = N0>N1?N0:N1;
                ndarray<T0,N0> a0;
                ndarray<T1,N1> a1;
                numpy_expr(ndarray<T0,N0> const& arg0, ndarray<T1,N1> const& arg1) :
                    arg0(arg0.data->data + *arg0.offset_data),
                    arg1(arg1.data->data + *arg1.offset_data),
                    _size(std::max(arg0.size(), arg1.size())),
                    a0(arg0), a1(arg1) {
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
                std::array<long, N0> const & shape() const { return *a0.shape; }
            };

        template<class Op, class T0, unsigned long N0, class Arg1>
            struct numpy_expr<Op, ndarray<T0,N0>, Arg1> {
                T0* arg0;
                Arg1 arg1;
                long _size;
                typedef decltype(Op()(arg0[std::declval<long>()], arg1[std::declval<long>()])) value_type;
                static constexpr unsigned long value = N0>Arg1::value?N0:Arg1::value;
                ndarray<T0,N0> a0;
                numpy_expr(ndarray<T0,N0> const& arg0, Arg1 const& arg1) :
                    arg0(arg0.data->data + *arg0.offset_data),
                    arg1(arg1),
                    _size(std::max(arg0.size(), arg1.size())),
                    a0(arg0) {
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
                std::array<long, N0> const & shape() const { return *a0.shape; }
            };

        template<class Op, class Arg0, class T1, unsigned long N1>
            struct numpy_expr<Op, Arg0, ndarray<T1,N1>> {
                Arg0 arg0;
                T1* arg1;
                long _size;
                typedef decltype(Op()(arg0[std::declval<long>()], arg1[std::declval<long>()])) value_type;
                static constexpr unsigned long value = Arg0::value>N1?Arg0::value:N1;
                ndarray<T1,N1> a1;
                numpy_expr(Arg0 const& arg0, ndarray<T1,N1> const& arg1) :
                    arg0(arg0),
                    arg1(arg1.data->data + *arg1.offset_data),
                    _size(std::max(arg0.size(), arg1.size())),
                    a1(arg1) {
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
                std::array<long, N1> const & shape() const { return *a1.shape; }
            };

        template<class Expr>
            struct is_numpy_expr {
                static constexpr bool value = false;
            };
        template<class Op, class Arg>
            struct is_numpy_expr<numpy_uexpr<Op, Arg>> {
                static constexpr bool value = true;
            };
        template<class Op, class Arg0, class Arg1>
            struct is_numpy_expr<numpy_expr<Op, Arg0, Arg1>> {
                static constexpr bool value = true;
            };

        template <class Expr>
            struct numpy_expr_to_ndarray;

        template<class Op, class Arg>
            struct numpy_expr_to_ndarray<numpy_uexpr<Op, Arg>> {
                typedef typename std::remove_cv<typename std::remove_reference< decltype(std::declval<numpy_uexpr<Op, Arg>>()[0]) >::type>::type T;
                static const unsigned long N = std::tuple_size< typename std::remove_cv<typename std::remove_reference< decltype(std::declval<numpy_uexpr<Op, Arg>>().shape()) >::type > ::type > ::value;
                typedef core::ndarray<T, N> type;
            };

        template<class Op, class Arg0, class Arg1>
            struct numpy_expr_to_ndarray<numpy_expr<Op, Arg0, Arg1>> {
                typedef typename std::remove_cv<typename std::remove_reference< decltype(std::declval<numpy_expr<Op, Arg0, Arg1>>()[0]) >::type>::type T;
                static const unsigned long N = std::tuple_size< typename std::remove_cv<typename std::remove_reference< decltype(std::declval<numpy_expr<Op, Arg0, Arg1>>().shape()) >::type > ::type > ::value;
                typedef core::ndarray<T, N> type;
            };

        template <class E>
            struct numpy_expr_flat_const_iterator {
                E const& expr;
                long i;
                numpy_expr_flat_const_iterator(E const& expr, long i) : expr(expr), i(i) {
                }
                void operator++() { ++i;}
                auto operator*() const -> decltype(expr[i]) { return expr[i]; }
                bool operator!=(numpy_expr_flat_const_iterator const & other) { return i != other.i;}
            };

        template <class E>
            struct numpy_expr_flat_const {
                E const& expr;
                numpy_expr_flat_const(E const& expr) : expr(expr) {
                }
                numpy_expr_flat_const_iterator<E> begin() const {
                    return numpy_expr_flat_const_iterator<E>(expr, 0);
                }
                numpy_expr_flat_const_iterator<E> end() const {
                    return numpy_expr_flat_const_iterator<E>(expr, expr.size());
                }
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
            ndarray_flat_const<T,N> make_ndarray_const_iterator(core::ndarray<T,N> const& array) {
                return ndarray_flat_const<T,N>(array);
            }
        template<class E>
            numpy_expr_flat_const<E> make_ndarray_const_iterator(E const& expr) {
                return numpy_expr_flat_const<E>(expr);
            }

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

                ndarray(std::array<long, N> const& s, T value): offset_data(impl::shared_ref<size_t>(0))
                {
                    size_t r = 1;
                    auto is = shape->begin();
                    for(auto v :s )
                        r*=(*is++=v);
                    data = impl::shared_ref< raw_array<T> >(r);
                    std::fill(data->data, data->data+r, value);
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
                    ndarray(typename std::enable_if<!std::is_fundamental<InputIterator>::value, InputIterator>::type lower, InputIterator upper) : offset_data(impl::shared_ref<size_t>(0))
                {
                    (*shape)[0] = (upper - lower);
                    data = impl::shared_ref< raw_array<T> >((*shape)[0]);
                    std::copy(lower, upper, data->data);
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
                        shape = expr.shape();
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
                    ndarray(numpy_expr<Op, Arg0, Arg1> const & expr) : offset_data(impl::shared_ref<size_t>(0)), shape(expr.shape()), data(expr.size()) {
                        initialize(expr);
                    }
                template<class Op, class Arg0>
                    ndarray(numpy_uexpr<Op, Arg0> const & expr) : offset_data(impl::shared_ref<size_t>(0)), shape(expr.shape()), data(expr.size()) {
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
                template<class Op, class Arg0>
                    ndarray<T,N>& operator=(numpy_uexpr<Op, Arg0> & expr) {
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
#endif
    }
}
#endif
