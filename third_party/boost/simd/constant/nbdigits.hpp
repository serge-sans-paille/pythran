//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_NBDIGITS_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_NBDIGITS_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generate the number of mantissa bits of a floating point number,
    and the total number of bits for integral types.

    @par Semantic:

    @code
    T r = Nbdigits<T>();
    @endcode

    is similar to:

    @code
    if T is integral
      r = sizeof(T)*8
    else if T is double
      r =  53;
    else if T is float
      r =  24;
    @endcode

    @return The Nbdigits constant for the proper type
  **/
  template<typename T> T Nbdigits();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generate the  constant nbdigits.

      @return The Nbdigits constant for the proper type
    **/
    Value Nbdigits();
  }
} }
#endif

#include <boost/simd/constant/definition/nbdigits.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
