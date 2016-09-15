//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_FACT_11_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_FACT_11_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generate 11! that is 39916800,

    @par Semantic:

    @code
    T r = Fact_11<T>();
    @endcode
    is similar to:

    @code
    T r = T(39916800);
    @endcode

    @return The Fact_11 constant for the proper type
  **/
  template<typename T> T Fact_11();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generate the  constant fact_11.

      @return The Fact_11 constant for the proper type
    **/
    const boost::dispatch::functor<tag::fact_11_> fact_11 = {};
  }
} }
#endif

#include <boost/simd/constant/definition/fact_11.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
