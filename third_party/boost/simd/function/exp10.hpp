//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_EXP10_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_EXP10_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-exponential
    Function object implementing exp10 capabilities

    Computes the base ten exponential function: \f$10^{x}\f$

    @par Semantic:

    For every parameter of floating type T

    @code
    T r = exp10(x);
    @endcode

    is similar to:

    @code
    T r = exp(x*log_10<T>());
    @endcode

    @par Note:

    provisions are made for obtaining a flint result from a flint input

    @see exp2, exp, pow

  **/
  Value exp10(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/exp10.hpp>
#include <boost/simd/function/simd/exp10.hpp>

#endif
