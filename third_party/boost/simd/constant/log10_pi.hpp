//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_LOG10_PI_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_LOG10_PI_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Log10_pi Log10_pi (function template)

  Generates the constant \f$\log_{10}(\pi)\f$

  @headerref{<boost/simd/constant/log10_pi.hpp>}

  @par Description

  1.  @code
      template<typename T> T Log10_pi();
      @endcode

  2.  @code
      template<typename T> T Log10_pi( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to \f$\log_{10}(\pi)\f$.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to `T(0.4971498726941338543512682882909)`.

  @par Requirements
  - **T** models IEEEValue
**/

#include <boost/simd/constant/scalar/log10_pi.hpp>
#include <boost/simd/constant/simd/log10_pi.hpp>

#endif
