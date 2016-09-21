//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_MINDENORMAL_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_MINDENORMAL_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generate the the least of all non zero positive value including denormals.

    @par Semantic:

    @code
    T r = Mindenormal<T>();
    @endcode

    is similar to:

    @code
    if T is integral
      r = T(1)
    else if T is double
      r =  4.940656458412465e-324;
    else if T is float
      r = 1.4012985e-45;
    @endcode

    @return The Mindenormal constant for the proper type
  **/
  template<typename T> T Mindenormal();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generate the  constant mindenormal.

      @return The Mindenormal constant for the proper type
    **/
    Value Mindenormal();
  }
} }
#endif

#include <boost/simd/constant/definition/mindenormal.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
