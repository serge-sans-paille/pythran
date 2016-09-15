//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_THREEEPS_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_THREEEPS_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generate  a value equal to 3 times @ref Eps of the chosen type

    @par Semantic:

    @code
    T r = Threeeps<T>();
    @endcode

    @code
    if T is integral
      r = 3
    else if T is double
      r =   6.661338147750939e-16;
    else if T is float
      r =  3.5762787e-07;
    @endcode

    @return The Threeeps constant for the proper type
  **/
  template<typename T> T Threeeps();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generate the  constant threeeps.

      @return The Threeeps constant for the proper type
    **/
    Value Threeeps();
  }
} }
#endif

#include <boost/simd/constant/definition/threeeps.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
