//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_SQRTSMALLESTPOSVAL_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_SQRTSMALLESTPOSVAL_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Sqrtsmallestposval Sqrtsmallestposval (function template)

  Generates the square root of the least non-zero, positive, non-denormal value.

  @headerref{<boost/simd/constant/sqrtsmallestposval.hpp>}

  @par Description

  1.  @code
      template<typename T> T Sqrtsmallestposval();
      @endcode

  2.  @code
      template<typename T> T Sqrtsmallestposval( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to the square root of the least non-zero,
  positive, non-denormal value of type @c T.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to:

  | Type         | double                        | float          | Integral        |
  |:-------------|:------------------------------|----------------|-----------------|
  | **Values**   |   1.491668146240041e-154      | 1.0842022e-19f |  1              |

  @par Requirements
  - **T** models Value
**/

#include <boost/simd/constant/scalar/sqrtsmallestposval.hpp>
#include <boost/simd/constant/simd/sqrtsmallestposval.hpp>

#endif
