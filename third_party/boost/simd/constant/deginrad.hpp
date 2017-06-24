//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_DEGINRAD_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_DEGINRAD_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Deginrad Deginrad (function template)

  Generates the constant \f$\frac\pi{180}\f$.

  @headerref{<boost/simd/constant/deginrad.hpp>}

  @par Description

  1.  @code
      template<typename T> T Deginrad();
      @endcode

  2.  @code
      template<typename T> T Deginrad( boost::simd::as_<T> const& target );
      @endcode

  Generates the constant \f$\frac\pi{180}\f$ usable to convert degrees to radians.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to `Pi<T>()/180`.

  @par Requirements
  - **T** models IEEEValue
**/

#include <boost/simd/constant/scalar/deginrad.hpp>
#include <boost/simd/constant/simd/deginrad.hpp>

#endif
