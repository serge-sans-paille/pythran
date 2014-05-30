#ifndef PYTHONIC_TYPES_NDARRAY_HPP
#define PYTHONIC_TYPES_NDARRAY_HPP

#include "pythonic/types/assignable.hpp"
#include "pythonic/types/empty_iterator.hpp"
#include "pythonic/types/attr.hpp"

#include "pythonic/utils/nested_container.hpp"
#include "pythonic/utils/shared_ref.hpp"
#include "pythonic/utils/reserve.hpp"
#include "pythonic/utils/int_.hpp"
#include "pythonic/utils/broadcast_copy.hpp"

#include "pythonic/types/slice.hpp"
#include "pythonic/types/tuple.hpp"
#include "pythonic/types/list.hpp"
#include "pythonic/types/raw_array.hpp"

#include "pythonic/types/numexpr_to_ndarray.hpp"
#include "pythonic/types/numpy_fexpr.hpp"
#include "pythonic/types/numpy_expr.hpp"
#include "pythonic/types/numpy_uexpr.hpp"
#include "pythonic/types/numpy_texpr.hpp"
#include "pythonic/types/numpy_iexpr.hpp"
#include "pythonic/types/numpy_gexpr.hpp"

#include "pythonic/__builtin__/len.hpp"

#include <cassert>
#include <iostream>
#include <iterator>
#include <array>
#include <initializer_list>
#include <numeric>

#ifdef ENABLE_PYTHON_MODULE
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include "arrayobject.h"

#include <boost/python/object.hpp>
#endif

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

        template<class Expr>
            struct is_array;
        template<class T>
            struct type_helper;

        /* Type adaptor for broadcasted array values
         *
         * Used when the args of a binary operator do not have the same dimensions:
         * in that case their first dimension always yields a copy
         */
        template<class T>
            struct broadcasted {
                typedef typename T::dtype dtype;
                typedef typename T::value_type value_type;
                static constexpr size_t value = T::value + 1;

                T const & ref;
                array<long, value> shape;

                broadcasted(T const& ref) : ref(ref), shape() {
                    shape[0] = 1;
                    std::copy(ref.shape.begin(), ref.shape.end(), shape.begin() + 1);
                }

                T const & operator[](long i) const { return ref;}
                T const & fast(long i) const { return ref;}

                long size() const { return 0;}


            };

        /* Type adaptor for scalar values
         *
         * Have them behave like infinite arrays of that value
         */
        template<class T>
            struct broadcast {
                typedef T dtype;
                typedef T value_type;
                static constexpr size_t value = 0;
                T __value;

                broadcast() {}
                broadcast(T v) : __value(v) {}

                T operator[](long ) const {
                    return __value;
                }
                T fast(long ) const {
                    return __value;
                }
                long size() const { return 0; }
            };


        /* Helper for dimension-specific part of ndarray
         *
         * Instead of specializing the whole ndarray class, the dimension-specific behavior are stored here.
         * There are two specialization for this type:
         * - a specialization depending on the dimensionality (==1 or > 1)
         * - a specialization depending on the constness.
         *
         * The raw ndarray<T,N> specialization implies a *swallow copy* of the ndarray, and thus a refcount increase.
         * It is meant to be used when indexing an rvalue, as in ``np.zeros(10)[i]``.
         *
         * The ndarray<T,N> const& specialization implies a *reference copy*. It is used when indexing a lvalue, as in ``a[i]``
         */

        template<class T, size_t N>
            struct type_helper<ndarray<T,N>> {
                typedef numpy_iexpr<ndarray<T,N>> type;

                typedef nditerator<ndarray<T,N>> iterator;
                typedef const_nditerator<ndarray<T,N>> const_iterator;

                type_helper() = delete; // Not intended to be instantiated

                static iterator make_iterator(ndarray<T,N>& n, long i) { return iterator(n, i); }
                static const_iterator make_iterator(ndarray<T,N> const & n, long i) { return const_iterator(n, i); }

                template<class S, class Iter>
                    static T* initialize_from_iterable(S& shape, T* from, Iter&& iter) {
                        return type_helper<ndarray<T,N> const &>::initialize_from_iterable(shape, from, std::forward<Iter>(iter));
                    }

                static numpy_iexpr<ndarray<T,N>> get(ndarray<T,N> && self, long i) {
                    return numpy_iexpr<ndarray<T,N>>(std::move(self), i);
                }
                static long step(ndarray<T,N> const& self) { return std::accumulate(self.shape.begin() + 1, self.shape.end(), 1L, std::multiplies<long>());}
            };

        template<class T, size_t N>
            struct type_helper<ndarray<T,N> const&> {
                typedef numpy_iexpr<ndarray<T,N> const&> type;

                typedef nditerator<ndarray<T,N>> iterator;
                typedef const_nditerator<ndarray<T,N>> const_iterator;

                type_helper() = delete; // Not intended to be instantiated

                static iterator make_iterator(ndarray<T,N>& n, long i) { return iterator(n, i); }
                static const_iterator make_iterator(ndarray<T,N> const & n, long i) { return const_iterator(n, i); }

                template<class S, class Iter>
                    static T* initialize_from_iterable(S& shape, T* from, Iter&& iter) {
                        shape[std::tuple_size<S>::value - N] = iter.size();
                        for(auto content : iter) {
                            from = type_helper<ndarray<T,N - 1> const &>::initialize_from_iterable(shape, from, content);
                        }
                        return from;
                    }

                static numpy_iexpr<ndarray<T,N>const &> get(ndarray<T,N> const& self, long i) {
                    return numpy_iexpr<ndarray<T,N> const&>(self, i);
                }
                static long step(ndarray<T,N> const& self) { return std::accumulate(self.shape.begin() + 1, self.shape.end(), 1L, std::multiplies<long>());}
            };

        template<class T>
            struct type_helper<ndarray<T,1>> {
                typedef T type;

                typedef T* iterator;
                typedef T const * const_iterator;

                type_helper() = delete; // Not intended to be instantiated

                static iterator make_iterator(ndarray<T,1>& n, long i) { return n.buffer + i; }
                static const_iterator make_iterator(ndarray<T,1> const & n, long i) { return n.buffer + i; }

                template<class S, class Iter>
                    static T* initialize_from_iterable(S& shape, T* from, Iter&& iter) {
                        shape[std::tuple_size<S>::value - 1] = iter.size();
                        return std::copy(iter.begin(), iter.end(), from);
                    }

                static type get(ndarray<T,1> && self, long i) {
                    return self.buffer[i];
                }
                static constexpr long step(ndarray<T,1> const& ) { return 1;}
            };
        template<class T>
            struct type_helper<ndarray<T,1> const &> {
                typedef T type;

                typedef T* iterator;
                typedef T const * const_iterator;

                type_helper() = delete; // Not intended to be instantiated

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

        /* recursively return the value at the position given by `indices' in the `self' "array like". It may be a sub array instead of real value.
         * indices[0] is the coordinate for the first dimension and indices[M-1] is for the last one.
         */
        template<size_t L>
            struct nget {
                template <class A, size_t M>
                    auto operator()(A && self, array<long, M> const& indices)
                    -> decltype(nget<L-1>()(std::forward<A>(self)[0], indices))
                    {
                        return nget<L-1>()(std::forward<A>(self)[indices[M - L - 1]], indices);
                    }
            };
        template<>
            struct nget<0> {
                template<class A, size_t M>
                    auto operator()(A && self, array<long, M> const& indices)
                    -> decltype(std::forward<A>(self)[indices[M - 1]])
                    {
                        return std::forward<A>(self)[indices[M - 1]];
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
                static constexpr size_t value = N;
                typedef T dtype;
                typedef typename type_helper<ndarray>::type value_type;
                typedef value_type& reference;
                typedef value_type const & const_reference;

                typedef typename type_helper<ndarray>::iterator iterator;
                typedef typename type_helper<ndarray>::const_iterator const_iterator;
                typedef T* flat_iterator;
                typedef T const * const_flat_iterator;

                /* members */
                utils::shared_ref<raw_array<T>> mem;    // shared data pointer
                T* buffer;                              // pointer to the first data stored in the equivalent flat array
                array<long, N> shape;                   // shape of the multidimensional array

                /* constructors */
                ndarray() : mem(utils::no_memory()), buffer(nullptr), shape() {}
                ndarray(ndarray const & ) = default;
                ndarray(ndarray && ) = default;

                /* assignment */
                ndarray& operator=(ndarray const& other) = default;

                /* from other memory */
                ndarray(utils::shared_ref<raw_array<T>> const &mem, array<long,N> const& shape):
                    mem(mem),
                    buffer(mem->data),
                    shape(shape)
                {
                }

                /* from other array */
                template<class Tp, size_t Np>
                    ndarray(ndarray<Tp, Np> const& other):
                        mem(other.size()),
                        buffer(mem->data),
                        shape(other.shape)
                {
                    std::copy(other.fbegin(), other.fend(), fbegin());
                }

                /* from a seed */
                ndarray(array<long, N> const& shape, none_type init ):
                    mem(std::accumulate(shape.begin(), shape.end(), 1, std::multiplies<long>())),
                    buffer(mem->data),
                    shape(shape)
                {
                }
                ndarray(array<long, N> const& shape, T init ): ndarray(shape, none_type())
                {
                    std::fill(fbegin(), fend(), init);
                }

                /* from a foreign pointer */
                ndarray(T* data, long * pshape):
                    mem(data),
                    buffer(mem->data),
                    shape()
                {
                    std::copy(pshape, pshape + N, shape.begin());
                }

#ifdef ENABLE_PYTHON_MODULE

                ndarray(T* data, long * pshape, PyObject* obj_ptr): ndarray(data, pshape)
                {
                    mem.external(obj_ptr); // mark memory as external to decref at the end of its lifetime
                }

#endif

                template<class Iterable,
                    class = typename std::enable_if<
                        !is_array<typename std::remove_cv<typename std::remove_reference<Iterable>::type>::type>::value
                        and is_iterable<typename std::remove_cv<typename std::remove_reference<Iterable>::type>::type>::value,
                    void>::type
                        >
                        ndarray(Iterable&& iterable):
                            mem(utils::nested_container_size<Iterable>::size(std::forward<Iterable>(iterable))),
                            buffer(mem->data),
                            shape()
                {
                    type_helper<ndarray>::initialize_from_iterable(shape, mem->data, std::forward<Iterable>(iterable));
                }

                /* from a  numpy expression */
                template<class E>
                    void initialize_from_expr(E const & expr) {
                        std::copy(expr.begin(), expr.end(), begin());
                    }

                template<class Op, class Arg0, class Arg1>
                    ndarray(numpy_expr<Op, Arg0, Arg1> const & expr) :
                        mem(expr.size()),
                        buffer(mem->data),
                        shape(expr.shape)
                {
                    initialize_from_expr(expr);
                }

                template<class Arg>
                    ndarray(numpy_texpr<Arg> const & expr) :
                        mem(expr.size()),
                        buffer(mem->data),
                        shape(expr.shape)
                {
                    initialize_from_expr(expr);
                }

                template<class Op, class Arg>
                    ndarray(numpy_uexpr<Op, Arg> const & expr) :
                        mem(expr.size()),
                        buffer(mem->data),
                        shape(expr.shape)
                {
                    initialize_from_expr(expr);
                }

                template<class Arg, class... S>
                    ndarray(numpy_gexpr<Arg, S...> const & expr) :
                        mem(expr.size()),
                        buffer(mem->data),
                        shape(expr.shape)
                {
                    initialize_from_expr(expr);
                }

                template<class Arg>
                    ndarray(numpy_iexpr<Arg> const & expr) :
                        mem(expr.size()),
                        buffer(mem->data),
                        shape(expr.shape)
                {
                    initialize_from_expr(expr);
                }

                template<class Arg, class F>
                    ndarray(numpy_fexpr<Arg, F> const & expr) :
                        mem(expr.size()),
                        buffer(mem->data),
                        shape(expr.shape)
                {
                    initialize_from_expr(expr);
                }

                /* update operators */
                template<class Expr>
                    ndarray& operator+=(Expr const& expr) {
                        return (*this) = (*this) + expr;
                    }
                template<class Expr>
                    ndarray& operator-=(Expr const& expr) {
                        return (*this) = (*this) - expr;
                    }
                template<class Expr>
                    ndarray& operator*=(Expr const& expr) {
                        return (*this) = (*this) * expr;
                    }
                template<class Expr>
                    ndarray& operator/=(Expr const& expr) {
                        return (*this) = (*this) / expr;
                    }
                template<class Expr>
                    ndarray& operator&=(Expr const& expr) {
                        return (*this) = (*this) & expr;
                    }
                template<class Expr>
                    ndarray& operator|=(Expr const& expr) {
                        return (*this) = (*this) | expr;
                    }

                /* element indexing
                 * differentiate const from non const, and r-value from l-value
                 * */
                auto fast(long i) const & -> decltype(type_helper<ndarray const &>::get(*this, i))
                {
                    return type_helper<ndarray const &>::get(*this, i);
                }
                auto fast(long i) && -> decltype(type_helper<ndarray>::get(std::move(*this), i))
                {
                    return type_helper<ndarray>::get(std::move(*this), i);
                }

                auto operator[](long i) const & -> decltype(this->fast(i))
                {
                    if(i<0) i += shape[0];
                    return fast(i);
                }
                auto operator[](long i) && -> decltype(std::move(*this).fast(i))
                {
                    if(i<0) i += shape[0];
                    return std::move(*this).fast(i);
                }
                auto operator()(long i) const & -> decltype((*this)[i])
                {
                    return (*this)[i];
                }
                auto operator()(long i) && -> decltype(std::move(*this)[i])
                {
                    return std::move(*this)[i];
                }

                T const &operator[](array<long, N> const& indices) const
                {
                    size_t offset = indices[N-1];
                    long mult = shape[N-1];
                    for(size_t i = N - 2; i > 0; --i) {
                        offset +=  indices[i] * mult;
                        mult *= shape[i];
                    }
                    return buffer[offset + indices[0] * mult];
                }
                T& operator[](array<long, N> const& indices)
                {
                    return const_cast<T&>(const_cast<ndarray const&>(*this)[indices]);
                }

                template<size_t M>
                    auto operator[](array<long, M> const& indices) const &
                    -> decltype(nget<M-1>()(*this, indices))
                    {
                        return nget<M-1>()(*this, indices);
                    }
                template<size_t M>
                    auto operator[](array<long, M> const& indices) &&
                    -> decltype(nget<M-1>()(std::move(*this), indices))
                    {
                        return nget<M-1>()(std::move(*this), indices);
                    }

                /* slice indexing */
                numpy_gexpr<ndarray const &, slice> operator[](slice const& s) const
                {
                    return numpy_gexpr<ndarray const &, slice>(*this, s);
                }

                numpy_gexpr<ndarray const &, contiguous_slice> operator[](contiguous_slice const& s) const
                {
                    return numpy_gexpr<ndarray const &, contiguous_slice>(*this, s);
                }
                numpy_gexpr<ndarray const &, slice> operator()(slice const& s) const
                {
                    return numpy_gexpr<ndarray const &, slice>(*this, s);
                }

                numpy_gexpr<ndarray const &, contiguous_slice> operator()(contiguous_slice const& s) const
                {
                    return numpy_gexpr<ndarray const &, contiguous_slice>(*this, s);
                }

                /* extended slice indexing */
                template<class ...S>
                    numpy_gexpr<ndarray const &, slice, S...> operator()(slice const& s0, S const&... s) const
                    {
                        return numpy_gexpr<ndarray const &, slice, S...>(*this, s0, s...);
                    }
                template<class ...S>
                    numpy_gexpr<ndarray const &, contiguous_slice, S...> operator()(contiguous_slice const& s0, S const&... s) const
                    {
                        return numpy_gexpr<ndarray const &, contiguous_slice, S...>(*this, s0, s...);
                    }
                template<class ...S>
                    auto operator()(long s0, S const&... s) const -> decltype((*this)[s0](s...))
                    {
                        return (*this)[s0](s...);
                    }
                template<class ...S>
                    auto operator()(long s0, S const&... s) && -> decltype(std::declval<numpy_iexpr<ndarray>>()(s...))
                    {
                        return std::move(*this)[s0](s...);
                    }

                /* element filtering */
                template<class F> // indexing through an array of boolean -- a mask
                    typename std::enable_if<is_numexpr_arg<F>::value and std::is_same<bool, typename F::dtype>::value, numpy_fexpr<ndarray, F>>::type
                    operator[](F const& filter) const {
                        return numpy_fexpr<ndarray, F>(*this, filter);
                    }
                template<class F> // indexing through an array of indices -- a view
                    typename std::enable_if<is_numexpr_arg<F>::value and not std::is_same<bool, typename F::dtype>::value, ndarray<T, 1>>::type
                    operator[](F const& filter) const {
                        ndarray<T,1> out(array<long, 1>{{filter.size()}}, none_type());
                        std::transform(filter.begin(), filter.end(), out.begin(), [this](typename F::dtype index) { return fast(index); });
                        return out;
                    }

                /* through iterators */
                iterator begin() { return type_helper<ndarray>::make_iterator(*this, 0); }
                const_iterator begin() const { return type_helper<ndarray>::make_iterator(*this, 0); }
                iterator end() { return type_helper<ndarray>::make_iterator(*this, shape[0]); }
                const_iterator end() const { return type_helper<ndarray>::make_iterator(*this, shape[0]); }

                const_flat_iterator fbegin() const { return buffer; }
                const_flat_iterator fend() const { return buffer + size(); }
                flat_iterator fbegin() { return buffer; }
                flat_iterator fend() { return buffer + size(); }

                /* member functions */
                long size() const { return std::accumulate(shape.begin(), shape.end(), 1, std::multiplies<long>()); }
                template<size_t M>
                    ndarray<T,M> reshape(array<long,M> const& shape) const {
                        return ndarray<T, M>(mem, shape);
                    }
                ndarray<T,1> flat() const {
                    return ndarray<T, 1>(mem, array<long, 1>{{size()}});
                }
                ndarray<T,N> copy() const {
                    ndarray<T,N> res(shape, __builtin__::None);
                    std::copy(fbegin(), fend(), res.fbegin());
                    return res;
                }
                intptr_t id() const {
                    return reinterpret_cast<intptr_t>(&(*mem));
                }

            };


        template<class T>
            struct is_ndarray {
                static constexpr bool value = false;
            };
        template<class T, size_t N>
            struct is_ndarray<ndarray<T,N>> {
                static constexpr bool value = true;
            };

        /* Type trait that checks if a type is a potential numpy expression parameter
         *
         * Only used to write concise expression templates
         */
        template<class T>
            struct is_array {
                static constexpr bool value = false;
            };
        template<class T, size_t N>
            struct is_array<ndarray<T,N>> {
                static constexpr bool value = true;
            };
        template<class A>
            struct is_array<numpy_iexpr<A>> {
                static constexpr bool value = true;
            };
        template<class A, class F>
            struct is_array<numpy_fexpr<A,F>> {
                static constexpr bool value = true;
            };
        template<class A, class... S>
            struct is_array<numpy_gexpr<A,S...>> {
                static constexpr bool value = true;
            };
        template<class O, class A>
            struct is_array<numpy_uexpr<O,A>> {
                static constexpr bool value = true;
            };
        template<class A>
            struct is_array<numpy_texpr<A>> {
                static constexpr bool value = true;
            };
        template<class O, class A0, class A1>
            struct is_array<numpy_expr<O,A0,A1>> {
                static constexpr bool value = true;
            };

        template<class T>
            struct is_numexpr_arg : is_array<T> {
            };
        template<class T>
            struct is_numexpr_arg<list<T>> {
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
                if( e.size())
                    oss << *std::max_element(e.fbegin(), e.fend());
                int size = oss.str().length();
                auto iter = e.fbegin();
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
        template<class E>
            typename std::enable_if<is_array<E>::value, std::ostream&>::type
            operator<<(std::ostream& os, E const& e) {
                return os << typename numpy_expr_to_ndarray<E>::type(e);
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

        template<class Op, class Arg0, class Arg1>
            struct nested_container_depth<types::numpy_expr<Op, Arg0, Arg1>> {
                static const int  value = types::numpy_expr<Op, Arg0, Arg1>::value;
            };
    }


}

/* std::get overloads */
namespace std {

    template <size_t I, class E>
        auto get( E&& a)
        -> typename std::enable_if<pythonic::types::is_array<typename std::remove_cv<typename std::remove_reference<E>::type>::type>::value, decltype(a[I])>::type
        {
            return a[I];
        }

    template <size_t I, class T, size_t N>
        struct tuple_element<I, pythonic::types::ndarray<T,N> > {
            typedef typename pythonic::types::ndarray<T,N>::value_type type;
        };
    template <size_t I, class Op, class Arg0, class Arg1>
        struct tuple_element<I, pythonic::types::numpy_expr<Op,Arg0, Arg1> > {
            typedef typename pythonic::types::numpy_expr_to_ndarray<pythonic::types::numpy_expr<Op,Arg0, Arg1>>::type::value_type type;
        };
    template <size_t I, class E>
        struct tuple_element<I, pythonic::types::numpy_iexpr<E> > {
            typedef decltype(std::declval<pythonic::types::numpy_iexpr<E>>()[0]) type;
        };

}

/* pythran attribute system { */
#include "pythonic/numpy/transpose.hpp"
namespace pythonic {
    namespace types {
        namespace __ndarray {

            template<int I, class E>
                struct getattr;

            template<class E> struct getattr<attr::SHAPE, E> {
                auto operator()(E const& a) -> decltype(a.shape) { return a.shape; }
            };
            template<class E> struct getattr<attr::NDIM, E> {
                long operator()(E const& a) { return numpy_expr_to_ndarray<E>::N; }
            };
            template<class E> struct getattr<attr::STRIDES, E> {
                array<long, numpy_expr_to_ndarray<E>::N> operator()(E const& a) {
                    array<long,numpy_expr_to_ndarray<E>::N> strides;
                    strides[numpy_expr_to_ndarray<E>::N-1] = sizeof(typename numpy_expr_to_ndarray<E>::T);
                    auto shape = a.shape;
                    std::transform(strides.rbegin(), strides.rend() -1, shape.rbegin(), strides.rbegin()+1, std::multiplies<long>());
                    return strides;
                }
            };
            template<class E> struct getattr<attr::SIZE, E> {
                long operator()(E const& a) { return a.size(); }
            };
            template<class E> struct getattr<attr::ITEMSIZE, E> {
                long operator()(E const& a) { return sizeof(typename numpy_expr_to_ndarray<E>::T); }
            };
            template<class E> struct getattr<attr::NBYTES, E> {
                long operator()(E const& a) { return a.size() * sizeof(typename numpy_expr_to_ndarray<E>::T); }
            };
            template<class E> struct getattr<attr::FLAT, E> {
                auto operator()(E const& a) -> decltype(a.flat()) { return a.flat(); }
            };
            template<class E> struct getattr<attr::DTYPE, E> {
                typename numpy_expr_to_ndarray<E>::T operator()(E const& a) { return typename numpy_expr_to_ndarray<E>::T(); }
            };
            template<class E> struct getattr<attr::T, E> {
                auto operator()(E const& a) -> decltype(numpy::transpose(a)) { return numpy::transpose(a); }
            };
        }
    }
    namespace __builtin__ {
        template<int I, class T, size_t N>
            auto getattr(types::ndarray<T,N> const& f)
            -> decltype(types::__ndarray::getattr<I,types::ndarray<T,N>>()(f))
            {
                return types::__ndarray::getattr<I,types::ndarray<T,N>>()(f);
            }

        template<int I, class O, class A0, class A1>
            auto getattr(types::numpy_expr<O,A0,A1> const& f)
            -> decltype(types::__ndarray::getattr<I,types::numpy_expr<O,A0,A1>>()(f))
            {
                return types::__ndarray::getattr<I,types::numpy_expr<O,A0,A1>>()(f);
            }

        template<int I, class A, class F>
            auto getattr(types::numpy_fexpr<A,F> const& f)
            -> decltype(types::__ndarray::getattr<I,types::numpy_fexpr<A,F>>()(f))
            {
                return types::__ndarray::getattr<I,types::numpy_fexpr<A,F>>()(f);
            }

        template<int I, class A, class... S>
            auto getattr(types::numpy_gexpr<A,S...> const& f)
            -> decltype(types::__ndarray::getattr<I,types::numpy_gexpr<A,S...>>()(f))
            {
                return types::__ndarray::getattr<I,types::numpy_gexpr<A,S...>>()(f);
            }
        template<int I, class A>
            auto getattr(types::numpy_iexpr<A> const& f)
            -> decltype(types::__ndarray::getattr<I,types::numpy_iexpr<A>>()(f))
            {
                return types::__ndarray::getattr<I,types::numpy_iexpr<A>>()(f);
            }

        template<int I, class A>
            auto getattr(types::numpy_texpr<A> const& f)
            -> decltype(types::__ndarray::getattr<I,types::numpy_texpr<A>>()(f))
            {
                return types::__ndarray::getattr<I,types::numpy_texpr<A>>()(f);
            }

        template<int I, class O, class A>
            auto getattr(types::numpy_uexpr<O,A> const& f)
            -> decltype(types::__ndarray::getattr<I,types::numpy_uexpr<O,A>>()(f))
            {
                return types::__ndarray::getattr<I,types::numpy_uexpr<O,A>>()(f);
            }

    }
}

/* } */

/* type inference stuff  {*/
#include "pythonic/types/combined.hpp"

template<class T1, class T2, size_t N, size_t M>
struct __combined<pythonic::types::ndarray<T1,N>, pythonic::types::ndarray<T2,M>> {
    typedef pythonic::types::ndarray<typename __combined<T1, T2>::type, N> type;
};
template<size_t N, class T, class O>
struct __combined<pythonic::types::ndarray<T,N>, O> {
    typedef pythonic::types::ndarray<T,N> type;
};
template<size_t N, class T, class O>
struct __combined<O, pythonic::types::ndarray<T,N>> {
    typedef pythonic::types::ndarray<T,N> type;
};

/* } */

#include "pythonic/types/numpy_operators.hpp"

#ifdef ENABLE_PYTHON_MODULE
#include "pythonic/python/register_once.hpp"

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
        struct c_type_to_numpy_type<unsigned long long> {
            static const int value = NPY_ULONGLONG;
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
                new (storage) types::ndarray< T, N>((T*)PyArray_BYTES(reinterpret_cast<PyArrayObject*>(obj_ptr)), PyArray_DIMS(reinterpret_cast<PyArrayObject*>(obj_ptr)), obj_ptr);
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
                if(n.mem.foreign)
                {
                    n.mem.forget();
                    PyObject* p = n.mem.foreign;
                    PyArrayObject *arr = reinterpret_cast<PyArrayObject*>(p);
                    auto pshape = PyArray_DIMS(arr);
                    Py_INCREF(p);
                    if(std::equal(n.shape.begin(), n.shape.end(), pshape))
                    {
                        return p;
                    }
                    else
                    {
                        Py_INCREF(PyArray_DESCR(arr));
                        return PyArray_NewFromDescr(Py_TYPE(arr),
                                PyArray_DESCR(arr),
                                N, n.shape.data(),
                                NULL,
                                PyArray_DATA(arr),
                                PyArray_FLAGS(arr) & ~NPY_ARRAY_OWNDATA, p);
                    }
                } else {
                    PyObject* result = PyArray_SimpleNewFromData(N, n.shape.data(), c_type_to_numpy_type<T>::value, n.buffer);
                    n.mem.foreign = result;
                    n.mem.forget();
                    if (!result)
                        return nullptr;
                    PyArray_ENABLEFLAGS(reinterpret_cast<PyArrayObject*>(result), NPY_ARRAY_OWNDATA);
                    return result;
                }
            }
        };
    template<class E>
        struct custom_expr_to_ndarray {
            static PyObject* convert( E n) {
                return custom_array_to_ndarray<typename types::numpy_expr_to_ndarray<E>::T,
                                               types::numpy_expr_to_ndarray<E>::N
                                              >::convert(n);
            }
        };

    template<class T, size_t N>
        struct pythran_to_python< types::ndarray<T,N> > {
            pythran_to_python() {
                register_once< types::ndarray<T,N> , custom_array_to_ndarray<T,N> >();
            }
        };

    template<class Arg>
        struct pythran_to_python< types::numpy_iexpr<Arg> > {
            pythran_to_python() {
                register_once< types::numpy_iexpr<Arg>, custom_expr_to_ndarray<types::numpy_iexpr<Arg>> >();
            }
        };
    template<class Arg, class...S>
        struct pythran_to_python< types::numpy_gexpr<Arg, S...> > {
            pythran_to_python() {
                register_once< types::numpy_gexpr<Arg, S...>, custom_expr_to_ndarray<types::numpy_gexpr<Arg, S...>> >();
            }
        };
}

#endif


#endif

