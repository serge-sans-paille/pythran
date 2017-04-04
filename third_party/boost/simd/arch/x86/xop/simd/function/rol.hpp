//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_XOP_SIMD_FUNCTION_ROL_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_XOP_SIMD_FUNCTION_ROL_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/meta/cardinal_of.hpp>
#include <boost/simd/function/rrol.hpp>

#if BOOST_HW_SIMD_X86_AMD_XOP
namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD_IF( rol_
                            , (typename A0, typename A1)
                            , (nsm::bool_<bs::cardinal_of<A0>::value == bs::cardinal_of<A1>::value>)
                            , bs::avx_
                            , bs::pack_< bd::integer_<A0>, bs::sse_>
                            , bs::pack_< bd::integer_<A1>, bs::sse_>
                            )
  {
    BOOST_FORCEINLINE A0 operator()(A0 const& a0, A1 const& a1) const
    {
      return rrol(a0,a1);
    }
  };
} } }
#endif

#endif
