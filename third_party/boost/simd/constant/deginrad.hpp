//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEGINRAD_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEGINRAD_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!

    @ingroup group-constant

    Constant radian in Degree multiplier, \f$\frac{180}\pi\f$.

    @par Semantic:

    For type T:

    @code
    T r = Deginrad<T>();
    @endcode

    is similar to:

    @code
    T r = Ratio<T, 180>()/Pi<T>() ;
    @endcode

    @see  inrad, indeg, Radindeg, Radindegr, Ratio
    @return a value of type T

**/
  template<typename T> T Deginrad();

  namespace functional
  {
    /*!
      @ingroup group-callable-constant


      Constant radian in Degree multiplier, \f$\frac{180}\pi\f$.

      Generate the  constant deginrad.

      @return The Deginrad constant for the proper type
    **/
    Value Deginrad();
  }
} }
#endif

#include <boost/simd/constant/definition/deginrad.hpp>
#include <boost/simd/arch/common/scalar/constant/constant_value.hpp>
#include <boost/simd/arch/common/simd/constant/constant_value.hpp>

#endif
