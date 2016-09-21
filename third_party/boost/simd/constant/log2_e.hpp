//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_LOG2_E_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_LOG2_E_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!

    @ingroup group-constant

    Generates constant Log2_e.This constant is coupled with Log2_lo and is
    used in the float logarithms computations
    We have double(Log2_e<float>())+double(Log2_lo<float>()) == Log_2<double>()

    @par Semantic:

    @code
    T r = log2_e<T>();
    @endcode


**/
  template<typename T> T Log2_e();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant


      Generates constant Log2_e.This constant is coupled with Log2_lo and is
      used in the float logarithms computations
      We have double(Log2_e<float>())+double(Log2_lo<float>()) == Log_2<double>()

      Generate the  constant log2_e.

      @return The Log2_e constant for the proper type
    **/
    Value log2_e<Value>();
  }
} }
#endif

#include <boost/simd/constant/definition/log2_e.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
