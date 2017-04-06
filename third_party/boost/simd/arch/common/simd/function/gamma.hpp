//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_GAMMA_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_GAMMA_HPP_INCLUDED

#include <boost/simd/function/std.hpp>
#include <boost/simd/arch/common/detail/generic/gamma_kernel.hpp>

#include <boost/simd/constant/half.hpp>
#include <boost/simd/constant/inf.hpp>
#include <boost/simd/constant/logpi.hpp>
#include <boost/simd/constant/logsqrt2pi.hpp>
#include <boost/simd/constant/minf.hpp>
#include <boost/simd/constant/mone.hpp>
#include <boost/simd/constant/nan.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/constant/two.hpp>
#include <boost/simd/constant/three.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/constant/pi.hpp>
#include <boost/simd/constant/two.hpp>

#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/any.hpp>
#include <boost/simd/function/bitwise_or.hpp>
#include <boost/simd/function/floor.hpp>
#include <boost/simd/function/is_even.hpp>
#include <boost/simd/function/fma.hpp>
#include <boost/simd/function/if_dec.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/if_inc.hpp>
#include <boost/simd/function/if_nan_else.hpp>
#include <boost/simd/function/is_equal.hpp>
#include <boost/simd/function/is_eqz.hpp>
#include <boost/simd/function/is_flint.hpp>
#include <boost/simd/function/is_less.hpp>
#include <boost/simd/function/is_lez.hpp>
#include <boost/simd/function/log.hpp>
#include <boost/simd/function/logical_and.hpp>
#include <boost/simd/function/logical_andnot.hpp>
#include <boost/simd/function/logical_or.hpp>
#include <boost/simd/function/nbtrue.hpp>
#include <boost/simd/function/if_neg.hpp>
#include <boost/simd/function/sinpi.hpp>
#include <boost/simd/function/sqr.hpp>

#include <boost/simd/meta/as_logical.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/meta/scalar_of.hpp>
#include <boost/config.hpp>
#include <cmath>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;
  BOOST_DISPATCH_OVERLOAD_IF ( gamma_
                             , (typename A0, typename X)
                             , (detail::is_native<X>)
                             , bd::cpu_
                             , bs::pack_< bd::floating_<A0>, X>
                             )
  {
    BOOST_FORCEINLINE A0 operator() (const A0& a0) const BOOST_NOEXCEPT
    {
      auto nan_result = logical_and(is_ltz(a0), is_flint(a0));
      #ifndef BOOST_SIMD_NO_INVALIDS
      nan_result = logical_or(bs::is_nan(a0), nan_result);
      #endif
      A0 q = bs::abs(a0);
      auto test = is_less(a0, A0(-33.0));
      std::size_t nb = bs::nbtrue(test);
      A0 r =  Nan<A0>();
      if(nb > 0)
      {
        //treat negative large with reflection
        r = large_negative(q);
        if (nb >= A0::static_size)
          return bs::if_nan_else(nan_result, r);
      }
      A0 r1 = other(a0, test);
      A0 r2 = if_else(test, r, r1);
      return bs::if_else(is_eqz(a0), copysign(Inf<A0>(), a0), bs::if_nan_else(nan_result, r2));
    }
  private :
    static  A0 large_negative(const A0& q) BOOST_NOEXCEPT
    {
      A0 st =  bs::stirling(q);
      A0 p = bs::floor(q);
      A0 sgngam = bs::if_neg(bs::is_even(p), One<A0>());
      A0 z = q - p;
      auto test2 = is_less(z, bs::Half<A0>() );
      z = bs::if_dec(test2, z);
      z = q*bs::sinpi(z);
      z =  bs::abs(z);
      return sgngam*bs::Pi<A0>()/(z*st);
    }

    template < typename BA0>
    static A0 other(const A0& q, const BA0& test) BOOST_NOEXCEPT
    {
      A0 x =  bs::if_else(test, Two<A0>(), q);
      #ifndef BOOST_SIMD_NO_INFINITIES
      auto inf_result = is_equal(q, Inf<A0>());
      x = if_else(inf_result, Two<A0>(), x);
      #endif
      A0 z = bs::One<A0>();
      auto test1 = is_greater_equal(x,Three<A0>());
      while( bs::any(test1) )
      {
        x = bs::if_dec(test1, x);
        z = bs::if_else(   test1, z*x, z);
        test1 = is_greater_equal(x,Three<A0>());
      }
      //all x are less than 3
      test1 = bs::is_ltz(x);
      while( bs::any(test1) )
      {
        z = bs::if_else(test1, z/x, z);
        x = bs::if_inc(test1, x);
        test1 = bs::is_ltz(x);
      }
      //all x are greater than 0 and less than 3
      auto test2 = is_less(x,bs::Two<A0>());
      while( bs::any(test2))
      {
        z = bs::if_else(test2, z/x, z);
        x = bs::if_inc(test2, x);
        test2 = is_less(x,bs::Two<A0>());
      }
      //all x are greater equal 2 and less than 3
      x = z*detail::gamma_kernel<A0>::gamma1(x-bs::Two<A0>());
      #ifndef BOOST_SIMD_NO_INFINITIES
      return if_else(inf_result, q, x);
      #else
      return x;
      #endif
    }
  };


} } }


#endif
