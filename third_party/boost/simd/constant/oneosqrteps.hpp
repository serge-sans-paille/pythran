//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_ONEOSQRTEPS_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_ONEOSQRTEPS_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generate \f$1/\sqrt\epsilon\f$

    @par Semantic:

    @code
    T r = Oneosqrteps<T>();
    @endcode

    is similar to:

    @code
    if T is integral
      r = T(0)
    else if T is double
      r =  pow(2.0, 26);
    else if T is float
      r =  pow(2.0f, 11.5);
    @endcode


    @return The Oneosqrteps constant for the proper type
  **/
  template<typename T> T Oneosqrteps();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generate the  constant oneosqrteps.

      @return The Oneosqrteps constant for the proper type
    **/
    Value Oneosqrteps();
  }
} }
#endif

#include <boost/simd/constant/definition/oneosqrteps.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
