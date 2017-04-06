//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SHR_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SHR_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!

    @ingroup group-operator
    This function object returns the first parameter *logically* shifted right
    by value of the second one.

    @par Header <boost/simd/function/shr.hpp>

    @par Notes:
      - On many architectures a scalar second parameter results in a much faster call.
      - If the second entry is negative the result is not defined.

      @pre the second parameter must be of integer type, scalar or associated to
      the first parameter

    @par Note:
      - on many architectures a scalar second parameter results in a much faster call

    @see  shift_right, shift_left, rshl, rshr, rol, ror

    @par Example:

      @snippet shr.cpp shr

    @par Possible output:

      @snippet shr.txt shr

  **/
  Value shr(Value const& x, IntegerValue const& n);
} }
#endif

#include <boost/simd/function/scalar/shr.hpp>
#include <boost/simd/function/simd/shr.hpp>

#endif
