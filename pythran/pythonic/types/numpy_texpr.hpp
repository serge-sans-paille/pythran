#ifndef PYTHONIC_TYPES_NUMPY_TEXPR_HPP
#define PYTHONIC_TYPES_NUMPY_TEXPR_HPP

#include "pythonic/include/types/numpy_texpr.hpp"

#include "pythonic/types/ndarray.hpp"

#include "pythonic/operator_/iadd.hpp"
#include "pythonic/operator_/iand.hpp"
#include "pythonic/operator_/idiv.hpp"
#include "pythonic/operator_/imul.hpp"
#include "pythonic/operator_/ior.hpp"
#include "pythonic/operator_/isub.hpp"

PYTHONIC_NS_BEGIN

namespace types
{

  template <class E>
  numpy_texpr_2<E>::numpy_texpr_2()
  {
  }

  template <class E>
  numpy_texpr_2<E>::numpy_texpr_2(Arg const &arg)
      : arg(arg), _shape{{arg.shape()[1], arg.shape()[0]}}
  {
  }

  template <class E>
  typename numpy_texpr_2<E>::const_iterator numpy_texpr_2<E>::begin() const
  {
    return {*this, 0};
  }

  template <class E>
  typename numpy_texpr_2<E>::const_iterator numpy_texpr_2<E>::end() const
  {
    return {*this, _shape[0]};
  }

  template <class E>
  typename numpy_texpr_2<E>::iterator numpy_texpr_2<E>::begin()
  {
    return {*this, 0};
  }

  template <class E>
  typename numpy_texpr_2<E>::iterator numpy_texpr_2<E>::end()
  {
    return {*this, _shape[0]};
  }

  template <class E>
  auto numpy_texpr_2<E>::fast(long i) const
      -> decltype(this->arg(contiguous_slice(pythonic::__builtin__::None,
                                             pythonic::__builtin__::None),
                            i))
  {
    return arg(contiguous_slice(pythonic::__builtin__::None,
                                pythonic::__builtin__::None),
               i);
  }

  template <class E>
  auto numpy_texpr_2<E>::fast(long i)
      -> decltype(this->arg(contiguous_slice(pythonic::__builtin__::None,
                                             pythonic::__builtin__::None),
                            i))
  {
    return arg(contiguous_slice(pythonic::__builtin__::None,
                                pythonic::__builtin__::None),
               i);
  }

#ifdef USE_BOOST_SIMD
  template <class E>
  template <class vectorizer>
  typename numpy_texpr_2<E>::simd_iterator
      numpy_texpr_2<E>::vbegin(vectorizer) const
  {
    return {*this};
  }

  template <class E>
  template <class vectorizer>
  typename numpy_texpr_2<E>::simd_iterator
      numpy_texpr_2<E>::vend(vectorizer) const
  {
    return {*this}; // ! vectorizable anyway
  }
#endif

  template <class E>
  auto numpy_texpr_2<E>::operator[](long i) const -> decltype(this->fast(i))
  {
    if (i < 0)
      i += _shape[0];
    return fast(i);
  }

  template <class E>
  auto numpy_texpr_2<E>::operator[](long i) -> decltype(this->fast(i))
  {
    if (i < 0)
      i += _shape[0];
    return fast(i);
  }

  template <class E>
  template <class T0, class T1>
  auto numpy_texpr_2<E>::operator[](std::tuple<T0, T1> const &indices)
      -> decltype(
          arg[std::tuple<T1, T0>{std::get<1>(indices), std::get<0>(indices)}])
  {
    return arg[std::tuple<T1, T0>{std::get<1>(indices), std::get<0>(indices)}];
  }
  template <class E>
  template <class T0, class T1>
  auto numpy_texpr_2<E>::operator[](std::tuple<T0, T1> const &indices) const
      -> decltype(
          arg[std::tuple<T1, T0>{std::get<1>(indices), std::get<0>(indices)}])
  {
    return arg[std::tuple<T1, T0>{std::get<1>(indices), std::get<0>(indices)}];
  }

  template <class E>
  auto numpy_texpr_2<E>::operator[](contiguous_slice const &s0) const
      -> decltype(this->arg(contiguous_slice(pythonic::__builtin__::None,
                                             pythonic::__builtin__::None),
                            s0))
  {
    return arg(contiguous_slice(pythonic::__builtin__::None,
                                pythonic::__builtin__::None),
               s0);
  }

  template <class E>
  auto numpy_texpr_2<E>::operator[](contiguous_slice const &s0)
      -> decltype(this->arg(contiguous_slice(pythonic::__builtin__::None,
                                             pythonic::__builtin__::None),
                            s0))
  {
    return arg(contiguous_slice(pythonic::__builtin__::None,
                                pythonic::__builtin__::None),
               s0);
  }

  template <class E>
  auto numpy_texpr_2<E>::operator[](slice const &s0) const
      -> decltype(this->arg(contiguous_slice(pythonic::__builtin__::None,
                                             pythonic::__builtin__::None),
                            s0))
  {
    return arg(contiguous_slice(pythonic::__builtin__::None,
                                pythonic::__builtin__::None),
               s0);
  }

  template <class E>
  auto numpy_texpr_2<E>::operator[](slice const &s0)
      -> decltype(this->arg(contiguous_slice(pythonic::__builtin__::None,
                                             pythonic::__builtin__::None),
                            s0))
  {
    return arg(contiguous_slice(pythonic::__builtin__::None,
                                pythonic::__builtin__::None),
               s0);
  }

  /* element filtering */
  template <class E>
  template <class F> // indexing through an array of boolean -- a mask
  typename std::enable_if<is_numexpr_arg<F>::value &&
                              std::is_same<bool, typename F::dtype>::value,
                          numpy_fexpr<numpy_texpr_2<E>, F>>::type
  numpy_texpr_2<E>::fast(F const &filter) const
  {
    return {*this, filter};
  }

  template <class E>
  template <class F> // indexing through an array of boolean -- a mask
  typename std::enable_if<is_numexpr_arg<F>::value &&
                              std::is_same<bool, typename F::dtype>::value,
                          numpy_fexpr<numpy_texpr_2<E>, F>>::type
      numpy_texpr_2<E>::
      operator[](F const &filter) const
  {
    return fast(filter);
  }

  template <class E>
  template <class F> // indexing through an array of indices -- a view
  typename std::enable_if<is_numexpr_arg<F>::value &&
                              !std::is_same<bool, typename F::dtype>::value,
                          ndarray<typename numpy_texpr_2<E>::dtype, 2>>::type
      numpy_texpr_2<E>::
      operator[](F const &filter) const
  {
    static_assert(F::value == 1,
                  "advanced indexing only supporint with 1D index");

    ndarray<typename numpy_texpr_2<E>::dtype, 2> out(
        array<long, 2>{{filter.flat_size(), shape()[1]}}, none_type());
    std::transform(
        filter.begin(), filter.end(), out.begin(),
        [this](typename F::dtype index) { return operator[](index); });
    return out;
  }

  template <class E>
  template <class F> // indexing through an array of indices -- a view
  typename std::enable_if<is_numexpr_arg<F>::value &&
                              !std::is_same<bool, typename F::dtype>::value,
                          ndarray<typename numpy_texpr_2<E>::dtype, 2>>::type
  numpy_texpr_2<E>::fast(F const &filter) const
  {
    static_assert(F::value == 1,
                  "advanced indexing only supporint with 1D index");
    ndarray<typename numpy_texpr_2<E>::dtype, 2> out(
        array<long, 2>{{filter.flat_size(), shape()[1]}}, none_type());
    std::transform(filter.begin(), filter.end(), out.begin(),
                   [this](typename F::dtype index) { return fast(index); });
    return out;
  }

  template <class E>
  template <class S, size_t... I>
  auto numpy_texpr_2<E>::_reverse_index(S const &indices,
                                        utils::index_sequence<I...>) const
      -> decltype(this->arg(std::get<I>(indices)...))
  {
    return arg(std::get<I>(indices)...);
  }

  template <class E>
  template <class S0, class... S>
  auto numpy_texpr_2<E>::operator()(S0 const &s0, S const &... s) const
      -> decltype(this->_reverse_index(
          std::tuple<S0 const &, S const &...>{s0, s...},
          utils::make_reversed_index_sequence<1 + sizeof...(S)>()))
  {
    return _reverse_index(
        std::tuple<S0 const &, S const &...>{s0, s...},
        utils::make_reversed_index_sequence<1 + sizeof...(S)>());
  }

  template <class E>
  long numpy_texpr_2<E>::flat_size() const
  {
    return arg.flat_size();
  }

  template <class E>
  intptr_t numpy_texpr_2<E>::id() const
  {
    return arg.id();
  }

  template <class Arg>
  template <class Expr>
  numpy_texpr_2<Arg> &numpy_texpr_2<Arg>::operator=(Expr const &expr)
  {
    assert(buffer);
    return utils::broadcast_copy < numpy_texpr_2 &, Expr, value,
           value - utils::dim_of<Expr>::value,
           is_vectorizable &&
               std::is_same<dtype, typename dtype_of<Expr>::type>::value &&
               types::is_vectorizable<Expr>::value > (*this, expr);
  }

  template <class Arg>
  template <class Op, class Expr>
  numpy_texpr_2<Arg> &numpy_texpr_2<Arg>::update_(Expr const &expr)
  {
    using BExpr =
        typename std::conditional<std::is_scalar<Expr>::value,
                                  broadcast<Expr, dtype>, Expr const &>::type;
    BExpr bexpr = expr;
    utils::broadcast_update<
        Op, numpy_texpr_2 &, BExpr, value,
        value - (std::is_scalar<Expr>::value + utils::dim_of<Expr>::value),
        is_vectorizable &&
            types::is_vectorizable<typename std::remove_cv<
                typename std::remove_reference<BExpr>::type>::type>::value &&
            std::is_same<dtype, typename dtype_of<typename std::decay<
                                    BExpr>::type>::type>::value>(*this, bexpr);
    return *this;
  }

  template <class Arg>
  template <class Expr>
  numpy_texpr_2<Arg> &numpy_texpr_2<Arg>::operator+=(Expr const &expr)
  {
    return update_<pythonic::operator_::functor::iadd>(expr);
  }

  template <class Arg>
  template <class E>
  numpy_texpr_2<Arg> &numpy_texpr_2<Arg>::operator-=(E const &expr)
  {
    return update_<pythonic::operator_::functor::isub>(expr);
  }

  template <class Arg>
  template <class E>
  numpy_texpr_2<Arg> &numpy_texpr_2<Arg>::operator*=(E const &expr)
  {
    return update_<pythonic::operator_::functor::imul>(expr);
  }

  template <class Arg>
  template <class E>
  numpy_texpr_2<Arg> &numpy_texpr_2<Arg>::operator/=(E const &expr)
  {
    return update_<pythonic::operator_::functor::idiv>(expr);
  }

  template <class Arg>
  template <class E>
  numpy_texpr_2<Arg> &numpy_texpr_2<Arg>::operator&=(E const &expr)
  {
    return update_<pythonic::operator_::functor::iand>(expr);
  }

  template <class Arg>
  template <class E>
  numpy_texpr_2<Arg> &numpy_texpr_2<Arg>::operator|=(E const &expr)
  {
    return update_<pythonic::operator_::functor::ior>(expr);
  }

  // only implemented for N = 2
  template <class T>
  numpy_texpr<ndarray<T, 2>>::numpy_texpr()
  {
  }

  template <class T>
  numpy_texpr<ndarray<T, 2>>::numpy_texpr(ndarray<T, 2> const &arg)
      : numpy_texpr_2<ndarray<T, 2>>{arg}
  {
  }

  template <class E, class... S>
  numpy_texpr<numpy_gexpr<E, S...>>::numpy_texpr()
  {
  }

  template <class E, class... S>
  numpy_texpr<numpy_gexpr<E, S...>>::numpy_texpr(
      numpy_gexpr<E, S...> const &arg)
      : numpy_texpr_2<numpy_gexpr<E, S...>>{arg}
  {
  }
}
PYTHONIC_NS_END

#endif
