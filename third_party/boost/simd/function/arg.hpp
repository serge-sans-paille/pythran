//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ARG_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ARG_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-arithmetic
    This function computes the angular orientation of its floating parameter
    (the result is undifined for Nan entries if the @c pedantic_ decorator is not
    used)


    @par Header <boost/simd/function/arg.hpp>

    Using  `arg(x)` is equivalent to  `(is_negative(x)) ? Pi(as(x)) : Zero(as(x))`

    @par Notes

    - always returns \f$+0\f$ or \f$\pi\f$ taking into account the bit of sign
       even in the Nan case.

    - This function implement the restriction to real numbers of the
       complex arg(ument) function.

    @par Decorators

    - `pedantic_`  returns `Nan(as(x))` for a  nan input,


    @see is_negative, Pi, Nan

    @par Example:

      @snippet arg.cpp arg

    @par Possible output:

      @snippet arg.txt arg

  **/
  IEEEValue arg(IEEEValue const & x);
} }
#endif

#include <boost/simd/function/scalar/arg.hpp>
#include <boost/simd/function/simd/arg.hpp>

#endif
