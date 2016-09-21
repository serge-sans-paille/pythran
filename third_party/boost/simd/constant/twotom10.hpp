//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_TWOTOM10_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_TWOTOM10_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generate 2 to the power -10 (\f$2^{-10}\f$)

    @par Semantic:

    @code
    T r = Twotom10<T>();
    @endcode

    is similar to:

    @code
    T r = pow(2, -10);
    @endcode

    @return The Twotom10 constant for the proper type
  **/
  template<typename T> T Twotom10();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generate the  constant twotom10.

      @return The Twotom10 constant for the proper type
    **/
    const boost::dispatch::functor<tag::twotom10_> twotom10 = {};
  }
} }
#endif

#include <boost/simd/constant/definition/twotom10.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
