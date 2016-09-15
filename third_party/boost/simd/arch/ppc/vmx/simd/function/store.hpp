//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_STORE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_STORE_HPP_INCLUDED

#include <boost/simd/detail/predef.hpp>
#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/dispatch/adapted/common/pointer.hpp>
#include <boost/simd/meta/is_pointing_to.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = ::boost::dispatch;
  namespace bs = ::boost::simd;

  BOOST_DISPATCH_OVERLOAD_IF( store_
                            , (typename Src, typename Pointer)
                            , (bs::is_pointing_to<Pointer,typename Src::value_type>)
                            , bs::vmx_
                            , bs::pack_<bd::arithmetic_<Src>,bs::vmx_>
                            , bd::pointer_<bd::scalar_<bd::arithmetic_<Pointer>>,1u>
                            )
  {
    BOOST_FORCEINLINE void operator()(const Src& s, Pointer p) const BOOST_NOEXCEPT
    {
      #pragma GCC diagnostic push
      #pragma GCC diagnostic ignored "-Wdeprecated"
      __vector unsigned char  edgeAlign = vec_lvsl(0 , p);
      auto                    MSQ       = vec_ld  (0 , p);
      auto                    LSQ       = vec_ld  (16, p);
      __vector unsigned char  align     = vec_lvsr(0 , p);
      auto                    edges     = vec_perm(LSQ , MSQ, edgeAlign);

      vec_st(vec_perm(s.storage(), edges      , align), 16 , p);
      vec_st(vec_perm(edges      , s.storage(), align), 0  , p);
      #pragma GCC diagnostic pop
    }
  };
} } }

#endif
