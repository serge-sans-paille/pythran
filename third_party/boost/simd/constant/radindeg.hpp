//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_RADINDEG_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_RADINDEG_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!

    @ingroup group-constant

    Constant Radindeg : Degree in Radian multiplier, \f$\frac\pi{180}\f$.

    @par Semantic:

    For type T:

    @code
    T r = Radindeg<T>();
    @endcode

    is similar to:

    @code
    T r = Pi<T>()/Ratio<T>(180);
    @endcode

    @see  inrad, indeg, Radindegr, Deginrad
    @return a value of type T

**/
  template<typename T> T Radindeg();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant


      Constant Radindeg : Degree in Radian multiplier, \f$\frac{180}\pi\f$.

      Generate the  constant radindeg.

      @return The Radindeg constant for the proper type
    **/
    Value Radindeg();
  }
} }
#endif

#include <boost/simd/constant/definition/radindeg.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
