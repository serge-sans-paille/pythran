//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SIGNBIT_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SIGNBIT_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!
  @ingroup group-arithmetic
    Function object implementing signbit capabilities

    True or false according to the bit of sign set or not set.

    This is a convenience alias of @ref is_negative used by stdlibc++.
  **/
  as_logical_t<Value> signbit(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/is_negative.hpp>
#include <boost/simd/function/simd/signbit.hpp>

#endif
