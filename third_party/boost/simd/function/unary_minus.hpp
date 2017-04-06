//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_UNARY_MINUS_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_UNARY_MINUS_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!

    @ingroup group-operator
    This function object returns the elementwise unary minus of the parameter

    Infix notation can be used with operator '-'


    @par Header <boost/simd/function/unary_minus.hpp>

    @par Note:

    - `r = unary_minus(x)` is equivalent to  `r = -x` for SIMD types.

    @warningbox{Take care that the infix notation in scalar integral mode encurs
    a possible promotion of the type as C++ rules state.}


    @par Decorators
    - `saturated_` ensures that `saturated_(unary_minus)(Valmin<T>())` is `Valmin<T>()`

    @see  minus, unary_plus

    @par Example:

      @snippet unary_minus.cpp unary_minus

    @par Possible output:

      @snippet unary_minus.txt unary_minus

  **/
  Value unary_minus(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/unary_minus.hpp>
#include <boost/simd/function/simd/unary_minus.hpp>

#endif
