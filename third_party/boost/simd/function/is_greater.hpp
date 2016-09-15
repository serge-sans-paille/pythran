//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IS_GREATER_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IS_GREATER_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-predicates
    Function object implementing is_greater capabilities

    Returns @ref True or @ref False according x is greater than y or not.

    Infix notation can be used with operator '>'.

    @par Semantic:

    @code
    auto r = is_greater(x,y);
    @endcode

    is similar to:

    @code
    auto r = x > y;
    @endcode

    @see  is_greater_equal, is_gtz, is_nle, is_nle

  **/
  as_logical_t<Value> is_greater(Value const& x, Value const& y);
} }
#endif

#include <boost/simd/function/scalar/is_greater.hpp>
#include <boost/simd/function/simd/is_greater.hpp>

#endif
