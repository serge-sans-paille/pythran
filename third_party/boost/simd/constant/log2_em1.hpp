//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_CONSTANT_LOG2_EM1_HPP_INCLUDED
#define BOOST_SIMD_CONSTANT_LOG2_EM1_HPP_INCLUDED

/*!
  @ingroup group-constant
  @defgroup constant-Log2_em1 Log2_em1 (function template)

  Generates the constant \f$\log_2(e)-1\f$

  @headerref{<boost/simd/constant/log2_em1.hpp>}

  @par Description

  1.  @code
      template<typename T> T Log2_em1();
      @endcode

  2.  @code
      template<typename T> T Log2_em1( boost::simd::as_<T> const& target );
      @endcode

  Generates a value of type @c T that evaluates to \f$\log_2(e)-1\f$.

  @par Parameters

  | Name                | Description                                                         |
  |--------------------:|:--------------------------------------------------------------------|
  | **target**          | a [placeholder](@ref type-as) value encapsulating the constant type |

  @par Return Value
  A value of type @c T that evaluates to `T(0.44269504088896340735992468100189)`

  @par Requirements
  - **T** models IEEEValue
**/

#include <boost/simd/constant/scalar/log2_em1.hpp>
#include <boost/simd/constant/simd/log2_em1.hpp>

#endif
