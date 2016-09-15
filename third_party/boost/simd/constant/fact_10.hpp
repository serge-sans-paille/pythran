//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_FACT_10_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_FACT_10_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generate 10! that is 3628800

    @par Semantic:

    @code
    T r = Fact_10<T>();
    @endcode

    is similar to:

    @code
    T r = T(3628800);
    @endcode

    @return The Fact_10 constant for the proper type
  **/
  template<typename T> T Fact_10();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generate the  constant fact_10.

      @return The Fact_10 constant for the proper type
    **/
    Value Fact_10(Value const& x);
  }
} }
#endif

#include <boost/simd/constant/definition/fact_10.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
