#ifndef PYTHONIC_TYPES_NDARRAY_HPP
#define PYTHONIC_TYPES_NDARRAY_HPP

#include "pythonic/include/types/ndarray.hpp"

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

#include "pythonic/numpy/uint8.hpp"
#include "pythonic/numpy/int8.hpp"
#include "pythonic/numpy/uint16.hpp"
#include "pythonic/numpy/int16.hpp"
#include "pythonic/numpy/uint32.hpp"
#include "pythonic/numpy/int32.hpp"
#include "pythonic/numpy/uint64.hpp"
#include "pythonic/numpy/int64.hpp"
#include "pythonic/numpy/float32.hpp"
#include "pythonic/numpy/float64.hpp"
#include "pythonic/numpy/complex64.hpp"
#include "pythonic/numpy/complex128.hpp"

#include "pythonic/types/vectorizable_type.hpp"
#include "pythonic/types/numpy_op_helper.hpp"
#include "pythonic/types/numpy_fexpr.hpp"
#include "pythonic/types/numpy_expr.hpp"
#include "pythonic/types/numpy_texpr.hpp"
#include "pythonic/types/numpy_iexpr.hpp"
#include "pythonic/types/numpy_gexpr.hpp"
#include "pythonic/utils/numpy_traits.hpp"

#include "pythonic/__builtin__/len.hpp"
#include "pythonic/operator_/iadd.hpp"
#include "pythonic/operator_/iand.hpp"
#include "pythonic/operator_/idiv.hpp"
#include "pythonic/operator_/imul.hpp"
#include "pythonic/operator_/ior.hpp"
#include "pythonic/operator_/isub.hpp"

#include <cassert>
#include <iostream>
#include <iterator>
#include <array>
#include <initializer_list>
#include <numeric>

#ifdef ENABLE_PYTHON_MODULE
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include "numpy/arrayobject.h"
#endif

#include <boost/simd/sdk/simd/logical.hpp>

#ifdef USE_BOOST_SIMD
#include <boost/simd/sdk/simd/native.hpp>
#include <boost/simd/include/functions/load.hpp>
#include <boost/simd/include/functions/store.hpp>
#endif

namespace pythonic
{

  namespace types
  {

    template <class T, size_t N>
    typename type_helper<ndarray<T, N>>::iterator
    type_helper<ndarray<T, N>>::make_iterator(ndarray<T, N> &n, long i)
    {
      return {n, i};
    }

    template <class T, size_t N>
    typename type_helper<ndarray<T, N>>::const_iterator
    type_helper<ndarray<T, N>>::make_iterator(ndarray<T, N> const &n, long i)
    {
      return {n, i};
    }

    template <class T, size_t N>
    template <class S, class Iter>
    T *type_helper<ndarray<T, N>>::initialize_from_iterable(S &shape, T *from,
                                                            Iter &&iter)
    {
      return type_helper<ndarray<T, N> const &>::initialize_from_iterable(
          shape, from, std::forward<Iter>(iter));
    }

    template <class T, size_t N>
    numpy_iexpr<ndarray<T, N>>
    type_helper<ndarray<T, N>>::get(ndarray<T, N> &&self, long i)
    {
      return {std::move(self), i};
    }

    template <class T, size_t N>
    long type_helper<ndarray<T, N>>::step(ndarray<T, N> const &self)
    {
      return std::accumulate(self.shape.begin() + 1, self.shape.end(), 1L,
                             std::multiplies<long>());
    }

    template <class T, size_t N>
    typename type_helper<ndarray<T, N> const &>::iterator
    type_helper<ndarray<T, N> const &>::make_iterator(ndarray<T, N> &n, long i)
    {
      return {n, i};
    }

    template <class T, size_t N>
    typename type_helper<ndarray<T, N> const &>::const_iterator
    type_helper<ndarray<T, N> const &>::make_iterator(ndarray<T, N> const &n,
                                                      long i)
    {
      return {n, i};
    }

    template <class T, size_t N>
    template <class S, class Iter>
    T *type_helper<ndarray<T, N> const &>::initialize_from_iterable(S &shape,
                                                                    T *from,
                                                                    Iter &&iter)
    {
      shape[std::tuple_size<S>::value - N] = iter.size();
      for (auto content : iter)
        from = type_helper<ndarray<T, N - 1> const &>::initialize_from_iterable(
            shape, from, content);
      return from;
    }

    template <class T, size_t N>
    numpy_iexpr<ndarray<T, N> const &>
    type_helper<ndarray<T, N> const &>::get(ndarray<T, N> const &self, long i)
    {
      return numpy_iexpr<ndarray<T, N> const &>(self, i);
    }

    template <class T, size_t N>
    long type_helper<ndarray<T, N> const &>::step(ndarray<T, N> const &self)
    {
      return std::accumulate(self.shape.begin() + 1, self.shape.end(), 1L,
                             std::multiplies<long>());
    }

    template <class T>
    typename type_helper<ndarray<T, 1>>::iterator
        type_helper<ndarray<T, 1>>::make_iterator(ndarray<T, 1> &n, long i)
    {
      return n.buffer + i;
    }

    template <class T>
    typename type_helper<ndarray<T, 1>>::const_iterator
        type_helper<ndarray<T, 1>>::make_iterator(ndarray<T, 1> const &n,
                                                  long i)
    {
      return n.buffer + i;
    }

    template <class T>
    template <class S, class Iter>
    T *type_helper<ndarray<T, 1>>::initialize_from_iterable(S &shape, T *from,
                                                            Iter &&iter)
    {
      shape[std::tuple_size<S>::value - 1] = iter.size();
      return std::copy(iter.begin(), iter.end(), from);
    }

    template <class T>
    typename type_helper<ndarray<T, 1>>::type
        type_helper<ndarray<T, 1>>::get(ndarray<T, 1> &&self, long i)
    {
      return self.buffer[i];
    }

    template <class T>
    constexpr long type_helper<ndarray<T, 1>>::step(ndarray<T, 1> const &)
    {
      return 1;
    }

    template <class T>
    typename type_helper<ndarray<T, 1> const &>::iterator
        type_helper<ndarray<T, 1> const &>::make_iterator(ndarray<T, 1> &n,
                                                          long i)
    {
      return n.buffer + i;
    }

    template <class T>
    typename type_helper<ndarray<T, 1> const &>::const_iterator
        make_iterator(ndarray<T, 1> const &n, long i)
    {
      return n.buffer + i;
    }

    template <class T>
    template <class S, class Iter>
    T *type_helper<ndarray<T, 1> const &>::initialize_from_iterable(S &shape,
                                                                    T *from,
                                                                    Iter &&iter)
    {
      shape[std::tuple_size<S>::value - 1] = iter.size();
      return std::copy(iter.begin(), iter.end(), from);
    }

    template <class T>
    typename type_helper<ndarray<T, 1> const &>::type &
        type_helper<ndarray<T, 1> const &>::get(ndarray<T, 1> const &self,
                                                long i)
    {
      return self.buffer[i];
    }

    template <class T>
    constexpr long
        type_helper<ndarray<T, 1> const &>::step(ndarray<T, 1> const &)
    {
      return 1;
    }

    /* recursively return the value at the position given by `indices' in the
     * `self' "array like". It may be a sub array instead of real value.
     * indices[0] is the coordinate for the first dimension and indices[M-1] is
     * for the last one.
     */
    template <size_t L>
    template <class A, size_t M>
    auto nget<L>::operator()(A &&self, array<long, M> const &indices)
        -> decltype(nget<L - 1>()(std::forward<A>(self)[0], indices))
    {
      return nget<L - 1>()(std::forward<A>(self)[indices[M - L - 1]], indices);
    }

    template <class A, size_t M>
    auto nget<0>::operator()(A &&self, array<long, M> const &indices)
        -> decltype(std::forward<A>(self)[indices[M - 1]])
    {
      return std::forward<A>(self)[indices[M - 1]];
    }

    template <size_t L>
    template <size_t M>
    long noffset<L>::operator()(array<long, M> const &shape,
                                array<long, M> const &indices) const
    {
      return noffset<L - 1>{}(shape, indices) * shape[L] + indices[L];
    }

    template <size_t M>
    long noffset<0>::operator()(array<long, M> const &,
                                array<long, M> const &indices) const
    {
      return indices[0];
    }

    /* constructors */
    template <class T, size_t N>
    ndarray<T, N>::ndarray()
        : mem(utils::no_memory()), buffer(nullptr), _shape()
    {
    }

    /* from other memory */
    template <class T, size_t N>
    ndarray<T, N>::ndarray(utils::shared_ref<raw_array<T>> const &mem,
                           array<long, N> const &shape)
        : mem(mem), buffer(mem->data), _shape(shape)
    {
    }

    /* from other array */
    template <class T, size_t N>
    template <class Tp, size_t Np>
    ndarray<T, N>::ndarray(ndarray<Tp, Np> const &other)
        : mem(other.flat_size()), buffer(mem->data), _shape(other._shape)
    {
      std::copy(other.fbegin(), other.fend(), fbegin());
    }

    /* from a seed */
    template <class T, size_t N>
    ndarray<T, N>::ndarray(array<long, N> const &shape, none_type init)
        : mem(std::accumulate(shape.begin(), shape.end(), 1,
                              std::multiplies<long>())),
          buffer(mem->data), _shape(shape)
    {
    }

    template <class T, size_t N>
    ndarray<T, N>::ndarray(array<long, N> const &shape, T init)
        : ndarray(shape, none_type())
    {
      std::fill(fbegin(), fend(), init);
    }

    /* from a foreign pointer */
    template <class T, size_t N>
    template <class S>
    ndarray<T, N>::ndarray(T *data, S const *pshape)
        : mem(data), buffer(mem->data), _shape()
    {
      std::copy(pshape, pshape + N, _shape.begin());
    }

#ifdef ENABLE_PYTHON_MODULE
    template <class T, size_t N>
    template <class S>
    ndarray<T, N>::ndarray(T *data, S const *pshape, PyObject *obj_ptr)
        : ndarray(data, pshape)
    {
      mem.external(obj_ptr); // mark memory as external to decref at the end of
                             // its lifetime
    }

#endif

    template <class T, size_t N>
    template <class Iterable, class>
    ndarray<T, N>::ndarray(Iterable &&iterable)
        : mem(utils::nested_container_size<Iterable>::flat_size(
              std::forward<Iterable>(iterable))),
          buffer(mem->data), _shape()
    {
      type_helper<ndarray>::initialize_from_iterable(
          _shape, mem->data, std::forward<Iterable>(iterable));
    }

    /* from a  numpy expression */
    template <class T, size_t N>
    template <class E>
    void ndarray<T, N>::initialize_from_expr(E const &expr)
    {
      utils::broadcast_copy<ndarray &, E, value, 0,
                            is_vectorizable and E::is_vectorizable>(*this,
                                                                    expr);
    }

    template <class T, size_t N>
    template <class Op, class... Args>
    ndarray<T, N>::ndarray(numpy_expr<Op, Args...> const &expr)
        : mem(expr.flat_size()), buffer(mem->data), _shape(expr.shape())
    {
      initialize_from_expr(expr);
    }

    template <class T, size_t N>
    template <class Arg>
    ndarray<T, N>::ndarray(numpy_texpr<Arg> const &expr)
        : mem(expr.flat_size()), buffer(mem->data), _shape(expr.shape())
    {
      initialize_from_expr(expr);
    }

    template <class T, size_t N>
    template <class Arg>
    ndarray<T, N>::ndarray(numpy_texpr_2<Arg> const &expr)
        : mem(expr.flat_size()), buffer(mem->data), _shape(expr.shape())
    {
      initialize_from_expr(expr);
    }

    template <class T, size_t N>
    template <class Arg, class... S>
    ndarray<T, N>::ndarray(numpy_gexpr<Arg, S...> const &expr)
        : mem(expr.flat_size()), buffer(mem->data), _shape(expr.shape())
    {
      initialize_from_expr(expr);
    }

    template <class T, size_t N>
    template <class Arg>
    ndarray<T, N>::ndarray(numpy_iexpr<Arg> const &expr)
        : mem(expr.flat_size()), buffer(mem->data), _shape(expr.shape())
    {
      initialize_from_expr(expr);
    }

    template <class T, size_t N>
    template <class Arg, class F>
    ndarray<T, N>::ndarray(numpy_fexpr<Arg, F> const &expr)
        : mem(expr.flat_size()), buffer(mem->data), _shape(expr.shape())
    {
      initialize_from_expr(expr);
    }

    /* update operators */

    template <class T, size_t N>
    template <class Op, class Expr>
    ndarray<T, N> &ndarray<T, N>::update_(Expr const &expr)
    {
      using BExpr =
          typename std::conditional<std::is_scalar<Expr>::value,
                                    broadcast<Expr, T>, Expr const &>::type;
      BExpr bexpr = expr;
      utils::broadcast_update<
          Op, ndarray &, BExpr, value,
          value - (std::is_scalar<Expr>::value + utils::dim_of<Expr>::value),
          is_vectorizable and
              std::remove_reference<BExpr>::type::is_vectorizable and
              std::is_same<dtype,
                           typename std::decay<BExpr>::type::dtype>::value>(
          *this, bexpr);
      return *this;
    }

    template <class T, size_t N>
    template <class Expr>
    ndarray<T, N> &ndarray<T, N>::operator+=(Expr const &expr)
    {
      return update_<pythonic::operator_::functor::iadd>(expr);
    }

    template <class T, size_t N>
    template <class Expr>
    ndarray<T, N> &ndarray<T, N>::operator-=(Expr const &expr)
    {
      return update_<pythonic::operator_::functor::isub>(expr);
    }

    template <class T, size_t N>
    template <class Expr>
    ndarray<T, N> &ndarray<T, N>::operator*=(Expr const &expr)
    {
      return update_<pythonic::operator_::functor::imul>(expr);
    }

    template <class T, size_t N>
    template <class Expr>
    ndarray<T, N> &ndarray<T, N>::operator/=(Expr const &expr)
    {
      return update_<pythonic::operator_::functor::idiv>(expr);
    }

    template <class T, size_t N>
    template <class Expr>
    ndarray<T, N> &ndarray<T, N>::operator&=(Expr const &expr)
    {
      return update_<pythonic::operator_::functor::iand>(expr);
    }

    template <class T, size_t N>
    template <class Expr>
    ndarray<T, N> &ndarray<T, N>::operator|=(Expr const &expr)
    {
      return update_<pythonic::operator_::functor::ior>(expr);
    }

    /* element indexing
     * differentiate const from non const, and r-value from l-value
     * */
    template <class T, size_t N>
    auto ndarray<T, N>::fast(long i) const
        & -> decltype(type_helper<ndarray const &>::get(*this, i))
    {
      return type_helper<ndarray const &>::get(*this, i);
    }

    template <class T, size_t N>
        auto ndarray<T, N>::fast(long i) &&
        -> decltype(type_helper<ndarray>::get(std::move(*this), i))
    {
      return type_helper<ndarray>::get(std::move(*this), i);
    }

    template <class T, size_t N>
    auto ndarray<T, N>::operator[](long i) const & -> decltype(this->fast(i))
    {
      if (i < 0)
        i += _shape[0];
      return fast(i);
    }

    template <class T, size_t N>
        auto ndarray<T, N>::operator[](long i) &&
        -> decltype(std::move(*this).fast(i))
    {
      if (i < 0)
        i += _shape[0];
      return std::move(*this).fast(i);
    }

    template <class T, size_t N>
    auto ndarray<T, N>::operator()(long i) const & -> decltype((*this)[i])
    {
      return (*this)[i];
    }

    template <class T, size_t N>
        auto ndarray<T, N>::operator()(long i) &&
        -> decltype(std::move (*this)[i])
    {
      return std::move(*this)[i];
    }

    template <class T, size_t N>
    T const &ndarray<T, N>::operator[](array<long, N> const &indices) const
    {
      return *(buffer + noffset<N - 1>{}(_shape, indices));
    }

    template <class T, size_t N>
    T &ndarray<T, N>::operator[](array<long, N> const &indices)
    {
      return *(buffer + noffset<N - 1>{}(_shape, indices));
    }

    template <class T, size_t N>
    template <size_t M>
    auto ndarray<T, N>::operator[](array<long, M> const &indices) const
        & -> decltype(nget<M - 1>()(*this, indices))
    {
      return nget<M - 1>()(*this, indices);
    }

    template <class T, size_t N>
        template <size_t M>
        auto ndarray<T, N>::operator[](array<long, M> const &indices) &&
        -> decltype(nget<M - 1>()(std::move(*this), indices))
    {
      return nget<M - 1>()(std::move(*this), indices);
    }

#ifdef USE_BOOST_SIMD
    template <class T, size_t N>
    typename ndarray<T, N>::simd_iterator ndarray<T, N>::vbegin() const
    {
      return {*this, 0};
    }

    template <class T, size_t N>
    typename ndarray<T, N>::simd_iterator ndarray<T, N>::vend() const
    {
      using vector_type =
          typename boost::simd::native<dtype, BOOST_SIMD_DEFAULT_EXTENSION>;
      static const std::size_t vector_size =
          boost::simd::meta::cardinal_of<vector_type>::value;
      return {*this, long(_shape[0] / vector_size * vector_size)};
    }
    template <class T, size_t N>
    auto ndarray<T, N>::load(long i) const -> decltype(
        boost::simd::load<boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION>>(
            buffer, i))
    {
      return boost::simd::load<
          boost::simd::native<T, BOOST_SIMD_DEFAULT_EXTENSION>>(buffer, i);
    }

    template <class T, size_t N>
    template <class V>
    void ndarray<T, N>::store(V &&v, long i)
    {
      boost::simd::store(v, buffer, i);
    }
#endif

    /* slice indexing */
    template <class T, size_t N>
    ndarray<T, N + 1> ndarray<T, N>::operator[](none_type) const
    {
      array<long, N + 1> new_shape;
      new_shape[0] = 1;
      std::copy(_shape.begin(), _shape.end(), new_shape.begin() + 1);
      return reshape(new_shape);
    }

    template <class T, size_t N>
    auto ndarray<T, N>::operator()(none_type const &n) const
        -> decltype((*this)[n])
    {
      return (*this)[n];
    }

    template <class T, size_t N>
    numpy_gexpr<ndarray<T, N> const &, slice> ndarray<T, N>::
    operator[](slice const &s) const
    {
      return make_gexpr(*this, s);
    }

    template <class T, size_t N>
    numpy_gexpr<ndarray<T, N> const &, contiguous_slice> ndarray<T, N>::
    operator[](contiguous_slice const &s) const
    {
      return make_gexpr(*this, s);
    }

    template <class T, size_t N>
    numpy_gexpr<ndarray<T, N> const &, slice> ndarray<T, N>::
    operator()(slice const &s) const
    {
      return make_gexpr(*this, s);
    }

    template <class T, size_t N>
    numpy_gexpr<ndarray<T, N> const &, contiguous_slice> ndarray<T, N>::
    operator()(contiguous_slice const &s) const
    {
      return make_gexpr(*this, s);
    }

    template <class T, size_t N>
    long ndarray<T, N>::size() const
    {
      return _shape[0];
    }

    /* extended slice indexing */
    template <class T, size_t N>
    template <class S0, class... S>
    auto ndarray<T, N>::operator()(S0 const &s0, S const &... s) const
        -> decltype(extended_slice<count_new_axis<S0, S...>::value>{}((*this),
                                                                      s0, s...))
    {
      return extended_slice<count_new_axis<S0, S...>::value>{}((*this), s0,
                                                               s...);
    }

    template <class T, size_t N>
        template <class S0, class... S>
        auto ndarray<T, N>::operator()(S0 const &s0, S const &... s) &&
        -> decltype(extended_slice<count_new_axis<S0, S...>::value>{}(
            std::move(*this), s0, s...))
    {
      return extended_slice<count_new_axis<S0, S...>::value>{}(std::move(*this),
                                                               s0, s...);
    }

    /* element filtering */
    template <class T, size_t N>
    template <class F> // indexing through an array of boolean -- a mask
    typename std::enable_if<is_numexpr_arg<F>::value and
                                std::is_same<bool, typename F::dtype>::value,
                            numpy_fexpr<ndarray<T, N>, F>>::type
    ndarray<T, N>::fast(F const &filter) const
    {
      return numpy_fexpr<ndarray, F>(*this, filter);
    }

    template <class T, size_t N>
    template <class F> // indexing through an array of boolean -- a mask
    typename std::enable_if<is_numexpr_arg<F>::value and
                                std::is_same<bool, typename F::dtype>::value,
                            numpy_fexpr<ndarray<T, N>, F>>::type ndarray<T, N>::
    operator[](F const &filter) const
    {
      return fast(filter);
    }

    template <class T, size_t N>
    template <class F> // indexing through an array of indices -- a view
    typename std::enable_if<
        is_numexpr_arg<F>::value and
            not std::is_same<bool, typename F::dtype>::value,
        ndarray<T, N>>::type ndarray<T, N>::
    operator[](F const &filter) const
    {
      array<long, N> shape = this->shape();
      shape[0] = filter.flat_size();
      ndarray<T, N> out(shape, none_type());
      std::transform(
          filter.begin(), filter.end(), out.begin(),
          [this](typename F::dtype index) { return operator[](index); });
      return out;
    }

    template <class T, size_t N>
    template <class F> // indexing through an array of indices -- a view
    typename std::enable_if<
        is_numexpr_arg<F>::value and
            not std::is_same<bool, typename F::dtype>::value,
        ndarray<T, N>>::type
    ndarray<T, N>::fast(F const &filter) const
    {
      array<long, N> shape = this->shape();
      shape[0] = filter.flat_size();
      ndarray<T, N> out(shape, none_type());
      std::transform(filter.begin(), filter.end(), out.begin(),
                     [this](typename F::dtype index) { return fast(index); });
      return out;
    }

    /* through iterators */
    template <class T, size_t N>
    typename ndarray<T, N>::iterator ndarray<T, N>::begin()
    {
      return type_helper<ndarray>::make_iterator(*this, 0);
    }

    template <class T, size_t N>
    typename ndarray<T, N>::const_iterator ndarray<T, N>::begin() const
    {
      return type_helper<ndarray>::make_iterator(*this, 0);
    }

    template <class T, size_t N>
    typename ndarray<T, N>::iterator ndarray<T, N>::end()
    {
      return type_helper<ndarray>::make_iterator(*this, _shape[0]);
    }

    template <class T, size_t N>
    typename ndarray<T, N>::const_iterator ndarray<T, N>::end() const
    {
      return type_helper<ndarray>::make_iterator(*this, _shape[0]);
    }

    template <class T, size_t N>
    typename ndarray<T, N>::const_flat_iterator ndarray<T, N>::fbegin() const
    {
      return buffer;
    }

    template <class T, size_t N>
    typename ndarray<T, N>::const_flat_iterator ndarray<T, N>::fend() const
    {
      return buffer + flat_size();
    }

    template <class T, size_t N>
    typename ndarray<T, N>::flat_iterator ndarray<T, N>::fbegin()
    {
      return buffer;
    }

    template <class T, size_t N>
    typename ndarray<T, N>::flat_iterator ndarray<T, N>::fend()
    {
      return buffer + flat_size();
    }

    /* member functions */
    template <class T, size_t N>
    long ndarray<T, N>::flat_size() const
    {
      return std::accumulate(_shape.begin(), _shape.end(), 1,
                             std::multiplies<long>());
    }
    template <class T, size_t N>
    bool ndarray<T, N>::may_overlap(ndarray const &expr) const
    {
      return id() == expr.id();
    }

    template <class T, size_t N>
    template <size_t M>
    ndarray<T, M> ndarray<T, N>::reshape(array<long, M> const &shape) const
    {
      return ndarray<T, M>(mem, shape);
    }

    template <class T, size_t N>
    ndarray<T, 1> ndarray<T, N>::flat() const
    {
      return ndarray<T, 1>(mem, array<long, 1>{{flat_size()}});
    }

    template <class T, size_t N>
    ndarray<T, N> ndarray<T, N>::copy() const
    {
      ndarray<T, N> res(_shape, __builtin__::None);
      std::copy(fbegin(), fend(), res.fbegin());
      return res;
    }

    template <class T, size_t N>
    intptr_t ndarray<T, N>::id() const
    {
      return reinterpret_cast<intptr_t>(&(*mem));
    }

    template <class T, size_t N>
    array<long, N> const &ndarray<T, N>::shape() const
    {
      return _shape;
    }

    /* pretty printing { */
    namespace impl
    {
      template <class T, size_t N>
      int get_spacing(ndarray<T, N> const &e)
      {
        std::ostringstream oss;
        if (e.flat_size())
          oss << *std::max_element(e.fbegin(), e.fend());
        return oss.str().length();
      }
      template <class T, size_t N>
      int get_spacing(ndarray<std::complex<T>, N> const &e)
      {
        std::ostringstream oss;
        if (e.flat_size())
          oss << *e.fbegin();
        return oss.str().length() + 2;
      }
    }

    template <class T, size_t N>
    std::ostream &operator<<(std::ostream &os, ndarray<T, N> const &e)
    {
      std::array<long, N> strides;
      auto shape = e.shape();
      strides[N - 1] = shape[N - 1];
      if (strides[N - 1] == 0)
        return os << "[]";
      std::transform(strides.rbegin(), strides.rend() - 1, shape.rbegin() + 1,
                     strides.rbegin() + 1, std::multiplies<long>());
      size_t depth = N;
      int step = -1;
      int size = impl::get_spacing(e);
      auto iter = e.fbegin();
      int max_modulo = 1000;

      os << "[";
      if (shape[0] != 0)
        do {
          if (depth == 1) {
            os.width(size);
            os << *iter++;
            for (int i = 1; i < shape[N - 1]; i++) {
              os.width(size + 1);
              os << *iter++;
            }
            step = 1;
            depth++;
            max_modulo =
                std::lower_bound(
                    strides.begin(), strides.end(), iter - e.buffer,
                    [](int comp, int val) { return val % comp != 0; }) -
                strides.begin();
          } else if (max_modulo + depth == N + 1) {
            depth--;
            step = -1;
            os << "]";
            for (size_t i = 0; i < depth; i++)
              os << std::endl;
            for (size_t i = 0; i < N - depth; i++)
              os << " ";
            os << "[";
          } else {
            depth += step;
            if (step == 1)
              os << "]";
            else
              os << "[";
          }
        } while (depth != N + 1);

      return os << "]";
    }

    template <class E>
    typename std::enable_if<is_array<E>::value, std::ostream &>::type
    operator<<(std::ostream &os, E const &e)
    {
      return os << ndarray<typename E::dtype, E::value>{e};
    }

    /* } */
    template <class T>
    list<T> &list<T>::operator=(ndarray<T, 1> const &other)
    {
      data = utils::shared_ref<T>(other.begin(), other.end());
      return *this;
    }
  }
}

/* std::get overloads */
namespace std
{

  template <size_t I, class E>
  auto get(E &&a) -> typename std::enable_if<
      pythonic::types::is_array<typename std::remove_cv<
          typename std::remove_reference<E>::type>::type>::value,
      decltype(std::forward<E>(a)[I])>::type
  {
    return std::forward<E>(a)[I];
  }
}

/* pythran attribute system { */
#include "pythonic/numpy/transpose.hpp"
namespace pythonic
{
  namespace types
  {
    namespace __ndarray
    {

      template <class E>
      auto getattr<attr::SHAPE, E>::operator()(E const &a)
          -> decltype(a.shape())
      {
        return a.shape();
      }

      template <class E>
      long getattr<attr::NDIM, E>::operator()(E const &a)
      {
        return E::value;
      }

      template <class E>
      array<long, E::value> getattr<attr::STRIDES, E>::operator()(E const &a)
      {
        array<long, E::value> strides;
        strides[E::value - 1] = sizeof(typename E::dtype);
        auto shape = a.shape();
        std::transform(strides.rbegin(), strides.rend() - 1, shape.rbegin(),
                       strides.rbegin() + 1, std::multiplies<long>());
        return strides;
      }

      template <class E>
      long getattr<attr::SIZE, E>::operator()(E const &a)
      {
        return a.flat_size();
      }

      template <class E>
      long getattr<attr::ITEMSIZE, E>::operator()(E const &a)
      {
        return sizeof(typename E::dtype);
      }

      template <class E>
      long getattr<attr::NBYTES, E>::operator()(E const &a)
      {
        return a.flat_size() * sizeof(typename E::dtype);
      }

      template <class E>
      auto getattr<attr::FLAT, E>::operator()(E const &a) -> decltype(a.flat())
      {
        return a.flat();
      }

      template <class E>
      dtype_t<typename E::dtype> getattr<attr::DTYPE, E>::operator()(E const &a)
      {
        return {};
      }

      template <class E>
      auto getattr<attr::T, E>::operator()(E const &a)
          -> decltype(numpy::transpose(a))
      {
        return numpy::transpose(a);
      }

      namespace
      {
        template <size_t N>
        template <class E, class... S>
        auto _build_gexpr<N>::operator()(E const &a, S &&... slices)
            -> decltype(_build_gexpr<N - 1>{}(a, contiguous_slice(),
                                              std::forward<S>(slices)...))
        {
          return _build_gexpr<N - 1>{}(
              a, contiguous_slice(__builtin__::None, __builtin__::None),
              std::forward<S>(slices)...);
        }

        template <class E, class... S>
        numpy_gexpr<E, S...> _build_gexpr<1>::operator()(E const &a,
                                                         S &&... slices)
        {
          return a(std::forward<S>(slices)...);
        }
      }

      template <class E>
      E getattr<attr::REAL, E>::make_real(E const &a, utils::int_<0>)
      {
        return a;
      }

      template <class E>
      auto getattr<attr::REAL, E>::make_real(E const &a, utils::int_<1>)
          -> decltype(_build_gexpr<E::value>{}(
              ndarray<typename types::is_complex<typename E::dtype>::type,
                      E::value>{},
              slice{0, 0, 2}))
      {
        using stype = typename types::is_complex<typename E::dtype>::type;
        auto new_shape = a.shape();
        new_shape[E::value - 1] *= 2;
        // this is tricky and dangerous!
        auto translated_mem =
            reinterpret_cast<utils::shared_ref<raw_array<stype>> const &>(
                a.mem);
        ndarray<stype, E::value> translated{translated_mem, new_shape};
        return _build_gexpr<E::value>{}(translated,
                                        slice{0, new_shape[E::value - 1], 2});
      }

      template <class E>
      auto getattr<attr::REAL, E>::operator()(E const &a)
          -> decltype(this->make_real(
              a, utils::int_<types::is_complex<typename E::dtype>::value>{}))
      {
        return make_real(
            a, utils::int_<types::is_complex<typename E::dtype>::value>{});
      }

      template <class E>
      auto getattr<attr::REAL, types::numpy_texpr<E>>::
      operator()(types::numpy_texpr<E> const &a) -> decltype(
          types::numpy_texpr<decltype(getattr<attr::REAL, E>{}(a.arg))>{
              getattr<attr::REAL, E>{}(a.arg)})
      {
        auto ta = getattr<attr::REAL, E>{}(a.arg);
        return types::numpy_texpr<decltype(ta)>{ta};
      }

      template <class E>
      types::ndarray<typename E::dtype, E::value>
      getattr<attr::IMAG, E>::make_imag(E const &a, utils::int_<0>)
      {
        // cannot use numpy.zero: forward declaration issue
        return E((typename E::dtype *)calloc(a.flat_size(),
                                             sizeof(typename E::dtype)),
                 a.shape().data());
      }

      template <class E>
      auto getattr<attr::IMAG, E>::make_imag(E const &a, utils::int_<1>)
          -> decltype(_build_gexpr<E::value>{}(
              ndarray<typename types::is_complex<typename E::dtype>::type,
                      E::value>{},
              slice{0, 0, 2}))
      {
        using stype = typename types::is_complex<typename E::dtype>::type;
        auto new_shape = a.shape();
        new_shape[E::value - 1] *= 2;
        // this is tricky and dangerous!
        auto translated_mem =
            reinterpret_cast<utils::shared_ref<raw_array<stype>> const &>(
                a.mem);
        ndarray<stype, E::value> translated{translated_mem, new_shape};
        return _build_gexpr<E::value>{}(translated,
                                        slice{1, new_shape[E::value - 1], 2});
      }

      template <class E>
      auto getattr<attr::IMAG, E>::operator()(E const &a)
          -> decltype(this->make_imag(
              a, utils::int_<types::is_complex<typename E::dtype>::value>{}))
      {
        return make_imag(
            a, utils::int_<types::is_complex<typename E::dtype>::value>{});
      }

      template <class E>
      auto getattr<attr::IMAG, types::numpy_texpr<E>>::
      operator()(types::numpy_texpr<E> const &a) -> decltype(
          types::numpy_texpr<decltype(getattr<attr::IMAG, E>{}(a.arg))>{
              getattr<attr::IMAG, E>{}(a.arg)})
      {
        auto ta = getattr<attr::IMAG, E>{}(a.arg);
        return types::numpy_texpr<decltype(ta)>{ta};
      }
    }
  }
  namespace __builtin__
  {
    template <int I, class T, size_t N>
    auto getattr(types::ndarray<T, N> const &f)
        -> decltype(types::__ndarray::getattr<I, types::ndarray<T, N>>()(f))
    {
      return types::__ndarray::getattr<I, types::ndarray<T, N>>()(f);
    }

    template <int I, class O, class... Args>
    auto getattr(types::numpy_expr<O, Args...> const &f) -> decltype(
        types::__ndarray::getattr<I, types::numpy_expr<O, Args...>>()(f))
    {
      return types::__ndarray::getattr<I, types::numpy_expr<O, Args...>>()(f);
    }

    template <int I, class A, class F>
    auto getattr(types::numpy_fexpr<A, F> const &f)
        -> decltype(types::__ndarray::getattr<I, types::numpy_fexpr<A, F>>()(f))
    {
      return types::__ndarray::getattr<I, types::numpy_fexpr<A, F>>()(f);
    }

    template <int I, class A, class... S>
    auto getattr(types::numpy_gexpr<A, S...> const &f) -> decltype(
        types::__ndarray::getattr<I, types::numpy_gexpr<A, S...>>()(f))
    {
      return types::__ndarray::getattr<I, types::numpy_gexpr<A, S...>>()(f);
    }

    template <int I, class A>
    auto getattr(types::numpy_iexpr<A> const &f)
        -> decltype(types::__ndarray::getattr<I, types::numpy_iexpr<A>>()(f))
    {
      return types::__ndarray::getattr<I, types::numpy_iexpr<A>>()(f);
    }

    template <int I, class A>
    auto getattr(types::numpy_texpr<A> const &f)
        -> decltype(types::__ndarray::getattr<I, types::numpy_texpr<A>>()(f))
    {
      return types::__ndarray::getattr<I, types::numpy_texpr<A>>()(f);
    }
  }
}

/* } */

#include "pythonic/types/numpy_operators.hpp"

#ifdef ENABLE_PYTHON_MODULE

namespace pythonic
{

  namespace details
  {
    constexpr int signed_int_types[] = {0, NPY_INT8, NPY_INT16, 0, NPY_INT32, 0,
                                        0, 0,        NPY_INT64};
    constexpr int unsigned_int_types[] = {
        0, NPY_UINT8, NPY_UINT16, 0, NPY_UINT32, 0, 0, 0, NPY_UINT64};
  }

  template <class T>
  struct c_type_to_numpy_type
      : c_type_to_numpy_type<decltype(std::declval<T>()())> {
  };

  template <>
  struct c_type_to_numpy_type<double>
      : std::integral_constant<int, NPY_DOUBLE> {
  };

  template <>
  struct c_type_to_numpy_type<float> : std::integral_constant<int, NPY_FLOAT> {
  };

  template <>
  struct c_type_to_numpy_type<std::complex<float>>
      : std::integral_constant<int, NPY_CFLOAT> {
  };

  template <>
  struct c_type_to_numpy_type<std::complex<double>>
      : std::integral_constant<int, NPY_CDOUBLE> {
  };

  template <>
  struct c_type_to_numpy_type<signed long long> {
    static const int value =
        details::signed_int_types[sizeof(signed long long)];
  };

  template <>
  struct c_type_to_numpy_type<unsigned long long> {
    static const int value =
        details::unsigned_int_types[sizeof(unsigned long long)];
  };

  template <>
  struct c_type_to_numpy_type<signed long> {
    static const int value = details::signed_int_types[sizeof(signed long)];
  };

  template <>
  struct c_type_to_numpy_type<unsigned long> {
    static const int value = details::unsigned_int_types[sizeof(unsigned long)];
  };

  template <>
  struct c_type_to_numpy_type<signed int> {
    static const int value = details::signed_int_types[sizeof(signed int)];
  };

  template <>
  struct c_type_to_numpy_type<unsigned int> {
    static const int value = details::unsigned_int_types[sizeof(unsigned int)];
  };

  template <>
  struct c_type_to_numpy_type<signed short> {
    static const int value = details::signed_int_types[sizeof(signed short)];
  };

  template <>
  struct c_type_to_numpy_type<unsigned short> {
    static const int value =
        details::unsigned_int_types[sizeof(unsigned short)];
  };

  template <>
  struct c_type_to_numpy_type<signed char> {
    static const int value = details::signed_int_types[sizeof(signed char)];
  };

  template <>
  struct c_type_to_numpy_type<unsigned char> {
    static const int value = details::unsigned_int_types[sizeof(unsigned char)];
  };

  template <>
  struct c_type_to_numpy_type<bool> {
    static const int value = NPY_BOOL;
  };

  template <class T>
  struct c_type_to_numpy_type<boost::simd::logical<T>> {
    static const int value = NPY_BOOL;
  };

  /* wrapper around Python array creation
   * its purpose is to hide the difference between the shape stored in pythran
   * (aka long) and the shape stored in numpy (aka npy_intp)
   * it should work (with an extra copy) on 32 bit architecture and without copy
   * on 64 bits architecture
   */
  template <class T, size_t N>
  struct pyarray_new {

    static_assert(!std::is_same<T, npy_intp>::value, "correctly specialized");

    PyObject *from_descr(PyTypeObject *subtype, PyArray_Descr *descr, T *dims,
                         void *data, int flags, PyObject *obj)
    {
      npy_intp shape[N];
      std::copy(dims, dims + N, shape);
      return pyarray_new<npy_intp, N>{}.from_descr(subtype, descr, shape, data,
                                                   flags, obj);
    }
    PyObject *from_data(T *dims, int typenum, void *data)
    {
      npy_intp shape[N];
      std::copy(dims, dims + N, shape);
      return pyarray_new<npy_intp, N>{}.from_data(shape, typenum, data);
    }
  };

  template <size_t N>
  struct pyarray_new<npy_intp, N> {

    PyObject *from_descr(PyTypeObject *subtype, PyArray_Descr *descr,
                         npy_intp *dims, void *data, int flags, PyObject *obj)
    {
      return PyArray_NewFromDescr(subtype, descr, N, dims, nullptr, data, flags,
                                  obj);
    }

    PyObject *from_data(npy_intp *dims, int typenum, void *data)
    {

      return PyArray_SimpleNewFromData(N, dims, typenum, data);
    }
  };

  template <class T, size_t N>
  PyObject *to_python<types::ndarray<T, N>>::convert(types::ndarray<T, N> n)
  {
    if (n.mem.get_foreign()) {
      PyObject *p = n.mem.get_foreign();
      n.mem.forget();
      PyArrayObject *arr = reinterpret_cast<PyArrayObject *>(p);
      auto const *pshape = PyArray_DIMS(arr);
      Py_INCREF(p);
      if (std::equal(n.shape().begin(), n.shape().end(), pshape))
        return p;
      else {
        Py_INCREF(PyArray_DESCR(arr));
        return pyarray_new<long, N>{}.from_descr(
            Py_TYPE(arr), PyArray_DESCR(arr), n._shape.data(),
            PyArray_DATA(arr), PyArray_FLAGS(arr) & ~NPY_ARRAY_OWNDATA, p);
      }
    } else {
      PyObject *result = pyarray_new<long, N>{}.from_data(
          n._shape.data(), c_type_to_numpy_type<T>::value, n.buffer);
      n.mem.external(result);
      n.mem.forget();
      if (!result)
        return nullptr;
      PyArray_ENABLEFLAGS(reinterpret_cast<PyArrayObject *>(result),
                          NPY_ARRAY_OWNDATA);
      return result;
    }
  }

  template <class Arg>
  PyObject *
  to_python<types::numpy_iexpr<Arg>>::convert(types::numpy_iexpr<Arg> const &v)
  {
    return ::to_python(types::ndarray<typename types::numpy_iexpr<Arg>::dtype,
                                      types::numpy_iexpr<Arg>::value>(v));
  }

  template <class Arg, class... S>
  PyObject *to_python<types::numpy_gexpr<Arg, S...>>::convert(
      types::numpy_gexpr<Arg, S...> const &v)
  {
    return ::to_python(
        types::ndarray<typename types::numpy_gexpr<Arg, S...>::dtype,
                       types::numpy_gexpr<Arg, S...>::value>{v});
  }

  namespace impl
  {
    template <typename T, size_t N>
    PyArrayObject *check_array_type_and_dims(PyObject *obj)
    {
      if (!PyArray_Check(obj))
        return nullptr;
      // the array must have the same dtype and the same number of dimensions
      PyArrayObject *arr = reinterpret_cast<PyArrayObject *>(obj);
      if (PyArray_TYPE(arr) != c_type_to_numpy_type<T>::value)
        return nullptr;
      if (PyArray_NDIM(arr) != N)
        return nullptr;
      return arr;
    }

    template <class T, class S>
    std::tuple<types::slice> make_slices(long const *strides,
                                         long const *offsets, S const *dims,
                                         utils::int_<1>)
    {
      return std::tuple<types::slice>(types::slice(
          *offsets, *offsets + *dims * *strides, *strides / sizeof(T)));
    }

    template <class T, class S, size_t N>
    auto make_slices(long const *strides, long const *offsets, S const *dims,
                     utils::int_<N>)
        -> decltype(std::tuple_cat(
            make_slices<T>(strides, offsets, dims, utils::int_<1>()),
            make_slices<T>(strides + 1, offsets + 1, dims + 1,
                           utils::int_<N - 1>())))
    {
      return std::tuple_cat(
          make_slices<T>(strides, offsets, dims, utils::int_<1>()),
          make_slices<T>(strides + 1, offsets + 1, dims + 1,
                         utils::int_<N - 1>()));
    }
  }

  template <typename T, size_t N>
  bool from_python<types::ndarray<T, N>>::is_convertible(PyObject *obj)
  {
    PyArrayObject *arr = impl::check_array_type_and_dims<T, N>(obj);
    if (not arr)
      return false;
    auto const *stride = PyArray_STRIDES(arr);
    auto const *dims = PyArray_DIMS(arr);
    long current_stride = PyArray_ITEMSIZE(arr);
    for (long i = N - 1; i >= 0; i--) {
      if (stride[i] != current_stride)
        return false;
      current_stride *= dims[i];
    }
    // this is supposed to be a texpr
    if (PyArray_FLAGS(arr) & NPY_ARRAY_F_CONTIGUOUS && N > 1)
      return false;
    else
      return true;
  }
  template <typename T, size_t N>
  types::ndarray<T, N> from_python<types::ndarray<T, N>>::convert(PyObject *obj)
  {
    PyArrayObject *arr = reinterpret_cast<PyArrayObject *>(obj);
    types::ndarray<T, N> r((T *)PyArray_BYTES(arr), PyArray_DIMS(arr), obj);
    Py_INCREF(obj);
    return r;
  }

  template <typename T, size_t N, class... S>
  bool
  from_python<types::numpy_gexpr<types::ndarray<T, N>, S...>>::is_convertible(
      PyObject *obj)
  {
    PyArrayObject *arr = impl::check_array_type_and_dims<T, N>(obj);
    if (not arr)
      return false;

    PyObject *base_obj = PyArray_BASE(arr);
    if (!base_obj or !PyArray_Check(base_obj))
      return false;
    PyArrayObject *base_arr = reinterpret_cast<PyArrayObject *>(base_obj);

    auto const *stride = PyArray_STRIDES(arr);
    auto const *dims = PyArray_DIMS(arr);

    /* FIXME If we have at least one stride, we convert the whole
     * array to a numpy_gexpr, without trying to be smarter with
     * contiguous slices
     */
    long current_stride = PyArray_ITEMSIZE(arr);
    bool at_least_one_stride = false;
    for (long i = N - 1; i >= 0; i--) {
      if (stride[i] < 0) {
        std::cerr << "array with negative strides are not supported"
                  << std::endl;
        return false;
      } else if (stride[i] != current_stride) {
        at_least_one_stride = true;
        break;
      }
      current_stride *= dims[i];
    }
    if (at_least_one_stride) {
      if (PyArray_NDIM(base_arr) != N) {
        std::cerr << "reshaped array are not supported" << std::endl;
        return false;
      }
      return true;
    } else
      return false;
  }

  template <typename T, size_t N, class... S>
  types::numpy_gexpr<types::ndarray<T, N>, S...>
  from_python<types::numpy_gexpr<types::ndarray<T, N>, S...>>::convert(
      PyObject *obj)
  {
    PyArrayObject *arr = reinterpret_cast<PyArrayObject *>(obj);
    PyArrayObject *base_arr =
        reinterpret_cast<PyArrayObject *>(PyArray_BASE(arr));

    /* from the base array pointer and this array pointer, we can recover the
     * full slice informations
     * unfortunately, the PyArray representation is different from our.
     * - PyArray_BYTES gives the start of the base pointer
     * - PyArray_Dims give the dimension array (the shape)
     * - PyArray_STRIDES gives the stride information, but relative to the
     * base
     * pointer and not relative to the lower dimension
     */
    long offsets[N];
    long strides[N];
    auto const *base_dims = PyArray_DIMS(base_arr);

    auto full_offset = PyArray_BYTES(arr) - PyArray_BYTES(base_arr);
    auto const *arr_strides = PyArray_STRIDES(arr);
    long accumulated_dim = 1;
    offsets[N - 1] = full_offset % base_dims[N - 1];
    strides[N - 1] = arr_strides[N - 1];
    for (ssize_t i = N - 2; i >= 0; --i) {
      accumulated_dim *= base_dims[i + 1];
      offsets[i] = full_offset / accumulated_dim;
      strides[i] = arr_strides[i] / accumulated_dim;
    }

    types::ndarray<T, N> base_array((T *)PyArray_BYTES(base_arr),
                                    PyArray_DIMS(base_arr), obj);
    auto slices = impl::make_slices<T>(strides, offsets, PyArray_DIMS(arr),
                                       utils::int_<N>());
    types::numpy_gexpr<types::ndarray<T, N>, S...> r(base_array, slices);

    Py_INCREF(obj);
    return r;
  }

  template <typename E>
  bool from_python<types::numpy_texpr<E>>::

      is_convertible(PyObject *obj)
  {
    constexpr auto N = E::value;
    PyArrayObject *arr =
        impl::check_array_type_and_dims<typename E::dtype, E::value>(obj);
    if (not arr)
      return false;
    // check strides. Note that because it's a texpr, the check is done in the
    // opposite direction compared to ndarrays
    auto const *stride = PyArray_STRIDES(arr);
    auto const *dims = PyArray_DIMS(arr);
    long current_stride = PyArray_ITEMSIZE(arr);
    for (size_t i = 0; i < N; i++) {
      if (stride[i] != current_stride)
        return false;
      current_stride *= dims[i];
    }

    return PyArray_FLAGS(arr) & NPY_ARRAY_F_CONTIGUOUS && N > 1;
  }

  template <typename E>
  types::numpy_texpr<E>
  from_python<types::numpy_texpr<E>>::convert(PyObject *obj)
  {
    constexpr size_t N = E::value;
    using T = typename E::dtype;
    PyArrayObject *arr = reinterpret_cast<PyArrayObject *>(obj);
    std::array<long, N> shape;
    auto const *dims = PyArray_DIMS(arr);
    for (size_t i = 0; i < N; ++i)
      shape[i] = dims[N - 1 - i];
    types::ndarray<T, N> base_array((T *)PyArray_BYTES(arr), shape.data(), obj);
    types::numpy_texpr<types::ndarray<T, N>> r(base_array);
    Py_INCREF(obj);
    return r;
  }
}

#endif

#endif
