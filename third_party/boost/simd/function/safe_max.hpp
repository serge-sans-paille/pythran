//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SAFE_MAX_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SAFE_MAX_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-ieee
    This function object returns a safe maximal value relative to the input,  i.e. a
    value which will not overflow when multiplied by the input argument.


    @par Header <boost/simd/function/safe_max.hpp>

    @par Example:

      @snippet safe_max.cpp safe_max

    @par Possible output:

      @snippet safe_max.txt safe_max

  **/
  IEEEValue safe_max(IEEEValue const& x);
} }
#endif

#include <boost/simd/function/scalar/safe_max.hpp>
#include <boost/simd/function/simd/safe_max.hpp>

#endif
