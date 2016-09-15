//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_NEXTPOW2_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_NEXTPOW2_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-ieee
    Function object implementing nextpow2 capabilities

    Returns the greatest integer n such that abs_s(x) is greater or equal to \f$2^n\f$

    @par Semantic:

    @code
    auto n = nextpow2(x);
    @endcode

    is similar to:

    @code
    auto n = floor(log2(saturated_(abs)(x)));
    @endcode

    @see floor, log2, abs, saturated
  **/
  Value nextpow2(Value const & x);
} }
#endif

#include <boost/simd/function/scalar/nextpow2.hpp>
#include <boost/simd/function/simd/nextpow2.hpp>

#endif
