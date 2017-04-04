//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_CAST_DOWNCAST_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_CAST_DOWNCAST_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/dispatch/as.hpp>
#include <boost/simd/detail/dispatch/meta/downgrade.hpp>
#include <boost/simd/detail/traits.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/function/deinterleave.hpp>
#include <boost/simd/function/slice_low.hpp>
#include <boost/simd/constant/zero.hpp>
#include <type_traits>

namespace boost { namespace simd { namespace detail
{
  // -----------------------------------------------------------------------------------------------
  // downward cast with sign
  template<typename A0, typename A1>
  struct downward_cast
  {
    using result = typename A0::template rebind<typename A1::type>;
    static BOOST_FORCEINLINE result do_(const A0& a0 ) BOOST_NOEXCEPT
    {
      using sub = pack<typename A1::type, A0::static_size*2>;

      #if BOOST_ENDIAN_BIG_BYTE
      auto x = deinterleave_second(bitwise_cast<sub>(a0), Zero<sub>());
      #else
      auto x = deinterleave_first(bitwise_cast<sub>(a0), Zero<sub>());
      #endif

      return slice_low( x );
    }
  };
} } }

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD_IF( pack_cast_
                            , (typename A0, typename A1, typename S, typename X, std::size_t N)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_<bd::integral_<A0,2*N,S>, X>
                            , bd::target_< bd::scalar_< bd::ints_<A1,N> > >
                            )
  {
    using result = typename A0::template rebind<typename A1::type>;

    BOOST_FORCEINLINE result operator()(const A0 & a0, A1 const&) const BOOST_NOEXCEPT
    {
      return detail::downward_cast<A0,A1>::do_( a0 );
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF( pack_cast_
                            , (typename A0, typename A1, typename S, typename X, std::size_t N)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_<bd::integral_<A0,4*N,S>, X>
                            , bd::target_< bd::scalar_< bd::ints_<A1,N> > >
                            )
  {
    using result = typename A0::template rebind<typename A1::type>;

    BOOST_FORCEINLINE result operator()(const A0 & a0, A1 const&) const BOOST_NOEXCEPT
    {
      using tgt = typename bd::downgrade_t<A0>::value_type;
      return pack_cast<typename A1::type>( pack_cast<tgt>(a0) );
    }
  };

  BOOST_DISPATCH_OVERLOAD_IF( pack_cast_
                            , (typename A0, typename A1, typename S, typename X, std::size_t N)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_<bd::integral_<A0,8*N,S>, X>
                            , bd::target_< bd::scalar_< bd::ints_<A1,N> > >
                            )
  {
    using result = typename A0::template rebind<typename A1::type>;

    BOOST_FORCEINLINE result operator()(const A0 & a0, A1 const&) const BOOST_NOEXCEPT
    {
      using tgt = typename bd::downgrade_t<A0>::value_type;
      return pack_cast<typename A1::type>( pack_cast<tgt>(a0) );
    }
  };
} } }

#endif
