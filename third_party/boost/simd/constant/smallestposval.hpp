//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_SMALLESTPOSVAL_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_SMALLESTPOSVAL_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Smallestposval Smallestposval (function template)

  Generates the least non zero, non denormal, positive value.

  @headerref{<boost/simd/constant/smallestposval.hpp>}

  @par Description

  1.  @code
      template<typename T> T Smallestposval();
      @endcode

  2.  @code
      template<typename T> T Smallestposval( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to the smallest positive, non-denormal value of
  type @c T.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c as_integer_t<T> that evaluates to

  | Type            | double                        | float         | Integral        |
  |:----------------|:------------------------------|---------------|-----------------|
  | **Values**      |   2.225073858507201e-308      | 1.1754944e-38 |  1              |

  @par Requirements
  - **T** models Value
**/

#include <boost/simd/constant/scalar/smallestposval.hpp>
#include <boost/simd/constant/simd/smallestposval.hpp>

#endif
