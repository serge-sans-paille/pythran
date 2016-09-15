//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_TWOTOMNMBO_3_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_TWOTOMNMBO_3_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!

    @ingroup group-constant

    Generates constant e.

    @par Semantic:
    \f$2^(-nmb/3)\f$

    @code
    T r = twotomnmbo_3<T>();
    @endcode

    is similar to:

    @code
    if T is float
      r = 4.921566601151848e-03f
    else
      r = 4.806217383937348e-06
    @endcode


**/
  template<typename T> T Twotomnmbo_3();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant


      Generates constant e.

      Generate the  constant twotomnmbo_3.

      @return The Twotomnmbo_3 constant for the proper type
    **/
    const boost::dispatch::functor<tag::twotomnmbo_3_> twotomnmbo_3 = {};
  }
} }
#endif

#include <boost/simd/constant/definition/twotomnmbo_3.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
