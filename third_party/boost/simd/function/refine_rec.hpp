//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_REFINE_REC_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_REFINE_REC_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-arithmetic
    Function object implementing refine_rec capabilities

    Performs a Newton-Raphson step to improve precision of reciprocate estimate.
    This function can be used in conjunction with raw_(rec) or
    fast_(rec) to add more precision to the estimate if their default
    precision is not enough.

    @par semantic:
    For any given value @c x, @c est  of floating type T:

    @code
    T r =refine_rec(x, est);
    @endcode

    is similar to

    @code
    T r = fma(fnms(est, a0, One<T>()), est, est);
    @endcode

    @see rec

  **/
  Value refine_rec(Value const & v0, Value const& est);
} }
#endif

#include <boost/simd/function/scalar/refine_rec.hpp>
#include <boost/simd/function/simd/refine_rec.hpp>

#endif
