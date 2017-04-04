//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ATAN2_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_ATAN2_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/meta/as_logical.hpp>
#include <boost/simd/arch/common/detail/simd/f_invtrig.hpp>
#include <boost/simd/arch/common/detail/simd/d_invtrig.hpp>
#include <boost/simd/arch/common/detail/tags.hpp>
#include <boost/simd/constant/pi.hpp>
#include <boost/simd/function/divides.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/function/is_eqz.hpp>
#include <boost/simd/function/is_gtz.hpp>
#include <boost/simd/function/is_ltz.hpp>
#include <boost/simd/function/is_positive.hpp>
#include <boost/simd/function/minus.hpp>
#include <boost/simd/function/negatenz.hpp>
#include <boost/simd/function/rec.hpp>

#ifndef BOOST_SIMD_NO_INFINITIES
#include <boost/simd/constant/one.hpp>
#include <boost/simd/function/copysign.hpp>
#include <boost/simd/function/is_inf.hpp>
#include <boost/simd/function/logical_and.hpp>
#endif

#ifndef BOOST_SIMD_NO_NANS
#include <boost/simd/function/if_allbits_else.hpp>
#include <boost/simd/function/is_nan.hpp>
#include <boost/simd/function/logical_or.hpp>
#endif

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;
   BOOST_DISPATCH_OVERLOAD_IF( atan2_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pedantic_tag
                          , bs::pack_<bd::floating_<A0>, X>
                          , bs::pack_<bd::floating_<A0>, X>
                          )
   {
     inline A0 operator()(const pedantic_tag &,
                          const A0& a0,const A0& a1) const
      {
        A0 a00 = a0, a10 = a1;
  #ifndef BOOST_SIMD_NO_INFINITIES
        auto test1 =  bs::logical_and(bs::is_inf(a0),  bs::is_inf(a1));
        a00 =  bs::if_else(test1, bs::copysign(One<A0>(), a00), a00);
        a10 =  bs::if_else(test1, bs::copysign(One<A0>(), a10), a10);
  #endif
        A0 q = bs::abs(a00/a10);
        A0 z = detail::invtrig_base<A0,tag::radian_tag, tag::simd_type>::kernel_atan(q, rec(q));
        //A0 z = atan(abs(a0/a1));  // case a1 > 0,  a0 > 0
        A0 sgn = signnz(a0);
        z = bs::if_else(bs::is_positive(a10), z, bs::Pi<A0>()-z)*sgn;
        z = bs::if_else( bs::is_eqz(a00),
                         bs::if_else_zero( bs::is_negative(a10),  bs::Pi<A0>()*sgn),
                         z);
  #ifdef BOOST_SIMD_NO_NANS
        return z;
  #else
        return  bs::if_nan_else( bs::logical_or( bs::is_nan(a00),  bs::is_nan(a10)), z);
  #endif
      }
   };

  BOOST_DISPATCH_OVERLOAD_IF( atan2_
                          , (typename A0, typename X)
                          , (detail::is_native<X>)
                          , bd::cpu_
                          , bs::pack_<bd::floating_<A0>, X>
                          , bs::pack_<bd::floating_<A0>, X>
                          )
   {
     inline A0 operator()(const A0& a0,const A0& a1) const
      {
        A0 q = bs::abs(a0/a1);
        A0 z = detail::invtrig_base<A0,tag::radian_tag, tag::simd_type>::kernel_atan(q, rec(q));
        return bs::if_else(bs::is_positive(a1), z, bs::Pi<A0>()-z)* signnz(a0);
      }
   };
} } }

#endif
