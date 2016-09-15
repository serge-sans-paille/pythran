//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_CBRT_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_CBRT_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-exponential
    Function object implementing cbrt capabilities

    Compute the cubic root: \f$\sqrt[3]{x}\f$

    @par Semantic:

    For every parameter of floating type T

    @code
    T r = cbrt(x);
    @endcode

    is similar to:

    @code
    T r = pow(x, T(1/3.0));
    @endcode

    but not equivalent because pow cannot raise a negative base to a fractional exponent.
    we have for all non Nan floating values cbrt(-x) = -cbrt(x).

    @par Decorators

    std_ for floating entries

    @see pow, sqrt

  **/
  Value cbrt(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/cbrt.hpp>
#include <boost/simd/function/simd/cbrt.hpp>

#endif
