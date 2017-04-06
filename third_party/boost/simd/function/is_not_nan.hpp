//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IS_NOT_NAN_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IS_NOT_NAN_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-predicates

    This function object returns @ref False or @ref True according x is @ref Nan or not.


    @par Header <boost/simd/function/is_not_nan.hpp>

    @par Note

     Using `is_not_nan(x)` is similar to: `x == x`

    @par Example:

      @snippet is_not_nan.cpp is_not_nan

    @par Possible output:

      @snippet is_not_nan.txt is_not_nan

  **/
  as_logical_t<Value> is_not_nan(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/is_not_nan.hpp>
#include <boost/simd/function/simd/is_not_nan.hpp>

#endif
