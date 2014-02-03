#ifndef PYTHONIC_TYPES_NDARRAY_HPP
#define PYTHONIC_TYPES_NDARRAY_HPP

#include "pythonic/utils/proxy.hpp"
#include "pythonic/types/assignable.hpp"
#include "pythonic/types/empty_iterator.hpp"
#include "pythonic/utils/nested_container.hpp"
#include "pythonic/utils/shared_ref.hpp"
#include "pythonic/utils/reserve.hpp"
#include "pythonic/utils/int_.hpp"
#include "pythonic/types/slice.hpp"
#include "pythonic/types/tuple.hpp"
#include "pythonic/types/list.hpp"
#include "pythonic/__builtin__/len.hpp"

#include <cassert>
#include <iostream>
#include <iterator>
#include <array>
#include <initializer_list>
#include <numeric>

#include <boost/simd/sdk/simd/logical.hpp>

#ifdef USE_BOOST_SIMD
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/functions/unaligned_load.hpp>
#include <boost/simd/include/functions/unaligned_store.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/include/functions/store.hpp>
#endif

namespace pythonic {

    namespace types {

        struct foreign {}; // used to mark memory as foreigned memory

        template<class T, size_t N>
            struct ndarray;
        template<class T, size_t N>
            struct indexed_ndarray;
        template<class Expr>
            struct is_array;
        template<class Expr>
            struct is_numpy_expr;
        template<class T>
            struct type_helper;
        template<class T>
            struct numpy_expr_to_ndarray;

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

#ifdef USE_BOOST_SIMD
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
#ifdef USE_BOOST_SIMD
                typename vectorized<T>::type load(long ) const { return _value;}
#endif
                T at(long ) const {
                    return __value;
                }
            };
        /* Expression template for numpy expressions - filter
         */
        template<class Arg0, class F>
            struct numpy_fexpr {
                Arg0 arg0;
                utils::shared_ref<raw_array<long>> indices;
                static constexpr size_t value = 1;
                typedef typename numpy_expr_to_ndarray<Arg0>::T value_type;
                array<long, value> shape;
                numpy_fexpr() : indices() {}
                numpy_fexpr(Arg0 const& arg0, F const& filter) : arg0(arg0), indices(arg0.size()) {
                    long j = 0, n = filter.size();
                    auto iter = indices->data;
                    for(long i = 0; i < n ; ++i)
                        if(filter.at(i))
                            iter[j++] = i;
                    shape[0] = { j };
                }
#ifdef USE_BOOST_SIMD
                auto load(long i) const -> decltype(arg0.load(i)) {
                    return arg0.load(i); // FIXME
                }
#endif
                auto at(long i) const -> decltype(arg0.at(indices->data[i])) {
                    return arg0.at(indices->data[i]);
                }

                long size() const { return shape[0]; }

                template<class E>
                    typename std::enable_if<is_numpy_expr<E>::value, numpy_fexpr< numpy_fexpr<Arg0, F>, E > >::type
                    operator[](E const & expr)
                    {
                        return numpy_fexpr<numpy_fexpr<Arg0, F>, E >(*this, expr);
                    }

                numpy_fexpr<Arg0, F>& operator=(value_type const& v) {
                    for(long i=0, n= size(); i<n ; ++i)
                        arg0.at(indices->data[i]) = v;
                    return *this;
                }
                template<class E>
                    typename std::enable_if<is_array<typename std::remove_reference<E>::type>::value, numpy_fexpr<Arg0, F>&>::type
                    operator=(E&& e)
                    {
                        for(long i=0, n= size(); i<n ; ++i)
                            arg0.at(indices->data[i]) = e.at(i);
                        return *this;
                    }

            };

        /* Expression template for numpy expressions - unary operators
         */
        template<class Op, class Arg0>
            struct numpy_uexpr {

                Arg0 arg0;
                static constexpr size_t value = std::remove_reference<Arg0>::type::value;
                typedef typename type_helper<ndarray<decltype(Op()(arg0.at(std::declval<long>()))), value>>::type value_type;
                array<long, value> shape;
                numpy_uexpr() {}
                numpy_uexpr(Arg0 const& arg0) : arg0(arg0), shape(arg0.shape) {
                }
                template<class Arg0_ = typename std::conditional<std::is_reference<Arg0>::value, Arg0, Arg0&>::type>
                    numpy_uexpr(numpy_uexpr<Op, Arg0_> const& expr) : arg0(expr.arg0), shape(expr.arg0.shape) {}
#ifdef USE_BOOST_SIMD
                auto load(long i) const -> decltype(Op()(arg0.load(i))) {
                    return Op()(arg0.load(i));
                }
#endif
                auto at(long i) const -> decltype(Op()(arg0.at(i))) {
                    return Op()(arg0.at(i));
                }
                long size() const { return arg0.size(); }

                template<class E>
                    typename std::enable_if<is_numpy_expr<E>::value, numpy_fexpr<numpy_uexpr<Op, Arg0>, E> >::type
                    operator[](E const & expr)
                    {
                        return  numpy_fexpr<numpy_uexpr<Op, Arg0>, E>(*this, expr);
                    }
            };

        template<class U, class V, size_t N>
            typename std::enable_if<U::value!=0, array<long, N>>::type const& select_shape(U const& u, V const&, utils::int_<N> ) {
                return u.shape;
            }
        template<class U, class V, size_t N>
            typename std::enable_if<U::value==0 and V::value!=0, array<long, N>>::type const& select_shape(U const& , V const&v, utils::int_<N> ) {
                return v.shape;
            }
        template<class U, class V>
            array<long, 0> select_shape(U const& u, V const&, utils::int_<0> ) {
                return array<long, 0>();
            }

        template <class E>
            struct numpy_iterator : std::iterator< std::random_access_iterator_tag, decltype(std::declval<E>().at(0))> {
                E expr;
                long i;
                numpy_iterator() {}
                numpy_iterator(E expr, long i) : expr(expr), i(i) {}
                auto operator*() -> decltype(expr.at(i)) { return expr.at(i); }
                numpy_iterator& operator++() { ++i; return *this; }
                numpy_iterator operator++(int) { numpy_iterator self(*this); ++i; return self; }
                numpy_iterator& operator+=(long n) { i+=n; return *this; }
                bool operator!=(numpy_iterator const& other) const { return i != other.i; }
                bool operator==(numpy_iterator const& other) const { return i == other.i; }
                bool operator<(numpy_iterator const& other) const { return i < other.i; }
                long operator-(numpy_iterator const& other) const { return i - other.i; }
            };

        /* Expression template for numpy expressions - binary operators
         */
        template<class Op, class Arg0, class Arg1>
            struct numpy_expr {
                typedef numpy_iterator<numpy_expr<Op, Arg0, Arg1>> iterator;
                Arg0 arg0;
                Arg1 arg1;
                static constexpr size_t value = std::remove_reference<Arg0>::type::value>std::remove_reference<Arg1>::type::value?std::remove_reference<Arg0>::type::value: std::remove_reference<Arg1>::type::value;
                typedef typename type_helper<ndarray<decltype(Op()(arg0.at(std::declval<long>()), arg1.at(std::declval<long>()))), value>>::type value_type;
                array<long, value> shape;
                numpy_expr() {}

                numpy_expr(Arg0 arg0, Arg1 arg1) : arg0(arg0), arg1(arg1), shape(select_shape(arg0,arg1, utils::int_<value>())) {
                }
                template<class Arg0_ = typename std::conditional<std::is_reference<Arg0>::value, Arg0, Arg0&>::type, class Arg1_ = typename std::conditional<std::is_reference<Arg0>::value, Arg1, Arg1&>::type>
                    numpy_expr(numpy_expr<Op, Arg0_, Arg1_> const& expr) : arg0(expr.arg0), arg1(expr.arg1), shape(select_shape(expr.arg0,expr.arg1, utils::int_<value>())) {}

                iterator begin() const { return iterator(*this, 0); }
                iterator end() const { return iterator(*this, size()); }
#ifdef USE_BOOST_SIMD
                auto load(long i) const -> decltype(Op()(arg0.load(i), arg1.load(i))) {
                    return Op()(arg0.load(i), arg1.load(i));
                }
#endif
                auto at(long i) const -> decltype(Op()(arg0.at(i), arg1.at(i))) {
                    return Op()(arg0.at(i), arg1.at(i));
                }
                long size() const { return std::max(arg0.size(), arg1.size()); }

                template<class E>
                    typename std::enable_if<is_numpy_expr<E>::value, numpy_fexpr<numpy_expr<Op, Arg0, Arg1>, E> >::type
                    operator[](E const & expr)
                    {
                        return numpy_fexpr<numpy_expr<Op, Arg0, Arg1>, E>(*this, expr);
                    }
            };




        /* Random Access Iterator over an ndarray
         *
         * wrapper around the operator[] of ndarray, when iterating over the first dimension
         * returned by calls to begin() or end() over an ndarray
         */
        template<class T>
            struct nditerator;
        template<class T, size_t N>
            struct nditerator<ndarray<T,N>> : std::iterator<std::random_access_iterator_tag, typename ndarray<T,N>::value_type, ptrdiff_t, typename ndarray<T,N>::value_type *, typename ndarray<T,N>::value_type /* no ref here */> {
                ndarray<T,N> data;
                long index;
                nditerator(ndarray<T,N> const& data, long index) : data(data), index(index) {
                }
                auto operator*() const -> decltype(data[index]) { return data[index]; }
                auto operator*() -> decltype(data[index]) { return data[index]; }
                nditerator<ndarray<T,N>>& operator++() { ++index; return *this;}
                nditerator<ndarray<T,N>>& operator--() { --index; return *this;}
                nditerator<ndarray<T,N>> operator+(long i) const { nditerator<ndarray<T,N>> other(*this); other.index+=i; return other; }
                nditerator<ndarray<T,N>> operator-(long i) const { nditerator<ndarray<T,N>> other(*this); other.index-=i; return other; }
                nditerator<ndarray<T,N>>& operator+=(long i) { index += i; return *this;}
                nditerator<ndarray<T,N>>& operator-=(long i) { index -= i; return *this;}
                long operator-(nditerator<ndarray<T,N>> const& other) const { return index - other.index; }
                bool operator!=(nditerator<ndarray<T,N>> const& other) const {
                    return index != other.index;
                }
                bool operator==(nditerator<ndarray<T,N>> const& other) const {
                    return index == other.index;
                }
                bool operator<(nditerator<ndarray<T,N>> const& other) const {
                    return index < other.index;
                }
                //operator T*() const { return iter.buffer; }
            };


        /* proxy type to hold the return of an index
         */
        template <class T, size_t N>
            struct indexed_ndarray : ndarray<T,N> {
                typedef typename ndarray<T,N>::value_type value_type;

                indexed_ndarray() : ndarray<T,N>() {}
                indexed_ndarray(ndarray<T,N> const& t) : ndarray<T,N>(t) {}
                indexed_ndarray(ndarray<T,N+1> const& t, long i) {
                    ndarray<T,N>::data_size = t.shape[1];
                    ndarray<T,N>::mem = t.mem;
                    ndarray<T,N>::buffer = t.buffer + i*std::accumulate(t.shape.begin() + 1, t.shape.end(), 1L, std::multiplies<long>());
                    for(size_t i =1; i<N+1;i++)
                        ndarray<T,N>::shape[i-1] = t.shape[i];
                }
                template<size_t M>
                    indexed_ndarray(ndarray<T,N+M> const& a, array<long,M> const& l)
                    {
                        std::copy(a.shape.begin() + M, a.shape.end(), ndarray<T,N>::shape.begin());
                        long mult = a.shape[N+M-1];
                        for(size_t i=N+M-2; i>M-1; --i)
                            mult *= a.shape[i];
                        size_t offset = 0;
                        for(size_t i=M-1;i>0;--i) {
                            offset += l[i]*mult;
                            mult *= a.shape[i];
                        }
                        ndarray<T,N>::data_size = ndarray<T,N>::shape[0];
                        ndarray<T,N>::mem = a.mem;
                        ndarray<T,N>::buffer = a.buffer + offset + l[0] * mult;
                    }

                indexed_ndarray(indexed_ndarray<T,N>&& a): ndarray<T,N>(std::forward<ndarray<T,N>>(a)) {
                }
                indexed_ndarray(indexed_ndarray<T,N>const& a): ndarray<T,N>(static_cast<ndarray<T,N> const&>(a)) {
                }

                indexed_ndarray<T,N>& operator=(indexed_ndarray<T,N> const& e) {
                    if(ndarray<T,N>::data_size) {
                        for(long i=0, n=e.size(); i<n; ++i)
                            ndarray<T,N>::buffer[i] = e.at(i);
                    }
                    else
                        ndarray<T,N>::operator=(std::forward<indexed_ndarray<T,N>>(e));
                    return *this;
                }

                template<class E>
                    typename std::enable_if<is_array<typename std::remove_reference<E>::type>::value, indexed_ndarray<T,N>&>::type
                    operator=(E&& e) {
                        if(ndarray<T,N>::data_size) {
                            for(long i=0, n=e.size(); i<n; ++i)
                                ndarray<T,N>::buffer[i] = e.at(i);
                        }
                        else
                            ndarray<T,N>::operator=(std::forward<E>(e));
                        return *this;
                    }
                template<class M, size_t L>
                    indexed_ndarray<T,N>& operator=(array<M,L> const& e) {
                        ndarray<T,N>::operator=(e);
                        return *this;
                    }
                template<class E>
                    typename std::enable_if<not is_array<typename std::remove_reference<E>::type>::value, indexed_ndarray<T,N>&>::type
                    operator=(E&& e) {
                        ndarray<T,N>::operator=(std::forward<E>(e));
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
                static iterator make_iterator(ndarray<T,N>& n, long i) { return iterator(n, i); }
                static const_iterator make_iterator(ndarray<T,N> const & n, long i) { return const_iterator(n, i); }
                template<class S, class Iter>
                    static T* initialize_from_iterable(S& shape, T* from, Iter&& iter) {
                        shape[std::tuple_size<S>::value - N] = iter.size();
                        for(auto content : iter) {
                            from = type_helper<type>::initialize_from_iterable(shape, from, content);
                        }
                        return from;
                    }

                static indexed_ndarray<T,N-1> get(ndarray<T,N> const& self, long i) {
                    return indexed_ndarray<T,N-1>(self, i);
                }
                static long step(ndarray<T,N> const& self) { return std::accumulate(self.shape.begin() + 1, self.shape.end(), 1L, std::multiplies<long>());}
            };

        template<class T>
            struct type_helper<ndarray<T,1>> {
                typedef T type;
                typedef T* holder;
                typedef holder iterator;
                typedef T const * const_iterator;
                static iterator make_iterator(ndarray<T,1>& n, long i) { return n.buffer + i; }
                static const_iterator make_iterator(ndarray<T,1> const & n, long i) { return n.buffer + i; }
                template<class S, class Iter>
                    static T* initialize_from_iterable(S& shape, T* from, Iter&& iter) {
                        shape[std::tuple_size<S>::value - 1] = iter.size();
                        return std::copy(iter.begin(), iter.end(), from);
                    }
                static type& get(ndarray<T,1> const& self, long i) {
                    return self.buffer[i];
                }
                static constexpr long step(ndarray<T,1> const& ) { return 1;}
            };

        /* Type converter from index to slice
         */
        slice const& as_slice(slice const& s) { return s;}
        slice as_slice(long s) {
            return slice(s,s+1);
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
           for a = np.arange(2*3*4).reshape(2,3,4)
           a = a[1,0:1]
T : type of the sliced array, ex: ndarray<long, 3>
N : number of slices, ex: 1
M : number of args, ex: 2

we assume that M>=N
         */
        template<class T, size_t N, size_t M>
            struct gsliced_ndarray {
                static_assert(M>=N, "dimension doesn't match in gsliced_ndarray");
                static constexpr size_t value = T::value + N - M; // number of slice (N) + number of implicit dimension (T::value - M)

                typedef typename utils::nested_container_value_type<T, value>::type value_type;
                // with a.shape = [7,5,10]

                // list of slices :
                // ex : a[1:3,3,7:] -> [(1,3,1), (3,4,1), (7,10,1)]
                array<normalized_slice,M> gslice;
                // shape of this extslice_array with 1 in flat dimension :
                // ex : a[1:3,3,7:] -> [2,1,3]
                array<long,M> gshape;
                // shape of this extslice :
                // ex : a[1:3,3,7:] -> [2,3]
                array<long,value> shape;

                T data;
                long _size;
                utils::shared_ref<raw_array<long>> to_index;
                // number of elements between 2 value in implicit dimension (it is an offset)
                //ex : a[:,1] -> 10
                long islice;

                gsliced_ndarray(T const& data, array<slice,M> const& s, array<bool,M> const& mask) :
                    gslice(),
                    gshape(),
                    shape(),
                    data(data)
                {
                    std::copy_n(data.shape.begin(), M, gshape.begin());
                    for(size_t i=0, j=0;i<M;i++) {
                        gslice[i] = s[i].normalize(data.shape[i]);
                        if(mask[i])
                        {
                            gshape[i] = gslice[i].size();
                            shape[j++] = gshape[i];
                        }
                        else {
                            gshape[i] = 1;
                        }
                    }
                    std::copy(data.shape.begin() + M , data.shape.end(), shape.begin() + N);

                    long start_index = 0;
                    auto const &dshape = data.shape;
                    long dmult = 1;
                    long gmult = 1;
                    // number of elts before the next elts of this dimension in the extslice :
                    // ex : a[1:3,3,7:] -> [50,10,1]
                    array<long,M> jump_array;
                    // number of elts before the next elts of this dimension in the array :
                    // ex : a[1:3,3,7:] -> [3,3,1]
                    array<long,M> jump_extslice;
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
                    fill_index(start_index, 0, utils::int_<M>(), jump_array, jump_extslice);
                }

                template<size_t L>
                    void fill_index(int offset, int indice, utils::int_<L>, array<long, M> const& jump_array, array<long, M> const& jump_extslice)
                    {
                        const size_t s = gshape[M-L];
                        const long ja = jump_array[M-L];
                        const long je = jump_extslice[M-L];
                        for(size_t i=0; i<s; i++)
                        {
                            fill_index(offset, indice, utils::int_<L-1>(), jump_array, jump_extslice);
                            offset += ja;
                            indice += je;
                        }
                    }

                void fill_index(int offset, int indice, utils::int_<1>, array<long, M> const&, array<long, M> const&)
                {
                    auto begin = to_index->data + indice;
                    auto end = begin + gshape[M-1];
                    while(begin != end)
                        *begin++ = offset++;
                }

                template<size_t V>
                    auto _at(long i, utils::int_<V>) const-> typename std::remove_reference<decltype(data.at(0))>::type
                    {
                        //for performance
                        if(islice==1)
                            return data.at(to_index->data[i]);
                        else
                            return data.at(to_index->data[i/islice]*islice + i % islice);
                    }

                template<size_t V>
                    auto _at(long i, utils::int_<V>) -> decltype(data.at(0))
                    {
                        //for performance
                        if(islice==1)
                            return data.at(to_index->data[i]);
                        else
                            return data.at(to_index->data[i/islice]*islice + i % islice);
                    }

                auto _at(long i, utils::int_<1>) -> decltype(data.at(0))
                {
                    return data.at(to_index->data[i]);
                }

                auto _at(long i, utils::int_<1>) const -> typename std::remove_reference<decltype(data.at(0))>::type
                {
                    return data.at(to_index->data[i]);
                }

                auto at(long i) const -> typename std::remove_reference<decltype(data.at(0))>::type {
                    return _at(i, utils::int_<value>());
                }

                auto at(long i) -> decltype(data.at(0)) {
                    return _at(i, utils::int_<value>());
                }

                template<size_t V, size_t NN>
                    gsliced_ndarray<T, N-1, M> get(long i, utils::int_<V>, utils::int_<NN>) const
                    {
                        array<bool,M> mask;
                        for(size_t i=0, j=0; i<M; i++)
                        {
                            if(shape[j] == gshape[i])
                            {
                                mask[i] = true;
                                j++;
                            }
                        }
                        return gsliced_ndarray<T, N-1, M>(data, gshape, mask);
                    }

                template<size_t NN>
                    value_type get(long i, utils::int_<1>, utils::int_<NN>) const
                    {
                        return _at(i, utils::int_<1>());
                    }

                value_type get(long i, utils::int_<1>, utils::int_<1>) const
                {
                    return _at(i, utils::int_<1>());
                }

                template<size_t V>
                    indexed_ndarray<typename utils::nested_container_value_type<T>::type, value-1> get(long i, utils::int_<V>, utils::int_<1>) const
                    {
                        array<long, M> tuple;
                        for(int i=0; i<M; i++)
                        {
                            if(gslice[i].step == 1)
                                tuple[i] = gslice[i].lower;
                            else
                                tuple[i] = i;
                        }
                        return indexed_ndarray<typename utils::nested_container_value_type<T>::type, value-1>(data, tuple);
                    }

                auto operator[](long i) const -> typename std::remove_reference<decltype(this->get(i, utils::int_<value>(), utils::int_<N>()))>::type
                {
                    return this->get(i, utils::int_<value>(), utils::int_<N>());
                }

                auto operator[](long i) -> decltype(this->get(i, utils::int_<value>(), utils::int_<N>()))
                {
                    return this->get(i, utils::int_<value>(), utils::int_<N>());
                }

                long size() const {
                    return _size;
                }

                template<class E>
                    typename std::enable_if<is_numpy_expr<E>::value, numpy_fexpr<gsliced_ndarray<T,N,M>, E> >::type
                    operator[](E const & expr)
                    {
                        return numpy_fexpr<gsliced_ndarray<T,N,M>, E>(*this, expr);
                    }

                gsliced_ndarray<T,N,M>& operator=(gsliced_ndarray<T,N,M> const& v) {
                    long bound = size();
                    for(long i=0, k=0; k<bound; ++i) {
                        auto I = to_index->data[i]*islice;
                        for(long j=0;j<islice; j++,k++)
                            data.at(I+j) = v.at(k%v.size());
                    }
                    return *this;
                }

                template<class E>
                    typename std::enable_if<not is_array<E>::value, gsliced_ndarray<T,N,M>&>::type operator=(E const& v) {
                        for(long i=0, n= size(); i<n ; ++i)
                            data.buffer[to_index->data[i]] = v;
                        return *this;
                    }

                template<class E>
                    typename std::enable_if<is_array<E>::value, gsliced_ndarray<T,N,M>&>::type operator=(E const& v) {
                        long bound = size();
                        for(long i=0, k=0; k<bound; ++i) {
                            auto I = to_index->data[i]*islice;
                            for(long j=0;j<islice; j++,k++)
                                data.at(I+j) = v.at(k%v.size());
                        }
                        return *this;
                    }


                template<class U, size_t K, size_t L>
                    gsliced_ndarray<T,N,M>& operator+=(gsliced_ndarray<U,K,L> const& v) {
                        for(long i=0, n= size(); i<n ; ++i)
                            data.buffer[to_index->data[i]] += v.data.buffer[v.to_index->data[i]];
                        return *this;
                    }


                gsliced_ndarray<T,N,M>& operator/=(typename utils::nested_container_value_type<gsliced_ndarray<T,N,M>>::type v) {
                    for(long i=0, n= size(); i<n ; ++i)
                        data.buffer[to_index->data[i]] /= v;
                    return *this;
                }

                gsliced_ndarray<T,N,M>& operator-=(typename utils::nested_container_value_type<gsliced_ndarray<T,N,M>>::type v) {
                    for(long i=0, n= size(); i<n ; ++i)
                        data.buffer[to_index->data[i]] -= v;
                    return *this;
                }

                gsliced_ndarray<T,N,M>& operator+=(typename utils::nested_container_value_type<gsliced_ndarray<T,N,M>>::type v) {
                    for(long i=0, n= size(); i<n ; ++i)
                        data.buffer[to_index->data[i]] += v;
                    return *this;
                }

            };

        /* proxy type to hold the return of a slice
         */
        template<class T>
            struct sliced_ndarray : normalized_slice {
                static constexpr size_t value = T::value;
                typedef typename T::value_type value_type;
                typedef typename T::reference reference;
                typedef typename T::const_reference const_reference;
                array<long, value> shape;
                long jump;

                T data;

                sliced_ndarray() {}

                sliced_ndarray(T const& data, slice const& s) : normalized_slice(s.normalize(data.shape[0])), shape(data.shape), data(data) {
                    shape[0] = normalized_slice::size();
                    jump = 1;
                    for(size_t i=1;i<value; ++i)
                        jump*=shape[i];
                }

                auto at(long i) const -> decltype(data.at(0)) {
                    return data.at(jump*lower+i*step);
                }
                long size() const { return (data.size() / data.shape[0]) * shape[0] ; }
                reference operator[](long i) { return data[jump*lower+i*step]; }
                const_reference operator[](long i) const { return data[jump*lower+i*step]; }

                sliced_ndarray<T> operator[](slice const& s) const {
                    normalized_slice norm = s.normalize(normalized_slice::size());
                    return sliced_ndarray(data, slice(lower + step*norm.lower, lower + step*norm.upper, step*norm.step));
                }
                sliced_ndarray<T> operator[](slice const& s) {
                    normalized_slice norm = s.normalize(normalized_slice::size());
                    return sliced_ndarray(data, slice(lower + step*norm.lower, lower + step*norm.upper, step*norm.step));
                }

                sliced_ndarray<T>& operator=(sliced_ndarray<T> const& v) {
                    normalized_slice::operator=(v);
                    shape = v.shape;
                    jump = v.jump;
                    data = v.data;
                    return *this;
                }

                template<class E>
                    typename std::enable_if<not is_array<E>::value, sliced_ndarray<T>&>::type operator=(E const& v) {
                        for(long i =0; i<normalized_slice::size(); i++)
                            data[lower + i * step] = v;
                        return *this;
                    }

                template<class E>
                    typename std::enable_if< (value>1) and is_array<E>::value, sliced_ndarray<T>&>::type operator=(E const& v) {
                        long slice = v.size()/normalized_slice::size();
                        for(long i=0, j=0; i<normalized_slice::size(); i++)
                            for(long k=0;k<slice; ++k, ++j)
                                data[lower + i * step].at(k) = v.at(j);
                        return *this;
                    }
                template<class E>
                    typename std::enable_if<value==1 and is_array<E>::value, sliced_ndarray<T>&>::type operator=(E const& v) {
#pragma omp parallel for if(normalized_slice::size() > 10000)
                        for(long i=0; i<normalized_slice::size(); i++)
                            data.at(lower + i * step) = v.at(i);
                        return *this;
                    }

                sliced_ndarray<T>& operator+=(value_type v) {
#pragma omp parallel for if(normalized_slice::size() > 10000)
                    for(long i=0; i<normalized_slice::size(); i++)
                        data.at(lower + i * step) += v;
                    return *this;
                }

                sliced_ndarray<T>& operator-=(value_type v) {
#pragma omp parallel for if(normalized_slice::size() > 10000)
                    for(long i=0; i<normalized_slice::size(); i++)
                        data.at(lower + i * step) -= v;
                    return *this;
                }
                template<class E>
                    typename std::enable_if<is_numpy_expr<E>::value, numpy_fexpr<sliced_ndarray<T>, E> >::type
                    operator[](E const & expr)
                    {
                        return numpy_fexpr<sliced_ndarray<T>, E>(*this, expr);
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

                utils::shared_ref<raw_array<T>> mem;     // shared data pointer
                T* buffer;                              // pointer to the first data stored in the equivalent flat array
                array<long, N> shape;             // shape of the multidimensional array

                /* constructors */
                ndarray() : data_size(0), mem(utils::no_memory()), buffer(nullptr), shape() {}

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
                        and !std::is_same<typename std::remove_cv<typename std::remove_reference<Iterable>::type>::type, indexed_ndarray<T,N>>::value
                        and !is_numpy_expr<typename std::remove_cv<typename std::remove_reference<Iterable>::type>::type>::value
                        and is_iterable<typename std::remove_cv<typename std::remove_reference<Iterable>::type>::type>::value,
                    void>::type
                        >
                        ndarray(Iterable&& iterable):
                            data_size(0),
                            mem(utils::nested_container_size<Iterable>::size(std::forward<Iterable>(iterable))),
                            buffer(mem->data),
                            shape()
                {
                    type_helper<ndarray<T,N>>::initialize_from_iterable(shape, mem->data, std::forward<Iterable>(iterable));
                    data_size = shape[0];
                }

                /* from a shape */
                ndarray(array<long, N> const& shape, T value):
                    data_size(shape[0]),
                    mem(std::accumulate(shape.begin(), shape.end(), 1, std::multiplies<long>())),
                    buffer(mem->data),
                    shape(shape)

                {
                    std::fill(mem->data, mem->data + size(), value);
                }

                /* from a shape without setting values */
                ndarray(array<long, N> const& shape, none_type):
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
                }
                ndarray(T* data, long * pshape, foreign const&):
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
#ifdef USE_BOOST_SIMD
                        typedef typename boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION> vT;
                        static const std::size_t vN = boost::simd::meta::cardinal_of< vT >::value;
                        const long bound = n/vN*vN;
#else
                        const long bound = n/8*8;
#endif
#pragma omp parallel for if(n>1000)
#ifdef USE_BOOST_SIMD
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

                template<class Op, class Arg0>
                    ndarray(numpy_fexpr<Op, Arg0> const & expr) :
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
                template<class Tp>
                    ndarray(indexed_ndarray<Tp,N> const& expr):
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
                ndarray<T,N>& operator=(indexed_ndarray<T,N> const& other) {
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
                T& get(array<long, N> const& l, utils::int_<0>)
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
                    indexed_ndarray<T, N-M> get(array<long,M> const& l, utils::int_<K>)
                    {
                        return indexed_ndarray<T, N-M>(*this, l);
                    }
                template<size_t M>
                    auto operator[](array<long, M> const& arr) ->decltype(this->get(arr, utils::int_<N-M>())) {
                        return get(arr, utils::int_<N-M>());
                    }
                T get(array<long, N> const& l, utils::int_<0>) const
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
                    indexed_ndarray<T, N-M> get(array<long,M> const& l, utils::int_<K>) const
                    {
                        return indexed_ndarray<T, N-M>(*this, l);
                    }

                template<size_t M>
                    auto operator[](array<long, M> const& arr) const ->decltype(this->get(arr, utils::int_<N-M>())) {
                        return get(arr, utils::int_<N-M>());
                    }

                /* by slice */
                sliced_ndarray<ndarray<T,N>> operator[](slice const& s) const
                {
                    return sliced_ndarray<ndarray<T,N>>(*this, s);
                }
                sliced_ndarray<ndarray<T,N>> operator[](slice const& s)
                {
                    return sliced_ndarray<ndarray<T,N>>(*this, s);
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
                        return gsliced_ndarray<ndarray<T,N>, count_slices<S0,S1,S...>::value, 2 + sizeof...(S)>(*this, array<slice, 2 + sizeof...(S)>{{as_slice(s0), as_slice(s1), as_slice(s_)...}}, array<bool, 2 + sizeof...(S)>{{std::is_same<S0,slice>::value, std::is_same<S1,slice>::value, std::is_same<S,slice>::value...}});
                    }

                /* by array */

                template<class E>
                    typename std::enable_if<is_array<E>::value, numpy_fexpr<ndarray<T,N>, E>>::type
                    operator[](E const & expr) {
                        return numpy_fexpr<ndarray<T,N>, E>(*this, expr);
                    }
                template<class E>
                    typename std::enable_if<is_array<E>::value, numpy_fexpr<ndarray<T,N>, E>>::type
                    operator[](E const & expr) const {
                        return numpy_fexpr<ndarray<T,N>, E>(*this, expr);
                    }

                /* to the flat array */
                T at(long i) const { return buffer[i]; }
                T& at(long i) { return buffer[i]; }

#ifdef USE_BOOST_SIMD
                auto load(long i) const -> decltype(boost::simd::unaligned_load<boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION>>(buffer,i)) {
                    return boost::simd::unaligned_load<boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION>>(buffer,i);
                }
#endif

                /* through iterators */
                iterator begin() { return type_helper<ndarray<T,N>>::make_iterator(*this, 0); }
                const_iterator begin() const { return type_helper<ndarray<T,N>>::make_iterator(*this, 0); }
                iterator end() { return type_helper<ndarray<T,N>>::make_iterator(*this, data_size); }
                const_iterator end() const { return type_helper<ndarray<T,N>>::make_iterator(*this, data_size); }

                /* member functions */
                long size() const {
                    return std::accumulate(shape.begin()+1, shape.end(), *shape.begin(), std::multiplies<long>());
                }
                ndarray<T,1> flat() const {
                    ndarray<T, 1> flatty;
                    flatty.data_size = size();
                    flatty.mem = mem;
                    flatty.buffer = buffer;
                    return flatty;
                }
                template<size_t M>
                    ndarray<T,M> reshape(array<long,M> const& shape) const {
                        ndarray<T, M> reshappy;
                        reshappy.data_size = shape[0];
                        reshappy.mem = mem;
                        reshappy.buffer = mem->data;
                        reshappy.shape = shape;
                        return reshappy;
                    }

                ndarray<T,N> copy() const {
                    auto res = ndarray<T,N>(shape, __builtin__::None);
                    std::copy(buffer, buffer + size(), res.buffer);
                    return res;
                }

                intptr_t id() const {
                    return reinterpret_cast<intptr_t>(&(*mem));
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
            struct numpy_expr_to_ndarray<list<L>> {
                typedef typename utils::nested_container_value_type<list<L>>::type T;
                static const size_t N = utils::nested_container_depth<list<L>>::value;
                typedef ndarray<T, N> type;
            };

        template <class T_, size_t N_>
            struct numpy_expr_to_ndarray<ndarray<T_, N_>> {
                typedef T_ T;
                static const size_t N = N_;
                typedef ndarray<T, N> type;
            };

        template<class Op, class Arg>
            struct numpy_expr_to_ndarray<numpy_uexpr<Op, Arg>> {
                typedef typename std::remove_cv<typename std::remove_reference< decltype(std::declval<numpy_uexpr<Op, Arg>>().at(0)) >::type>::type T;
                static const size_t N = std::tuple_size< typename std::remove_cv<typename std::remove_reference< decltype(std::declval<numpy_uexpr<Op, Arg>>().shape) >::type > ::type > ::value;
                typedef ndarray<T, N> type;
            };

        template<class Op, class Arg0, class Arg1>
            struct numpy_expr_to_ndarray<numpy_expr<Op, Arg0, Arg1>> {
                typedef typename std::remove_cv<typename std::remove_reference< decltype(std::declval<numpy_expr<Op, Arg0, Arg1>>().at(0)) >::type>::type T;
                static const size_t N = std::tuple_size< typename std::remove_cv<typename std::remove_reference< decltype(std::declval<numpy_expr<Op, Arg0, Arg1>>().shape) >::type > ::type > ::value;
                typedef ndarray<T, N> type;
            };
        template<class E, size_t M, size_t L>
            struct numpy_expr_to_ndarray<gsliced_ndarray<E,M,L>> {
                typedef typename std::remove_cv<typename std::remove_reference< decltype(std::declval<gsliced_ndarray<E,M,L>>().at(0)) >::type>::type T;
                static const size_t N = std::tuple_size< typename std::remove_cv<typename std::remove_reference< decltype(std::declval<gsliced_ndarray<E,M,L>>().shape) >::type > ::type > ::value;
                typedef ndarray<T, N> type;

            };
        template<class E>
            struct numpy_expr_to_ndarray<sliced_ndarray<E>> {
                typedef typename std::remove_cv<typename std::remove_reference< decltype(std::declval<sliced_ndarray<E>>().at(0)) >::type>::type T;
                static const size_t N = std::tuple_size< typename std::remove_cv<typename std::remove_reference< decltype(std::declval<sliced_ndarray<E>>().shape) >::type > ::type > ::value;
                typedef ndarray<T, N> type;

            };
        template<class Arg, class F>
            struct numpy_expr_to_ndarray<numpy_fexpr<Arg, F>> {
                typedef typename std::remove_cv<typename std::remove_reference< decltype(std::declval<numpy_fexpr<Arg, F>>().at(0)) >::type>::type T;
                static const size_t N = std::tuple_size< typename std::remove_cv<typename std::remove_reference< decltype(std::declval<numpy_fexpr<Arg, F>>().shape) >::type > ::type > ::value;
                typedef ndarray<T, N> type;
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
        template< class T, size_t N>
            struct is_array< indexed_ndarray<T,N> > {
                static constexpr bool value = true;
            };
        template< class T, size_t M, size_t N>
            struct is_array< gsliced_ndarray<T,M,N> > {
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
            struct is_array_like<list<L>>{
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
        template<class T, size_t N>
            struct is_numexpr_arg<indexed_ndarray<T,N>> {
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
        template<class A, class F >
            struct is_numexpr_arg<numpy_fexpr<A,F>> {
                static constexpr bool value = true;
            };

        /* pretty printing { */
        template<class T, size_t N>
            std::ostream& operator<<(std::ostream& os, ndarray<T,N> const& e)
            {
                std::array<long, N> strides;
                auto shape = e.shape;
                strides[N-1] = shape[N-1];
                if(strides[N-1]==0)
                    return os << "[]";
                std::transform(strides.rbegin(), strides.rend() -1, shape.rbegin() + 1, strides.rbegin() + 1, std::multiplies<long>());
                size_t depth = N;
                int step = -1;
                std::ostringstream oss;
                auto e_count = e.size();
                oss << *std::max_element(e.buffer, e.buffer+ e_count);
                int size = oss.str().length();
                T* iter = e.buffer;
                int max_modulo = 1000;

                os << "[";
                if( shape[0] != 0)
                    do {
                        if(depth==1)
                        {
                            os.width(size);
                            os << *iter++;
                            for(int i=1; i<shape[N-1]; i++)
                            {
                                os.width(size+1);
                                os << *iter++;
                            }
                            step = 1;
                            depth++;
                            max_modulo = std::lower_bound(strides.begin(), strides.end(), iter - e.buffer, [](int comp, int val){ return val%comp!=0; }) - strides.begin();
                        }
                        else if(max_modulo + depth == N + 1)
                        {
                            depth--;
                            step = -1;
                            os << "]";
                            for(size_t i=0;i<depth;i++)
                                os << std::endl;
                            for(size_t i=0;i<N-depth;i++)
                                os << " ";
                            os << "[";
                        }
                        else
                        {
                            depth+=step;
                            if(step==1)
                                os << "]";
                            else
                                os << "[";
                        }
                    }
                    while(depth != N+1);

                return os << "]";
            }

        /* } */

    }

    /* make sure the size method from ndarray is not used */
    namespace __builtin__ {
        template <class T, size_t N, class I>
            struct _len<types::ndarray<T,N>, I, true> {
                long operator()(types::ndarray<T,N> const &t) {
                    return t.shape[0];
                }
            };

    }

    namespace utils {

        template<class Op, class Arg>
            struct nested_container_depth<types::numpy_uexpr<Op, Arg>> {
                static const int value = types::numpy_uexpr<Op, Arg>::value;
            };
        template<class Op, class Arg0, class Arg1>
            struct nested_container_depth<types::numpy_expr<Op, Arg0, Arg1>> {
                static const int  value = types::numpy_expr<Op, Arg0, Arg1>::value;
            };
    }

    template<class Op, class Arg0, class Arg1>
        struct assignable<types::numpy_expr<Op, Arg0, Arg1>>
        {
            typedef typename types::numpy_expr_to_ndarray<types::numpy_expr<Op, Arg0, Arg1>>::type type;
        };
    template<class Op, class Arg0>
        struct assignable<types::numpy_uexpr<Op, Arg0>>
        {
            typedef typename types::numpy_expr_to_ndarray<types::numpy_uexpr<Op, Arg0>>::type type;
        };
    template<class Arg, class Filter>
        struct assignable<types::numpy_fexpr<Arg, Filter>>
        {
            typedef typename types::numpy_expr_to_ndarray<types::numpy_fexpr<Arg, Filter>>::type type;
        };
    template<class T, size_t N>
        struct lazy<types::indexed_ndarray<T,N>>
        {
            typedef types::indexed_ndarray<T,N> type;
        };
    template<class Op, class Arg0>
        struct lazy<types::numpy_uexpr<Op,Arg0>>
        {
            typedef types::numpy_uexpr<Op,typename lazy<Arg0>::type> type;
        };
    template<class Op, class Arg0, class Arg1>
        struct lazy<types::numpy_expr<Op,Arg0,Arg1>>
        {
            typedef types::numpy_expr<Op,typename lazy<Arg0>::type, typename lazy<Arg1>::type> type;
        };
}

/* std::get overloads */
namespace std {

    template <size_t i, class t, size_t n>
        auto get( pythonic::types::ndarray<t,n>& a) -> decltype(a[i]) { return a[i]; }
    template <size_t i, class t, size_t n>
        auto get( pythonic::types::ndarray<t,n> const& a) -> decltype(a[i]) { return a[i]; }

    template <size_t i, class t>
        auto get( pythonic::types::sliced_ndarray<t>& a) -> decltype(a[i]) { return a[i]; }
    template <size_t i, class t>
        auto get( pythonic::types::sliced_ndarray<t> const& a) -> decltype(a[i]) { return a[i]; }

    template <size_t i, class t, size_t n>
        auto get( pythonic::types::indexed_ndarray<t,n>& a) -> decltype(a[i]) { return a[i]; }
    template <size_t i, class t, size_t n>
        auto get( pythonic::types::indexed_ndarray<t,n> const& a) -> decltype(a[i]) { return a[i]; }

    template <size_t I, class O, class A0, class A1>
        auto get( pythonic::types::numpy_expr<O,A0,A1> const& a) -> decltype(a[I]) { return a[I]; }
    template <size_t I, class O, class A>
        auto get( pythonic::types::numpy_uexpr<O,A> const& a) -> decltype(a[I]) { return a[I]; }

    template <size_t I, class T, size_t N>
        struct tuple_element<I, pythonic::types::ndarray<T,N> > {
            typedef typename pythonic::types::ndarray<T,N>::value_type type;
        };
    template <size_t I, class T, size_t N>
        struct tuple_element<I, pythonic::types::indexed_ndarray<T,N> > {
            typedef typename pythonic::types::ndarray<T,N>::value_type type;
        };
    template <size_t I, class T>
        struct tuple_element<I, pythonic::types::sliced_ndarray<T> > {
            typedef typename T::value_type type;
        };
    template <size_t I, class Op, class Arg0, class Arg1>
        struct tuple_element<I, pythonic::types::numpy_expr<Op,Arg0, Arg1> > {
            typedef typename pythonic::types::numpy_expr_to_ndarray<pythonic::types::numpy_expr<Op,Arg0, Arg1>>::type::value_type type;
        };
}

/* pythran attribute system { */
#include "pythonic/numpy/transpose.hpp"
namespace pythonic {
    namespace types {
        namespace __ndarray {

            template<int I, class E>
                struct getattr;

            template<class E> struct getattr<0, E> {
                auto operator()(E const& a) -> decltype(a.shape) { return a.shape; }
            };
            template<class E> struct getattr<1, E> {
                long operator()(E const& a) { return numpy_expr_to_ndarray<E>::N; }
            };
            template<class E> struct getattr<2, E> {
                array<long, numpy_expr_to_ndarray<E>::N> operator()(E const& a) {
                    array<long,numpy_expr_to_ndarray<E>::N> strides;
                    strides[numpy_expr_to_ndarray<E>::N-1] = sizeof(typename numpy_expr_to_ndarray<E>::T);
                    auto shape = a.shape;
                    std::transform(strides.rbegin(), strides.rend() -1, shape.rbegin(), strides.rbegin()+1, std::multiplies<long>());
                    return strides;
                }
            };
            template<class E> struct getattr<3, E> {
                long operator()(E const& a) { return a.size(); }
            };
            template<class E> struct getattr<4, E> {
                long operator()(E const& a) { return sizeof(typename numpy_expr_to_ndarray<E>::T); }
            };
            template<class E> struct getattr<5, E> {
                long operator()(E const& a) { return a.size() * sizeof(typename numpy_expr_to_ndarray<E>::T); }
            };
            template<class E> struct getattr<6, E> {
                auto operator()(E const& a) -> decltype(a.flat()) { return a.flat(); }
            };
            template<class E> struct getattr<7, E> {
                typename numpy_expr_to_ndarray<E>::T operator()(E const& a) { return typename numpy_expr_to_ndarray<E>::T(); }
            };
            template<class E> struct getattr<8, E> {
                auto operator()(E const& a) -> decltype(numpy::transpose(a)) { return numpy::transpose(a); }
            };
        }
    }
}
    template<int I, class T, size_t N>
    auto getattr(pythonic::types::ndarray<T,N> const& f)
-> decltype(pythonic::types::__ndarray::getattr<I,pythonic::types::ndarray<T,N>>()(f))
{
    return pythonic::types::__ndarray::getattr<I,pythonic::types::ndarray<T,N>>()(f);
}
    template<int I, class O, class A>
    auto getattr(pythonic::types::numpy_uexpr<O,A> const& f)
-> decltype(pythonic::types::__ndarray::getattr<I,pythonic::types::numpy_uexpr<O,A>>()(f))
{
    return pythonic::types::__ndarray::getattr<I,pythonic::types::numpy_uexpr<O,A>>()(f);
}
    template<int I, class O, class A0, class A1>
    auto getattr(pythonic::types::numpy_expr<O,A0,A1> const& f)
-> decltype(pythonic::types::__ndarray::getattr<I,pythonic::types::numpy_expr<O,A0,A1>>()(f))
{
    return pythonic::types::__ndarray::getattr<I,pythonic::types::numpy_expr<O,A0,A1>>()(f);
}
    template<int I, class E>
    auto getattr(pythonic::types::sliced_ndarray<E> const& f)
-> decltype(pythonic::types::__ndarray::getattr<I,pythonic::types::sliced_ndarray<E>>()(f))
{
    return pythonic::types::__ndarray::getattr<I,pythonic::types::sliced_ndarray<E>>()(f);
}
    template<int I, class E, size_t N, size_t M>
    auto getattr(pythonic::types::gsliced_ndarray<E,N,M> const& f)
-> decltype(pythonic::types::__ndarray::getattr<I,pythonic::types::gsliced_ndarray<E,N,M>>()(f))
{
    return pythonic::types::__ndarray::getattr<I,pythonic::types::gsliced_ndarray<E,N,M>>()(f);
}
    template<int I, class T, size_t N>
    auto getattr(pythonic::types::indexed_ndarray<T,N> const& f)
-> decltype(pythonic::types::__ndarray::getattr<I,pythonic::types::indexed_ndarray<T,N>>()(f))
{
    return pythonic::types::__ndarray::getattr<I,pythonic::types::indexed_ndarray<T,N>>()(f);
}

/* } */

/* type inference stuff  {*/
#include "pythonic/types/combined.hpp"

template<size_t N, class T, size_t M>
struct __combined<pythonic::types::ndarray<T,N>, pythonic::types::ndarray<T,M>> {
    typedef pythonic::types::ndarray<T,N> type;
};
template<size_t N, class T, class O>
struct __combined<pythonic::types::ndarray<T,N>, O> {
    typedef pythonic::types::ndarray<T,N> type;
};
template<size_t N, class T, class O>
struct __combined<O, pythonic::types::ndarray<T,N>> {
    typedef pythonic::types::ndarray<T,N> type;
};
template<class T, size_t N>
struct __combined<pythonic::types::indexed_ndarray<T,N>, pythonic::types::indexed_ndarray<T,N>> {
    typedef pythonic::types::indexed_ndarray<T,N> type;
};
template<class T, class O, size_t N>
struct __combined<pythonic::types::indexed_ndarray<T,N>, O> {
    typedef pythonic::types::indexed_ndarray<T,N> type;
};
template<class T, class O, size_t N>
struct __combined<O, pythonic::types::indexed_ndarray<T,N>> {
    typedef pythonic::types::indexed_ndarray<T,N> type;
};

template<class Arg0, class Op, class K>
struct __combined<pythonic::types::numpy_uexpr<Op, Arg0>, indexable<K>> {
    typedef pythonic::types::numpy_uexpr<Op, Arg0> type;
};

template<class Arg0, class Arg1, class Op, class K>
struct __combined<pythonic::types::numpy_expr<Op, Arg0, Arg1>, indexable<K>> {
    typedef pythonic::types::numpy_expr<Op, Arg0, Arg1> type;
};

template<class Arg0, class Op, class K>
struct __combined<indexable<K>, pythonic::types::numpy_uexpr<Op, Arg0>> {
    typedef pythonic::types::numpy_uexpr<Op, Arg0> type;
};

template<class Arg0, class Arg1, class Op, class K>
struct __combined<indexable<K>, pythonic::types::numpy_expr<Op, Arg0, Arg1>> {
    typedef pythonic::types::numpy_expr<Op, Arg0, Arg1> type;
};

template<class Arg0, class Op, class K, class V>
struct __combined<pythonic::types::numpy_uexpr<Op, Arg0>, indexable_container<K,V>> {
    typedef pythonic::types::numpy_uexpr<Op, Arg0> type;
};

template<class Arg0, class Arg1, class Op, class K, class V>
struct __combined<pythonic::types::numpy_expr<Op, Arg0, Arg1>, indexable_container<K,V>> {
    typedef pythonic::types::numpy_expr<Op, Arg0, Arg1> type;
};

template<class Arg0, class Op, class K, class V>
struct __combined<indexable_container<K,V>, pythonic::types::numpy_uexpr<Op, Arg0>> {
    typedef pythonic::types::numpy_uexpr<Op, Arg0> type;
};

template<class Arg0, class Arg1, class Op, class K, class V>
struct __combined<indexable_container<K,V>, pythonic::types::numpy_expr<Op, Arg0, Arg1>> {
    typedef pythonic::types::numpy_expr<Op, Arg0, Arg1> type;
};


template<class Arg0, class Op, class K>
struct __combined<container<K>, pythonic::types::numpy_uexpr<Op, Arg0>> {
    typedef pythonic::types::numpy_uexpr<Op, Arg0> type;
};

template<class Arg0, class Arg1, class Op, class K>
struct __combined<container<K>, pythonic::types::numpy_expr<Op, Arg0, Arg1>> {
    typedef pythonic::types::numpy_expr<Op, Arg0, Arg1> type;
};

template<class Arg0, class Op, class K>
struct __combined<pythonic::types::numpy_uexpr<Op, Arg0>, container<K>> {
    typedef pythonic::types::numpy_uexpr<Op, Arg0> type;
};

template<class Arg0, class Arg1, class Op, class K>
struct __combined<pythonic::types::numpy_expr<Op, Arg0, Arg1>, container<K>> {
    typedef pythonic::types::numpy_expr<Op, Arg0, Arg1> type;
};

template<class Arg0, class Arg1, class Op, class Op2, class Arg2, class Arg3>
struct __combined<pythonic::types::numpy_expr<Op, Arg0, Arg1>, pythonic::types::numpy_expr<Op2, Arg2, Arg3>> {
    typedef typename pythonic::types::numpy_expr_to_ndarray<pythonic::types::numpy_expr<Op, Arg0, Arg1>>::type type;
};

template<class Arg0, class Arg1, class Op, class Op2>
struct __combined<pythonic::types::numpy_uexpr<Op, Arg0>, pythonic::types::numpy_uexpr<Op2, Arg1>> {
    typedef typename pythonic::types::numpy_expr_to_ndarray<pythonic::types::numpy_uexpr<Op, Arg0>>::type type;
};

//
// PB : This led to poor performance (but I don't understand why)
//
//template<class Arg0, class Arg1, class Op, class Arg2, class Arg3>
//struct __combined<pythonic::types::numpy_expr<Op, Arg0, Arg1>, pythonic::types::numpy_expr<Op, Arg2, Arg3>> {
//    typedef pythonic::types::numpy_expr<Op, typename __combine<Arg0, Arg2>, typename __combine<Arg1, Arg3>> type;
//};
//
//template<class Arg0, class Arg1, class Op>
//struct __combined<pythonic::types::numpy_uexpr<Op, Arg0>, pythonic::types::numpy_uexpr<Op, Arg1>> {
//    typedef pythonic::types::numpy_uexpr<Op, typename __combine<Arg0, Arg1>::type> type;
//};

/* } */

#include "pythonic/types/numpy_operators.hpp"

#ifdef ENABLE_PYTHON_MODULE

#include "pythonic/python/register_once.hpp"
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include "arrayobject.h"

#include <boost/python/object.hpp>

namespace pythonic {

    template<class T>
        struct c_type_to_numpy_type {
            static const int value = c_type_to_numpy_type<decltype(std::declval<T>()())>::value;
        };

    template<>
        struct c_type_to_numpy_type<double> {
            static const int value = NPY_DOUBLE;
        };

    template<>
        struct c_type_to_numpy_type<float> {
            static const int value = NPY_FLOAT;
        };

    template<>
        struct c_type_to_numpy_type<std::complex<double>> {
            static const int value = NPY_CDOUBLE;
        };

    template<>
        struct c_type_to_numpy_type<long int> {
            static const int value = NPY_LONG;
        };

    template<>
        struct c_type_to_numpy_type<long unsigned int> {
            static const int value = NPY_ULONG;
        };

    template<>
        struct c_type_to_numpy_type<long long> {
            static const int value = NPY_LONGLONG;
        };

    template<>
        struct c_type_to_numpy_type<int> {
            static const int value = NPY_INT;
        };

    template<>
        struct c_type_to_numpy_type<unsigned int> {
            static const int value = NPY_UINT;
        };
    template<>
        struct c_type_to_numpy_type<short> {
            static const int value = NPY_SHORT;
        };

    template<>
        struct c_type_to_numpy_type<unsigned short> {
            static const int value = NPY_USHORT;
        };


    template<>
        struct c_type_to_numpy_type<signed char> {
            static const int value = NPY_INT8;
        };

    template<>
        struct c_type_to_numpy_type<unsigned char> {
            static const int value = NPY_UINT8;
        };

    template<>
        struct c_type_to_numpy_type<bool> {
            static const int value = NPY_BOOL;
        };

    template<class T>
        struct c_type_to_numpy_type< boost::simd::logical<T>> {
            static const int value = NPY_BOOL;
        };

    template<typename T, size_t N>
        struct python_to_pythran< types::ndarray<T, N> >{
            python_to_pythran(){
                static bool registered=false;
                python_to_pythran<T>();
                if(not registered) {
                    registered=true;
                    boost::python::converter::registry::push_back(&convertible,&construct,boost::python::type_id< types::ndarray<T, N> >());
                }
            }
            //reinterpret_cast needed to fit BOOST Python API. Check is done by template and PyArray_Check
            static void* convertible(PyObject* obj_ptr){
                if(!PyArray_Check(obj_ptr) or PyArray_TYPE(reinterpret_cast<PyArrayObject*>(obj_ptr)) != c_type_to_numpy_type<T>::value )
                    return 0;
                return obj_ptr;
            }

            static void construct(PyObject* obj_ptr, boost::python::converter::rvalue_from_python_stage1_data* data){
                void* storage=((boost::python::converter::rvalue_from_python_storage<types::ndarray<T,N>>*)(data))->storage.bytes;
                new (storage) types::ndarray< T, N>((T*)PyArray_BYTES(reinterpret_cast<PyArrayObject*>(obj_ptr)), PyArray_DIMS(reinterpret_cast<PyArrayObject*>(obj_ptr)), types::foreign());
                Py_INCREF(obj_ptr);
                data->convertible=storage;
            }
        };

    template <typename T>
        struct custom_boost_simd_logical {
            static PyObject* convert( boost::simd::logical<T> const& n) {
                return boost::python::incref(boost::python::object((T)n).ptr());
            }
        };
    template<typename T>
        struct pythran_to_python< boost::simd::logical<T> > {
            pythran_to_python() { register_once< boost::simd::logical<T>, custom_boost_simd_logical<T> >(); }
        };

    template<class T, size_t N>
        struct custom_array_to_ndarray {
            static PyObject* convert( types::ndarray<T,N> n) {
                n.mem.forget();
                PyObject* result = PyArray_SimpleNewFromData(N, n.shape.data(), c_type_to_numpy_type<T>::value, n.buffer);
                if (!result)
                    return nullptr;
                return result;
            }
        };

    template<class T, size_t N>
        struct pythran_to_python< types::ndarray<T,N> > {
            pythran_to_python() {
                register_once< types::ndarray<T,N> , custom_array_to_ndarray<T,N> >();
            }
        };

    template<class T>
        struct custom_sliced_array_to_ndarray {
            static PyObject* convert( types::sliced_ndarray<T> n) {
                return custom_array_to_ndarray<typename T::dtype, T::value>().convert(n);
            }
        };

    template<class T>
        struct pythran_to_python< types::sliced_ndarray<T> > {
            pythran_to_python() {
                register_once< types::sliced_ndarray<T> , custom_sliced_array_to_ndarray<T> >();
            }
        };
}

#endif


#endif

