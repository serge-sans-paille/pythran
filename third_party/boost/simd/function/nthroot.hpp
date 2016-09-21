//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_NTHROOT_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_NTHROOT_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-exponential
    Function object implementing nthroot capabilities

    nth root function: \f$\sqrt[n]{x}\f$
    \arg n must be of integer type
    \arg if n is even and x negative the result is @ref Nan
    \arg if x is null the result is @ref Zero
    \arg if x is one  the result is @ref One

    @par Semantic:

    For every parameters of  floating type T and integral type N:

    @code
    T r = nthroot(x, n);
    @endcode

    is similar to:

    @code
    T r = n >= 0 ? pow(x, rec(tofloat(n))) : Nan;
    @endcode

    @par Note:
    nthroot is more expansive than pow(x, rec(tofloat(n))) because
    it takes care of some limits issues that @ref pow does not mind of.

    See if it suits you better.

    @see pow, rec, sqrt, cbrt

  **/
  Value nthroot(Value const & x, IntegerValue const &n);
} }
#endif

#include <boost/simd/function/scalar/nthroot.hpp>
#include <boost/simd/function/simd/nthroot.hpp>

#endif
