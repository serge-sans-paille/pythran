//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SAFE_MIN_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SAFE_MIN_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-ieee
    This function object returns a safe mininimal value relative to the input, i.e. a
    value which will not underflow when divided by the input argument.


    @par Header <boost/simd/function/safe_min.hpp>

    @par Example:

      @snippet safe_min.cpp safe_min

    @par Possible output:

      @snippet safe_min.txt safe_min

  **/
  IEEEValue safe_min(IEEEValue const& x);
} }
#endif

#include <boost/simd/function/scalar/safe_min.hpp>
#include <boost/simd/function/simd/safe_min.hpp>

#endif
