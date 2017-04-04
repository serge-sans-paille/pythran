//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_EXPRECNEG_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_EXPRECNEG_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!
    @ingroup group-exponential
    This function object computes: \f$e^{-\frac1x}\f$

    @par Header <boost/simd/function/exprecneg.hpp>

    @par Example:

      @snippet exprecneg.cpp exprecneg

    @par Possible output:

      @snippet exprecneg.txt exprecneg

  **/
  IEEEValue exprecneg(IEEEValue const& x);
} }
#endif

#include <boost/simd/function/scalar/exprecneg.hpp>
#include <boost/simd/function/simd/exprecneg.hpp>

#endif
