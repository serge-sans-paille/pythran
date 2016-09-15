//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_SQRTEPS_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_SQRTEPS_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generate the square root of constant Eps

    @par Semantic:

    @code
    T r = Sqrteps<T>();
    @endcode

    is similar to:

    @code
    if T is integral
      r = 1
    else if T is double
      r =  Pow(2,-26);
    else if T is float
      r =  pow(2,-11.5f);
    @endcode

    @return The Sqrteps constant for the proper type
  **/
  template<typename T> T Sqrteps();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generate the  constant sqrteps.

      @return The Sqrteps constant for the proper type
    **/
    Value Sqrteps();
  }
} }
#endif

#include <boost/simd/constant/definition/sqrteps.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
