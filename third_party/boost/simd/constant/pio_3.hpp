//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_PIO_3_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_PIO_3_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Pio_3 Pio_3 (function template)

  Generates the constant \f$\frac\pi{3}\f$.

  @headerref{<boost/simd/constant/pio_3.hpp>}

  @par Description

  1.  @code
      template<typename T> T Pio_3();
      @endcode

  2.  @code
      template<typename T> T Pio_3( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T  that evaluates to \f$\frac\pi{3}\f$.


  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to `T(1.0471975511965977461542144610932)`

  @par Requirements
  - **T** models IEEEValue
**/

#include <boost/simd/constant/scalar/pio_3.hpp>
#include <boost/simd/constant/simd/pio_3.hpp>

#endif
