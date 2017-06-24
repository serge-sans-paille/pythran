//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_PIO_6_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_PIO_6_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Pio_6 Pio_6 (function template)

  Generates the constant \f$\frac\pi{6}\f$.

  @headerref{<boost/simd/constant/pio_6.hpp>}

  @par Description

  1.  @code
      template<typename T> T Pio_6();
      @endcode

  2.  @code
      template<typename T> T Pio_6( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to \f$\frac\pi{6}\f$.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to `T(0.52359877559829887307710723054658)`

  @par Requirements
  - **T** models IEEEValue
**/

#include <boost/simd/constant/scalar/pio_6.hpp>
#include <boost/simd/constant/simd/pio_6.hpp>

#endif
