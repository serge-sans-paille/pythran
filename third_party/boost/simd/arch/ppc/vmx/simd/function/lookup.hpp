//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_LOOKUP_HPP_INCLUDED
#define BOOST_SIMD_ARCH_PPC_VMX_SIMD_FUNCTION_LOOKUP_HPP_INCLUDED

#include <boost/simd/detail/predef.hpp>
#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/constant/one.hpp>
#include <boost/simd/constant/two.hpp>

namespace boost { namespace simd { namespace detail {

  template <typename A0, typename A1, typename A2>
  BOOST_FORCEINLINE A0 lookup( A0 const& a0
                             , A1 const& a1
                             , A2 const& rep
                             , A2 const& inc
                             , A2 const& mul
                             )
  {
    using u8type = typename A0::template rebind<unsigned char>::template resize<16>;
    using u8n = typename u8type::storage_type;

    u8n v1 = bitwise_cast<u8type>(a1).storage();
    // Replicates indexes in zeroed bytes
    // LE: [(a, 0), (b, 0), ...] -> [(a, a), (b, b), ...]
    // BE: [(0, a), (0, b), ...] -> [(a, a), (b, b), ...]
    u8n v2 = vec_perm(v1, v1, rep);
    // Multiplies each bytes by the sizeof (<< 1 = 2, << 2 = 4)
    v2 = vec_sl(v2, mul);
    // Add increment mask (so that: [(a, a+1), (b, b+1), ...])
    v2 = vec_add(v2, inc);
    // Pick each bytes using computed vector of indexes
    return vec_perm(a0.storage(), a0.storage(), v2);
  }

} } }

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD( lookup_
                         , (typename A0)
                         , bs::vmx_
                         , bs::pack_<bd::ints8_<A0>, bs::vmx_>
                         , bs::pack_<bd::ints8_<A0>, bs::vmx_>
                         )
  {
    BOOST_FORCEINLINE A0 operator()( const A0& a0, const A0& a1) const BOOST_NOEXCEPT
    {
      using u8type = typename A0::template rebind<unsigned char>::template resize<16>;
      return vec_perm(a0.storage(),a0.storage(), bitwise_cast<u8type>(a1).storage());
    }
  };

  BOOST_DISPATCH_OVERLOAD( lookup_
                         , (typename A0, typename A1)
                         , bs::vmx_
                         , bs::pack_<bd::type16_<A0>, bs::vmx_>
                         , bs::pack_<bd::ints16_<A1>, bs::vmx_>
                         )
  {
    BOOST_FORCEINLINE A0 operator()( const A0& a0, const A1& a1) const BOOST_NOEXCEPT
    {
      using u8type = typename A0::template rebind<unsigned char>::template resize<16>;
      using u8n    = typename u8type::storage_type;

      #if BOOST_ENDIAN_BIG_BYTE
      u8n rep = {1,1, 3,3, 5,5, 7,7, 9,9, 11,11, 13,13, 15,15};
      #else
      u8n rep = {0,0, 2,2, 4,4, 6,6, 8,8, 10,10, 12,12, 14,14};
      #endif
      u8n inc = {0,1, 0,1, 0,1, 0,1, 0,1,  0,1,   0,1,    0,1};

      return detail::lookup(a0, a1, rep, inc, One<u8type>().storage());
    }
  };

  BOOST_DISPATCH_OVERLOAD( lookup_
                         , (typename A0, typename A1)
                         , bs::vmx_
                         , bs::pack_<bd::type32_<A0>, bs::vmx_>
                         , bs::pack_<bd::ints32_<A1>, bs::vmx_>
                         )
  {
    BOOST_FORCEINLINE A0 operator()( const A0& a0, const A1& a1) const BOOST_NOEXCEPT
    {
      using u8type = typename A0::template rebind<unsigned char>::template resize<16>;
      using u8n    = typename u8type::storage_type;

      #if BOOST_ENDIAN_BIG_BYTE
      u8n rep = {3,3,3,3, 7,7,7,7, 11,11,11,11, 15,15,15,15};
      #else
      u8n rep = {0,0,0,0, 4,4,4,4,     8,8,8,8, 12,12,12,12};
      #endif
      u8n inc = {0,1,2,3, 0,1,2,3,     0,1,2,3,     0,1,2,3};

      return detail::lookup(a0, a1, rep, inc, Two<u8type>().storage());
    }
  };

} } }

#endif
