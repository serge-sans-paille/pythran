//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IS_LESS_EQUAL_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IS_LESS_EQUAL_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-predicates
    Function object implementing is_less_equal capabilities

    Returns @ref True  or @ref False depending on whether x is
    less than or equal to y or not.

    Infix notation can be used with operator '<='.

    @par Semantic:

    @code
    auto r = is_less_equal(x,y);
    @endcode

    or

    @code
    auto r = x <= y;
    @endcode

    @see  is_equal, is_eqz

  **/
  as_logical_t<Value> is_less_equal(Value const& x, Value const& y);
} }
#endif

#include <boost/simd/function/scalar/is_less_equal.hpp>
#include <boost/simd/function/simd/is_less_equal.hpp>

#endif
