//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IS_LESS_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IS_LESS_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-predicates
    Function object implementing is_less capabilities

    Returns  @ref True or @ref False according x is less than y or not.
    Infix notation can be used with operator '<'.

    @par Semantic:

    @code
    auto r = is_less(x,y);
    @endcode

    or

    @code
    auto r = x < y;
    @endcode

    @see  is_less_equal, is_ltz

  **/
  as_logical_t<Value> is_less(Value const& x, Value const& y);
} }
#endif

#include <boost/simd/function/scalar/is_less.hpp>
#include <boost/simd/function/simd/is_less.hpp>

#endif
