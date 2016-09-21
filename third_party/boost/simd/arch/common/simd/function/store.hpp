//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_STORE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_STORE_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/dispatch/adapted/common/pointer.hpp>
#include <boost/simd/function/extract.hpp>
#include <boost/simd/function/slice.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = ::boost::dispatch;
  namespace bs = ::boost::simd;

  //------------------------------------------------------------------------------------------------
  // Whenever we store with an offset
  BOOST_DISPATCH_OVERLOAD ( store_
                          , (typename Src, typename A1, typename X, typename A2)
                          , bd::cpu_
                          , bs::pack_<bd::unspecified_<Src>, X>
                          , bd::pointer_<bd::scalar_<bd::unspecified_<A1>>,1u>
                          , bd::scalar_<bd::integer_<A2>>
                          )
  {
    BOOST_FORCEINLINE void operator()(Src const& a0, A1 a1, A2 const & a2) const BOOST_NOEXCEPT
    {
      bs::store(a0,a1+a2);
    }
  };

  //------------------------------------------------------------------------------------------------
  // Whenever we have no clue how to store
  BOOST_DISPATCH_OVERLOAD( store_
                          , (typename Src, typename Pointer, typename X)
                          , bd::cpu_
                          , bs::pack_<bd::unspecified_<Src>, X>
                          , bd::pointer_<bd::scalar_<bd::unspecified_<Pointer>>,1u>
                          )
  {
    using storage_t = typename Src::storage_type;
    using value_t   = typename storage_t::value_type;
    using s_t       = typename boost::pointee<Pointer>::type;

    BOOST_FORCEINLINE void operator()(const Src& s, Pointer p) const
    {
      do_(s, p, typename Src::storage_kind{}, typename Src::traits::element_range{} );
    }

    // aggregate pack are calling store twice
    template<typename... N> static BOOST_FORCEINLINE
    void do_( Src const & s, Pointer p, aggregate_storage const&, brigand::list<N...> const&)
    {
      store(slice_low(s) , p);
      store(slice_high(s), p+Src::traits::element_size);
    }

    // other pack are calling store N times
    template<typename I> static BOOST_FORCEINLINE void sto_(const Src& s, Pointer  p)
    {
      p[I::value] = static_cast<s_t>(extract<I::value>(s));
    }

    template<typename K, typename... N>
    static BOOST_FORCEINLINE void do_(Src const & s, Pointer p, K const&, brigand::list<N...> const&)
    {
      (void)(std::initializer_list<bool>{(sto_<N>(s,p),true)...});
    }
  };
} } }

#endif
