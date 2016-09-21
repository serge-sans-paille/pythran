//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_POW_ABS_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_POW_ABS_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-exponential
    Function object implementing pow_abs capabilities

    Computes \f$|x|^y\f$.

    @par Semantic:

    For every parameters of floating type  T:

    @code
    T r = pow_abs(x, y);
    @endcode

    is similar to:

    @code
    T r = pow(abs(x), y);
    @endcode

    @see pow, abs

  **/
  Value pow_abs(Value const & x, Value const& y);
} }
#endif

#include <boost/simd/function/scalar/pow_abs.hpp>
#include <boost/simd/function/simd/pow_abs.hpp>

#endif
