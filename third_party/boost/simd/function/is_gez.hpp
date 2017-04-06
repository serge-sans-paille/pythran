//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IS_GEZ_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IS_GEZ_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!

    @ingroup group-predicates
    This function object returns @ref True or @ref False according x
    is greater or equal to @ref Zero or not.


    @par Header <boost/simd/function/is_gez.hpp>

    @par Note

      Using `is_gez(x)` is equivalent to `x >= 0`

    @par Example:

      @snippet is_gez.cpp is_gez

    @par Possible output:

      @snippet is_gez.txt is_gez

  **/
  as_logical_t<Value> is_gez(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/is_gez.hpp>
#include <boost/simd/function/simd/is_gez.hpp>

#endif
