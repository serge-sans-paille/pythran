//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_LOG10_PI_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_LOG10_PI_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-constant

    Generate base ten logarithm of pi (\f$\log\!10(\pi)\f$)

    @par Semantic:

    @code
    T r = Log10_pi<T>();
    @endcode

    is similar to:

    @code
    T r = log10(Pi<T>());
    @endcode

    @return The Log10_pi constant for the proper type
  **/
  template<typename T> T Log10_pi();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant
      Generate the  constant log10_pi.

      @return The Log10_pi constant for the proper type
    **/
    const boost::dispatch::functor<tag::log10_pi_> log10_pi = {};
  }
} }
#endif

#include <boost/simd/constant/definition/log10_pi.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
