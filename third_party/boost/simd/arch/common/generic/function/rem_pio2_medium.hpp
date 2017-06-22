//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_GENERIC_FUNCTION_REM_PIO2_MEDIUM_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_GENERIC_FUNCTION_REM_PIO2_MEDIUM_HPP_INCLUDED

#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>
#include <boost/simd/function/nearbyint.hpp>
#include <boost/simd/function/toint.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>
#include <boost/simd/constant/three.hpp>
#include <boost/simd/detail/constant/pio2_1.hpp>
#include <boost/simd/detail/constant/pio2_1t.hpp>
#include <boost/simd/detail/constant/pio2_2.hpp>
#include <boost/simd/detail/constant/pio2_2t.hpp>
#include <boost/simd/detail/constant/pio2_3.hpp>
#include <boost/simd/detail/constant/pio2_3t.hpp>
#include <boost/simd/constant/twoopi.hpp>
#include <boost/simd/function/quadrant.hpp>
#include <boost/simd/function/bitwise_and.hpp>
#include <utility>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD (rem_pio2_medium_
                          , (typename A0)
                          , bd::cpu_
                          , bd::generic_ < bd::floating_<A0> >
                          )
  {
    using result_t = std::pair<A0, A0>;
    BOOST_FORCEINLINE result_t operator() ( A0 const& t) const
    {
      const A0 fn = nearbyint(t*Twoopi<A0>());
      A0 r  = t-fn*Pio2_1<A0>();
      A0 w  = fn*Pio2_1t<A0>();
      A0 t2 = r;
      w  = fn*Pio2_2<A0>();
      r  = t2-w;
      w  = fn*Pio2_2t<A0>()-((t2-r)-w);
      t2 = r;
      w  = fn*Pio2_3<A0>();
      r  = t2-w;
      w  = fn*Pio2_3t<A0>()-((t2-r)-w);
      return  {quadrant(fn), r-w};
    }
  };

} } }


#endif
