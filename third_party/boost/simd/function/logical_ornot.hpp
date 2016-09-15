//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_LOGICAL_ORNOT_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_LOGICAL_ORNOT_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-boolean
    Function object implementing logical_ornot capabilities

    return the logical or of the first parameter and of the negation the second parameter.

    The operands must share the same @ref cardinal_of value.

    The result type is logical type associated to the first parameter.

    @par Semantic:

    @code
    auto r = logical_ornot(x,y);
    @endcode

    is similar to:

    @code
    as_logical_t<T2> r = x || !y;
    @endcode

    @see  logical_or, logical_xor, logical_notand,
    logical_andnot, logical_notor, logical_and, logical_not

  **/
  as_logical_t<Value0> logical_ornot(Value0 const& x, Value1 const& y);
} }
#endif

#include <boost/simd/function/scalar/logical_ornot.hpp>
#include <boost/simd/function/simd/logical_ornot.hpp>

#endif
