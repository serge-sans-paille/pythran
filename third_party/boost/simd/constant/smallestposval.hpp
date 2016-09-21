//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_SMALLESTPOSVAL_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_SMALLESTPOSVAL_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generate the least non zero, non denormal, positive value.

    @par Semantic:

    @code
    T r = Smallestposval<T>();
    @endcode

    is similar to:

    @code
    if T is integral
      r = 1
    else if T is double
      r =  2.225073858507201e-308;
    else if T is float
      r =  1.1754944e-38;
    @endcode

    @return The Smallestposval constant for the proper type
  **/
  template<typename T> T Smallestposval();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generate the  constant smallestposval.

      @return The Smallestposval constant for the proper type
    **/
    Value Smallestposval();
  }
} }
#endif

#include <boost/simd/constant/definition/smallestposval.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
