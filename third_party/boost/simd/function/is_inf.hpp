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

    This function object returns @ref True if x is inf or -inf else returns @ref False.


    @par Header <boost/simd/function/is_inf.hpp>

    @par Note

     Using `is_inf(x)` is similar to `(x == Inf) || (x == -Inf)`

    @par Example:

      @snippet is_inf.cpp is_inf

    @par Possible output:

      @snippet is_inf.txt is_inf

  **/
  as_logical_t<Value> is_inf(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/is_inf.hpp>
#include <boost/simd/function/simd/is_inf.hpp>

#endif
