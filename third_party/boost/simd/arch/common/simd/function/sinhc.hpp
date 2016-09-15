//==================================================================================================
/**

  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SINHC_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SINHC_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/arch/common/detail/generic/sinhc_kernel.hpp>
#include <boost/simd/meta/as_logical.hpp>
#include <boost/simd/constant/half.hpp>
#include <boost/simd/constant/log_2.hpp>
#include <boost/simd/detail/constant/maxlog.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/average.hpp>
#include <boost/simd/function/divides.hpp>
#include <boost/simd/function/exp.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/nbtrue.hpp>
#include <boost/simd/function/is_greater.hpp>
#include <boost/simd/function/is_less.hpp>
#include <boost/simd/function/minus.hpp>
#include <boost/simd/function/multiplies.hpp>
#include <boost/simd/function/rec.hpp>
#include <boost/simd/function/sqr.hpp>
#include <boost/simd/function/unary_minus.hpp>

#ifndef BOOST_SIMD_NO_INFINITIES
#include <boost/simd/constant/inf.hpp>
#endif

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;
   BOOST_DISPATCH_OVERLOAD_IF( sinhc_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::floating_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0) const BOOST_NOEXCEPT
      {
        //////////////////////////////////////////////////////////////////////////////
        // if x = abs(a0) is less than 1 sinhc is computed using a polynomial(float)
        // respectively rational(double) approx inspired from cephes sinh approx.
        // else according x < Threshold e =  exp(x) or exp(x/2) is respectively
        // computed
        // * in the first case sinh is ((e-rec(e))/2)/x
        // * in the second     sinh is (e/2/x)*e (avoiding undue overflow)
        // Threshold is Maxlog - Log_2
        //////////////////////////////////////////////////////////////////////////////
        A0 x = bs::abs(a0);
        auto lt1= is_less(x, One<A0>());
        std::size_t nb = nbtrue(lt1);
        A0 z = Zero<A0>();
        if( nb > 0)
        {
          z = detail::sinhc_kernel<A0>::compute(sqr(x));
          if(nb >=A0::static_size) return z;
        }
        auto test1 = is_greater(x, Maxlog<A0>()-Log_2<A0>());
        A0 fac = if_else(test1, Half<A0>(), One<A0>());
        A0 tmp = exp(x*fac);
        A0 tmp1 = (Half<A0>()*tmp)/x;
        A0 r =  if_else(test1, tmp1*tmp, average(tmp, -rec(tmp))/x);
        #ifndef BOOST_SIMD_NO_INFINITIES
        r = if_else(is_equal(x, Inf<A0>()), x, r);
        #endif
        return if_else(lt1, z, r);
      }
   };

} } }

#endif
