//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_CAST_BASIC_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_CAST_BASIC_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/dispatch/as.hpp>
#include <boost/simd/detail/traits.hpp>
#include <boost/simd/detail/nsm.hpp>
#include <boost/simd/function/combine.hpp>
#include <boost/simd/function/slice.hpp>
#include <type_traits>

namespace boost { namespace simd { namespace ext
{
 namespace bd = boost::dispatch;
 namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( pack_cast_
                          , (typename A0, typename A1, typename X)
                          , bd::cpu_
                          , bs::pack_< bd::unspecified_<A0>, X>
                          , bd::target_< bd::scalar_< bd::unspecified_<A1> > >
                          )
  {
    using result = typename A0::template rebind<typename A1::type>;

    BOOST_FORCEINLINE result operator()(A0 const& a0, A1 const& ) const BOOST_NOEXCEPT
    {
      return do_(a0, typename std::is_same<A0, result>::type{});
    }

    template<typename... N>
    BOOST_FORCEINLINE result manual(A0 const& a0, nsm::list<N...> const&) const BOOST_NOEXCEPT
    {
      return result{static_cast<typename A1::type>(a0[N::value])...};
    }

    BOOST_FORCEINLINE result combined(A0 const& a0) const BOOST_NOEXCEPT
    {
      using tg_t = typename A1::type;
      return combine( pack_cast<tg_t>(slice_low(a0)), pack_cast<tg_t>(slice_high(a0)) );
    }

    template<typename K0, typename K1>
    BOOST_FORCEINLINE result do_( A0 const& a0, K0 const&, K1 const&) const BOOST_NOEXCEPT
    {
      return manual(a0, typename A0::traits::element_range{});
    }

    BOOST_FORCEINLINE result do_( A0 const& a0
                                , aggregate_storage const&, aggregate_storage const&
                                ) const BOOST_NOEXCEPT
    {
      return combined( a0 );
    }

    BOOST_FORCEINLINE result do_( A0 const& a0
                                , aggregate_storage const&, native_storage const&
                                ) const BOOST_NOEXCEPT
    {
      return combined( a0 );
    }

    BOOST_FORCEINLINE result do_( A0 const& a0
                                , native_storage const&, aggregate_storage const&
                                ) const BOOST_NOEXCEPT
    {
      return combined( a0 );
    }

    BOOST_FORCEINLINE result do_(A0 const& a0, std::false_type ) const BOOST_NOEXCEPT
    {
      return do_( a0, typename A0::storage_kind{}, typename result::storage_kind{} );
    }

    BOOST_FORCEINLINE result do_(A0 const& a0, std::true_type const& ) const BOOST_NOEXCEPT
    {
      return a0;
    }
  };
} } }

#endif
