//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_IFLOOR_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_IFLOOR_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!

    @ingroup group-arithmetic
    This function object computes the integer conversion of the @ref floor of its parameter.


    @par Header <boost/simd/function/ifloor.hpp>

    @par Note:
    This operation is properly saturated

    @see floor, ifloor, iround, ifix, inearbyint

    @par Example:

      @snippet ifloor.cpp ifloor

    @par Possible output:

      @snippet ifloor.txt ifloor

  **/
  as_integer_t<Value> ifloor(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/ifloor.hpp>
#include <boost/simd/function/simd/ifloor.hpp>

#endif
