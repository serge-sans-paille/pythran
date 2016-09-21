//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_MINNUM_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_MINNUM_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-ieee
    Function object implementing minnum capabilities

     Returns the minimum value, ignoring nans.

    @par Semantic:

    @code
    auto r = minnum(x,y);
    @endcode

    is similar to:

    @code
    auto r = (is_nan(x) ? y : (isnan(y) ? x : min(x, y));;
    @endcode

    @par Alias:
    fmin

    With the std_ decorator std_(minnum)(x, y) calls the stdlibc++ function std::fmin.

    @par Decorators

    std_ for floating entries

  **/
  Value minnum(Value const & x, Value const& y);
} }
#endif

#include <boost/simd/function/scalar/minnum.hpp>
#include <boost/simd/function/simd/minnum.hpp>

#endif
