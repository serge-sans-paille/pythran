#ifndef PYTHONIC_TYPES_NUMPY_IEXPR_HPP
#define PYTHONIC_TYPES_NUMPY_IEXPR_HPP

#include "pythonic/include/types/numpy_iexpr.hpp"

#include "pythonic/types/nditerator.hpp"
#include "pythonic/types/tuple.hpp"
#include "pythonic/utils/array_helper.hpp"

#include "pythonic/operator_/iadd.hpp"
#include "pythonic/operator_/iand.hpp"
#include "pythonic/operator_/idiv.hpp"
#include "pythonic/operator_/imul.hpp"
#include "pythonic/operator_/ior.hpp"
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
  }

  template <class Arg>
  numpy_iexpr<Arg>::numpy_iexpr(Arg const &arg, long index)
      : buffer(arg.buffer)
  {
    buffer += buffer_offset(arg.shape(), index, utils::int_<value>());
  }

  template <class Arg>
  long numpy_iexpr<Arg>::size() const
  {
    return _shape[0];
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
           is_vectorizable && numpy_iexpr<Arg>::is_vectorizable > (*this, expr);
  }

  template <class Arg>
  template <class Op, class Expr>
  numpy_iexpr<Arg> &numpy_iexpr<Arg>::update_(Expr const &expr)
  {
    using BExpr =
        typename std::conditional<std::is_scalar<Expr>::value,
                                  broadcast<Expr, dtype>, Expr const &>::type;
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
  typename numpy_iexpr<Arg>::const_iterator numpy_iexpr<Arg>::begin() const
  {
    return make_const_nditerator < is_strided || value != 1 > ()(*this, 0);
  }

  template <class Arg>
  typename numpy_iexpr<Arg>::const_iterator numpy_iexpr<Arg>::end() const
  {
    return make_const_nditerator < is_strided ||
           value != 1 > ()(*this, _shape[0]);
  }

  template <class Arg>
  typename numpy_iexpr<Arg>::iterator numpy_iexpr<Arg>::begin()
  {
    return make_nditerator < is_strided || value != 1 > ()(*this, 0);
  }

  template <class Arg>
  typename numpy_iexpr<Arg>::iterator numpy_iexpr<Arg>::end()
  {
    return make_nditerator < is_strided || value != 1 > ()(*this, _shape[0]);
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

  template <class Arg>
  auto numpy_iexpr<Arg>::fast(long i) const
      & -> decltype(numpy_iexpr_helper<numpy_iexpr<Arg>, value>::get(*this, i))
  {
    return numpy_iexpr_helper<numpy_iexpr, value>::get(*this, i);
  }

  template <class Arg>
      auto numpy_iexpr<Arg>::fast(long i) &
      -> decltype(numpy_iexpr_helper<numpy_iexpr<Arg>, value>::get(*this, i))
  {
    return numpy_iexpr_helper<numpy_iexpr, value>::get(*this, i);
  }

  template <class Arg>
      auto numpy_iexpr<Arg>::fast(long i) &&
      -> decltype(
          numpy_iexpr_helper<numpy_iexpr<Arg>, value>::get(std::move(*this), i))
  {
    return numpy_iexpr_helper<numpy_iexpr, value>::get(std::move(*this), i);
  }

  template <class Arg>
  typename numpy_iexpr<Arg>::dtype const &
  numpy_iexpr<Arg>::fast(array<long, value> const &indices) const
  {
    size_t offset = indices[value - 1];
    long mult = _shape[value - 1];
    for (size_t i = value - 2; i > 0; --i) {
      offset += indices[i] * mult;
      mult *= _shape[i];
    }
    return buffer[offset + indices[0] * mult];
  }

  template <class Arg>
  typename numpy_iexpr<Arg>::dtype &
  numpy_iexpr<Arg>::fast(array<long, value> const &indices)
  {
    return const_cast<dtype &>(const_cast<numpy_iexpr const &>(*this)[indices]);
  }

  template <class Arg>
  template <class F>
  typename std::enable_if<is_numexpr_arg<F>::value,
                          numpy_fexpr<numpy_iexpr<Arg>, F>>::type
  numpy_iexpr<Arg>::fast(F const &filter) const
  {
    return numpy_fexpr<numpy_iexpr, F>(*this, filter);
  }

#ifdef USE_BOOST_SIMD
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
    using vector_type = typename boost::simd::pack<dtype>;
    static const std::size_t vector_size = vector_type::static_size;
    return {buffer + long(_shape[0] / vector_size * vector_size)};
  }

#endif
  template <class Arg>
  auto numpy_iexpr<Arg>::operator[](long i) const & -> decltype(this->fast(i))
  {
    if (i < 0)
      i += _shape[0];
    return fast(i);
  }

  template <class Arg>
      auto numpy_iexpr<Arg>::operator[](long i) & -> decltype(this->fast(i))
  {
    if (i < 0)
      i += _shape[0];
    return fast(i);
  }

  template <class Arg>
      auto numpy_iexpr<Arg>::operator[](long i) &&
      -> decltype(std::move(*this).fast(i))
  {
    if (i < 0)
      i += _shape[0];
    return std::move(*this).fast(i);
  }

  template <class Arg>
  numpy_gexpr<numpy_iexpr<Arg>, slice> numpy_iexpr<Arg>::
  operator[](slice const &s0) const
  {
    return make_gexpr(*this, s0);
  }

  template <class Arg>
  numpy_gexpr<numpy_iexpr<Arg>, contiguous_slice> numpy_iexpr<Arg>::
  operator[](contiguous_slice const &s0) const
  {
    return make_gexpr(*this, s0);
  }

  template <class Arg>
  template <class... S>
  numpy_gexpr<numpy_iexpr<Arg>, slice, S...> numpy_iexpr<Arg>::
  operator()(slice const &s0, S const &... s) const
  {
    return make_gexpr(*this, s0, s...);
  }

  template <class Arg>
  template <class... S>
  numpy_gexpr<numpy_iexpr<Arg>, contiguous_slice, S...> numpy_iexpr<Arg>::
  operator()(contiguous_slice const &s0, S const &... s) const
  {
    return make_gexpr(*this, s0, s...);
  }

  template <class Arg>
  template <class... S>
  auto numpy_iexpr<Arg>::operator()(long s0, S const &... s) const
      -> decltype(std::declval<numpy_iexpr<numpy_iexpr<Arg>>>()(s...))
  {
    return (*this)[s0](s...);
  }

  template <class Arg>
  template <class F>
  typename std::enable_if<is_numexpr_arg<F>::value,
                          numpy_fexpr<numpy_iexpr<Arg>, F>>::type
      numpy_iexpr<Arg>::
      operator[](F const &filter) const
  {
    return fast(filter);
  }

  template <class Arg>
  typename numpy_iexpr<Arg>::dtype const &numpy_iexpr<Arg>::
  operator[](array<long, value> const &indices) const
  {
    size_t offset = indices[value - 1] < 0
                        ? indices[value - 1] + _shape[value - 1]
                        : indices[value - 1];
    long mult = _shape[value - 1];
    for (size_t i = value - 2; i > 0; --i) {
      offset += (indices[i] < 0 ? indices[i] + _shape[i] : indices[i]) * mult;
      mult *= _shape[i];
    }
    return buffer[offset +
                  (indices[0] < 0 ? indices[0] + _shape[0] : indices[0]) *
                      mult];
  }

  template <class Arg>
  typename numpy_iexpr<Arg>::dtype &numpy_iexpr<Arg>::
  operator[](array<long, value> const &indices)
  {
    return const_cast<dtype &>(const_cast<numpy_iexpr const &>(*this)[indices]);
  }

  template <class Arg>
  long numpy_iexpr<Arg>::flat_size() const
  {
    return std::accumulate(_shape.begin() + 1, _shape.end(), *_shape.begin(),
                           std::multiplies<long>());
  }

  template <class Arg>
  long numpy_iexpr<Arg>::buffer_offset(array<long, value + 1> const &shape,
                                       long index, utils::int_<0>)
  {
    return index;
  }

  template <class Arg>
  template <size_t N>
  long numpy_iexpr<Arg>::buffer_offset(array<long, value + 1> const &shape,
                                       long index, utils::int_<N>)
  {
    _shape[value - N] = shape[value - N + 1];
    return buffer_offset(shape, index * shape[value - N + 1],
                         utils::int_<N - 1>());
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
