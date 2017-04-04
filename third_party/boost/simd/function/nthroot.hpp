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
    This function object returns the nth root of its first argument: \f$\sqrt[n]{x}\f$
    \arg n must be of integer type
    \arg if n is even and x negative the result is @ref Nan
    \arg if x is null the result is @ref Zero
    \arg if x is one  the result is @ref One



    @par Header <boost/simd/function/nthroot.hpp>

    @par Note:
    nthroot is slower than `pow(x, rec(tofloat(n))`) because
    it takes care of some limits issues that @ref pow ignores.

    See if it suits you better or use raw_ decorator for intermediate solution.

    @par Decorators

      - raw_ provides increased speed but is undefined for limitings values

    @see pow, rec, sqrt, cbrt


    @par Example:

      @snippet nthroot.cpp nthroot

    @par Possible output:

      @snippet nthroot.txt nthroot

  **/
  Value nthroot(Value const& x, IntegerValue const& n);
} }
#endif

#include <boost/simd/function/scalar/nthroot.hpp>
#include <boost/simd/function/simd/nthroot.hpp>

#endif
