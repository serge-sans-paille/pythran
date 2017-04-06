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
    This function object returns the rounding to n significants digits of its argument.

    @par Header <boost/simd/function/signiicants.hpp>

    @par Example:

      @snippet significants.cpp significants

    @par Possible output:

      @snippet significants.txt significants

  **/
  IEEEValue significants(IEEEValue const& x, IntegerValue const& n);
} }
#endif

#include <boost/simd/function/scalar/significants.hpp>
#include <boost/simd/function/simd/significants.hpp>

#endif
