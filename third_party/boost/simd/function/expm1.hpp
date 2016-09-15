//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_EXPM1_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_EXPM1_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-exponential
    Function object implementing expm1 capabilities

    exponential function minus one:\f$e^{x}-1\f$

    @par Semantic:

    For every parameter of floating type T

    @code
    T r = expm1(x);
    @endcode

    is similar to:

    @code
    T r = dec(exp(x));
    @endcode

    @par Notes:

    - result is accurate even for x of small modulus

    @par Decorators

    std_ for floating entries

    @see exp

  **/
  Value expm1(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/expm1.hpp>
#include <boost/simd/function/simd/expm1.hpp>

#endif
