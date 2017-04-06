//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_LOG1P_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_LOG1P_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
   namespace bd = boost::dispatch;
   namespace bs = boost::simd;

   BOOST_DISPATCH_OVERLOAD_IF( log1p_
                             , (typename A0)
                             , (detail::is_native<bs::avx_>)
                             , bs::avx_
                             , bs::pack_<bd::single_<A0>, bs::avx_>
                          )
   {
      BOOST_FORCEINLINE A0 operator()( const A0& a0) const BOOST_NOEXCEPT
      {
        return plain_(log1p)(a0);
      }
   };


} } }

#endif
