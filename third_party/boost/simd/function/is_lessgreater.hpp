//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IS_LESSGREATER_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IS_LESSGREATER_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-predicates

    This function object returns @ref True if neither x nor y is @ref Nan and x is not equal to y.


    @par Header <boost/simd/function/is_lessgreater.hpp>

    @par Note

     Using `is_lessgreater(x,y)` is similar to: `(x == x) && (y == y) && (x!= y)`

    @par Decorators

     - std_ can be used to call std::islessgreater

    @par Example:

      @snippet is_lessgreater.cpp is_lessgreater

    @par Possible output:

      @snippet is_lessgreater.txt is_lessgreater

  **/
  as_logical_t<Value> is_lessgreater(Value const& x, Value const& y);
} }
#endif

#include <boost/simd/function/scalar/is_lessgreater.hpp>
#include <boost/simd/function/simd/is_lessgreater.hpp>

#endif
