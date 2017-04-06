//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IS_NAN_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IS_NAN_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-predicates

    This function object returns @ref True or @ref False according x is nan or not.


    @par Header <boost/simd/function/is_nan.hpp>

    @par Note

     Using `is_nan(x)` is similar to `x != x`

    @par Example:

      @snippet is_nan.cpp is_nan

    @par Possible output:

      @snippet is_nan.txt is_nan

  **/
  as_logical_t<Value> is_nan(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/is_nan.hpp>
#include <boost/simd/function/simd/is_nan.hpp>

#endif
