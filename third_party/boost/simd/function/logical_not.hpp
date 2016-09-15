//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_LOGICAL_NOT_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_LOGICAL_NOT_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-boolean
    Function object implementing logical_not capabilities

    return the logical negation of the parameter,
    i.e. True or False of the logical type associated entry type according that
    the input is @ref Zero or non @ref Zero (False or True).

    Infix notation can be used with operator '!'

    @par Semantic:

    For every parameter of type @c T

    @code
    auto r = logical_not(x);
    @endcode

    is similar to:

    @code
    auto r =!x;
    @endcode

    @see  logical_or, logical_xor, logical_notand,
    logical_andnot, logical_notor, logical_ornot

  **/
  as_logical_t<Value0> logical_not(Value0 const& x, Value1 const& y);
} }
#endif

#include <boost/simd/function/scalar/logical_not.hpp>
#include <boost/simd/function/simd/logical_not.hpp>

#endif
