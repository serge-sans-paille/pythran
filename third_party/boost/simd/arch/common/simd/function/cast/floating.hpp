//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_CAST_FLOATING_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_CAST_FLOATING_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/dispatch/as.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <type_traits>

namespace boost { namespace simd { namespace ext
{
 namespace bd = boost::dispatch;
 namespace bs = boost::simd;

  // -----------------------------------------------------------------------------------------------
  // integer -> float
  BOOST_DISPATCH_OVERLOAD_IF( pack_cast_
                            , (typename A0, typename A1, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_<bd::integer_<A0>, X>
                            , bd::target_< bd::scalar_< bd::single_<A1> > >
                            )
  {
    using result = typename A0::template rebind<typename A1::type>;

    BOOST_FORCEINLINE result operator()(A0 const& a0, A1 const& ) const BOOST_NOEXCEPT
    {
      using tgt_t = bd::as_integer_t<typename A1::type>;
      return pack_cast<typename A1::type>( pack_cast<tgt_t>(a0) );
    }
  };

  // -----------------------------------------------------------------------------------------------
  // float -> integer
  BOOST_DISPATCH_OVERLOAD_IF( pack_cast_
                            , (typename A0, typename A1, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_<bd::single_<A0>, X>
                            , bd::target_< bd::scalar_< bd::integer_<A1> > >
                            )
  {
    using result = typename A0::template rebind<typename A1::type>;

    BOOST_FORCEINLINE result operator()(A0 const& a0, A1 const& ) const BOOST_NOEXCEPT
    {
      using tgt_t = bd::as_integer_t<typename A0::value_type>;
      return pack_cast<typename A1::type>( pack_cast<tgt_t>(a0) );
    }
  };

  // -----------------------------------------------------------------------------------------------
  // integer -> double
  BOOST_DISPATCH_OVERLOAD_IF( pack_cast_
                            , (typename A0, typename A1, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_<bd::integer_<A0>, X>
                            , bd::target_< bd::scalar_< bd::double_<A1> > >
                            )
  {
    using result = typename A0::template rebind<typename A1::type>;

    BOOST_FORCEINLINE result operator()(A0 const& a0, A1 const& ) const BOOST_NOEXCEPT
    {
      using tgt_t = bd::downgrade_t<typename A1::type>;
      return pack_cast<typename A1::type>( pack_cast<tgt_t>(a0) );
    }
  };

  // -----------------------------------------------------------------------------------------------
  // double -> integer
  BOOST_DISPATCH_OVERLOAD_IF( pack_cast_
                            , (typename A0, typename A1, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_<bd::double_<A0>, X>
                            , bd::target_< bd::scalar_< bd::integer_<A1> > >
                            )
  {
    using result = typename A0::template rebind<typename A1::type>;

    BOOST_FORCEINLINE result operator()(A0 const& a0, A1 const& ) const BOOST_NOEXCEPT
    {
      using tgt_t = bd::downgrade_t<typename A0::value_type>;
      return pack_cast<typename A1::type>( pack_cast<tgt_t>(a0) );
    }
  };
} } }

#endif
