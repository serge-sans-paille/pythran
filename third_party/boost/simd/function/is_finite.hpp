//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IS_FINITE_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IS_FINITE_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!

    @ingroup group-predicates
    This function object returns @ref True if x is not inf, -inf or nan, else returns @ref False.


    @par Header <boost/simd/function/is_finite.hpp>

    @par Note

    Using `is_finite(x)` is similar to `x-x == Zero`

    @par Alias:
    is_not_invalid

    @par Example:

      @snippet is_finite.cpp is_finite

    @par Possible output:

      @snippet is_finite.txt is_finite

  **/
  as_logical_t<Value> is_finite(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/is_finite.hpp>
#include <boost/simd/function/simd/is_finite.hpp>

#endif
