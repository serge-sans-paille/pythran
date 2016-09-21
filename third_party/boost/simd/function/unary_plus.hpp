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
    Function object implementing unary_plus capabilities

    return the elementwise unary plus of the parameter

    Infix notation can be used with operator '+'

    @par Semantic:

    @code
    auto r = unary_plus(x);
    @endcode

    or

    @code
    auto r = +x;
    @endcode

    @warningbox{Take care that the infix notation in scalar integral mode encurs
    a possible promotion of the type as C++ rules state.}

    @see  plus, unary_minus

  **/
  Value unary_plus(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/unary_plus.hpp>
#include <boost/simd/function/simd/unary_plus.hpp>

#endif
