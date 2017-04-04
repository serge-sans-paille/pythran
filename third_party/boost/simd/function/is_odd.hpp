//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IS_ODD_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IS_ODD_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-predicates

    This function object returns @ref True or @ref False according x is odd or not.


    @par Header <boost/simd/function/is_odd.hpp>

    @par Note

     Using `is_odd(x)` is similar to: `is_even(x-One(as(x))`

    @par Example:

      @snippet is_odd.cpp is_odd

    @par Possible output:

      @snippet is_odd.txt is_odd

  **/
  as_logical_t<Value> is_odd(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/is_odd.hpp>
#include <boost/simd/function/simd/is_odd.hpp>

#endif
