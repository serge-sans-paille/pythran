//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_PIO_2_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_PIO_2_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Pio_2 Pio_2 (function template)

  Generates the constant \f$\frac\pi{2}\f$.

  @headerref{<boost/simd/constant/pio_2.hpp>}

  @par Description

  1.  @code
      template<typename T> T Pio_2();
      @endcode

  2.  @code
      template<typename T> T Pio_2( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to \f$\frac\pi{2}\f$.


  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to `T(1.5707963267948966192313216916398)`

  @par Requirements
  - **T** models IEEEValue
**/

#include <boost/simd/constant/scalar/pio_2.hpp>
#include <boost/simd/constant/simd/pio_2.hpp>

#endif
