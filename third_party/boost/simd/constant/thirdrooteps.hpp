//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_THIRDROOTEPS_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_THIRDROOTEPS_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generate the cubic root of @ref Eps

    @par Semantic:

    @code
    T r = Thirdrooteps<T>();
    @endcode

    is similar to:

    @code
    if T is integral
      r = 1
    else if T is double
      r =  6.055454452393343e-06;
    else if T is float
      r =  4.9215667e-03 ;
    @endcode

    @return The Thirdrooteps constant for the proper type
  **/
  template<typename T> T Thirdrooteps();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generate the  constant thirdrooteps.

      @return The Thirdrooteps constant for the proper type
    **/
    Value Thirdrooteps();
  }
} }
#endif

#include <boost/simd/constant/definition/thirdrooteps.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
