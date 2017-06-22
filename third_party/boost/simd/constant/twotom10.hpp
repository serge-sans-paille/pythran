//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_TWOTOM10_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_TWOTOM10_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Twotom10 Twotom10 (function template)

  Generates the constant \f$2^{-10}\f$

  @headerref{<boost/simd/constant/twotom10.hpp>}

  @par Description

  1.  @code
      template<typename T> T Twotom10();
      @endcode

  2.  @code
      template<typename T> T Twotom10( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to \f$2^{-10}\f$.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to <tt>T(0.0009765625)</tt>.

  @par Requirements
  - **T** models IEEEValue
**/

#include <boost/simd/constant/scalar/twotom10.hpp>
#include <boost/simd/constant/simd/twotom10.hpp>

#endif
