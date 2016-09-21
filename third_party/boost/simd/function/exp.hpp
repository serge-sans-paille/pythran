//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_EXP_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_EXP_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!
  @ingroup group-exponential
    Function object implementing exp capabilities

   Computes the exponential function: \f$e^{x}\f$

    @par Semantic:

    For every parameter of floating type T

    @code
    T r = exp(x);
    @endcode

    @par Decorators

    std_ for floating entries

    @see exp2, exp10, pow, expm1, log

  **/
  Value exp(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/exp.hpp>
#include <boost/simd/function/simd/exp.hpp>

#endif
