//==================================================================================================
/*!
  @file


  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_HORN_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_HORN_HPP_INCLUDED
#include <boost/simd/constant/constant.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/function/fma.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>
#include <cmath>

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-arithmetic

    Computes the value of a polynomial by Horner algorithm.
    This is a static polynomial evaluation.


    @par Header <boost/simd/function/horn.hpp>

    @par Semantic

    For any value @c x of floating point type @c T,
    and any integral constants c0,  c1,  ..., cn representing floating point values
    bits in hexadecimal:

    @code
    T r = horn <T, c0, c1, c2, ...,  cn>(x);
    @endcode

    is equivalent to:

    @code
    T r = (C(n)*x+C(n-1))*x+C(n-2))*x+...+C(1))*x+C(0));
    @endcode

    where C(i) is Constant<T, ci>(),  that is the corresponding floating point value.

    This function evaluates the polynomial of degree n, whose increasing degrees
    coefficients are given by  C(0), C(1), ..., C(n) :

      \f$\sum_0^n C(i)x^i\f$

  **/
  template <typename Value, uintmax_t... Coef> Value horn(Value const& x);
} }
#endif

namespace boost { namespace simd
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  template < typename T>
  BOOST_FORCEINLINE T horn(T) BOOST_NOEXCEPT
  {
    return bs::Zero<T>();
  }

  template < typename T,  uintmax_t Coef>
  BOOST_FORCEINLINE T horn(const T & ) BOOST_NOEXCEPT
  {
    return  bs::Constant<T, Coef>();
  }

  template < typename T, uintmax_t Coef0, uintmax_t Coef1, uintmax_t... Args>
  BOOST_FORCEINLINE T horn(const T & x) BOOST_NOEXCEPT
  {
    return bs::fma(x, horn < T, Coef1, Args...>(x),  bs::Constant<T, Coef0>());
  }

} }
#endif
