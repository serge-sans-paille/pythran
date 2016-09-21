//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_FACT_12_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_FACT_12_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generate 12! that is 479001600

    @par Semantic:

    @code
    T r = Fact_12<T>();
    @endcode

    is similar to:

    @code
    T r = T(479001600);
    @endcode

    @return The Fact_12 constant for the proper type
  **/
  template<typename T> T Fact_12();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generate the  constant fact_12.

      @return The Fact_12 constant for the proper type
    **/
    Value Fact_12<Value>();
  }
} }
#endif

#include <boost/simd/constant/definition/fact_12.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
