//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_MLOG10TWO2NMB_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_MLOG10TWO2NMB_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Mlog10two2nmb Mlog10two2nmb (function template)

  Generates the opposite of the base 10 logarithm of [Two2nmb](@ref constant-Twotonmb)

  @headerref{<boost/simd/constant/mlog10two2nmb.hpp>}

  @par Description

  1.  @code
      template<typename T> T Mlog10two2nmb();
      @endcode

  2.  @code
      template<typename T> T Mlog10two2nmb( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to `-log10(Two2nmb<T>())`.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to

  | Type          | double                                   | float                               |
  |:--------------|:-----------------------------------------|-------------------------------------|
  | **Values**    |  -15.653559774527022151114422525674      | -6.9236899002715674899159945786633f |

  @par Requirements
  - **T** models IEEEValue
**/

#include <boost/simd/constant/scalar/mlog10two2nmb.hpp>
#include <boost/simd/constant/simd/mlog10two2nmb.hpp>

#endif
