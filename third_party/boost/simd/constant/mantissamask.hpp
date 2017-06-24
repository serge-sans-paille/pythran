//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_MANTISSAMASK_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_MANTISSAMASK_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Mantissamask Mantissamask (function template)

  Generates a bit patterns able to extract mantissa from IEEE values.

  @headerref{<boost/simd/constant/mantissamask.hpp>}

  @par Description

  1.  @code
      template<typename T> T Mantissamask();
      @endcode

  2.  @code
      template<typename T> T Mantissamask( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to a type-specific value that can be used
  to access the mantissa of an IEEE value when used as a bitwise mask.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to a value so that, for any value `x` of type @c T, the
  expression `bitwise_and(x, Mantissamask<T>()) == mantissa(x)` evaluates to @c true.

  When used as an IEEE value, `Mantissamask<T>()` evaluates to:

   | Type       | double                      | float                       |
   |:-----------|:----------------------------|-----------------------------|
   | **Values** |  2.225073858507200889e-308  | -1.1754942106924410755e-38f |

  @par Requirements
  - **T** models IEEEValue
**/

#include <boost/simd/constant/scalar/mantissamask.hpp>
#include <boost/simd/constant/simd/mantissamask.hpp>

#endif
