//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_RSHL_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_RSHL_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-bitwise
    This function object returns the first entry shifted left or right
    by the absolute value of the second entry,
    according to its sign.

    @see  rshr, shr, shl



    @par Header <boost/simd/function/rshl.hpp>

    @par Example:

      @snippet rshl.cpp rshl

    @par Possible output:

      @snippet rshl.txt rshl

  **/
  Value rshl(Value const& x, IntegerValue const& n);
} }
#endif

#include <boost/simd/function/scalar/rshl.hpp>
#include <boost/simd/function/simd/rshl.hpp>

#endif
