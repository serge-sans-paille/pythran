//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_MAXINIT_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_MAXINIT_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Maxinit Maxinit (function template)

  Generates the constant maxinit which is identical to minf for
  arithmetic real types but that must be specialized for complex values ordering.
  maxinit is the value to be returned when a maximum of the elements function
  is used on an  empty container.

  @headerref{<boost/simd/constant/maxinit.hpp>}

  @par Description

  1.  @code
      template<typename T> T Maxinit();
      @endcode

  2.  @code
      template<typename T> T Maxinit( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T containing the Maxinit constant.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to `Minf<T>()`.

  @par Requirements
  - **T** models Value
**/

#include <boost/simd/constant/scalar/maxinit.hpp>
#include <boost/simd/constant/simd/maxinit.hpp>

#endif
