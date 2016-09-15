//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_LOGICAL_AND_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_LOGICAL_AND_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-boolean
    Function object implementing logical_and capabilities

    return the logical and of the two parameters.

    The operands must share the same @ref cardinal_of value.

    Infix notation can be used with operator '&&'.

    @warningbox{Take care that using && in scalar mode does short-circuit and does not in simd mode.}

    @par Semantic:

    @code
    auto r = logical_and(x,y);
    @endcode

    is similar to:

    @code
    auto r = x && y ;
    @endcode


    @see  logical_or, logical_xor, logical_notand,
    logical_andnot, logical_notor, logical_ornot, logical_not

  **/
  as_logical_t<Value> logical_and(Value1 const& x, Value2 const& y);
} }
#endif

#include <boost/simd/function/scalar/logical_and.hpp>
#include <boost/simd/function/simd/logical_and.hpp>

#endif
