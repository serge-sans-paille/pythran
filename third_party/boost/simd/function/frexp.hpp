//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_FREXP_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_FREXP_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-ieee
    This function object returns a mantissa and an exponent pair for the input


    @par Header <boost/simd/function/frexp.hpp>

    @par Semantic:

    For every parameter of floating type

    @code
    std::tie(m, e)= frexp(x);
    @endcode

    is similar to:

    @code
    auto e = tofloat(exponent(x)+1);
    auto m = mantissa(x)/2;
    @endcode

    @par Notes:

    - Without the pedantic_ decorator,  calling @c frexp on @c Nan or @c Inf
    has undefined behavior.

    - the exponent and matissa are both returned as floating values:
      if you need integral type exponent (as in the standard library)
      use @ref ifrexp

    - This function splits a floating point value \f$x\f$ in a signed
      mantissa \f$m\f$ and an exponent \f$e\f$ so that:  \f$x = m\times 2^e\f$,
      with absolute value of \f$m \in [0.5, 1[\f$ (except for \f$x = 0\f$)

      @warningbox{Take care that these results differ from the returns
      of the functions @ref mantissa and @ref exponent}

    @par Decorators

     - pedantic_ slower, but special values as @ref Nan or @ref Inf are handled properly.

     - std_ transmits the call to @c std::frexp and converts the exponent.

    @see ifrexp, exponent, mantissa


    @par Example:

      @snippet frexp.cpp frexp

    @par Possible output:

      @snippet frexp.txt frexp

  **/
  std::pair<IEEEValue, IEEEValue> frexp(IEEEValue const& x);
} }
#endif

#include <boost/simd/function/scalar/frexp.hpp>
#include <boost/simd/function/scalar/frexp.hpp>
#include <boost/simd/function/simd/frexp.hpp>

#endif
