//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_LOGICAL_ANDNOT_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_LOGICAL_ANDNOT_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-boolean
    Function object implementing logical_andnot capabilities

    The operands must share the same @ref cardinal_of value.

    return the logical and of the first parameter and of the negation the second parameter.

    The operands must share the same @ref cardinal_of value.

    The result type is logical type associated to the first parameter.

    @par Semantic:

    @code
    auto r = logical_andnot(x,y);
    @endcode

    is similar to:

    @code
    auto r = x && !y;
    @endcode

    @see  logical_or, logical_xor, logical_notand,
    logical_and, logical_notor, logical_ornot, logical_not

  **/
  as_logical_t<Value0> logical_andnot(Value0 const& x, Value1 const& y);
} }
#endif

#include <boost/simd/function/scalar/logical_andnot.hpp>
#include <boost/simd/function/simd/logical_andnot.hpp>

#endif
