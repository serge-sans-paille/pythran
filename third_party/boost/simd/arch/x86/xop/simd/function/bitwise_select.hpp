//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_XOP_SIMD_FUNCTION_BITWISE_SELECT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_XOP_SIMD_FUNCTION_BITWISE_SELECT_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/detail/dispatch/meta/as_integer.hpp>

#if BOOST_HW_SIMD_X86_AMD_XOP
namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD_IF( bitwise_select_
                            , (typename A0, typename A1)
                            , (nsm::bool_<A0::static_size == A1::static_size>)
                            , bs::avx_
                            , bs::pack_<bd::fundamental_<A0>, bs::sse_>
                            , bs::pack_<bd::fundamental_<A1>, bs::sse_>
                            , bs::pack_<bd::fundamental_<A1>, bs::sse_>
                            )
   {
     BOOST_FORCEINLINE A1 operator()(A0 const& a0, A1 const& a1, A1 const& a2) const
      {
        using itype =  bd::as_integer_t<A0, unsigned>;
        itype tmp = _mm_cmov_si128( bitwise_cast<itype>(a1)
                                                , bitwise_cast<itype>(a2)
                                                , bitwise_cast<itype>(a0)
                                                );
        return bitwise_cast<A1> ( tmp );
      }
   };

  BOOST_DISPATCH_OVERLOAD_IF( bitwise_select_
                            , (typename A0, typename A1)
                            , (nsm::bool_<A0::static_size == A1::static_size>)
                            , bs::avx_
                            , bs::pack_<bd::fundamental_<A0>, bs::avx_>
                            , bs::pack_<bd::fundamental_<A1>, bs::avx_>
                            , bs::pack_<bd::fundamental_<A1>, bs::avx_>
                            )
  {
    BOOST_FORCEINLINE A1 operator()(A0 const& a0, A1 const& a1, A1 const& a2) const
    {
      using itype = bd::as_integer_t<A0, unsigned>;
      itype tmp = _mm256_cmov_si256 ( bitwise_cast<itype>(a1)
                                                  , bitwise_cast<itype>(a2)
                                                  , bitwise_cast<itype>(a0)
                                    );
      return bitwise_cast<A1> (tmp );
    }
  };
} } }
#endif

#endif
