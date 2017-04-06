//==================================================================================================
/*!
  @file
    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_GAMMA_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_GAMMA_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-euler
    This function object computes the gamma function:
   \f$\displaystyle \int_0^{\infty} t^{x-1}e^{-t}\mbox{d}t\f$


    @par Header <boost/simd/function/gamma.hpp>

    @par Decorators

     - std_ calls @c std::tgamma

    @see gammaln

    @par Example:

      @snippet gamma.cpp gamma

    @par Possible output:

      @snippet gamma.txt gamma
  **/
  IEEEValue gamma(IEEEValue const& x);
} }
#endif

#include <boost/simd/function/scalar/gamma.hpp>
#include <boost/simd/function/simd/gamma.hpp>

#endif
