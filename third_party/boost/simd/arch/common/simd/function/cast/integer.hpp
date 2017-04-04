//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_CAST_INTEGER_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_CAST_INTEGER_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/dispatch/as.hpp>
#include <boost/simd/detail/traits.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/function/if_allbits_else_zero.hpp>
#include <boost/simd/function/interleave.hpp>
#include <boost/simd/function/combine.hpp>
#include <boost/simd/function/is_ltz.hpp>
#include <boost/simd/function/slice.hpp>
#include <boost/simd/constant/zero.hpp>
#include <type_traits>

namespace boost { namespace simd { namespace detail
{
  // -----------------------------------------------------------------------------------------------
  // upward cast with sign
  template<typename A0, typename A1, bool Sign>
  struct upward_cast
  {
    using result = typename A0::template rebind<typename A1::type>;
    static BOOST_FORCEINLINE result do_(const A0& a0 ) BOOST_NOEXCEPT
    {
      using upw = pack<typename A1::type, A0::static_size/2>;

      #if BOOST_ENDIAN_BIG_BYTE
      auto x = interleave(if_allbits_else_zero(is_ltz(a0)),a0);
      #else
      auto x = interleave(a0,if_allbits_else_zero(is_ltz(a0)));
      #endif

      return combine(bitwise_cast<upw>(x[0]),bitwise_cast<upw>(x[1]));
    }
  };

  template<typename A0, typename A1>
  struct upward_cast<A0, A1, false>
  {
    using result = typename A0::template rebind<typename A1::type>;
    static BOOST_FORCEINLINE result do_(const A0& a0) BOOST_NOEXCEPT
    {
      using upw = bd::upgrade_t<A0, bd::sign_of_t<typename A1::type>>;

      #if BOOST_ENDIAN_BIG_BYTE
      auto x = interleave(Zero<A0>(),a0);
      #else
      auto x = interleave(a0,Zero<A0>());
      #endif

      return combine(bitwise_cast<upw>(x[0]),bitwise_cast<upw>(x[1]));
    }
  };
} } }

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  // -----------------------------------------------------------------------------------------------
  // uint8/16 -> ints32/64
  BOOST_DISPATCH_OVERLOAD_IF( pack_cast_
                            , (typename A0, typename A1, typename S, typename X, std::size_t N)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_<bd::integral_<A0,N,S>, X>
                            , bd::target_< bd::scalar_< bd::ints_<A1,4*N> > >
                            )
  {
    using result = typename A0::template rebind<typename A1::type>;

    BOOST_FORCEINLINE result operator()(const A0 & a0, A1 const&) const BOOST_NOEXCEPT
    {
      using tgt = typename bd::upgrade_t<A0>::value_type;
      auto x = pack_cast<tgt>(a0);

      return combine( pack_cast<typename A1::type>(slice_low(x))
                    , pack_cast<typename A1::type>(slice_high(x))
                    );
    }
  };

  // -----------------------------------------------------------------------------------------------
  // int8 -> ints16
  BOOST_DISPATCH_OVERLOAD_IF( pack_cast_
                            , (typename A0, typename A1, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_<bd::ints8_<A0>, X>
                            , bd::target_< bd::scalar_< bd::ints16_<A1> > >
                            )
  {
    using result = typename A0::template rebind<typename A1::type>;
    BOOST_FORCEINLINE result operator() ( const A0 & a0, A1 const& ) const BOOST_NOEXCEPT
    {
      return detail::upward_cast<A0, A1, std::is_signed<typename A0::value_type>::value>::do_(a0);
    }
  };

  // -----------------------------------------------------------------------------------------------
  // int16 -> ints32
  BOOST_DISPATCH_OVERLOAD_IF( pack_cast_
                            , (typename A0, typename A1, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_<bd::ints16_<A0>, X>
                            , bd::target_< bd::scalar_< bd::ints32_<A1> > >
                            )
  {
    using result = typename A0::template rebind<typename A1::type>;
    BOOST_FORCEINLINE result operator() ( const A0 & a0, A1 const& ) const BOOST_NOEXCEPT
    {
      return detail::upward_cast<A0, A1, std::is_signed<typename A0::value_type>::value>::do_(a0);
    }
  };

  // -----------------------------------------------------------------------------------------------
  // int32 -> ints64
  BOOST_DISPATCH_OVERLOAD_IF( pack_cast_
                            , (typename A0, typename A1, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_<bd::ints32_<A0>, X>
                            , bd::target_< bd::scalar_< bd::ints64_<A1> > >
                            )
  {
    using result = typename A0::template rebind<typename A1::type>;
    BOOST_FORCEINLINE result operator() ( const A0 & a0, A1 const& ) const BOOST_NOEXCEPT
    {
      return detail::upward_cast<A0, A1, std::is_signed<typename A0::value_type>::value>::do_(a0);
    }
  };
} } }

#endif
