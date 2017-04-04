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
    This function object computes \f$|x|^y\f$.

    @par Header <boost/simd/function/pow_abs.hpp>

    @par Decorators

    - raw_  is faster but can be inaccurate.

    @see pow, abs


    @par Example:

      @snippet pow_abs.cpp pow_abs

    @par Possible output:

      @snippet pow_abs.txt pow_abs

  **/
  IEEEValue pow_abs(IEEEValue const& x, IEEEValue const& y);
} }
#endif

#include <boost/simd/function/scalar/pow_abs.hpp>
#include <boost/simd/function/simd/pow_abs.hpp>

#endif
