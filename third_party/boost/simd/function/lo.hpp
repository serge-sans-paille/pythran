//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_LO_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_LO_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-bitwise
    This function object returns the low part of the entry
    as an unsigned integer of the size of
    the input.

    @par Header <boost/simd/function/lo.hpp>

    @see  hi

    @par Header <boost/simd/function/lo.hpp>

    @par Example:

      @snippet lo.cpp lo

    @par Possible output:

      @snippet lo.txt lo

  **/
  as_integer_t<Value> lo(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/lo.hpp>
#include <boost/simd/function/simd/lo.hpp>

#endif
