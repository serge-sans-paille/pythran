//==================================================================================================
/*!
  @file
  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SIGNGAM_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SIGNGAM_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!
  @ingroup group-euler
    Function object implementing signgam capabilities

    sign of gamma function

    @par Semantic:

    For every parameter of floating type T0

    @code
    T0 r = signgam(x);
    @endcode

    is similar to

    @code
    T0 r = sign(gamma(x));
    @endcode

    signgam does not computes @ref gamma and is fast.

    @see gamma,  gammaln

  **/
  Value signgam(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/signgam.hpp>
//#include <boost/simd/function/simd/signgam.hpp>

#endif
