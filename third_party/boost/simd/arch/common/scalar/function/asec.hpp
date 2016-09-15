//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_ASEC_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SCALAR_FUNCTION_ASEC_HPP_INCLUDED

#include <boost/simd/constant/constant.hpp>
#include <boost/simd/constant/ratio.hpp>
#include <boost/simd/constant/nan.hpp>
#include <boost/simd/constant/pi.hpp>
#include <boost/simd/constant/pio_2.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/constant/ratio.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/acsc.hpp>
#include <boost/simd/function/is_equal.hpp>
#include <boost/simd/function/is_eqz.hpp>
#include <boost/simd/function/is_ltz.hpp>
#include <boost/simd/function/dec.hpp>
#include <boost/simd/function/sqrt.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD ( asec_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::double_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (A0 a0) const BOOST_NOEXCEPT
    {
      if (is_equal(a0, One<A0>())) return Zero<A0>();
      return (Pio_2<A0>()-acsc(a0)) +  Constant<A0, 0x3c91a62633145c07ll>();
    }
  };

  BOOST_DISPATCH_OVERLOAD ( asec_
                          , (typename A0)
                          , bd::cpu_
                          , bd::scalar_< bd::single_<A0> >
                          )
  {
    BOOST_FORCEINLINE A0 operator() (A0 a0) const BOOST_NOEXCEPT
    {
      A0 ax =  bs::abs(a0);
      if (ax <  One<A0>()) return Nan<A0>();
      A0 ax1 =  dec(ax);

      if (ax1 < 0.001f)
      {
        A0 tmp = sqrt(Two<A0>()*ax1)
          *oneminus(ax1*(Ratio<A0, 5, 12>()
                         +ax1*(Ratio<A0, 43, 160>()
                               -ax1*(Ratio<A0, 177, 896>()
                                     +ax1*Ratio<A0, 2867, 18432>()
                                    )
                              )
                        )
                   );

        return (is_ltz(a0)) ? Pi<A0>()-tmp : tmp;
      }

      if (is_equal(a0, One<A0>())) return Zero<A0>();
      return  (Pio_2<A0>()-acsc(a0));
    }
  };
} } }


#endif
