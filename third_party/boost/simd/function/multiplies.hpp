//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_MULTIPLIES_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_MULTIPLIES_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-operator
    This function object computes the product of two parameters of the same type.

    Infix notation can be used with operator '*',

    @par Header <boost/simd/function/multiplies.hpp>

    @par Decorators

     - `saturated_` (See @ref group-decorator) computes the saturated product.

    @see minus, divides, plus

    @par Example:

      @snippet multiplies.cpp multiplies

    @par Possible output:

      @snippet multiplies.txt multiplies

    returns the product of @c a and @c b

    @see fma, fms, fnma, fnms

  **/
  Value multiplies(Value const& x, Value const& y);
} }
#endif

#include <boost/simd/function/scalar/multiplies.hpp>
#include <boost/simd/function/simd/multiplies.hpp>

#endif
