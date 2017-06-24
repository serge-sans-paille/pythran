//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_PI_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_PI_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Pi Pi (function template)

  Generates the constant \f$\pi\f$.

  @headerref{<boost/simd/constant/pi.hpp>}

  @par Description

  1.  @code
    template<typename T> T Pi();
    @endcode

  2.  @code
    template<typename T> T Pi( boost::simd::as_<T> const& target );
    @endcode

  Generates a value of type @c T that evaluates to \f$\pi\f$.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to <tt>T(3.1415926535897932384626433832795)</tt>

  @par Requirements
  - **T** models IEEEValue
**/

#include <boost/simd/constant/scalar/pi.hpp>
#include <boost/simd/constant/simd/pi.hpp>

#endif
