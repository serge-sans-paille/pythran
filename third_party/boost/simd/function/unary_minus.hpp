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
    Function object implementing unary_minus capabilities

    return the elementwise unary minus of the parameter

    Infix notation can be used with operator '-'

    @par Semantic:

    For every parameter of type T

    @code
    auto r = unary_minus(x);
    @endcode

    or

    @code
    auto r = -x;
    @endcode

    @par Note:

    - Be aware that for signed integers the unary_minus of @ref Valmin is
    @ref Valmin. This is a side effect of the 2-complement
    representation of integers. To avoid this, you may use the
    saturated_ functor (calling saturated_(unary_minus)(x))
    or convert the input parameter to a larger type
    before taking the unary_minus value.

    @see  minus, unary_plus

  **/
  Value unary_minus(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/unary_minus.hpp>
#include <boost/simd/function/simd/unary_minus.hpp>

#endif
