//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_REM_PIO2_STRAIGHT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_REM_PIO2_STRAIGHT_HPP_INCLUDED

#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/detail/constant/pio2_1.hpp>
#include <boost/simd/detail/constant/pio2_2.hpp>
#include <boost/simd/detail/constant/pio2_3.hpp>
#include <boost/simd/constant/pio_4.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/is_greater.hpp>
#include <boost/simd/function/genmask.hpp>
#include <boost/simd/function/multiplies.hpp>
#include <boost/simd/function/minus.hpp>
#include <utility>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD (rem_pio2_straight_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_ < bd::floating_<A0> >
                          )
  {
    using result_t = std::pair<A0, A0>;
    BOOST_FORCEINLINE result_t operator() ( A0 const& x) const BOOST_NOEXCEPT
    {
      if (x < Pio_4<A0>())
        return {Zero<A0>(), x};
      A0 xr = x-Pio2_1<A0>();
      xr -= Pio2_2<A0>();
      xr -= Pio2_3<A0>();
      return { One<A0>(), xr};
    }
  };

} } }


#endif
