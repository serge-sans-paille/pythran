//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ILOGB_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ILOGB_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-ieee
    Function object implementing ilogb capabilities

    This function returns the integer truncation
    of the base 2 logarithm of x.

    It coincides with the @ref exponent function
    on all platforms supported.

    @par Semantic:

    @code
    auto r = ilogb(x);
    @endcode

    is similar to:

    @code
    auto r = saturated_(toint)(log2(x));
    @endcode

    @see exponent, log2, toint, saturated

  **/
  Value ilogb(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/ilogb.hpp>
#include <boost/simd/function/simd/ilogb.hpp>

#endif
