//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SIGNIFICANTS_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SIGNIFICANTS_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-exponential
    Function object implementing significants capabilities

    Compute the rounding to n significants digits

    @par Semantic:

    For every parameter of floating type T and strictly positive integer n

    @code
    T r = significants(x, n);
    @endcode

    is similar to round(x, m) where m is n-iceil(log10(abs(x)))

    @see round,  iceil, log10

  **/
  Value significants(Value const & v0, IntegerValue const& n);
} }
#endif

#include <boost/simd/function/scalar/significants.hpp>
#include <boost/simd/function/simd/significants.hpp>

#endif
