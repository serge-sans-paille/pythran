//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_DETAIL_PACK_OPERATORS_HPP_INCLUDED
#define BOOST_SIMD_DETAIL_PACK_OPERATORS_HPP_INCLUDED

#include <boost/simd/config.hpp>
#include <boost/simd/function/plus.hpp>
#include <boost/simd/function/minus.hpp>
#include <boost/simd/function/multiplies.hpp>
#include <boost/simd/function/divides.hpp>
#include <boost/simd/function/is_equal.hpp>
#include <boost/simd/function/rem.hpp>
#include <boost/simd/function/is_less.hpp>
#include <boost/simd/function/is_less_equal.hpp>
#include <boost/simd/function/is_greater.hpp>
#include <boost/simd/function/is_greater_equal.hpp>
#include <boost/simd/function/bitwise_and.hpp>
#include <boost/simd/function/bitwise_or.hpp>
#include <boost/simd/function/bitwise_xor.hpp>
#include <boost/simd/function/complement.hpp>
#include <boost/simd/function/logical_not.hpp>
#include <boost/simd/function/shift_left.hpp>
#include <boost/simd/function/shift_right.hpp>
#include <boost/simd/function/logical_and.hpp>
#include <boost/simd/function/logical_or.hpp>
#include <boost/simd/function/logical_not.hpp>
#include <boost/simd/function/rem.hpp>
#include <boost/simd/function/unary_plus.hpp>
#include <boost/simd/function/unary_minus.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/meta/is_pack.hpp>
#include <boost/simd/logical.hpp>

namespace boost { namespace simd
{
#define BOOST_SIMD_PACK_DEFINE_BINOP(type_, op, f)                                                 \
  template <typename T, std::size_t N, typename U> BOOST_FORCEINLINE                               \
  typename std::enable_if<is_not_pack_t<U>::value && std::is_convertible<U, T>::value,             \
                          pack<type_, N>>::type                                                    \
  op(pack<T, N> const& p0, U const& s1) BOOST_NOEXCEPT_IF_EXPR(f(p0, s1))                          \
  { return f(p0, s1); }                                                                            \
                                                                                                   \
  template <typename T, std::size_t N, typename U> BOOST_FORCEINLINE                               \
  typename std::enable_if<is_not_pack_t<U>::value && std::is_convertible<U, T>::value,             \
                          pack<type_, N>>::type                                                    \
  op(U const& s0, pack<T, N> const& p1) BOOST_NOEXCEPT_IF_EXPR(f(s0, p1))                          \
  { return f(s0, p1); }                                                                            \
                                                                                                   \
  template <typename T, typename U, std::size_t N> BOOST_FORCEINLINE                               \
  auto op(pack<T, N> const& p0, pack<U, N> const& p1)                                              \
  BOOST_NOEXCEPT_DECLTYPE_BODY(f(p0, p1))                                                          \
/**/

BOOST_SIMD_PACK_DEFINE_BINOP(T, operator+, plus)
BOOST_SIMD_PACK_DEFINE_BINOP(T, operator-, minus)
BOOST_SIMD_PACK_DEFINE_BINOP(T, operator%, rem)
BOOST_SIMD_PACK_DEFINE_BINOP(T, operator/, divides)
BOOST_SIMD_PACK_DEFINE_BINOP(T, operator*, multiplies)

BOOST_SIMD_PACK_DEFINE_BINOP(T, operator&, bitwise_and)
BOOST_SIMD_PACK_DEFINE_BINOP(T, operator|, bitwise_or)
BOOST_SIMD_PACK_DEFINE_BINOP(T, operator^, bitwise_xor)

BOOST_SIMD_PACK_DEFINE_BINOP(T, operator << , shift_left)
BOOST_SIMD_PACK_DEFINE_BINOP(T, operator >> , shift_right)

#define BOOST_SIMD_PACK_DEFINE_LOGICAL_BINOP(op, f)                                                \
  template <typename T, typename U, std::size_t N> BOOST_FORCEINLINE                               \
  auto op(pack<T, N> const& p0, pack<U, N> const& p1)                                              \
  BOOST_NOEXCEPT_DECLTYPE_BODY(f(p0, p1))                                                          \
                                                                                                   \
  template <typename T, std::size_t N, typename U> BOOST_FORCEINLINE                               \
  typename std::enable_if < is_not_pack_t<U>::value && std::is_convertible<U, T>::value            \
                          , pack<bs::as_logical_t<T>, N>                                           \
                          >::type                                                                  \
  op(pack<T, N> const& p0, U const& s1) BOOST_NOEXCEPT                                             \
  { return f(p0, s1); }                                                                            \
                                                                                                   \
  template <typename T, std::size_t N, typename U> BOOST_FORCEINLINE                               \
  typename std::enable_if < is_not_pack_t<U>::value && std::is_convertible<U, T>::value            \
                          , pack<bs::as_logical_t<T>, N>                                           \
                          >::type                                                                  \
  op(U const& s0, pack<T, N> const& p1) BOOST_NOEXCEPT                                             \
  { return f(s0, p1); }                                                                            \
/**/

BOOST_SIMD_PACK_DEFINE_LOGICAL_BINOP(operator&&, logical_and)
BOOST_SIMD_PACK_DEFINE_LOGICAL_BINOP(operator||, logical_or)
BOOST_SIMD_PACK_DEFINE_LOGICAL_BINOP(operator<,  is_less)
BOOST_SIMD_PACK_DEFINE_LOGICAL_BINOP(operator>,  is_greater)
BOOST_SIMD_PACK_DEFINE_LOGICAL_BINOP(operator==, is_equal)
BOOST_SIMD_PACK_DEFINE_LOGICAL_BINOP(operator<=, is_less_equal)
BOOST_SIMD_PACK_DEFINE_LOGICAL_BINOP(operator>=, is_greater_equal)
BOOST_SIMD_PACK_DEFINE_LOGICAL_BINOP(operator!=, is_not_equal)

#undef BOOST_SIMD_PACK_DEFINE_BINOP
#undef BOOST_SIMD_PACK_DEFINE_LOGICAL_BINOP

  template <typename T, std::size_t N>
  BOOST_FORCEINLINE auto operator!(pack<T,N> const& a)
  BOOST_NOEXCEPT_DECLTYPE_BODY(logical_not(a))

  template <typename T, std::size_t N>
  BOOST_FORCEINLINE auto operator+(pack<T,N> const& a)
  BOOST_NOEXCEPT_DECLTYPE_BODY(unary_plus(a))

  template <typename T, std::size_t N>
  BOOST_FORCEINLINE auto operator-(pack<T,N> const& a)
  BOOST_NOEXCEPT_DECLTYPE_BODY(unary_minus(a))

  template <typename T, std::size_t N>
  BOOST_FORCEINLINE auto operator~(pack<T,N> const& a)
  BOOST_NOEXCEPT_DECLTYPE_BODY(complement(a))
} }

#endif
