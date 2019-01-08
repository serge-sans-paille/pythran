#ifndef PYTHONIC_TYPES_NUMPY_IEXPR_HPP
#define PYTHONIC_TYPES_NUMPY_IEXPR_HPP

#include "pythonic/include/types/numpy_iexpr.hpp"

#include "pythonic/types/nditerator.hpp"
#include "pythonic/types/tuple.hpp"
#include "pythonic/utils/array_helper.hpp"
#include "pythonic/utils/broadcast_copy.hpp"
#include "pythonic/include/types/raw_array.hpp"
#include "pythonic/types/ndarray.hpp" // we should remove that dep during a refactoring :-)

#include "pythonic/operator_/iadd.hpp"
#include "pythonic/operator_/iand.hpp"
#include "pythonic/operator_/idiv.hpp"
#include "pythonic/operator_/imul.hpp"
#include "pythonic/operator_/ior.hpp"
#include "pythonic/operator_/ixor.hpp"
#include "pythonic/operator_/isub.hpp"

#include <numeric>

PYTHONIC_NS_BEGIN

namespace types
{

  template <class Arg>
  numpy_iexpr<Arg>::numpy_iexpr()
      : buffer(nullptr)
  {
  }

  template <class Arg>
  template <class Argp> // ! using the default one, to make it possible to
  // accept reference && non reference version of Argp
  numpy_iexpr<Arg>::numpy_iexpr(numpy_iexpr<Argp> const &other)
      : buffer(other.buffer), _shape(other.shape())
  {
    assert(buffer);
  }

  template <class Arg>
  numpy_iexpr<Arg>::numpy_iexpr(Arg const &arg, long index)
      : buffer(arg.buffer)
  {
    buffer += buffer_offset(arg, index, utils::int_<value>());
  }
  template <class Arg>
  numpy_iexpr<Arg>::numpy_iexpr(Arg const &arg, long index, dtype *b)
      : buffer(b)
  {
    buffer += buffer_offset(arg, index, utils::int_<value>());
  }

  template <class Arg>
  long numpy_iexpr<Arg>::size() const
  {
    return std::get<0>(_shape);
  }

  template <class Arg>
  template <class E>
  numpy_iexpr<Arg> &numpy_iexpr<Arg>::operator=(E const &expr)
  {
    assert(buffer);
    return utils::broadcast_copy < numpy_iexpr &, E, value,
           value - utils::dim_of<E>::value,
           is_vectorizable &&
               std::is_same<dtype, typename dtype_of<E>::type>::value &&
               types::is_vectorizable<E>::value > (*this, expr);
  }

  template <class Arg>
  numpy_iexpr<Arg> &numpy_iexpr<Arg>::operator=(numpy_iexpr<Arg> const &expr)
  {
    assert(buffer);
    return utils::broadcast_copy < numpy_iexpr &, numpy_iexpr const &, value,
           value - utils::dim_of<numpy_iexpr>::value,
           is_vectorizable && numpy_iexpr<Arg>::is_vectorizable &&
               std::is_same<dtype, typename numpy_iexpr<Arg>::dtype>::value >
                   (*this, expr);
  }

  template <class Arg>
  template <class Op, class Expr>
  numpy_iexpr<Arg> &numpy_iexpr<Arg>::update_(Expr const &expr)
  {
    using BExpr =
        typename std::conditional<std::is_scalar<Expr>::value,
                                  broadcast<Expr, dtype>, Expr const &>::type;
    assert(buffer);
    BExpr bexpr = expr;
    utils::broadcast_update<
        Op, numpy_iexpr &, BExpr, value,
        value - (std::is_scalar<Expr>::value + utils::dim_of<Expr>::value),
        is_vectorizable &&
            types::is_vectorizable<typename std::remove_cv<
                typename std::remove_reference<BExpr>::type>::type>::value &&
            std::is_same<dtype, typename dtype_of<typename std::decay<
                                    BExpr>::type>::type>::value>(*this, bexpr);
    return *this;
  }

  template <class Arg>
  template <class E>
  numpy_iexpr<Arg> &numpy_iexpr<Arg>::operator+=(E const &expr)
  {
    return update_<pythonic::operator_::functor::iadd>(expr);
  }

  template <class Arg>
  numpy_iexpr<Arg> &numpy_iexpr<Arg>::operator+=(numpy_iexpr<Arg> const &expr)
  {
    return update_<pythonic::operator_::functor::iadd>(expr);
  }

  template <class Arg>
  template <class E>
  numpy_iexpr<Arg> &numpy_iexpr<Arg>::operator-=(E const &expr)
  {
    return update_<pythonic::operator_::functor::isub>(expr);
  }

  template <class Arg>
  numpy_iexpr<Arg> &numpy_iexpr<Arg>::operator-=(numpy_iexpr<Arg> const &expr)
  {
    return update_<pythonic::operator_::functor::isub>(expr);
  }

  template <class Arg>
  template <class E>
  numpy_iexpr<Arg> &numpy_iexpr<Arg>::operator*=(E const &expr)
  {
    return update_<pythonic::operator_::functor::imul>(expr);
  }

  template <class Arg>
  numpy_iexpr<Arg> &numpy_iexpr<Arg>::operator*=(numpy_iexpr<Arg> const &expr)
  {
    return update_<pythonic::operator_::functor::imul>(expr);
  }

  template <class Arg>
  template <class E>
  numpy_iexpr<Arg> &numpy_iexpr<Arg>::operator/=(E const &expr)
  {
    return update_<pythonic::operator_::functor::idiv>(expr);
  }

  template <class Arg>
  numpy_iexpr<Arg> &numpy_iexpr<Arg>::operator/=(numpy_iexpr<Arg> const &expr)
  {
    return update_<pythonic::operator_::functor::idiv>(expr);
  }

  template <class Arg>
  template <class E>
  numpy_iexpr<Arg> &numpy_iexpr<Arg>::operator&=(E const &expr)
  {
    return update_<pythonic::operator_::functor::iand>(expr);
  }

  template <class Arg>
  numpy_iexpr<Arg> &numpy_iexpr<Arg>::operator&=(numpy_iexpr<Arg> const &expr)
  {
    return update_<pythonic::operator_::functor::iand>(expr);
  }
  template <class Arg>
  template <class E>
  numpy_iexpr<Arg> &numpy_iexpr<Arg>::operator|=(E const &expr)
  {
    return update_<pythonic::operator_::functor::ior>(expr);
  }

  template <class Arg>
  numpy_iexpr<Arg> &numpy_iexpr<Arg>::operator|=(numpy_iexpr<Arg> const &expr)
  {
    return update_<pythonic::operator_::functor::ior>(expr);
  }

  template <class Arg>
  template <class E>
  numpy_iexpr<Arg> &numpy_iexpr<Arg>::operator^=(E const &expr)
  {
    return update_<pythonic::operator_::functor::ixor>(expr);
  }

  template <class Arg>
  numpy_iexpr<Arg> &numpy_iexpr<Arg>::operator^=(numpy_iexpr<Arg> const &expr)
  {
    return update_<pythonic::operator_::functor::ixor>(expr);
  }

  template <class Arg>
  typename numpy_iexpr<Arg>::const_iterator numpy_iexpr<Arg>::begin() const
  {
    return make_const_nditerator < is_strided || value != 1 > ()(*this, 0);
  }

  template <class Arg>
  typename numpy_iexpr<Arg>::const_iterator numpy_iexpr<Arg>::end() const
  {
    return make_const_nditerator < is_strided ||
           value != 1 > ()(*this, std::get<0>(_shape));
  }

  template <class Arg>
  typename numpy_iexpr<Arg>::iterator numpy_iexpr<Arg>::begin()
  {
    return make_nditerator < is_strided || value != 1 > ()(*this, 0);
  }

  template <class Arg>
  typename numpy_iexpr<Arg>::iterator numpy_iexpr<Arg>::end()
  {
    return make_nditerator < is_strided ||
           value != 1 > ()(*this, std::get<0>(_shape));
  }

  template <class Arg>
  typename numpy_iexpr<Arg>::dtype const *numpy_iexpr<Arg>::fbegin() const
  {
    return buffer;
  }

  template <class Arg>
  typename numpy_iexpr<Arg>::dtype const *numpy_iexpr<Arg>::fend() const
  {
    return buffer + flat_size();
  }

  template <class Arg>
  typename numpy_iexpr<Arg>::dtype *numpy_iexpr<Arg>::fbegin()
  {
    return buffer;
  }

  template <class Arg>
  typename numpy_iexpr<Arg>::dtype const *numpy_iexpr<Arg>::fend()
  {
    return buffer + flat_size();
  }

  template <class T0, class T1>
  size_t compute_fast_offset(size_t offset, long mult, T0 const &indices,
                             T1 const &shape, std::integral_constant<long, 0>)
  {
    return offset;
  }

  template <long I, class T0, class T1>
  size_t compute_fast_offset(size_t offset, long mult, T0 const &indices,
                             T1 const &shape, std::integral_constant<long, I>)
  {
    return compute_fast_offset(offset + std::get<I - 1>(indices) * mult,
                               mult * std::get<I - 1>(shape), indices, shape,
                               std::integral_constant<long, I - 1>());
  }

  template <class Arg>
  typename numpy_iexpr<Arg>::dtype const &
  numpy_iexpr<Arg>::fast(array<long, value> const &indices) const
  {
    return buffer[compute_fast_offset(
        indices[value - 1], std::get<value - 1>(_shape), indices, _shape,
        std::integral_constant<long, value - 1>())];
  }

  template <class Arg>
  typename numpy_iexpr<Arg>::dtype &
  numpy_iexpr<Arg>::fast(array<long, value> const &indices)
  {
    return const_cast<dtype &>(
        const_cast<numpy_iexpr const &>(*this).fast(indices));
  }

  template <class Arg>
  template <class F>
  typename std::enable_if<
      is_numexpr_arg<F>::value && std::is_same<bool, typename F::dtype>::value,
      numpy_vexpr<numpy_iexpr<Arg>, ndarray<long, pshape<long>>>>::type
  numpy_iexpr<Arg>::fast(F const &filter) const
  {
    long sz = std::get<0>(filter.shape());
    long *raw = (long *)malloc(sz * sizeof(long));
    long n = 0;
    for (long i = 0; i < sz; ++i)
      if (filter.fast(i))
        raw[n++] = i;
    // realloc(raw, n * sizeof(long));
    long shp[1] = {n};
    return this->fast(
        ndarray<long, pshape<long>>(raw, shp, types::ownership::owned));
  }

#ifdef USE_XSIMD
  template <class Arg>
  template <class vectorizer>
  typename numpy_iexpr<Arg>::simd_iterator
      numpy_iexpr<Arg>::vbegin(vectorizer) const
  {
    return {buffer};
  }

  template <class Arg>
  template <class vectorizer>
  typename numpy_iexpr<Arg>::simd_iterator
      numpy_iexpr<Arg>::vend(vectorizer) const
  {
    using vector_type = typename xsimd::simd_type<dtype>;
    static const std::size_t vector_size = vector_type::size;
    return {buffer + long(std::get<0>(_shape) / vector_size * vector_size)};
  }

#endif
  template <class Arg>
  auto numpy_iexpr<Arg>::operator[](long i) const & -> decltype(this->fast(i))
  {
    if (i < 0)
      i += std::get<0>(_shape);
    return fast(i);
  }

  template <class Arg>
      auto numpy_iexpr<Arg>::operator[](long i) & -> decltype(this->fast(i))
  {
    if (i < 0)
      i += std::get<0>(_shape);
    return fast(i);
  }

  template <class Arg>
      auto numpy_iexpr<Arg>::operator[](long i) &&
      -> decltype(std::move(*this).fast(i))
  {
    if (i < 0)
      i += std::get<0>(_shape);
    return std::move(*this).fast(i);
  }

  template <class Arg>
  numpy_gexpr<numpy_iexpr<Arg>, normalized_slice> numpy_iexpr<Arg>::
  operator[](slice const &s0) const
  {
    return make_gexpr(*this, s0);
  }

  template <class Arg>
  numpy_gexpr<numpy_iexpr<Arg>, contiguous_normalized_slice> numpy_iexpr<Arg>::
  operator[](contiguous_slice const &s0) const
  {
    return make_gexpr(*this, s0);
  }

  template <class Arg>
  template <class... S>
  numpy_gexpr<numpy_iexpr<Arg>, normalized_slice, normalize_t<S>...>
      numpy_iexpr<Arg>::operator()(slice const &s0, S const &... s) const
  {
    return make_gexpr(*this, s0, s...);
  }

  template <class Arg>
  template <class... S>
  numpy_gexpr<numpy_iexpr<Arg>, contiguous_normalized_slice, normalize_t<S>...>
      numpy_iexpr<Arg>::operator()(contiguous_slice const &s0,
                                   S const &... s) const
  {
    return make_gexpr(*this, s0, s...);
  }

  template <class Arg>
  template <class F>
  typename std::enable_if<
      is_numexpr_arg<F>::value && std::is_same<bool, typename F::dtype>::value,
      numpy_vexpr<numpy_iexpr<Arg>, ndarray<long, pshape<long>>>>::type
      numpy_iexpr<Arg>::
      operator[](F const &filter) const
  {
    return fast(filter);
  }

  template <class T0, class T1>
  size_t compute_offset(size_t offset, long mult, T0 const &indices,
                        T1 const &shape, std::integral_constant<long, 0>)
  {
    return offset;
  }

  template <long I, class T0, class T1>
  size_t compute_offset(size_t offset, long mult, T0 const &indices,
                        T1 const &shape, std::integral_constant<long, I>)
  {
    return compute_offset(
        offset +
            (std::get<I - 1>(indices) < 0
                 ? std::get<I - 1>(indices) + std::get<I - 1>(shape)
                 : std::get<I - 1>(indices)) *
                mult,
        mult * std::get<I - 1>(shape), indices, shape,
        std::integral_constant<long, I - 1>());
  }

  template <class Arg>
  typename numpy_iexpr<Arg>::dtype const &numpy_iexpr<Arg>::
  operator[](array<long, value> const &indices) const
  {
    return buffer[compute_offset(indices[value - 1] < 0
                                     ? indices[value - 1] +
                                           std::get<value - 1>(_shape)
                                     : indices[value - 1],
                                 std::get<value - 1>(_shape), indices, _shape,
                                 std::integral_constant<long, value - 1>())];
  }

  template <class Arg>
  typename numpy_iexpr<Arg>::dtype &numpy_iexpr<Arg>::
  operator[](array<long, value> const &indices)
  {
    return const_cast<dtype &>(const_cast<numpy_iexpr const &>(*this)[indices]);
  }

  template <class Arg>
  numpy_iexpr<Arg>::operator bool() const
  {
    if (sutils::any_of(_shape, [](long n) { return n != 1; }))
      throw ValueError("The truth value of an array with more than one element "
                       "is ambiguous. Use a.any() or a.all()");
    return *buffer;
  }

  template <class Arg>
  long numpy_iexpr<Arg>::flat_size() const
  {
    return sutils::prod(_shape);
  }

  template <class Arg>
  long numpy_iexpr<Arg>::buffer_offset(Arg const &arg, long index,
                                       utils::int_<0>)
  {
    return index;
  }

  template <class Arg>
  template <class T, class pS, size_t N>
  long numpy_iexpr<Arg>::buffer_offset(ndarray<T, pS> const &arg, long index,
                                       utils::int_<N>)
  {
    sutils::assign(std::get<value - N>(_shape),
                   std::get<value - N + 1>(arg._shape));
    buffer_offset(arg, 0, utils::int_<N - 1>());
    return index * arg._strides[0];
  }

  template <class Arg>
  template <class E, size_t N>
  long numpy_iexpr<Arg>::buffer_offset(E const &arg, long index, utils::int_<N>)
  {
    auto tmp = std::get<value - N + 1>(arg.shape());
    sutils::assign(std::get<value - N>(_shape), tmp);
    return buffer_offset(arg, index * tmp, utils::int_<N - 1>());
  }

  template <class T, size_t N>
  numpy_iexpr<T> numpy_iexpr_helper<T, N>::get(T const &e, long i)
  {
    return {e, i};
  }

  template <class T>
  typename T::dtype numpy_iexpr_helper<T, 1>::get(T const &e, long i)
  {
    return e.buffer[i];
  }

  template <class T>
  typename T::dtype &numpy_iexpr_helper<T, 1>::get(T &&e, long i)
  {
    return e.buffer[i];
  }

  template <class T>
  typename T::dtype &numpy_iexpr_helper<T, 1>::get(T &e, long i)
  {
    return e.buffer[i];
  }
}
PYTHONIC_NS_END

#endif
