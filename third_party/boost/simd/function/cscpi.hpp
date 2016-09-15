//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_CSCPI_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_CSCPI_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-trigonometric
    Function object implementing cscpi capabilities

    cosecant of angle in \f$\pi\f$ multiples: \f$\sin(1/(\pi x))\f$.

    @par Semantic:

    For every parameter of floating type T

    @code
    T r = cscpi(x);
    @endcode

    As most other trigonometric function cscpi can be called with a second optional parameter
    which is a tag on speed and accuracy (see @ref cos for further details)

    @see cscd, csc,

  **/
  Value cscpi(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/cscpi.hpp>
#include <boost/simd/function/simd/cscpi.hpp>

#endif
