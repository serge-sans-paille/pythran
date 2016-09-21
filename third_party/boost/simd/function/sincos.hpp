//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SINCOS_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SINCOS_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-trigonometric
    Function object implementing sincos capabilities

    Computes simultaneouly and at lower cost the sine and cosine of the input

    For every parameter of floating type T:

    @par Semantic:

    @code
    T s, c;
    std::tie(s, c) = sincos(x);
    @endcode

    is similar to:

    @code
    T s =  sin(x);
    T c =  cos(x);
    @endcode

  **/
  std::pair<Value, Value> sincos(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/sincos.hpp>
#include <boost/simd/function/simd/sincos.hpp>

#endif
