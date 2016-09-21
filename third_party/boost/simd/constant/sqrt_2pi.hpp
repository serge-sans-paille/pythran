//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_SQRT_2PI_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_SQRT_2PI_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!

    @ingroup group-constant

    Constant \f$\sqrt{2\pi}\f$.

    @par Semantic:

    For type T:

    @code
    T r = Sqrt_2pi<T>();
    @endcode

    is similar to:

    @code
    T r = sqrt(Pix2<T>();
    @endcode

    @return a value of type T

**/
  template<typename T> T Sqrt_2pi();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant


      Constant \f$\sqrt{2\pi}\f$.

      Generate the  constant sqrt_2pi.

      @return The Sqrt_2pi constant for the proper type
    **/
    const boost::dispatch::functor<tag::sqrt_2pi_> sqrt_2pi = {};
  }
} }
#endif

#include <boost/simd/constant/definition/sqrt_2pi.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
