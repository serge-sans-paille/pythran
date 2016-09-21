//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_LOGICAL_NOTAND_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_LOGICAL_NOTAND_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-boolean
    Function object implementing logical_notand capabilities

    return the logical and of the negation of the first parameter and the second parameter

    The operands must share the same @ref cardinal_of value.

    The result type is logical type associated to the first parameter.

    @par Semantic:

    @code
    auto r = logical_notand(x,y);
    @endcode

    is similar to:

    @code
    auto r = !x && y;
    @endcode

    @see  logical_or, logical_xor, logical_and,
    logical_andnot, logical_notor, logical_ornot, logical_not

  **/
  as_logical_t<Value0> logical_notand(Value0 const& x, Value1 const& y);
} }
#endif

#include <boost/simd/function/scalar/logical_notand.hpp>
#include <boost/simd/function/simd/logical_notand.hpp>

#endif
