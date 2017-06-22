//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_INVLOG_10_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_INVLOG_10_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Invlog_10 Invlog_10 (function template)

  Generates constant \f$\frac{1}{\log(10)}\f$.

  @headerref{<boost/simd/constant/invlog_10.hpp>}

  @par Description

  1.  @code
      template<typename T> T Invlog_10();
      @endcode

  2.  @code
      template<typename T> T Invlog_10( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to \frac{1}{\log(10)}.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to `T(0.434294481903251827651128918916605082294397005803666)`.

  @par Requirements
  - **T** models IEEEValue
**/

#include <boost/simd/constant/scalar/invlog_10.hpp>
#include <boost/simd/constant/simd/invlog_10.hpp>

#endif
