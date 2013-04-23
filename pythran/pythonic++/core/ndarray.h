#ifndef PYTHONIC_ARRAY_H
#define PYTHONIC_ARRAY_H
#include <cassert>
#include <iostream>
#include <iterator>
#include <array>
#include <initializer_list>
#include "shared_ref.h"

#include <boost/simd/sdk/simd/native.hpp>
#ifdef __AVX__
#include <boost/simd/include/functions/unaligned_load.hpp>
#include <boost/simd/include/functions/unaligned_store.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/include/functions/store.hpp>
#endif


namespace  pythonic {
    namespace __builtin__ {
        template <class T>
            long len(T const &t);
    }

    namespace core {

        template<class T, size_t N>
            struct ndarray;

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

                size_t size() const { return 0; }
                T __value;
                typename vectorized<T>::type _value;
                static constexpr size_t value = 0;
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
                static constexpr size_t value = Arg0::value;
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
                size_t size() const { return arg0.size(); }
                auto shape() const -> decltype(arg0.shape()) { return arg0.shape(); }
            };

        template <class Op, class T0, size_t N0>
            struct numpy_uexpr<Op, ndarray<T0,N0>> {
                T0 *arg0;
                typedef decltype(Op()(arg0[std::declval<long>()])) value_type;
                static constexpr size_t value = N0;
                size_t _size;
                ndarray<T0,N0> a0;
                numpy_uexpr(ndarray<T0,N0> const& arg0 ) : arg0(arg0.buffer), _size(arg0.size()), a0(arg0) {
                }
#ifdef __AVX__
                auto load(long i) const -> decltype(Op()( boost::simd::unaligned_load<boost::simd::native<T0, BOOST_SIMD_DEFAULT_EXTENSION>>(arg0,i) )) {
                    return Op()(boost::simd::unaligned_load<boost::simd::native<T0, BOOST_SIMD_DEFAULT_EXTENSION>>(arg0,i));
                }
#endif
                auto operator[](long i) const -> decltype(Op()(arg0[i])) {
                    return Op()(arg0[i]);
                }
                size_t size() const { return _size; }
                core::ltuple<long, N0> const & shape() const { return a0.shape; }
            };

        template<class Op, class Arg0, class Arg1>
            struct numpy_expr {
                Arg0 arg0;
                Arg1 arg1;
                typedef decltype(Op()(arg0[std::declval<long>()], arg1[std::declval<long>()])) value_type;
                static constexpr size_t value = Arg0::value>Arg1::value?Arg0::value: Arg1::value;
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
                size_t size() const { return std::max(arg0.size(), arg1.size()); }
                auto shape() const -> decltype(arg0.shape()) { return arg0.shape(); }
            };

        template<class Op, class T0, size_t N0, class T1, size_t N1>
            struct numpy_expr<Op, ndarray<T0,N0>, ndarray<T1,N1>> {
                T0* arg0;
                T1* arg1;
                size_t _size;
                typedef decltype(Op()(arg0[std::declval<long>()], arg1[std::declval<long>()])) value_type;
                static constexpr size_t value = N0>N1?N0:N1;
                ndarray<T0,N0> a0;
                ndarray<T1,N1> a1;
                numpy_expr(ndarray<T0,N0> const& arg0, ndarray<T1,N1> const& arg1) :
                    arg0(arg0.buffer),
                    arg1(arg1.buffer),
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
                size_t size() const { return _size; }
                core::ltuple<long, N0> const & shape() const { return a0.shape; }
            };

        template<class Op, class T0, size_t N0, class Arg1>
            struct numpy_expr<Op, ndarray<T0,N0>, Arg1> {
                T0* arg0;
                Arg1 arg1;
                size_t _size;
                typedef decltype(Op()(arg0[std::declval<long>()], arg1[std::declval<long>()])) value_type;
                static constexpr size_t value = N0>Arg1::value?N0:Arg1::value;
                ndarray<T0,N0> a0;
                numpy_expr(ndarray<T0,N0> const& arg0, Arg1 const& arg1) :
                    arg0(arg0.buffer),
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
                size_t size() const { return _size; }
                core::ltuple<long, N0> const & shape() const { return a0.shape; }
            };

        template<class Op, class Arg0, class T1, size_t N1>
            struct numpy_expr<Op, Arg0, ndarray<T1,N1>> {
                Arg0 arg0;
                T1* arg1;
                size_t _size;
                typedef decltype(Op()(arg0[std::declval<long>()], arg1[std::declval<long>()])) value_type;
                static constexpr size_t value = Arg0::value>N1?Arg0::value:N1;
                ndarray<T1,N1> a1;
                numpy_expr(Arg0 const& arg0, ndarray<T1,N1> const& arg1) :
                    arg0(arg0),
                    arg1(arg1.buffer),
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
                size_t size() const { return _size; }
                core::ltuple<long, N1> const & shape() const { return a1.shape; }
            };

#if 0
        template <class Expr>
            struct numpy_expr_to_ndarray;

        template<class Op, class Arg>
            struct numpy_expr_to_ndarray<numpy_uexpr<Op, Arg>> {
                typedef typename std::remove_cv<typename std::remove_reference< decltype(std::declval<numpy_uexpr<Op, Arg>>()[0]) >::type>::type T;
                static const size_t N = std::tuple_size< typename std::remove_cv<typename std::remove_reference< decltype(std::declval<numpy_uexpr<Op, Arg>>().shape()) >::type > ::type > ::value;
                typedef core::ndarray<T, N> type;
            };

        template<class Op, class Arg0, class Arg1>
            struct numpy_expr_to_ndarray<numpy_expr<Op, Arg0, Arg1>> {
                typedef typename std::remove_cv<typename std::remove_reference< decltype(std::declval<numpy_expr<Op, Arg0, Arg1>>()[0]) >::type>::type T;
                static const size_t N = std::tuple_size< typename std::remove_cv<typename std::remove_reference< decltype(std::declval<numpy_expr<Op, Arg0, Arg1>>().shape()) >::type > ::type > ::value;
                typedef core::ndarray<T, N> type;
            };
#endif

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
                        self.data_size = iterable.size();
                        self.data.resize(self.data_size);
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
                        self.data_size = *shape_iterator;
                        self.data.resize(self.data_size);
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
                static iterator end(ndarray<T,1>& self) { return self.data + self.data_size; }
                static const_iterator begin(ndarray<T,1> const& self) { return self.data; }
                static const_iterator end(ndarray<T,1> const& self) { return self.data + self.data_size; }
                template<class Iterable>
                    static long initialize_from_iterable(ndarray<T,1>& self, memory& shared, T* mem_iter, Iterable&& iterable) {
                        self.mem = shared;
                        self.data = mem_iter;
                        self.data_size = iterable.size();
                        self.buffer = mem_iter;
                        auto data_end = std::copy(iterable.begin(), iterable.end(), self.data);
                        return data_end - self.data;
                    }
                template<class ShapeIterator>
                    static long initialize_from_shape(ndarray<T,1>& self, memory& shared, T* mem_iter, ShapeIterator& shape_iterator) {
                        self.mem = shared;
                        self.data = mem_iter;
                        self.data_size = *shape_iterator;
                        self.buffer = mem_iter;
                        return self.data_size;
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
                        *iter++ = array.data_size;
                        _get_shape<T, N-1>()(array.data[0], iter);
                    }
            };
        template<class T>
            struct _get_shape<T,1> {
                template<class Iter>
                    void operator()(ndarray<T,1> const& array, Iter iter) {
                        *iter = array.data_size;
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
                size_t data_size;
                typename type_helper<ndarray<T, N>>::memory mem;
                typename type_helper<ndarray<T, N>>::holder data;
                T* buffer;
                ltuple<long, N> shape;

                /* constructors */
                ndarray() : data_size(0), mem(impl::no_memory()), data(), buffer(nullptr) {}


                /* from a sequence */
                template<class Iterable>
                    ndarray(Iterable&& iterable, typename std::enable_if< // prevent destruction of copy constructor
                            !std::is_same<typename std::remove_cv<typename std::remove_reference<Iterable>::type>::type, ndarray<T,N>>::value
                            and
                            !is_numpy_expr<Iterable>::value,
                            bool>::type = false):
                        data_size(0),
                        mem(nested_container_size<Iterable>()(std::forward<Iterable>(iterable))),
                        data(),
                        shape(N)
                {
                    type_helper<ndarray<T,N>>::initialize_from_iterable(*this, mem, mem->data, std::forward<Iterable>(iterable));
                    shape = get_shape(*this);
                }

                /* from a shape */
                template<class Shape>
                    ndarray(Shape&& shape, T value):
                        data_size(0),
                        mem(std::accumulate(shape.begin(), shape.end(), 1, std::multiplies<long>())),
                        data(),
                        shape(shape)

                {
                    auto shape_iterator = shape.begin();
                    long offset = type_helper<ndarray<T,N>>::initialize_from_shape(*this, mem, mem->data, shape_iterator);
                    std::fill(mem->data, mem->data + offset, value);
                }

                /* from a shape without setting values */
                template<class Shape>
                    ndarray(Shape&& shape, none_type):
                        data_size(0),
                        mem(std::accumulate(shape.begin(), shape.end(), 1, std::multiplies<long>())),
                        data(),
                        shape(shape)
                {
                    auto shape_iterator = shape.begin();
                    long offset = type_helper<ndarray<T,N>>::initialize_from_shape(*this, mem, mem->data, shape_iterator);
                }

                /* from a foreign pointer */
                ndarray(T* data, long int* shape, size_t data_size):
                    data_size(data_size),
                    mem(data),
                    data(),
                    shape(shape, shape + N)
                {
                    mem.external(); // make sure we do not releas the pointer
                    auto shape_iterator = shape;
                    type_helper<ndarray<T,N>>::initialize_from_shape(*this, mem, mem->data, shape_iterator);
                }

                /* from a  numpy expression */
                template<class E>
                    void initialize_from_expr(E const & expr) {
                        long n = expr.size();
                        T* iter = buffer;
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
                    ndarray(numpy_expr<Op, Arg0, Arg1> const & expr) :
                        data_size(0),
                        mem(expr.size()),
                        data(),
                        shape(expr.shape())
                {
                    auto shape_iterator = shape.begin();
                    long offset = type_helper<ndarray<T,N>>::initialize_from_shape(*this, mem, mem->data, shape_iterator);
                    initialize_from_expr(expr);
                }

                template<class Op, class Arg0>
                    ndarray(numpy_uexpr<Op, Arg0> const & expr) :
                        data_size(0),
                        mem(expr.size()),
                        data(),
                        shape(expr.shape())
                {
                    auto shape_iterator = shape.begin();
                    long offset = type_helper<ndarray<T,N>>::initialize_from_shape(*this, mem, mem->data, shape_iterator);
                    initialize_from_expr(expr);
                }

                /* assignment */
                ndarray<T,N>& operator=(ndarray<T,N> const& other) {
                    if(data_size == other.data_size) // maybe a subarray copy ?
                        std::copy(other.begin(), other.end(), begin());
                    else { // just an init ?
                        data_size = other.data_size;
                        mem = other.mem;
                        data = other.data;
                        buffer = other.buffer;
                    }
                    shape = get_shape(*this);
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
                size_t size() const {
                    return std::accumulate(shape.begin(), shape.end(), 1, std::multiplies<long>());
                }
                ndarray<T,1> flat() const {
                    ndarray<T, 1> flatty;
                    flatty.data_size = size();
                    flatty.mem = mem;
                    flatty.data = flatty.buffer = buffer;
                    return flatty;
                }
                template<size_t M>
                    ndarray<T,M> reshape(core::ltuple<long,M> const& shape) const {
                        ndarray<T, M> reshappy;
                        reshappy.mem = mem;
                        auto shape_iterator = shape.begin();
                        type_helper<ndarray<T, M>>::initialize_from_shape(reshappy, reshappy.mem, reshappy.mem->data, shape_iterator);
                        return reshappy;
                    }

            };
    }
}
#endif
