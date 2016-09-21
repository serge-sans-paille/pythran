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
    Function object implementing shl capabilities

    return left shift of the first operand by the second
    that must be of integer type and of the same number
    of elements as the first parameter
    Infix notation can be used with operator '<<'

    This is a convenience alias of @ref shift_left
  **/
  Value shl(Value const & v0, IntegerValue const& n);
} }
#endif

#include <boost/simd/function/scalar/shift_left.hpp>
#include <boost/simd/function/simd/shl.hpp>

#endif
