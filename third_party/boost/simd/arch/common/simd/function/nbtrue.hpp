//==================================================================================================
/**
  Cpyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_NBTRUE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_NBTRUE_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/is_nez.hpp>
#include <boost/simd/function/extract.hpp>
#include <boost/simd/function/slice.hpp>
#include <boost/simd/function/if_one_else_zero.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = ::boost::dispatch;
  namespace bs = ::boost::simd;

  BOOST_DISPATCH_OVERLOAD ( nbtrue_
                          , (typename A0, typename X)
                          , bd::cpu_
                          , bs::pack_<bd::fundamental_<A0>,X>
                          )
  {
    BOOST_FORCEINLINE std::size_t operator()(A0 const& a0) const BOOST_NOEXCEPT
    {
      return nbtrue(is_nez(a0));
    }
  };

  BOOST_DISPATCH_OVERLOAD ( nbtrue_
                          , (typename A0, typename X)
                          , bd::cpu_
                          , bs::pack_<bs::logical_<A0>,X>
                          )
  {
    BOOST_FORCEINLINE std::size_t operator()(A0 const& a0) const BOOST_NOEXCEPT
    {
      return do_( a0, typename A0::storage_kind(), typename A0::traits::static_range{});
    }

    // Aggregate case: add the nbtrue of both sides
    template<typename... N> static BOOST_FORCEINLINE
    std::size_t do_(A0 const& a0, aggregate_storage const&, nsm::list<N...> const&) BOOST_NOEXCEPT
    {
      return nbtrue(slice_low(a0)) + nbtrue(slice_high(a0));
    }

    // Other case: Compute nbtrue piecewise
    template<typename K, typename... N> static BOOST_FORCEINLINE
    std::size_t do_(A0 const& a0, K const&, nsm::list<N...> const&) BOOST_NOEXCEPT
    {
      std::size_t that = 0;

      (void)std::initializer_list<std::size_t>
      {
        (that += if_one_else_zero(bs::extract<N::value>(a0)))...
      };

      return that;
    }
  };
} } }

#endif
