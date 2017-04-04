//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IFREXP_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IFREXP_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-ieee
    This function object computes a mantissa and an exponent pair for the input


    @par Header <boost/simd/function/ifrexp.hpp>

    @par Semantic:

    For every parameter of floating type @c T

    @code
    std::tie(m, e)= ifrexp(x);
    @endcode

    is similar to:

    @code
    as_integer_t<T> e = exponent(x)+1;
    T m = mantissa(x)/2;
    @endcode

    @par Note:

    if you need floating type exponent (unlike the standard)  use @ref frexp

    This function splits a floating point value \f$x\f$ in a signed mantissa \f$m\f$ and
    an exponent \f$e\f$ so that:  \f$x = m\times 2^e\f$,
    with absolute value of \f$m \in [0.5, 1[\f$ (except for \f$x = 0\f$)

    Without the pedantic_ decorator  @ref Nan or @ref Inf are not handled properly.

    @warningbox{Take care that these results differ from the returns of the functions @ref mantissa
    and @ref exponent}

    @par Decorators

     - pedantic_ slower, but special values as @ref Nan or @ref Inf are handled properly.

     - std_ transmits the call to @c std::frexp.

    @see exponent, mantissa, frexp


    @par Example:

      @snippet ifrexp.cpp ifrexp

    @par Possible output:

      @snippet ifrexp.txt ifrexp

  **/
  std::pair<IEEEValue, as_integer_t<IEEEValue>> ifrexp(IEEEValue const& x);
} }
#endif

#include <boost/simd/function/scalar/ifrexp.hpp>
#include <boost/simd/function/simd/ifrexp.hpp>

#endif
