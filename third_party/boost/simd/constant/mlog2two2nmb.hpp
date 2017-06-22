//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_MLOG2TWO2NMB_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_MLOG2TWO2NMB_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Mlog2two2nmb Mlog2two2nmb (function template)

  Generates the opposite of the base 2 logarithm of [Two2nmb](@ref constant-Twotonmb)

  @headerref{<boost/simd/constant/mlog2two2nmb.hpp>}

  @par Description

  1.  @code
      template<typename T> T Mlog2two2nmb();
      @endcode

  2.  @code
      template<typename T> T Mlog2two2nmb( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to `-log2(Two2nmb<T>())`.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  @par Return Value
  A value of type @c T that evaluates to

  | Type           | double                        | float                  |
  |:---------------|:------------------------------|------------------------|
  | **Values**     |   -52.0                       | -23.0f                 |

  @par Requirements
  - **T** models IEEEValue
**/

#include <boost/simd/constant/scalar/mlog2two2nmb.hpp>
#include <boost/simd/constant/simd/mlog2two2nmb.hpp>

#endif
