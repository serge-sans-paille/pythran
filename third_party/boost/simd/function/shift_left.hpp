//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SHIFT_LEFT_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SHIFT_LEFT_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!

    @ingroup group-operator
    This function object returns the first parameter shifted left by the second one

    Infix notation can be used with operator '<<'

    @par Header <boost/simd/function/shift_left.hpp>

      @pre the second parameter must be of integer type scalar or associated to
      the first parameter

    @par Note:
      - on many architectures a scalar second parameter results in a much faster call

    @par alias shl

    @see  shift_right, shr, rshl, rshr, rol, ror


   @par Example:

      @snippet shift_left.cpp shift_left

    @par Possible output:

      @snippet shift_left.txt shift_left

  **/
  Value shift_left(Value const& x, IntegerValue const& n);
} }
#endif

#include <boost/simd/function/scalar/shift_left.hpp>
#include <boost/simd/function/simd/shift_left.hpp>

#endif
