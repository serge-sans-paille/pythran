//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SHL_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SHL_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!

    @ingroup group-operator
     This function object returns the first operand shifted left by the second one

    Infix notation can be used with operator '<<'

    @par Header <boost/simd/function/shl.hpp>

    This is an alias of @ref shift_left
  **/
  Value shl(Value const& x, IntegerValue const& n);
} }
#endif

#include <boost/simd/function/scalar/shift_left.hpp>
#include <boost/simd/function/simd/shl.hpp>

#endif
