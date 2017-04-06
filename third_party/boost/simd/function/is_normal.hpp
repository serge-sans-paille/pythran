//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IS_NORMAL_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IS_NORMAL_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-predicates

    This function object returns @ref True or @ref False according x is normal or not.


    @par Header <boost/simd/function/is_normal.hpp>

    @par Note

     Using  `is_normal(x)` is similar to `!(is_denormal(x) || is_invalid(x) || !(x == 0)`

    @par Example:

      @snippet is_normal.cpp is_normal

    @par Possible output:

      @snippet is_normal.txt is_normal

  **/
  as_logical_t<Value> is_normal(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/is_normal.hpp>
#include <boost/simd/function/scalar/is_normal.hpp>
#include <boost/simd/function/simd/is_normal.hpp>

#endif
