//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_IF_ELSE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_IF_ELSE_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/dispatch/meta/as_floating.hpp>
#include <boost/simd/meta/cardinal_of.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/genmask.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;

   BOOST_DISPATCH_OVERLOAD( if_else_
                          , (typename A0, typename A1)
                          , bs::avx_
                          , bs::pack_<logical_<A0>, bs::avx_>
                          , bs::pack_<bd::single_<A1>, bs::avx_>
                          , bs::pack_<bd::single_<A1>, bs::avx_>
                          )
   {
     BOOST_FORCEINLINE A1 operator()(A0 const& a0,A1 const& a1,A1 const& a2) const
     {
       return _mm256_blendv_ps(a2, a1, bitwise_cast<A1>(genmask(a0)));
     }
   };

   BOOST_DISPATCH_OVERLOAD( if_else_
                          , (typename A0, typename A1)
                          , bs::avx_
                          , bs::pack_<logical_<A0>, bs::avx_>
                          , bs::pack_<bd::double_<A1>, bs::avx_>
                          , bs::pack_<bd::double_<A1>, bs::avx_>
                          )
   {
     BOOST_FORCEINLINE A1 operator()(A0 const& a0,A1 const& a1,A1 const& a2) const
     {
       return _mm256_blendv_pd(a2, a1, bitwise_cast<A1>(genmask(a0)));
     }
   };

   BOOST_DISPATCH_OVERLOAD_IF ( if_else_
                              , (typename A0, typename A1)
                              , (nsm::bool_<bs::cardinal_of<A0>::value <= 8>)
                              , bs::avx_
                              , bs::pack_<logical_<A0>, bs::avx_>
                              , bs::pack_<bd::integer_<A1>, bs::avx_>
                              , bs::pack_<bd::integer_<A1>, bs::avx_>
                              )
   {
     BOOST_FORCEINLINE A1 operator()(A0 const& a0,A1 const& a1,A1 const& a2) const
     {
        using f_t= bd::as_floating_t<A1>;
        return bitwise_cast<A1>(if_else(a0, bitwise_cast<f_t>(a1), bitwise_cast<f_t>(a2)));
     }
   };
} } }

#endif
