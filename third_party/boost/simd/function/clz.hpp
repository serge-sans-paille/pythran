//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_CLZ_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_CLZ_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-bitwise
    This function object returns  the bit count of leading zeros.

    @par Header <boost/simd/function/clz.hpp>

    @see  ctz, popcnt

    @par Example:

      @snippet clz.cpp clz

    @par Possible output:

      @snippet clz.txt clz

  **/
  as_integer_t<Value> clz(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/clz.hpp>
#include <boost/simd/function/simd/clz.hpp>

#endif
