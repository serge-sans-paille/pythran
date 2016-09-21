//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SINCOSPI_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SINCOSPI_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-trigonometric
    Function object implementing sincospi capabilities

    Computes simultaneously and at lower cost the sine and cosine
    of the input in \f$\pi\f$ multiples.

    @par Semantic:

    For every parameters of floating type T:

    @code
    T s, c;
    std::tie(s, c) = sincospi(x);
    @endcode

    is similar to:

    @code
    T s =  sinpi(x);
    T c =  cospi(x);
    @endcode

  **/
  std::pair<Value, Value> sincospi(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/sincospi.hpp>
#include <boost/simd/function/simd/sincospi.hpp>

#endif
