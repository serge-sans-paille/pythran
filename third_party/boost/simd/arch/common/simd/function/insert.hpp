//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_INSERT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_INSERT_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/genmask.hpp>
#include <boost/simd/detail/aliasing.hpp>
#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/meta/hierarchy/logical.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( insert_
                          , (typename A0, typename Ext, typename A1, typename A2)
                          , bd::cpu_
                          , bs::pack_<bd::unspecified_<A0>,Ext>
                          , bd::scalar_< bd::integer_<A1>>
                          , bd::scalar_< bd::unspecified_<A2>>
                          )
  {

    BOOST_FORCEINLINE void operator() ( A0 & a0, A1 const& a1, A2 const & a2) const BOOST_NOEXCEPT
    {
      reinterpret_cast<detail::may_alias_t<bd::scalar_of_t<A0>>*>(&a0.storage())[a1] = a2;
    }
  };

  BOOST_DISPATCH_OVERLOAD ( insert_
                          , (typename A0, typename Ext, typename A1, typename A2)
                          , bd::cpu_
                          , bs::pack_<bs::logical_<A0>,Ext>
                          , bd::scalar_< bd::integer_<A1>>
                          , bd::scalar_< bd::unspecified_<A2>>
                          )
  {
    static inline void do_( A0 & a0, A1 const& a1, A2 const & a2, aggregate_storage const&) BOOST_NOEXCEPT
    {
      A0::traits::at(a0,a1) = a2;
    }

    template<typename K>
    static inline void do_( A0 & a0, A1 const& a1, A2 const & a2, K const&) BOOST_NOEXCEPT
    {
      using value_t = typename A0::value_type::value_type;
      using ptr_t   = detail::may_alias_t<value_t>*;
      reinterpret_cast<ptr_t>(&a0.storage())[a1] = genmask<value_t>(a2);
    }

    BOOST_FORCEINLINE void operator() ( A0 & a0, A1 const& a1, A2 const & a2) const BOOST_NOEXCEPT
    {
      do_(a0,a1,a2, typename A0::storage_kind{});
    }
  };
} } }

#endif
