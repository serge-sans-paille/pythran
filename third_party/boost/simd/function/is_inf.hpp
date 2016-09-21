//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IS_INF_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IS_INF_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-predicates
    Function object implementing is_inf capabilities

    Returns @ref True if x is inf or -inf else returns @ref False.

    @par Semantic:

    @code
    auto r = is_inf(x);
    @endcode

    is similar to:

    @code
    auto r = (x == Inf) || (x == -Inf);
    @endcode

  **/
  as_logical_t<Value> is_inf(Value const& x);
  as_logical_t<Value> is_inf(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/is_inf.hpp>
#include <boost/simd/function/simd/is_inf.hpp>

#endif
