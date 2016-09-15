//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_INVSQRT_2PI_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_INVSQRT_2PI_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!

    @ingroup group-constant

    Constant  \f$\frac1{\sqrt{2\pi}}\f$.

    @par Semantic:

    For type T:

    @code
    T r = Invsqrt_2pi<T>();
    @endcode

    is similar to:

    @code
    T r = rsqrt(Two<T>()*Pi<T>());
    @endcode

    @return a value of type T

**/
  template<typename T> T Invsqrt_2pi();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant


      Constant  \f$\frac1{\sqrt{2\pi}}\f$.

      Generate the  constant invsqrt_2pi.

      @return The Invsqrt_2pi constant for the proper type
    **/
    const boost::dispatch::functor<tag::invsqrt_2pi_> invsqrt_2pi = {};
  }
} }
#endif

#include <boost/simd/constant/definition/invsqrt_2pi.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
