//==================================================================================================
/*!
  @file


  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_HORN1_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_HORN1_HPP_INCLUDED
#include <boost/simd/constant/constant.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/function/fma.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>
#include <cmath>

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-arithmetic

    Computes the value of a polynomial by Horner algorithm
    which leading 1 coeficient.
    This is a static polynomial evaluation.


    @par Header <boost/simd/function/horn1.hpp>

    @par Semantic

    For any value @c x of floating point type @c T,
    and any integral constants c0,  c1,  ..., cn representing floating point values
    bits in hexadecimal:

    @code
    T r = horn1 <T, c0, c1, c2, ...,  cn-1>(x);
    @endcode

    is equivalent to:

    @code
    T r = (x+C(n-1))*x+C(n-2))*x+...+C(1))*x+C(0));
    @endcode

    where C(i) is Constant<T, ci>(),  that is the corresponding floating point value.

    This function evaluates the polynomial of degree n, whose increasing degrees
    coefficients are given by  C(0), C(1), ..., C(n-1), 1:

      \f$ x^n+\sum_0^{n-1} C(i)x^i \f$

    This differs from @ref horn only by the fact that the leading polynomial
    coefficient is one, saving one multiplication.

  **/
  template <typename Value, uintmax_t... Coef> Value horn1(Value const& x) {}
} }
#endif

namespace boost { namespace simd
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  template < typename T>
  BOOST_FORCEINLINE T horn1(T) BOOST_NOEXCEPT
  {
    return bs::One<T>();
  }

  template < typename T,  uintmax_t Coef>
  BOOST_FORCEINLINE T horn1(const T & x) BOOST_NOEXCEPT
  {
    return x +  bs::Constant<T, Coef>();
  }

  template < typename T, uintmax_t Coef0, uintmax_t Coef1, uintmax_t... Args>
  BOOST_FORCEINLINE T horn1(const T & x) BOOST_NOEXCEPT
  {
    return bs::fma(x, horn1 < T, Coef1, Args...>(x),  bs::Constant<T, Coef0>());
  }

} }

#endif
