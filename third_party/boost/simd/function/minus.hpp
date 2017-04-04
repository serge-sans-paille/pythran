//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_MINUS_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_MINUS_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-operator
    This function object computes the difference of two parameters of the same type.

    Infix notation can be used with operator '-',

    @par Header <boost/simd/function/minus.hpp>

    @par Decorators

     - `saturated_` (See @ref group-decorator) computes the saturated difference.

    @see plus, divides, multiplies

    @par Example:

      @snippet minus.cpp minus

    @par Possible output:

      @snippet minus.txt minus

  **/
  Value minus(Value const& x, Value const& y);
} }
#endif

#include <boost/simd/function/scalar/minus.hpp>
#include <boost/simd/function/simd/minus.hpp>

#endif
