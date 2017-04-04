//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_BITWISE_NOTAND_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_BITWISE_NOTAND_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-bitwise
    This function object computes the bitwise not and of its parameters.

    The result type is the one of the first operand.

    @par Header <boost/simd/function/bitwise_notand.hpp>

    @pre  The operands must share the same bit size.

    @par Example:

      @snippet bitwise_notand.cpp bitwise_notand

    @par Possible output:

      @snippet bitwise_notand.txt bitwise_notand

  **/
  Value0 bitwise_notand(Value0 const& x, Value1 const& y);
} }
#endif

#include <boost/simd/function/scalar/bitwise_notand.hpp>
#include <boost/simd/function/simd/bitwise_notand.hpp>

#endif
