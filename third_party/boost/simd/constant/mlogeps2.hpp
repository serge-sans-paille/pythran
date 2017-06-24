//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_MLOGEPS2_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_MLOGEPS2_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Mlogeps2 Mlogeps2 (function template)

  Generates the constant \f$-\log\epsilon^2\f$

  @headerref{<boost/simd/constant/mlogeps2.hpp>}

  @par Description

  1.  @code
      template<typename T> T Mlogeps2();
      @endcode

  2.  @code
      template<typename T> T Mlogeps2( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evalujates to \f$-\log\epsilon^2\f$.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to `-log(sqr(Eps<T>()))`.

  @par Requirements
  - **T** models IEEEValue
**/

#include <boost/simd/constant/scalar/mlogeps2.hpp>
#include <boost/simd/constant/simd/mlogeps2.hpp>

#endif
