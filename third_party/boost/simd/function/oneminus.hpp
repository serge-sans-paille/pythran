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
    This function object returns  one minus the entry.


    @par Header <boost/simd/function/oneminus.hpp>

    @par Notes
    Using `oneminus(x)` is similar to `1-x`

    @par Decorator

    _saturated_ is available,  but for unsigned integral types the saturated_
    function is merely  equivalent to `x == 0 ? 1 : 0`

    @par Example:

      @snippet oneminus.cpp oneminus

    @par Possible output:

      @snippet oneminus.txt oneminus

  **/
  Value oneminus(Value const& x);
} }
#endif

#include <boost/simd/function/scalar/oneminus.hpp>
#include <boost/simd/function/simd/oneminus.hpp>

#endif
