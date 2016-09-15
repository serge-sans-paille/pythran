//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_LOG2_EM1_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_LOG2_EM1_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!

    @ingroup group-constant

    Generates constant Log2_em1 : \f$\log2(e)-1\f$

    @par Semantic:

    @code
    T r = log2_em1<T>();
    @endcode


**/
  template<typename T> T Log2_em1();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant


      Generates constant Log2_em1. (\f$\log2(e)-1\f$)

      Generate the  constant log2_em1.

      @return The Log2_em1 constant for the proper type
    **/
    Value log2_em1<Value>();
  }
} }
#endif

#include <boost/simd/constant/definition/log2_em1.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
