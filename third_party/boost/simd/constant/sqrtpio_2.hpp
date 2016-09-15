//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_SQRTPIO_2_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_SQRTPIO_2_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!

    @ingroup group-constant

    Constant Sqrtpio_2 : \f$\frac{\sqrt\pi}{2}\f$.

    @par Semantic:

    For type T:

    @code
    T r = sqrtpio_2<T>();
    @endcode

    is similar to:

    @code
    T r = sqrt(Two<T>())/Pi<T>();
    @endcode

    @return a value of type T

**/
  template<typename T> T Sqrtpio_2();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant


      Constant Sqrtpio_2 : \f$\frac{\sqrt\pi}{2}\f$.

      Generate the  constant sqrtpio_2.

      @return The Sqrtpio_2 constant for the proper type
    **/
    const boost::dispatch::functor<tag::sqrtpio_2_> sqrtpio_2 = {};
  }
} }
#endif

#include <boost/simd/constant/definition/sqrtpio_2.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
