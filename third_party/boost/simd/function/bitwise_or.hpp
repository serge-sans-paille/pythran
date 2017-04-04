//==================================================================================================
/*!
  @file

  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_BITWISE_OR_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_BITWISE_OR_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-bitwise
    This function object returns the return the bitwise or of the two parameters

    The result type is the one of the first operand.

    Infix notation can be used with operator '|',
    but this will not work in scalar mode if any
    operand is floating point because of C++ limitations.

    @par Header <boost/simd/function/bitwise_or.hpp>

    @pre  The operands must share the same bit size.

    @par Example:

      @snippet bitwise_or.cpp bitwise_or

    @par Possible output:

      @snippet bitwise_or.txt bitwise_or

  **/
  Value0 bitwise_or(Value0 const& x, Value1 const& y);
} }
#endif

#include <boost/simd/function/scalar/bitwise_or.hpp>
#include <boost/simd/arch/common/scalar/function/bitwise_or.hpp>
#include <boost/simd/function/simd/bitwise_or.hpp>

#endif
