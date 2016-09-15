//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_FACT_7_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_FACT_7_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generate 7! that is 5040

    @par Semantic:

    @code
    T r = Fact_7<T>();
    @endcode

    is similar to:

    @code
    T r = T(5040);
    @endcode

    @return The Fact_7 constant for the proper type
  **/
  template<typename T> T Fact_7();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generate the  constant fact_7.

      @return The Fact_7 constant for the proper type
    **/
    const boost::dispatch::functor<tag::fact_7_> fact_7 = {};
  }
} }
#endif

#include <boost/simd/constant/definition/fact_7.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
