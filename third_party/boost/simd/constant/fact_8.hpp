//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_FACT_8_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_FACT_8_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generate 8! that is 40320

    @par Semantic:

    @code
    T r = Fact_8<T>();
    @endcode

    is similar to:

    @code
    T r = T(40320);
    @endcode


    @return The Fact_8 constant for the proper type
  **/
  template<typename T> T Fact_8();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generate the  constant fact_8.

      @return The Fact_8 constant for the proper type
    **/
    const boost::dispatch::functor<tag::fact_8_> fact_8 = {};
  }
} }
#endif

#include <boost/simd/constant/definition/fact_8.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
