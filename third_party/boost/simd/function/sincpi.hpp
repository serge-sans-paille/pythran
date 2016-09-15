//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SINCPI_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SINCPI_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!
    @ingroup group-trigonometric
    Function object implementing sincpi capabilities

    Computes the sinpi cardinal  value of its parameter that is \f$sin(\pi x)/(\pix) \f$.
    @par Semantic:

    For every parameter of floating type T

    @code
    T r = sincpi(x);
    @endcode

    @see sin, sinc, sinhc

  **/
  Value sincpi(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/sincpi.hpp>
#include <boost/simd/function/simd/sincpi.hpp>

#endif
