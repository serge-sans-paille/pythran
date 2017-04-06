//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SPLAT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SPLAT_HPP_INCLUDED

#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/meta/as_arithmetic.hpp>
#include <boost/simd/function/genmask.hpp>
#include <boost/simd/function/combine.hpp>
#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/nsm.hpp>

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4244) // conversion and loss of data
#endif
#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-braces"
#endif
namespace boost { namespace simd { namespace ext
{
  namespace bd = ::boost::dispatch;
  namespace bs = ::boost::simd;

  //------------------------------------------------------------------------------------------------
  // splat from a scalar to a pack
  BOOST_DISPATCH_OVERLOAD ( splat_
                          , (typename Target, typename V)
                          , bd::cpu_
                          , bd::scalar_<bd::unspecified_<V>>
                          , bd::target_<bs::pack_<bd::unspecified_<Target>,bs::simd_emulation_>>
                          )
  {
    using target_t  = typename Target::type;
    using storage_t = typename target_t::storage_type;
    using value_t   = typename storage_t::value_type;

    BOOST_FORCEINLINE target_t operator()(V const& v, Target const&) const
    {
      return do_(v, typename target_t::storage_kind{}, typename target_t::traits::static_range{} );
    }

    template<typename N, typename T>
    BOOST_FORCEINLINE T const& value_(T const& t) const { return t; }

    template<typename K, typename N>
    BOOST_FORCEINLINE target_t do_(V const& v, K const&, nsm::list<N> const&) const
    {
      target_t that;
      that[0] = value_t(v);
      return that;
    }

    template<typename K, typename N0, typename N1, typename... N>
    BOOST_FORCEINLINE target_t do_(V const& v, K const&, nsm::list<N0,N1,N...> const&) const
    {
      value_t s(v);
      return {value_<N0>(s),value_<N1>(s),value_<N>(s)...};
    }

    template<typename N0, typename N1, typename... N> BOOST_FORCEINLINE
    target_t do_(V const& v, aggregate_storage const&, nsm::list<N0,N1,N...> const&) const
    {
      typename storage_t::value_type s(v);
      return combine(s,s);
    }
  };

  //------------------------------------------------------------------------------------------------
  // splat from a scalar to a pack of logical
  BOOST_DISPATCH_OVERLOAD ( splat_
                          , (typename Target, typename V, typename Ext)
                          , bd::cpu_
                          , bd::scalar_<bd::unspecified_<V>>
                          , bd::target_<bs::pack_<bs::logical_<Target>,Ext>>
                          )
  {
    using target_t  = typename Target::type;
    using storage_t = typename target_t::storage_type;

    BOOST_FORCEINLINE target_t operator()(V const& v, Target const&) const
    {
      return do_(v, typename target_t::storage_kind{}, typename target_t::traits::static_range{} );
    }

    template<typename K, typename... N>
    BOOST_FORCEINLINE target_t do_(V const& v, K const&, nsm::list<N...> const&) const
    {
      using base_t  = as_arithmetic_t<target_t>;
      return bitwise_cast<target_t>( genmask<base_t>(v) );
    }

    template<typename... N>
    BOOST_FORCEINLINE
    target_t do_(V const& v, aggregate_storage const&, nsm::list<N...> const&) const
    {
      typename storage_t::value_type s(!!v);
      return combine(s,s);
    }
  };
} } }

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif
#if defined(__GNUC__)
#pragma GCC diagnostic pop
#endif
#endif
