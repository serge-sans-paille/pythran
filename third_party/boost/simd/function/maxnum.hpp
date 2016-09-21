//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_MAXNUM_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_MAXNUM_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-ieee
    Function object implementing maxnum capabilities

    Returns the maximum value, ignoring nans.

    @par Semantic:

    @code
    auto r = maxnum(x,y);
    @endcode

    is similar to:

    @code
    auto r = (is_nan(x) ? y : (isnan(y) ? x : max(x, y));
    @endcode

    @par Alias:
     fmax

    With the std_ decorator std_(maxnum)(x, y) calls the stdlibc++ function std::fmax.

    @par Decorators

    std_ for floating entries

    @see max, maxnummag,  maxmag

  **/
  Value maxnum(Value const & x, Value const& y);
} }
#endif

#include <boost/simd/function/scalar/maxnum.hpp>
#include <boost/simd/function/simd/maxnum.hpp>

#endif
