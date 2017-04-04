//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IS_NLTZ_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IS_NLTZ_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-predicates

    This function object returns @ref True if x is not less than @ref Zero else returns @ref False.


    @par Header <boost/simd/function/is_nltz.hpp>

    @par Note

     Using `is_nltz(x)` is similar to: `!(x < 0)`

    @par Example:

      @snippet is_nltz.cpp is_nltz

    @par Possible output:

      @snippet is_nltz.txt is_nltz

  **/
  as_logical_t<Value> is_nltz(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/is_nltz.hpp>
#include <boost/simd/function/simd/is_nltz.hpp>

#endif
