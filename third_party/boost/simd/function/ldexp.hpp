//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_LDEXP_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_LDEXP_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-ieee
    This function object returns  \f$x\f$ multiplied by
    by \f$2^{n}\f$


    @par Header <boost/simd/function/ldexp.hpp>

    @par Note

     If @c n is not of integral type it is truncated:
     `ldexp(x,n)` is similar to: `x*pow(2, trunc(n))`

    @pre
     The @ref cardinal_of and the size of elements value of the types
     of @c x and @c n must be identical

    @par Decorators

     - pedantic_ By default @c ldexp does not take care of denormal or limiting values.
       Use the @c pedantic_ decorator if these are to be properly computed.

     - std_ give access to std::ldexp

    @par Example:

      @snippet ldexp.cpp ldexp

    @par Possible output:

      @snippet ldexp.txt ldexp

  **/
  Value0 ldexp(Value0 const& x, Value1 const& n);
} }
#endif

#include <boost/simd/function/scalar/ldexp.hpp>
#include <boost/simd/function/simd/ldexp.hpp>

#endif
