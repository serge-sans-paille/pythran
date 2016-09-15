//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_FUNCTION_ONEMINUS_HPP_INCLUDED
#define BOOST_SIMD_FUNCTION_ONEMINUS_HPP_INCLUDED

#if defined(DOXYGEN_ONLY)
namespace boost { namespace simd
{

 /*!

    @ingroup group-arithmetic
    Function object implementing oneminus capabilities

    Returns the one minus the entry.

    @par semantic:
    For any given value @c x of type @c T:

    @code
    T r = oneminus(x);
    @endcode

    For signed type is similar to:

    @code
    T r = 1-x
    @endcode

    @par Decorator

    saturated_ decorator is available,  but for unsigned integral types the saturated_
    function is equivalent to `x == 0 ? 1 : 0`

  **/
  Value oneminus(Value const & v0);
} }
#endif

#include <boost/simd/function/scalar/oneminus.hpp>
#include <boost/simd/function/simd/oneminus.hpp>

#endif
