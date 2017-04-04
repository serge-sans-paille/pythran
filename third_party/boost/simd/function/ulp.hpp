//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ULP_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ULP_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-ieee
    This function object returns the ulp distance to the nearest (distinct) element of the same type.

    @see ulpdist, eps, Eps



    @par Header <boost/simd/function/ulp.hpp>

    @par Example:

      @snippet ulp.cpp ulp

    @par Possible output:

      @snippet ulp.txt ulp

  **/
  Value ulp(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/ulp.hpp>
#include <boost/simd/function/simd/ulp.hpp>

#endif
