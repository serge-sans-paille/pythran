//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_SQRT1PM1_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_SQRT1PM1_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-arithmetic
    Function object implementing sqrt1pm1 capabilities

    Returns \f$\sqrt{1+x}-1\f$ and the
    result is accurate even for x  with small modulus

    @par Semantic:

    For every parameter of floating type T

    @code
    T r = sqrt1pm1(x);
    @endcode

    is similar to:

    @code
    T r = dec(sqrt(Oneplus(x));
    @endcode

    @see lol1p, expm1.

  **/
  Value sqrt1pm1(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/sqrt1pm1.hpp>
#include <boost/simd/function/simd/sqrt1pm1.hpp>

#endif
