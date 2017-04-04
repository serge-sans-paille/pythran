//==================================================================================================
/**

  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ASINH_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ASINH_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/meta/as_logical.hpp>
#include <boost/simd/function/horn.hpp>
#include <boost/simd/constant/half.hpp>
#include <boost/simd/constant/log_2.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/constant/oneosqrteps.hpp>
#include <boost/simd/constant/zero.hpp>
#include <boost/simd/function/abs.hpp>
#include <boost/simd/function/average.hpp>
#include <boost/simd/function/bitofsign.hpp>
#include <boost/simd/function/bitwise_xor.hpp>
#include <boost/simd/function/divides.hpp>
#include <boost/simd/function/hypot.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/if_nan_else.hpp>
#include <boost/simd/function/nbtrue.hpp>
#include <boost/simd/function/is_greater.hpp>
#include <boost/simd/function/is_less.hpp>
#include <boost/simd/function/log.hpp>
#include <boost/simd/function/dec.hpp>
#include <boost/simd/function/multiplies.hpp>
#include <boost/simd/function/inc.hpp>
#include <boost/simd/function/plus.hpp>
#include <boost/simd/function/sqr.hpp>

#ifndef BOOST_SIMD_NO_INFINITIES
#include <boost/simd/constant/inf.hpp>
#include <boost/simd/function/is_equal.hpp>
#endif

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;
   BOOST_DISPATCH_OVERLOAD_IF( asinh_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::double_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0) const BOOST_NOEXCEPT
      {
        A0 x =  bs::abs(a0);
        auto test = is_greater(x,Oneosqrteps<A0>());
        A0 z = if_else(test,dec(x), x+sqr(x)/bs::inc(hypot(One<A0>(), x)));
        #ifndef BOOST_SIMD_NO_INFINITIES
        z = if_else(is_equal(x, Inf<A0>()),x, z);
        #endif
        z =  if_plus(test, log1p(z), Log_2<A0>());
        return bitwise_xor(bitofsign(a0), z);
      }
   };

   BOOST_DISPATCH_OVERLOAD_IF( asinh_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::single_<A0>, X>
                          )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0) const BOOST_NOEXCEPT
      {
        // Exhaustive test for: boost::dispatch::functor<bs::tag::asinh_, bs::tag::sse4_2_>
        //              versus: float(boost::math::asinh(double)
        //              With T: bs::native<float, bs::tag::sse_, void>
        //            in range: [-3.40282e+38, 3.40282e+38]
        // 4278190076 values computed.
        // 3619320676 values (84.60%)  within 0.0 ULPs
        //  658843138 values (15.40%)  within 0.5 ULPs
        //      26262 values ( 0.00%)  within 1.0 ULPs
        A0 x = bs::abs(a0);
        bs::as_logical_t<A0> lthalf = is_less(x,Half<A0>());
        A0 x2 = bs::sqr(x);
        A0 z = Zero<A0>();
        std::size_t nb = nbtrue(lthalf);
        A0 bts = bitofsign(a0);
        if(nb > 0)
        {
          z = horn<A0
            , 0x3f800000
            , 0xbe2aa9ad
            , 0x3d9949b1
            , 0xbd2ee581
            , 0x3ca4d6e6
            > (x2)*x;

          if(nb >= A0::static_size) return  bitwise_xor(z, bts);
        }
        A0 tmp =  if_else(is_greater(x, Oneosqrteps<A0>()),
                          x, average(x, hypot(One<A0>(), x)));
       #ifndef  BOOST_SIMD_NO_NANS
        return if_nan_else(is_nan(a0), bitwise_xor(if_else(lthalf, z, log(tmp)+Log_2<A0>()), bts));
       #else
       return bitwise_xor(if_else(lthalf, z, log(tmp)+Log_2<A0>()), bts);
       #endif
      }
   };

} } }

#endif
