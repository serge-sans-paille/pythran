//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_FACT_6_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_FACT_6_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generates 6! that is 720

    @par Semantic:

    @code
    T r = Fact_6<T>();
    @endcode

    is similar to:

    @code
    T r = T(720);
    @endcode

    @return The Fact_6 constant for the proper type
  **/
  template<typename T> T Fact_6();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generate the  constant fact_6.

      @return The Fact_6 constant for the proper type
    **/
    const boost::dispatch::functor<tag::fact_6_> fact_6 = {};
  }
} }
#endif

#include <boost/simd/constant/definition/fact_6.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
