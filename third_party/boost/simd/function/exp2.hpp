//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_EXP2_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_EXP2_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-exponential
    Function object implementing exp2 capabilities

    base two exponential function: \f$2^{x}\f$

    @par Semantic:

    For every parameter of floating type T

    @code
    T r = exp2(x);
    @endcode

    is similar to:

    @code
    T r = pow(T(2), x);
    @endcode

    @par Note:

    - provisions are made to obtain a flint result from a flint input

    @par Decorators

    std_ for floating entries

    @see exp, exp10, pow, pow2

  **/
  Value exp2(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/exp2.hpp>
#include <boost/simd/function/simd/exp2.hpp>

#endif
