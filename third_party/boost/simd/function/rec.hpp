//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_REC_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_REC_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{
  /*!
    @ingroup group-arithmetic
    Function object implementing rec capabilities

    Returns the inverse (reciprocal) of the entry.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    T r = rec(x);
    @endcode

    The code is similar to:

    @code
    T r = T(1)/x;
    @endcode

    @par Note

    For integral typed entries the result is always in the set \f$\{0,  \pm1, Valmax \}\f$

    @par Decorators

     For floating types

     - raw_ decorator can be applied to rec as many systems provide fast low precision
       intrinsic for inverse computation. The result can be not fully accurate.

     - fast_ decorator can be applied to rec as using a one step refinement of raw_(rec)
       instead of division when available.


  **/
  Value rec(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/rec.hpp>
#include <boost/simd/function/simd/rec.hpp>

#endif
