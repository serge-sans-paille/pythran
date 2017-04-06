//==================================================================================================
/*!
  @file

    @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_REFINE_RSQRT_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_REFINE_RSQRT_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

  /*!

    @ingroup group-arithmetic
    This function object performs a Newton-Raphson step to improve precision of rsqrt estimate.

    This function can be used in conjunction with raw_(rsqrt)
    to add more precision to the estimates if their default
    precision is not enough.


    @par Header <boost/simd/function/refine_rsqrt.hpp>

    @par semantic:

    @code
     auto r = refine_rsqrt(x, est);
    @endcode

    is similar to

    @code
       auto r = fma( fnms(x, sqr(est), 1), est/2, est);
    @endcode

    @see rec

  **/
  IEEEValue refine_rsqrt(IEEEValue const& x, IEEEValue const& est);
} }
#endif

#include <boost/simd/function/scalar/refine_rsqrt.hpp>
#include <boost/simd/function/simd/refine_rsqrt.hpp>

#endif
