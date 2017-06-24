//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_TWOTONMB_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_TWOTONMB_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Twotonmb Twotonmb (function template)

  Generates the constant \f$2^{Nbmantissabits<T>()}\f$.

  @headerref{<boost/simd/constant/twotonmb.hpp>}

  @par Description

  1.  @code
    template<typename T> T Twotonmb();
    @endcode

  2.  @code
    template<typename T> T Twotonmb( boost::simd::as_<T> const& target );
    @endcode

  Generates a constant that evaluates to \f$2^{Nbmantissabits<T>()}\f$.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to:

  | Type       | double                | float         |
  |:-----------|:----------------------|---------------|
  | **Values** | 4503599627370496.0    |  8388608.0f   |


  @par Requirements
  - **T** models IEEEValue
**/

#include <boost/simd/constant/scalar/twotonmb.hpp>
#include <boost/simd/constant/simd/twotonmb.hpp>

#endif
