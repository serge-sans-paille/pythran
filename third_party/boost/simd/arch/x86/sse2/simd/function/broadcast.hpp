//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_BROADCAST_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_BROADCAST_HPP_INCLUDED

#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/detail/overload.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = ::boost::dispatch;
  namespace bs = ::boost::simd;
  namespace tt = nsm::type_traits;

  BOOST_DISPATCH_OVERLOAD ( broadcast_
                          , (typename A0, typename A1)
                          , bs::sse2_
                          , bs::pack_<bd::double_<A0>,bs::sse_>
                          , bd::constant_<bd::integer_<A1>>
                          )
  {
    BOOST_FORCEINLINE A0 operator()(A0 const& a0, A1 const&) const BOOST_NOEXCEPT
    {
      return do_(a0,nsm::bool_<(A1::value >= 0 && A1::value < 2)>{});
    }

    static BOOST_FORCEINLINE A0 do_(A0 const& a0, nsm::bool_<true> const&) BOOST_NOEXCEPT
    {
      return _mm_shuffle_pd(a0, a0, _MM_SHUFFLE2(A1::value,A1::value));
    }

    static BOOST_FORCEINLINE A0 do_(A0 const&, nsm::bool_<false> const&) BOOST_NOEXCEPT
    {
      return Zero<A0>();
    }
  };

  BOOST_DISPATCH_OVERLOAD ( broadcast_
                          , (typename A0, typename A1)
                          , bs::sse2_
                          , bs::pack_<bd::ints32_<A0>,bs::sse_>
                          , bd::constant_<bd::integer_<A1>>
                          )
  {
    BOOST_FORCEINLINE A0 operator()(A0 const& a0, A1 const&) const BOOST_NOEXCEPT
    {
      return do_(a0,nsm::bool_<(A1::value >= 0 && A1::value < 4)>{});
    }

    static BOOST_FORCEINLINE A0 do_(A0 const& a0, nsm::bool_<true> const&) BOOST_NOEXCEPT
    {
      return _mm_shuffle_epi32(a0, _MM_SHUFFLE ( A1::value, A1::value, A1::value, A1::value));
    }

    static BOOST_FORCEINLINE A0 do_(A0 const&, nsm::bool_<false> const&) BOOST_NOEXCEPT
    {
      return Zero<A0>();
    }
  };

  BOOST_DISPATCH_OVERLOAD ( broadcast_
                          , (typename A0, typename A1)
                          , bs::sse2_
                          , bs::pack_<bd::ints16_<A0>,bs::sse_>
                          , bd::constant_<bd::integer_<A1>>
                          )
  {
    BOOST_FORCEINLINE A0 operator()(A0 const& a0, A1 const&) const BOOST_NOEXCEPT
    {
      return do_(a0,nsm::bool_<(A1::value >= 0 && A1::value < 8)>{});
    }

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow"
#endif // __clang__

    static BOOST_FORCEINLINE A0 do_(A0 const& a0, nsm::bool_<true> const&) BOOST_NOEXCEPT
    {
      // This shuffle the 32 bits packet of the broadcast so
      // we end up with [ In In+1 In In+1 In In+1 In In+1 ]
      using partial_t = tt::integral_constant< int
                                              ,_MM_SHUFFLE( A1::value / 2,A1::value / 2
                                                          , A1::value / 2,A1::value / 2
                                                          )
                                              >;

      // This select either In or In+1 as 16 bits value and give us
      // [In In In In In In In In] or [In+1 In+1 In+1 In+1 In+1 In+1 In+1 In+1]
      using fix_t = tt::integral_constant< int
                                          , _MM_SHUFFLE ( A1::value % 2,A1::value % 2
                                                        , A1::value % 2,A1::value % 2
                                                        )
                                          >;

      return _mm_shufflehi_epi16( _mm_shufflelo_epi16 ( _mm_shuffle_epi32( a0, partial_t::value)
                                                      , fix_t::value
                                                      )
                                , fix_t::value
                                );
    }

#ifdef __clang__
#pragma clang diagnostic pop
#endif // __clang__

    static BOOST_FORCEINLINE A0 do_(A0 const&, nsm::bool_<false> const&) BOOST_NOEXCEPT
    {
      return Zero<A0>();
    }
  };
} } }

#endif
