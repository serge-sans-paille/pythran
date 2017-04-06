//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IS_ORD_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IS_ORD_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-predicates

    This function object returns @ref True if neither x nor y is @ref Nan.


    @par Header <boost/simd/function/is_ord.hpp>

    @par Note

     Using `is_ord(x,y)` is similar to: `(x == x) && (y == y)`

    @par Example:

      @snippet is_ord.cpp is_ord

    @par Possible output:

      @snippet is_ord.txt is_ord

  **/
  as_logical_t<Value> is_ord(Value const& x, Value const& y);
} }
#endif

#include <boost/simd/function/scalar/is_ord.hpp>
#include <boost/simd/function/simd/is_ord.hpp>

#endif
