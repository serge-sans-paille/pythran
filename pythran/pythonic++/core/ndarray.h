#ifndef PYTHONIC_NDARRAY_H
#define PYTHONIC_NDARRAY_H

#include <cassert>
#include <iostream>
#include <iterator>
#include <array>
#include <initializer_list>
#include <numeric>
#include "shared_ref.h"

#ifdef __AVX__
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/functions/unaligned_load.hpp>
#include <boost/simd/include/functions/unaligned_store.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/include/functions/store.hpp>
#endif


namespace  pythonic {

    namespace __builtin__ {         // forward declared to be specialized here
        template <class T>          // should disappear when header hierarchy is reworked
            long len(T const &t);
    }

    namespace core {

        template<class T, size_t N>
            struct ndarray;
        template<class T>
            struct indexed_ndarray;
        template<class Expr>
            struct is_array;
        template<class Expr>
            struct is_numpy_expr;
        template<class T>
            struct type_helper;

        /* type trait to store scalar <> vector type binding
        */
        template<class T>
            struct vectorized {
                typedef T type;
                static type broadcast(T value) {
                    /* impelmentation of the type-specific handler to broadcas a value */
                    return value;
                }
            };

#ifdef __AVX__
        /* specialized trait for doubles when vectorization is turned on
        */
        template<>
            struct vectorized<double> {
                typedef boost::simd::native<double, BOOST_SIMD_DEFAULT_EXTENSION> type;
                static type broadcast(double v) {
                    static const std::size_t N = boost::simd::meta::cardinal_of< type >::value;
                    return boost::simd::splat<type> (v);
                }
            };
#endif

        /* Type adaptor for scalar values
         *
         * Have them behave like infinite arrays of that value
         */
        template<class T>
            struct broadcast {

                long size() const { return 0; }
                T __value;
                typename vectorized<T>::type _value;
                static constexpr size_t value = 0;
                broadcast() {}
                broadcast(T v) : __value(v), _value(vectorized<T>::broadcast(v)) {}
#ifdef __AVX__
                typename vectorized<T>::type load(long ) const { return _value;}
#endif
                T at(long ) const {
                    return __value;
                }
            };

        /* Expression template for numpy expressions - unary operators
        */
        template<class Op, class Arg0>
            struct numpy_uexpr {

                Arg0 arg0;
                typedef decltype(Op()(arg0.at(std::declval<long>()))) value_type;
                static constexpr size_t value = std::remove_reference<Arg0>::type::value;
                std::array<long, value> shape;
                numpy_uexpr() {}
                numpy_uexpr(Arg0 const& arg0) : arg0(arg0), shape(arg0.shape) {
                }
#ifdef __AVX__
                auto load(long i) const -> decltype(Op()(arg0.load(i))) {
                    return Op()(arg0.load(i));
                }
#endif
                auto at(long i) const -> decltype(Op()(arg0.at(i))) {
                    return Op()(arg0.at(i));
                }
                long size() const { return arg0.size(); }
            };

        template<class U, class V, size_t N>
            typename std::enable_if<U::value!=0,std::array<long, N>>::type const& select_shape(U const& u, V const&, int_<N> ) {
                return u.shape;
            }
        template<class U, class V, size_t N>
            typename std::enable_if<U::value==0 and V::value!=0,std::array<long, N>>::type const& select_shape(U const& , V const&v, int_<N> ) {
                return v.shape;
            }
        template<class U, class V>
            std::array<long, 0> select_shape(U const& u, V const&, int_<0> ) {
                return std::array<long, 0>();
            }

        /* Expression template for numpy expressions - binary operators
        */
        template<class Op, class Arg0, class Arg1>
            struct numpy_expr {
                Arg0 arg0;
                Arg1 arg1;
                typedef decltype(Op()(arg0.at(std::declval<long>()), arg1.at(std::declval<long>()))) value_type;
                static constexpr size_t value = std::remove_reference<Arg0>::type::value>std::remove_reference<Arg1>::type::value?std::remove_reference<Arg0>::type::value: std::remove_reference<Arg1>::type::value;
                std::array<long, value> shape;
                numpy_expr() {}

                numpy_expr(Arg0 arg0, Arg1 arg1) : arg0(arg0), arg1(arg1), shape(select_shape(arg0,arg1, int_<value>())) {
                }
#ifdef __AVX__
                auto load(long i) const -> decltype(Op()(arg0.load(i), arg1.load(i))) {
                    return Op()(arg0.load(i), arg1.load(i));
                }
#endif
                auto at(long i) const -> decltype(Op()(arg0.at(i), arg1.at(i))) {
                    return Op()(arg0.at(i), arg1.at(i));
                }
                long size() const { return std::max(arg0.size(), arg1.size()); }
            };




        /* Wrapper class to store an array pointer
         *
         * for internal use only, meant to be stored in a shared_ptr
         */
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

        /* Random Access Iterator over an ndarray
         *
         * wrapper around the operator[] of ndarray, when iterating over the first dimension
         * returned by calls to begin() or end() over an ndarray
         */
        template<class T>
            struct nditerator : std::iterator<std::random_access_iterator_tag, typename std::remove_reference<decltype(std::declval<T>()[0])>::type> {
                T data;
                long index;
                nditerator(T const& data, long index) : data(data), index(index) {
                }
                auto operator*() const -> decltype(data[index]) { return data[index]; }
                auto operator*() -> decltype(data[index]) { return data[index]; }
                nditerator<T>& operator++() { ++index; return *this;}
                nditerator<T>& operator--() { --index; return *this;}
                nditerator<T> operator+(long i) const { return nditerator(data, index + i); }
                nditerator<T> operator-(long i) const { return nditerator(data, index - i); }
                nditerator<T>& operator+=(long i) { index+=i ; return *this;}
                nditerator<T>& operator-=(long i) { index-=i; return *this;}
                long operator-(nditerator<T> const& other) const { return index - other.index; }
                bool operator!=(nditerator<T> const& other) const {
                    return index != other.index;
                }
                bool operator==(nditerator<T> const& other) const {
                    return index == other.index;
                }
                bool operator<(nditerator<T> const& other) const {
                    return index < other.index;
                }
                operator typename T::iterator () const { return ((T*)this)->buffer + index; }
            };

        /* proxy type to hold the return of an index
         */
        template <class T>
            struct indexed_ndarray : T {
                indexed_ndarray() : T() {}
                indexed_ndarray(T const& t) : T(t) {
                }

                template<class E>
                    typename std::enable_if<is_array<typename std::remove_reference<E>::type>::value, indexed_ndarray<T>&>::type
                    operator=(E&& e) {
                        if(T::data_size) {
                            for(long i=0, n=e.size(); i<n; ++i)
                                T::buffer[i] = e.at(i);
                        }
                        else
                            T::operator=(std::forward<E>(e));
                        return *this;
                    }
                template<class M, size_t N>
                    indexed_ndarray<T>& operator=(std::array<M,N> const& e) {
                        T::operator=(e);
                        return *this;
                    }
                template<class E>
                    typename std::enable_if<not is_array<typename std::remove_reference<E>::type>::value, indexed_ndarray<T>&>::type
                    operator=(E&& e) {
                        T::operator=(std::forward<E>(e));
                        return *this;
                    }
            };


        /* Helper for dimension-specific part of ndarray
         *
         * Instead of specializing the whole ndarray class, the dimension-specific behavior are stored here.
         */

        template<class T, size_t N>
            struct type_helper<ndarray<T,N>> {
                typedef ndarray<T,N-1> type;
                typedef nditerator<ndarray<T,N>> iterator;
                typedef nditerator<ndarray<T,N>> const_iterator;
                template<class S, class Iter>
                static T* initialize_from_iterable(S& shape, T* from, Iter&& iter) {
                    shape[std::tuple_size<S>::value - N] = iter.size();
                    for(auto content : iter) {
                        from = type_helper<type>::initialize_from_iterable(shape, from, content);
                    }
                    return from;
                }

                static indexed_ndarray<type> get(ndarray<T,N> const& self, long i) {
                    indexed_ndarray<type> r;
                    r.data_size = self.shape[1];
                    r.mem = self.mem;
                    r.buffer = self.buffer + i*std::accumulate(self.shape.begin() + 1, self.shape.end(), 1L, std::multiplies<long>());
                    for(size_t i =1; i<N;i++)
                        r.shape[i-1] = self.shape[i];
                    return r;
                }
            };

        template<class T>
            struct type_helper<ndarray<T,1>> {
                typedef T type;
                typedef T* holder;
                typedef holder iterator;
                typedef const holder const_iterator;
                template<class S, class Iter>
                static T* initialize_from_iterable(S& shape, T* from, Iter&& iter) {
                    shape[std::tuple_size<S>::value - 1] = iter.size();
                    return std::copy(iter.begin(), iter.end(), from);
                }
                static type& get(ndarray<T,1> const& self, long i) {
                    return self.buffer[i];
                }
            };

        /* Type converter from index to slice
         */
        slice const& as_slice(slice const& s) { return s;}
        slice as_slice(long s) {
            if(s!=-1)
                return slice(s,s+1);
            else
                return slice(s,std::numeric_limits<long>::max());
        }

        /* Meta-Function to count the number of slices in a type list
         */
        template<class... Types>
            struct count_slices;
        template<>
            struct count_slices<long> {
                static constexpr size_t value = 0;
            };
        template<>
            struct count_slices<slice> {
                static constexpr size_t value = 1;
            };
        template<class T, class... Types>
            struct count_slices<T, Types...> {
                static constexpr size_t value = count_slices<T>::value + count_slices<Types...>::value;
            };

        /* Proxy type for extended slices
         */
        template<class T, size_t N, size_t M>
            struct gsliced_ndarray {
                static constexpr size_t value = N;

                typedef typename T::value_type value_type;
                typedef typename T::reference reference;
                typedef typename T::const_reference const_reference;
                // with a.shape = [7,5,10]

                // list of slices :
                // ex : a[1:3,3,7:] -> [(1,3,1), (3,4,1), (7,10,1)]
                std::array<slice,M> gslice;
                // shape of this extslice_array with 1 in flat dimension :
                // ex : a[1:3,3,7:] -> [2,1,3]
                std::array<long,M> gshape;
                // shape of this extslice :
                // ex : a[1:3,3,7:] -> [2,3]
                std::array<long,N> shape;

                T& data;
                long _size;
                impl::shared_ref<raw_array<long>> to_index;
                long islice;

                gsliced_ndarray(T & data, std::array<slice,M> const& s, std::array<bool,M> const& mask) :
                    gslice(s),
                    gshape(),
                    shape(),
                    data(data)
                {
                    std::copy_n(data.shape.begin(), M, gshape.begin());
                    for(size_t i=0, j=0;i<M;i++) {
                        if(gslice[i].upper > data.shape[i])
                            gslice[i].upper = data.shape[i];
                        else if(gslice[i].upper < 0)
                            gslice[i].upper += data.shape[i];
                        if(gslice[i].lower <0)
                            gslice[i].lower += data.shape[i];
                        gshape[i] = ceil(std::abs(double(gslice[i].upper - gslice[i].lower)/gslice[i].step));
                        if(mask[i])
                            shape[j++] = gshape[i];
                    }
                    long start_index = 0;
                    auto const &dshape = data.shape;
                    long dmult = 1;
                    long gmult = 1;
                    // number of elts before the next elts of thie dimension in the extslice :
                    // ex : a[1:3,3,7:] -> [50,10,1]
                    std::array<long,M> jump_array;
                    // number of elts before the next elts of thie dimension in the array :
                    // ex : a[1:3,3,7:] -> [3,3,1]
                    std::array<long,M> jump_extslice;
                    for(long j=M-1; j>=0; j--) {
                        jump_array[j] = dmult;
                        jump_extslice[j] = gmult;
                        start_index += gslice[j].lower*dmult;
                        dmult*=dshape[j];
                        gmult*=gshape[j];
                    }
                    islice = std::accumulate(data.shape.begin()+M, data.shape.end(),1, std::multiplies<long>());
                    _size = gmult * islice;
                    to_index->data = new long[gmult];
                    fill_index(start_index, 0, int_<M>(), jump_array, jump_extslice);
                }

                template<size_t L>
                void fill_index(int offset, int indice, int_<L>, std::array<long, M> const& jump_array, std::array<long, M> const& jump_extslice)
                {
                    const size_t s = gshape[M-L];
                    const long ja = jump_array[M-L];
                    const long je = jump_extslice[M-L];
                    for(int i=0; i<s; i++)
                    {
                        fill_index(offset, indice, int_<L-1>(), jump_array, jump_extslice);
                        offset += ja;
                        indice += je;
                    }
                }

                void fill_index(int offset, int indice, int_<1>, std::array<long, M> const&, std::array<long, M> const&)
                {
                    auto begin = to_index->data + indice;
                    auto end = begin + gshape[M-1];
                    while(begin != end)
                        *begin++ = offset++;
                }

                auto at(long i) const -> typename std::remove_reference<decltype(data.at(0))>::type {
                    //for performance
                    if(islice==1)
                        return data.at(to_index->data[i]);
                    else
                        return data.at(to_index->data[i/islice] + i % islice);
                }

                long size() const {
                    return _size;
                }

                template<class E>
                    typename std::enable_if<not core::is_array<E>::value, gsliced_ndarray<T,N,M>&>::type operator=(E const& v) {
                        for(long i=0, n= size(); i<n ; ++i)
                            data.buffer[to_index->data[i]] = v;
                        return *this;
                    }

                template<class E>
                    typename std::enable_if<core::is_array<E>::value, gsliced_ndarray<T,N,M>&>::type operator=(E const& v) {
                        long bound = size();
                        for(long i=0, k=0; k<bound; ++i) {
                            auto I = to_index->data[i]*islice;
                            for(long j=0;j<islice; j++,k++)
                                data.at(I+j) = v.at(k%v.size());
                        }
                        return *this;
                    }


                gsliced_ndarray<T,N,M>& operator+=(value_type v) {
                    for(long i=0, n= size(); i<n ; ++i)
                        data.buffer[to_index->data[i]] += v;
                    return *this;
                }

                gsliced_ndarray<T,N,M>& operator-=(value_type v) {
                    for(long i=0, n= size(); i<n ; ++i)
                        data.buffer[to_index->data[i]] -= v;
                    return *this;
                }
            };

        /* proxy type to hold the return of a slice
         */
        template<class T>
            struct sliced_ndarray : slice {
                static constexpr size_t value = T::value;
                typedef typename T::value_type value_type;
                typedef typename T::reference reference;
                typedef typename T::const_reference const_reference;
                std::array<long, value> shape;
                size_t jump;

                T data;

                sliced_ndarray() {}

                sliced_ndarray(T const& data, slice const& s) : slice(s), shape(data.shape), data(data) {
                    shape[0] = ceil(std::abs(double(upper - lower)/step));
                    jump = 1;
                    for(size_t i=1;i<value; ++i)
                        jump*=shape[i];
                }

                auto at(long i) const -> decltype(data.at(jump*lower+i*step)) {
                    return data.at(jump*lower+i*step);
                }
                long size() const { return (data.size() / data.shape[0]) * shape[0] ; }
                reference operator[](long i) { return data[jump*lower+i*step]; }
                const_reference operator[](long i) const { return data[jump*lower+i*step]; }
                sliced_ndarray<T> operator[](slice const& s) const { return sliced_ndarray(data, slice(lower + step*s.lower, std::min(upper, lower + step*s.upper), step*s.step)); }
                sliced_ndarray<T> operator[](slice const& s) { return sliced_ndarray(data, slice(lower + step*s.lower, std::min(upper, lower + step*s.upper), step*s.step)); }

                sliced_ndarray<T>& operator=(sliced_ndarray<T> const& v) {
                    slice::operator=(v);
                    shape = v.shape;
                    jump = v.jump;
                    data = v.data;
                    return *this;
                }

                template<class E>
                typename std::enable_if<not core::is_array<E>::value, sliced_ndarray<T>&>::type operator=(E const& v) {
                    if(step>0)
                    {
                        for(long i=lower; i<upper; i+=step)
                            data[i] = v;
                    }
                    else
                    {
                        for(long i=upper; i<lower; i-=step)
                            data[i] = v;
                    }
                    return *this;
                }

                template<class E>
                typename std::enable_if< (value>1) and core::is_array<E>::value, sliced_ndarray<T>&>::type operator=(E const& v) {
                    if(step>0)
                    {
                        long slice = v.size()/std::abs(((upper - lower)/step));
                        for(long i=lower, j=0; i<upper; i+=step)
                            for(long k=0;k<slice; ++k, ++j)
                                data[i].at(k) = v.at(j);
                    }
                    else
                    {
                        long slice = v.size()/std::abs(((upper - lower)/step));
                        for(long i=upper, j=0; i<lower; i-=step)
                            for(long k=0;k<slice; ++k, ++j)
                                data[i].at(k) = v.at(j);
                    }
                    return *this;
                }
                template<class E>
                typename std::enable_if<value==1 and core::is_array<E>::value, sliced_ndarray<T>&>::type operator=(E const& v) {
                    if(step>0)
                    {
                        for(long i=lower, j=0; i<upper; i+=step, j++)
                            data[i] = v.at(j);
                    }
                    else
                    {
                        for(long i=lower, j=0; i>upper; i+=step, j++)
                            data[i] = v.at(j);
                    }
                    return *this;
                }

                sliced_ndarray<T>& operator+=(value_type v) {
                    for(long i=lower; i<upper; i+=step)
                        data[i] += v;
                    return *this;
                }

                sliced_ndarray<T>& operator-=(value_type v) {
                    for(long i=lower; i<upper; i+=step)
                        data[i] -= v;
                    return *this;
                }
            };

        /* Multidimensional array of values
         *
         * An ndarray wraps a raw array pointers and manages multiple dimensions casted overt the raw data.
         * The number of dimensions is fixed as well as the type of the underlying data.
         * A shared pointer is used internally to mimic Python's behavior.
         *
         */
        template<class T, size_t N>
            struct ndarray {

                /* types */
                static const size_t value = N;
                typedef T dtype;
                typedef typename type_helper<ndarray<T, N>>::type value_type;
                typedef value_type& reference;
                typedef value_type const & const_reference;
                typedef typename type_helper<ndarray<T, N>>::iterator iterator;
                typedef typename type_helper<ndarray<T, N>>::const_iterator const_iterator;

                /* members */
                size_t data_size;                       // number of elements in the first dimension

                impl::shared_ref<raw_array<T>> mem;     // shared data pointer
                T* buffer;                              // pointer to the first data stored in the equivalent flat array
                std::array<long, N> shape;              // shape of the multidimensional array

                /* constructors */
                ndarray() : data_size(0), mem(impl::no_memory()), buffer(nullptr), shape() {}

                /* copy */
                ndarray(ndarray<T,N> const& other) :
                    data_size(other.data_size),
                    mem(other.mem),
                    buffer(other.buffer),
                    shape(other.shape)
                {
                }

                /* move */
                ndarray(ndarray<T,N> && other) :
                    data_size(other.data_size),
                    mem(std::move(other.mem)),
                    buffer(std::move(other.buffer)),
                    shape(std::move(other.shape))
                {
                }

                /* from a sequence */
                template<class Iterable,
                    class = typename std::enable_if< // prevent destruction of copy constructor
                        !std::is_same<typename std::remove_cv<typename std::remove_reference<Iterable>::type>::type, ndarray<T,N>>::value
                        and !is_numpy_expr<typename std::remove_cv<typename std::remove_reference<Iterable>::type>::type>::value
                        and is_iterable<typename std::remove_cv<typename std::remove_reference<Iterable>::type>::type>::value,
                    void>::type
                        >
                        ndarray(Iterable&& iterable):
                            data_size(0),
                            mem(nested_container_size<Iterable>::size(std::forward<Iterable>(iterable))),
                            buffer(mem->data),
                            shape()
                {
                    type_helper<ndarray<T,N>>::initialize_from_iterable(shape, mem->data, std::forward<Iterable>(iterable));
                    data_size = shape[0];
                }

                /* from a shape */
                ndarray(std::array<long, N> const& shape, T value):
                    data_size(shape[0]),
                    mem(std::accumulate(shape.begin(), shape.end(), 1, std::multiplies<long>())),
                    buffer(mem->data),
                    shape(shape)

                {
                    std::fill(mem->data, mem->data + size(), value);
                }

                /* from a shape without setting values */
                ndarray(std::array<long, N> const& shape, none_type):
                    data_size(shape[0]),
                    mem(std::accumulate(shape.begin(), shape.end(), 1, std::multiplies<long>())),
                    buffer(mem->data),
                    shape(shape)
                {
                }

                /* from a foreign pointer */
                ndarray(T* data, long * pshape):
                    data_size(*pshape),
                    mem(data),
                    buffer(mem->data),
                    shape()
                {
                    std::copy(pshape, pshape + N, shape.begin());
                    mem.external(); // make sure we do not releas the pointer
                }

                /* from a  numpy expression */
                template<class E>
                    void initialize_from_expr(E const & expr) {
                        long n = expr.size();
                        T* iter = buffer;
                        long i;
#ifdef __AVX__
                        typedef typename boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION> vT;
                        static const std::size_t vN = boost::simd::meta::cardinal_of< vT >::value;
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
                            iter[i+0] = expr.at(i+0);
                            iter[i+1] = expr.at(i+1);
                            iter[i+2] = expr.at(i+2);
                            iter[i+3] = expr.at(i+3);
                            iter[i+4] = expr.at(i+4);
                            iter[i+5] = expr.at(i+5);
                            iter[i+6] = expr.at(i+6);
                            iter[i+7] = expr.at(i+7);
                        }
#endif
                        for(i=bound;i< n; ++i)
                            iter[i] = expr.at(i);
                    }

                template<class Op, class Arg0, class Arg1>
                    ndarray(numpy_expr<Op, Arg0, Arg1> const & expr) :
                        data_size(expr.shape[0]),
                        mem(expr.size()),
                        buffer(mem->data),
                        shape(expr.shape)
                {
                    initialize_from_expr(expr);
                }

                template<class Op, class Arg0>
                    ndarray(numpy_uexpr<Op, Arg0> const & expr) :
                        data_size(expr.shape[0]),
                        mem(expr.size()),
                        buffer(mem->data),
                        shape(expr.shape)
                {
                    initialize_from_expr(expr);
                }
                /* from a slice */
                template<class E>
                    ndarray(sliced_ndarray<E> const& expr):
                        data_size(expr.shape[0]),
                        mem(expr.size()),
                        buffer(mem->data),
                        shape(expr.shape)
                {
                    initialize_from_expr(expr);
                }
                template<class E, size_t M, size_t L>
                    ndarray(gsliced_ndarray<E,M,L> const& expr):
                        data_size(expr.shape[0]),
                        mem(expr.size()),
                        buffer(mem->data),
                        shape(expr.shape)
                {
                    initialize_from_expr(expr);
                }

                /* assignment */

                /* of another array */
                ndarray<T,N>& operator=(ndarray<T,N> const& other) {
                    data_size = other.data_size;
                    mem = other.mem;
                    buffer = other.buffer;
                    shape = other.shape;
                    return *this;
                }

                /* of an indexed array */
                ndarray<T,N>& operator=(indexed_ndarray<ndarray<T,N>> const& other) {
                    data_size = other.data_size;
                    mem = other.mem;
                    buffer = other.buffer;
                    shape = other.shape;
                    return *this;
                }

                /* of a single value */
                ndarray<T,N>& operator=(T value) {
                    std::fill(buffer, buffer + size(), value);
                    return *this;
                }

                /* update operators */
                ndarray<T,N>& operator+=(T value) {
                    for(T* iter = buffer, end = buffer + size(); iter != end; ++iter)
                        *iter += value;
                    return *this;
                }
                template<class E>
                typename std::enable_if<is_array<E>::value, ndarray<T,N>&>::type operator+=(E const & other) {
                    for(long i=0, n=size(); i< n; ++i)
                        buffer[i] += other.at(i);
                    return *this;
                }
                ndarray<T,N>& operator-=(T value) {
                    for(T* iter = buffer, end = buffer + size(); iter != end; ++iter)
                        *iter -= value;
                    return *this;
                }
                template<class E>
                typename std::enable_if<is_array<E>::value, ndarray<T,N>&>::type operator-=(E const & other) {
                    for(long i=0, n=size(); i< n; ++i)
                        buffer[i] -= other.at(i);
                    return *this;
                }

                /* accessors */

                /* by index */
                auto operator[](long i) -> decltype(type_helper<ndarray<T,N>>::get(*this, i))
                {
                    if(i<0) i+=shape[0];
                    return type_helper<ndarray<T,N>>::get(*this, i);
                }
                auto operator[](long i) const -> decltype(type_helper<ndarray<T,N>>::get(*this, i))
                {
                    if(i<0) i+=shape[0];
                    return type_helper<ndarray<T,N>>::get(*this, i);
                }

                /* by tuple */
                T& get(std::array<long, N> const& l, int_<0>)
                {
                    size_t offset =l[N-1];
                    long mult = shape[N-1];
                    for(size_t i=N-2;i>0;--i) {
                        offset += l[i]*mult;
                        mult *= shape[i];
                    }
                    return buffer[offset + l[0] * mult];
                }

                template<size_t M, size_t K>
                    indexed_ndarray<typename type_helper<ndarray<T, N-M+1>>::type> get(std::array<long,M> const& l, int_<K>)
                    {
                        indexed_ndarray<typename type_helper<ndarray<T, N-M+1>>::type> out;
                        std::copy(shape.begin() + M, shape.end(), out.shape.begin());
                        long mult = shape[N-1];
                        for(size_t i=N-2; i>M-1; --i)
                            mult *= shape[i];
                        size_t offset = 0;
                        for(size_t i=M-1;i>0;--i) {
                            offset += l[i]*mult;
                            mult *= shape[i];
                        }
                        out.data_size = out.shape[0];
                        out.mem = mem;
                        out.buffer = buffer + offset + l[0] * mult;
                        return out;
                    }
                template<size_t M>
                auto operator[](std::array<long, M> const& arr) ->decltype(this->get(arr, int_<N-M>())) {
                    return get(arr, int_<N-M>());
                }
                T get(std::array<long, N> const& l, int_<0>) const
                {
                    size_t offset =l[N-1];
                    long mult = shape[N-1];
                    for(size_t i=N-2;i>0;--i) {
                        offset += l[i]*mult;
                        mult *= shape[i];
                    }
                    return buffer[offset + l[0] * mult];
                }

                template<size_t M, size_t K>
                    indexed_ndarray<typename type_helper<ndarray<T, N-M+1>>::type> get(std::array<long,M> const& l, int_<K>) const
                    {
                        indexed_ndarray<typename type_helper<ndarray<T, N-M+1>>::type> out;
                        std::copy(shape.begin() + M, shape.end(), out.shape.begin());
                        long mult = shape[N-1];
                        for(size_t i=N-2; i>M-1; --i)
                            mult *= shape[i];
                        size_t offset = 0;
                        for(size_t i=M-1;i>0;--i) {
                            offset += l[i]*mult;
                            mult *= shape[i];
                        }
                        out.data_size = out.shape[0];
                        out.mem = mem;
                        out.buffer = buffer + offset + l[0] * mult;
                        return out;
                    }
                    
                template<size_t M>
                auto operator[](std::array<long, M> const& arr) const ->decltype(this->get(arr, int_<N-M>())) {
                    return get(arr, int_<N-M>());
                }

                /* by slice */
                sliced_ndarray<ndarray<T,N>> operator[](slice const& s) const
                {
                    long lower, upper;
                    lower = s.lower >= 0L ? s.lower : ( s.lower + shape[0]);
                    lower = std::max(0L,lower);
                    upper = s.upper >= 0L ? s.upper : ( s.upper + shape[0]);
                    upper = std::min(upper, shape[0]);
                    return sliced_ndarray<ndarray<T,N>>(*this, slice(lower, upper, s.step));
                }
                sliced_ndarray<ndarray<T,N>> operator[](slice const& s)
                {
                    long lower, upper;
                    lower = s.lower >= 0L ? s.lower : ( s.lower + shape[0]);
                    lower = std::max(0L,lower);
                    upper = s.upper >= 0L ? s.upper : ( s.upper + shape[0]);
                    upper = std::min(upper, shape[0]);
                    return sliced_ndarray<ndarray<T,N>>(*this, slice(lower, upper, s.step));
                }
                sliced_ndarray<ndarray<T,N>> operator()(slice const& s) const
                {
                    return (*this)[s];
                }
                sliced_ndarray<ndarray<T,N>> operator()(slice const& s)
                {
                    return (*this)[s];
                }

                /* by extended slice */
                template<class S0, class S1, class...S>
                gsliced_ndarray<ndarray<T,N>, count_slices<S0,S1,S...>::value, 2 + sizeof...(S) > operator()(S0 const& s0, S1 const& s1, S const&... s_) const
                {
                    return gsliced_ndarray<ndarray<T,N>, count_slices<S0,S1,S...>::value, 2 + sizeof...(S)>(*this, std::array<slice, 2 + sizeof...(S)>({{as_slice(s0), as_slice(s1), as_slice(s_)...}}), std::array<bool, 2 + sizeof...(S)>({{std::is_same<S0,slice>::value, std::is_same<S1,slice>::value, std::is_same<S,slice>::value...}}));
                }
                template<class S0, class S1, class...S>
                gsliced_ndarray<ndarray<T,N>, count_slices<S0,S1,S...>::value, 2 + sizeof...(S) > operator()(S0 const& s0, S1 const& s1, S const&... s_)
                {
                    return gsliced_ndarray<ndarray<T,N>, count_slices<S0,S1,S...>::value, 2 + sizeof...(S)>(*this, std::array<slice, 2 + sizeof...(S)>({{as_slice(s0), as_slice(s1), as_slice(s_)...}}), std::array<bool, 2 + sizeof...(S)>({{std::is_same<S0,slice>::value, std::is_same<S1,slice>::value, std::is_same<S,slice>::value...}}));
                }

                /* by array */
                template<class E>
                typename std::enable_if<is_array<E>::value, ndarray<T,1>>::type
                operator[](E const & expr) {
                    long n= expr.size(), j=0;
                    T* obuffer = new T[n];
                    for(long i=0;i<n;++i)
                        if(expr.at(i))
                            obuffer[j++] = buffer[i];
                    long shape [] = { j };
                    return ndarray<T,1>(obuffer, shape);
                }

                /* to the flat array */
                T at(long i) const { return buffer[i]; }
                T& at(long i) { return buffer[i]; }

#ifdef __AVX__
                auto load(long i) const -> decltype(boost::simd::unaligned_load<boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION>>(buffer,i)) {
                    return boost::simd::unaligned_load<boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION>>(buffer,i);
                }
#endif

                /* through iterators */
                nditerator< ndarray<T,N> > begin() { return nditerator<ndarray<T,N> >(*this, 0); }
                nditerator< ndarray<T,N> > begin() const { return nditerator<ndarray<T,N> >(*this, 0); }
                nditerator< ndarray<T,N> > end() { return nditerator<ndarray<T,N> >(*this, data_size); }
                nditerator< ndarray<T,N> > end() const { return nditerator<ndarray<T,N> >(*this, data_size); }

                /* member functions */
                long size() const {
                    return std::accumulate(shape.begin(), shape.end(), 1, std::multiplies<long>());
                }
                ndarray<T,1> flat() const {
                    ndarray<T, 1> flatty;
                    flatty.data_size = size();
                    flatty.mem = mem;
                    flatty.buffer = buffer;
                    return flatty;
                }
                template<size_t M>
                    ndarray<T,M> reshape(std::array<long,M> const& shape) const {
                        ndarray<T, M> reshappy;
                        reshappy.data_size = shape[0];
                        reshappy.mem = mem;
                        reshappy.buffer = mem->data;
                        reshappy.shape = shape;
                        return reshappy;
                    }

            };


        /* Type trait to retrieve typing information from numpy expressions
         *
         * 3 informations are available:
         * - the type `type` of the equivalent array
         * - the number of dimensions `value` of the equivalent array
         * - the type `T` of the value contained by the equivalent array
         */
        template <class Expr>
            struct numpy_expr_to_ndarray {
                typedef Expr type;
            };

        template <class L>
            struct numpy_expr_to_ndarray<core::list<L>> {
                typedef typename nested_container_value_type<core::list<L>>::type T;
                static const size_t N = nested_container_depth<core::list<L>>::value;
                typedef core::ndarray<T, N> type;
            };

        template <class T_, size_t N_>
            struct numpy_expr_to_ndarray<ndarray<T_, N_>> {
                typedef T_ T;
                static const size_t N = N_;
                typedef core::ndarray<T, N> type;
            };

        template<class Op, class Arg>
            struct numpy_expr_to_ndarray<numpy_uexpr<Op, Arg>> {
                typedef typename std::remove_cv<typename std::remove_reference< decltype(std::declval<numpy_uexpr<Op, Arg>>().at(0)) >::type>::type T;
                static const size_t N = std::tuple_size< typename std::remove_cv<typename std::remove_reference< decltype(std::declval<numpy_uexpr<Op, Arg>>().shape) >::type > ::type > ::value;
                typedef core::ndarray<T, N> type;
            };

        template<class Op, class Arg0, class Arg1>
            struct numpy_expr_to_ndarray<numpy_expr<Op, Arg0, Arg1>> {
                typedef typename std::remove_cv<typename std::remove_reference< decltype(std::declval<numpy_expr<Op, Arg0, Arg1>>().at(0)) >::type>::type T;
                static const size_t N = std::tuple_size< typename std::remove_cv<typename std::remove_reference< decltype(std::declval<numpy_expr<Op, Arg0, Arg1>>().shape) >::type > ::type > ::value;
                typedef core::ndarray<T, N> type;
            };
        template<class E, size_t M, size_t L>
            struct numpy_expr_to_ndarray<gsliced_ndarray<E,M,L>> {
                typedef typename std::remove_cv<typename std::remove_reference< decltype(std::declval<gsliced_ndarray<E,M,L>>().at(0)) >::type>::type T;
                static const size_t N = std::tuple_size< typename std::remove_cv<typename std::remove_reference< decltype(std::declval<gsliced_ndarray<E,M,L>>().shape) >::type > ::type > ::value;
                typedef core::ndarray<T, N> type;

            };

        /* Type trait that checks if a type is a numpy expression
         *
         * valid numpy expressions are:
         * - numpy_uexpr
         * - numpy_expr
         */
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

        /* Type trait that checks if a type is an array expression
         *
         * valid array expressions are:
         * - numpy_uexpr
         * - numpy_expr
         * - ndarray
         */
        template<class Expr>
            struct is_array {
                static constexpr bool value = is_numpy_expr<Expr>::value;
            };
        template< class T, size_t N>
            struct is_array< ndarray<T,N> > {
                static constexpr bool value = true;
            };
        template< class T>
            struct is_array< indexed_ndarray<T> > {
                static constexpr bool value = true;
            };

        /* Type trait that checks if a type resemble an array expression
         *
         * valid candidates are:
         * - numpy_uexpr
         * - numpy_expr
         * - ndarray
         * - list
         */
        template<class Expr>
            struct is_array_like {
                static constexpr bool value = is_array<Expr>::value;
            };
        template<class L>
            struct is_array_like<core::list<L>>{
                static constexpr bool value = true;
            };

        /* Type trait that checks if a type is a potential numpy expression parameter
         *
         * Only used to write concise expression templates
         */
        template<class T>
            struct is_numexpr_arg {
                static constexpr bool value = false;
            };
        template<class T, size_t N>
            struct is_numexpr_arg<ndarray<T,N>> {
                static constexpr bool value = true;
            };
        template<class T>
            struct is_numexpr_arg<sliced_ndarray<T>> {
                static constexpr bool value = true;
            };
        template<class T>
            struct is_numexpr_arg<indexed_ndarray<T>> {
                static constexpr bool value = true;
            };
        template<class T, size_t N, size_t M>
            struct is_numexpr_arg<gsliced_ndarray<T,N,M>> {
                static constexpr bool value = true;
            };
        template<class O, class A0, class A1>
            struct is_numexpr_arg<numpy_expr<O,A0,A1>> {
                static constexpr bool value = true;
            };
        template<class O, class A0 >
            struct is_numexpr_arg<numpy_uexpr<O,A0>> {
                static constexpr bool value = true;
            };

    }

    template<class Op, class Arg>
        struct nested_container_depth<core::numpy_uexpr<Op, Arg>> {
            static const int value = core::numpy_uexpr<Op, Arg>::value;
        };
    template<class Op, class Arg0, class Arg1>
        struct nested_container_depth<core::numpy_expr<Op, Arg0, Arg1>> {
            static const int  value = core::numpy_expr<Op, Arg0, Arg1>::value;
        };
}
#endif
