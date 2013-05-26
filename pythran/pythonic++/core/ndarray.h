#ifndef PYTHONIC_ARRAY_H
#define PYTHONIC_ARRAY_H
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
                broadcast() {}
                broadcast(T v) : __value(v), _value(vectorized<T>::broadcast(v)) {}
#ifdef __AVX__
                typename vectorized<T>::type load(long ) const { return _value;}
#endif
                T at(long ) const {
                    return __value;
                }
            };

        template<class Op, class Arg0>
            struct numpy_uexpr {
                Arg0 arg0;
                typedef decltype(Op()(arg0.at(std::declval<long>()))) value_type;
                static constexpr size_t value = Arg0::value;
                core::ltuple<long, value> shape;
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
                size_t size() const { return arg0.size(); }
            };

        template<class U, class V, size_t N>
            typename std::enable_if<U::value!=0,core::ltuple<long, N>>::type const& select_shape(U const& u, V const&, int_<N> ) {
                return u.shape;
            }
        template<class U, class V, size_t N>
            typename std::enable_if<U::value==0 and V::value!=0,core::ltuple<long, N>>::type const& select_shape(U const& , V const&v, int_<N> ) {
                return v.shape;
            }
        template<class U, class V>
            core::ltuple<long, 0> select_shape(U const& u, V const&, int_<0> ) {
                return core::ltuple<long, 0>();
            }

        template<class Op, class Arg0, class Arg1>
            struct numpy_expr {
                Arg0 arg0;
                Arg1 arg1;
                typedef decltype(Op()(arg0.at(std::declval<long>()), arg1.at(std::declval<long>()))) value_type;
                static constexpr size_t value = Arg0::value>Arg1::value?Arg0::value: Arg1::value;
                core::ltuple<long, value> shape;
                numpy_expr() {}

                numpy_expr(Arg0 const& arg0, Arg1 const& arg1) : arg0(arg0), arg1(arg1), shape(select_shape(arg0,arg1, int_<value>())) {
                }
#ifdef __AVX__
                auto load(long i) const -> decltype(Op()(arg0.load(i), arg1.load(i))) {
                    return Op()(arg0.load(i), arg1.load(i));
                }
#endif
                auto at(long i) const -> decltype(Op()(arg0.at(i), arg1.at(i))) {
                    return Op()(arg0.at(i), arg1.at(i));
                }
                size_t size() const { return std::max(arg0.size(), arg1.size()); }
            };



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

        template<class T>
            struct to_ndarray {
                typedef T type;
            };
        template <class L>
            struct to_ndarray<core::list<L>> {
                typedef typename numpy_expr_to_ndarray<core::list<L>>::type type;
            };

        template<class Op, class Arg0, class Arg1>
            struct numpy_expr_to_ndarray<numpy_expr<Op, Arg0, Arg1>> {
                typedef typename std::remove_cv<typename std::remove_reference< decltype(std::declval<numpy_expr<Op, Arg0, Arg1>>().at(0)) >::type>::type T;
                static const size_t N = std::tuple_size< typename std::remove_cv<typename std::remove_reference< decltype(std::declval<numpy_expr<Op, Arg0, Arg1>>().shape) >::type > ::type > ::value;
                typedef core::ndarray<T, N> type;
            };


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

        template<class Expr>
            struct is_array {
                static constexpr bool value = is_numpy_expr<Expr>::value;
            };
        template< class T, size_t N>
            struct is_array< ndarray<T,N> > {
                static constexpr bool value = true;
            };

        template<class Expr>
            struct is_array_like {
                static constexpr bool value = is_array<Expr>::value;
            };
        template<class L>
            struct is_array_like<core::list<L>>{
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
                        self.shape = get_shape(self);
                        return offset;
                    }
                template<class ShapeIterator>
                    static long initialize_from_shape(ndarray<T,N>& self, memory& shared, T* mem_iter, ShapeIterator shape_iterator) {
                        self.mem = shared;
                        self.data_size = *shape_iterator;
                        self.data.resize(self.data_size);
                        self.buffer = mem_iter;
                        auto next_shape_iterator = ++shape_iterator;
                        long offset = 0;
                        for(auto & content : self.data)
                            offset += type_helper<ndarray<T,N-1>>::initialize_from_shape(content, shared, mem_iter + offset, next_shape_iterator);
                        self.shape = get_shape(self);
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
                        self.shape = get_shape(self);
                        return data_end - self.data;
                    }
                template<class ShapeIterator>
                    static long initialize_from_shape(ndarray<T,1>& self, memory& shared, T* mem_iter, ShapeIterator shape_iterator) {
                        self.mem = shared;
                        self.data = mem_iter;
                        self.data_size = *shape_iterator;
                        self.buffer = mem_iter;
                        self.shape = get_shape(self);
                        return self.data_size;
                    }
            };

        slice const& as_shape(slice const& s) { return s;}
        slice as_shape(long s) { return slice(s,s+1);}

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

        template<class T, size_t M>
            struct gsliced_ndarray {
                static constexpr size_t value = M;

                typedef typename T::value_type value_type;
                typedef typename T::reference reference;
                typedef typename T::const_reference const_reference;
                std::vector<slice> gslice;
                core::ltuple<long, value> shape;

                T data;

                gsliced_ndarray(T const& data, std::vector<slice> const& s) : gslice(s), shape(data.shape.begin(), data.shape.end()), data(data) {
                    for(size_t i=0;i<gslice.size();i++) {
                        if(gslice[i].upper > shape[i])
                            gslice[i].upper = shape[i];
                        else if(gslice[i].upper < 0)
                            gslice[i].upper += shape[i];
                        if(gslice[i].lower <0)
                            gslice[i].lower += shape[i];
                        shape[i] = ceil(std::abs(double(gslice[i].upper - gslice[i].lower)/gslice[i].step));
                    }
                }

                long to_index(long i) const {
                    long mult = 1;
                    long dmult = 1;
                    long findex = 0;
                    auto const &dshape = data.shape;
                    for(long j=gslice.size()-1; j>0; j--) {
                        findex += (gslice[j].lower + (i/mult)%shape[j])*dmult;
                        mult*=shape[j];
                        dmult*=dshape[j];
                    }
                    return findex + (gslice[0].lower + i/mult)*dmult;
                }

                auto at(long i) const -> decltype(data.at(0)) {
                    return data.at(to_index(i));
                }

                size_t size() const {
                    size_t n = data.size();
                    for(size_t i=0;i<gslice.size();++i)
                        n = (n / data.shape[i]) * shape[i];
                    return n;
                }

                gsliced_ndarray<T,M>& operator=(value_type v) {
                    for(long i=0, n= size(); i<n ; ++i)
                        data.buffer[to_index(i)] = v;
                    return *this;
                }

                template<class E, size_t P>
                    typename std::enable_if<core::is_array<E>::value, gsliced_ndarray<T,P>&>::type operator=(E const& v) {
                        for(long i=0, n= size(); i<n ; ++i)
                            data.buffer[to_index(i)] = v.at(i);
                        return *this;
                    }


                gsliced_ndarray<T,M>& operator+=(value_type v) {
                    for(long i=0, n= size(); i<n ; ++i)
                        data.buffer[to_index(i)] += v;
                    return *this;
                }

                gsliced_ndarray<T,M>& operator-=(value_type v) {
                    for(long i=0, n= size(); i<n ; ++i)
                        data.buffer[to_index(i)] -= v;
                    return *this;
                }
            };

        template<class T>
            struct sliced_ndarray : slice {
                static constexpr size_t value = T::value;
                typedef typename T::value_type value_type;
                typedef typename T::reference reference;
                typedef typename T::const_reference const_reference;
                core::ltuple<long, value> shape;
                size_t jump;

                T data;

                sliced_ndarray(T const& data, slice const& s) : slice(s), shape(data.shape.begin(), data.shape.end()), data(data) {
                    shape[0] = ceil(std::abs(double(upper - lower)/step));
                    jump = 1;
                    for(size_t i=1;i<value; ++i)
                        jump*=shape[i];
                }

                auto at(long i) const -> decltype(data.at(jump*lower+i*step)) {
                    return data.at(jump*lower+i*step);
                }
                size_t size() const { return (data.size() / data.shape[0]) * shape[0] ; }
                reference operator[](long i) { return data[jump*lower+i*step]; }
                const_reference operator[](long i) const { return data[jump*lower+i*step]; }
                sliced_ndarray<T> operator[](slice const& s) const { return sliced_ndarray(data, slice(lower + step*s.lower, std::min(upper, lower + step*s.upper), step*s.step)); }
                sliced_ndarray<T> operator[](slice const& s) { return sliced_ndarray(data, slice(lower + step*s.lower, std::min(upper, lower + step*s.upper), step*s.step)); }

                sliced_ndarray<T>& operator=(value_type v) {
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
                typename std::enable_if<core::is_array<E>::value, sliced_ndarray<T>&>::type operator=(E const& v) {
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

        /* a few helpers */
        long product(long t) { return t; }
        template<class... Types>
            long product(long t, Types... types) { return t * product(types...); }

        template<class T, size_t N>
            struct _get_shape {
                template<class Iter>
                    void operator()(ndarray<T,N> const& array, Iter iter) {
                        if((*iter++ = array.data_size))
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
                ltuple<long, N> v;
                _get_shape<T,N>()(array, v.begin());
                return v;
            }

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
                size_t data_size;
                typename type_helper<ndarray<T, N>>::memory mem;
                typename type_helper<ndarray<T, N>>::holder data;
                T* buffer;
                ltuple<long, N> shape;

                /* constructors */
                ndarray() : data_size(0), mem(impl::no_memory()), data(), buffer(nullptr), shape() {}

                /* copy */
                ndarray(ndarray<T,N> const& other) :
                    data_size(other.data_size),
                    mem(other.mem),
                    data(other.data),
                    buffer(other.buffer),
                    shape(other.shape)
                {
                }

                /* from a sequence */
                template<class Iterable>
                    ndarray(Iterable&& iterable, typename std::enable_if< // prevent destruction of copy constructor
                            !std::is_same<typename std::remove_cv<typename std::remove_reference<Iterable>::type>::type, ndarray<T,N>>::value
                            and
                            !is_numpy_expr<Iterable>::value
                            and
                            is_iterable<Iterable>::value,
                            bool>::type = false):
                        data_size(0),
                        mem(nested_container_size<Iterable>()(std::forward<Iterable>(iterable))),
                        data(),
                        shape()
                {
                    type_helper<ndarray<T,N>>::initialize_from_iterable(*this, mem, mem->data, std::forward<Iterable>(iterable));
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
                    type_helper<ndarray<T,N>>::initialize_from_shape(*this, mem, mem->data, shape_iterator);
                }

                /* from a foreign pointer */
                ndarray(T* data, long int* shape, size_t data_size):
                    data_size(data_size),
                    mem(data),
                    data(),
                    shape(shape, shape + N)
                {
                    mem.external(); // make sure we do not releas the pointer
                    auto shape_iterator = this->shape.begin();
                    type_helper<ndarray<T,N>>::initialize_from_shape(*this, mem, mem->data, shape_iterator);
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
                        data_size(0),
                        mem(expr.size()),
                        data(),
                        shape(expr.shape)
                {
                    auto shape_iterator = shape.begin();
                    type_helper<ndarray<T,N>>::initialize_from_shape(*this, mem, mem->data, shape_iterator);
                    initialize_from_expr(expr);
                }

                template<class Op, class Arg0>
                    ndarray(numpy_uexpr<Op, Arg0> const & expr) :
                        data_size(0),
                        mem(expr.size()),
                        data(),
                        shape(expr.shape)
                {
                    auto shape_iterator = shape.begin();
                    type_helper<ndarray<T,N>>::initialize_from_shape(*this, mem, mem->data, shape_iterator);
                    initialize_from_expr(expr);
                }
                /* from a slice */
                template<class E>
                    ndarray(sliced_ndarray<E> const& expr):
                        data_size(0),
                        mem(expr.size()),
                        data(),
                        shape(expr.shape)
                {
                    auto shape_iterator = shape.begin();
                    type_helper<ndarray<T,N>>::initialize_from_shape(*this, mem, mem->data, shape_iterator);
                    initialize_from_expr(expr);
                }
                template<class E, size_t M>
                    ndarray(gsliced_ndarray<E,M> const& expr):
                        data_size(0),
                        mem(expr.size()),
                        data(),
                        shape(expr.shape)
                {
                    auto shape_iterator = shape.begin();
                    type_helper<ndarray<T,N>>::initialize_from_shape(*this, mem, mem->data, shape_iterator);
                    initialize_from_expr(expr);
                }

                /* assignment */
                ndarray<T,N>& operator=(ndarray<T,N> const& other) {
                    if(data_size == other.data_size) { // maybe a subarray copy ?
                        data_size = other.data_size;
                        std::copy(other.begin(), other.end(), begin());
                    }
                    else {
                        data_size = other.data_size;
                        mem = other.mem;
                        data = other.data;
                        buffer = other.buffer;
                        shape = other.shape;
                    }
                    return *this;
                }

                /* accessors */
                reference operator[](long i) { if(i<0) return data[i+size()]; else return data[i]; }
                template<class U, size_t M>
                    typename ndarray<T, N-M+1>::reference operator[](ltuple<U,M> const& l) { return mat<typename ndarray<T, N-M+1>::reference>(l.begin(), int_<M>()); }
                const_reference operator[](long i) const { if(i<0) return data[i+size()]; else return data[i]; }
                sliced_ndarray<ndarray<T,N>> operator[](slice const& s) const
                {
                    long lower, upper;
                    lower = s.lower >= 0L ? s.lower : ( s.lower + size());
                    lower = std::max(0L,lower);
                    upper = s.upper >= 0L ? s.upper : ( s.upper + size());
                    upper = std::min(upper, (long)size());
                    return sliced_ndarray<ndarray<T,N>>(*this, slice(lower, upper, s.step));
                }
                sliced_ndarray<ndarray<T,N>> operator[](slice const& s)
                {
                    long lower, upper;
                    lower = s.lower >= 0L ? s.lower : ( s.lower + size());
                    lower = std::max(0L,lower);
                    upper = s.upper >= 0L ? s.upper : ( s.upper + size());
                    upper = std::min(upper, (long)size());
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

                template<class S0, class S1, class...S>
                gsliced_ndarray<ndarray<T,N>, count_slices<S0,S1,S...>::value > operator()(S0 const& s0, S1 const& s1, S const&... s_) const
                {
                    return gsliced_ndarray<ndarray<T,N>, count_slices<S0,S1,S...>::value>(*this, std::vector<slice>({as_shape(s0), as_shape(s1), as_shape(s_)...}));
                }

                template<class S0, class S1, class...S>
                gsliced_ndarray<ndarray<T,N>, count_slices<S0,S1,S...>::value > operator()(S0 const& s0, S1 const& s1, S const&... s_)
                {
                    return gsliced_ndarray<ndarray<T,N>, count_slices<S0,S1,S...>::value>(*this, std::vector<slice>({as_shape(s0), as_shape(s1), as_shape(s_)...}));
                }


                typename type_helper<ndarray<T, N>>::iterator begin() { return type_helper<ndarray<T, N>>::begin(*this); }
                typename type_helper<ndarray<T, N>>::iterator end() { return type_helper<ndarray<T, N>>::end(*this); }
                typename type_helper<ndarray<T, N>>::const_iterator begin() const { return type_helper<ndarray<T, N>>::begin(*this); }
                typename type_helper<ndarray<T, N>>::const_iterator end() const { return type_helper<ndarray<T, N>>::end(*this); }

                T& at(long i) { return buffer[i]; }
                T at(long i) const { return buffer[i]; }

#ifdef __AVX__
                auto load(long i) const -> decltype(boost::simd::unaligned_load<boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION>>(buffer,i)) {
                    return boost::simd::unaligned_load<boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION>>(buffer,i);
                }
#endif

                /* helpers */
                template<class R, class U, size_t M>
                    R mat(U&& iter, int_<M>) {
                        return (*this)[*iter].template mat<R>(iter+1, int_<M-1>());
                    }
                template<class R, class U>
                    R mat(U&& iter, int_<1>) {
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
