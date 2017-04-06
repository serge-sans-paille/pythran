//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IS_NEZ_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IS_NEZ_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-predicates

    This function object returns @ref True if x is not equal to @ref Zero else returns @ref False.


    @par Header <boost/simd/function/is_nez.hpp>

    @par Note

     Using `is_nez(x)` is similar to: `x != 0`

    @par Example:

      @snippet is_nez.cpp is_nez

    @par Possible output:

      @snippet is_nez.txt is_nez

  **/
  as_logical_t<Value> is_nez(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/is_nez.hpp>
#include <boost/simd/function/simd/is_nez.hpp>

#endif
