//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_UNARY_PLUS_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_UNARY_PLUS_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!

    @ingroup group-operator
    This function object returns the elementwise unary plus of the parameter

    Infix notation can be used with operator '+'


    @par Header <boost/simd/function/unary_plus.hpp>

    @par Note:

    - `r = unary_plus(x)` is equivalent to  `r = +x` for SIMD types.

    @warningbox{Take care that the infix notation in scalar integral mode encurs
    a possible promotion of the type as C++ rules state.}

    @see  plus, unary_minus

    @par Example:

      @snippet unary_plus.cpp unary_plus

    @par Possible output:

      @snippet unary_plus.txt unary_plus

  **/
  Value unary_plus(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/unary_plus.hpp>
#include <boost/simd/function/simd/unary_plus.hpp>

#endif
