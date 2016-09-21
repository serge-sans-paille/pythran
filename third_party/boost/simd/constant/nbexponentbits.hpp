//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_NBEXPONENTBITS_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_NBEXPONENTBITS_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generate  the number of exponent bits of a floating point number,

    @par Semantic:

    @code
    T r = Nbexponentbits<T>();
    @endcode

    is similar to:

    @code
    if T is integral
      r = 0
    else if T is double
      r =  11;
    else if T is float
      r =  8;
    @endcode

    @return The Nbexponentbits constant for the proper type
  **/
  template<typename T> T Nbexponentbits();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generate the  constant nbexponentbits.

      @return The Nbexponentbits constant for the proper type
    **/
    Value Nbexponentbits();
  }
} }
#endif

#include <boost/simd/constant/definition/nbexponentbits.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
