//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_NEARBYINT_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_NEARBYINT_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-arithmetic
    Function object implementing nearbyint capabilities

    Computes the rounded to even value of its parameter.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    T r = nearbyint(x);
    @endcode

    Returns the nearest integer to x.

    @par Note:
    - If arg is /f$\infty/f$, it is returned, unmodified
    - If arg is $\pm0/f$, it is returned, unmodified
    - If arg is NaN, NaN is returned

    - to even means that half integer values are rounded to the nearest
    even value.

    This function is in general quicker than @ref round which do the rouding on
    half integer values away from zero.

    @see round, ceil, floor, trunc
  **/
  Value nearbyint(Value const & x);
} }
#endif

#include <boost/simd/function/scalar/nearbyint.hpp>
#include <boost/simd/function/simd/nearbyint.hpp>

#endif
