//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_TAN_3PIO_8_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_TAN_3PIO_8_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Tan_3pio_8 Tan_3pio_8 (function template)

  Generates the constant \f$\tan\frac{3\pi}{8}\f$

  @headerref{<boost/simd/constant/tan_3pio_8.hpp>}

  @par Description

  1.  @code
      template<typename T> T Tan_3pio_8();
      @endcode

  2.  @code
      template<typename T> T Tan_3pio_8( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to \f$\tan\frac{3\pi}{8}\f$, i.e \f$\sqrt2 + 1\f$.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to  `T(2.4142135623730950488016887242097)`

  @par Requirements
  - **T** models IEEEValue
**/

#include <boost/simd/constant/scalar/tan_3pio_8.hpp>
#include <boost/simd/constant/simd/tan_3pio_8.hpp>

#endif
