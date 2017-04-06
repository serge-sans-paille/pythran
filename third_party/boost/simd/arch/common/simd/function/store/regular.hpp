//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_STORE_REGULAR_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_STORE_REGULAR_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/dispatch/adapted/common/pointer.hpp>
#include <boost/simd/detail/dispatch/meta/is_natural.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/if_one_else_zero.hpp>
#include <boost/simd/function/extract.hpp>
#include <boost/simd/function/slice.hpp>
#include <boost/simd/function/shuffle.hpp>
#include <boost/simd/meta/as_arithmetic.hpp>
#include <boost/simd/meta/is_bitwise_logical.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = ::boost::dispatch;
  namespace bs = ::boost::simd;

  //------------------------------------------------------------------------------------------------
  // Whenever we have no clue how to store
  BOOST_DISPATCH_OVERLOAD ( store_
                          , (typename Src, typename Pointer, typename X)
                          , bd::cpu_
                          , bs::pack_<bd::unspecified_<Src>, X>
                          , bd::pointer_<bd::scalar_<bd::unspecified_<Pointer>>,1u>
                          )
  {
    BOOST_FORCEINLINE void operator()(const Src& s, Pointer p) const
    {
      do_(s, p, typename Src::storage_kind{}, typename Src::traits::element_range{} );
    }

    // aggregate pack are calling store twice
    template<typename... N> static BOOST_FORCEINLINE
    void do_( Src const & s, Pointer p, aggregate_storage const&, nsm::list<N...> const&)
    {
      store(slice_low(s) , p);
      store(slice_high(s), p+Src::traits::element_size);
    }

    // other pack are calling store N times
    template<typename I> static BOOST_FORCEINLINE void sto_(const Src& s, Pointer  p)
    {
      using s_t   = typename boost::pointee<Pointer>::type;
      p[I::value] = static_cast<s_t>(extract<I::value>(s));
    }

    template<typename K, typename... N>
    static BOOST_FORCEINLINE void do_(Src const & s, Pointer p, K const&, nsm::list<N...> const&)
    {
      (void)(std::initializer_list<bool>{(sto_<N>(s,p),true)...});
    }
  };

  //------------------------------------------------------------------------------------------------
  // Bitwise_logical logical store
  BOOST_DISPATCH_OVERLOAD_IF( store_
                            , (typename Src, typename Pointer, typename X)
                            , (is_bitwise_logical<Src>)
                            , bd::cpu_
                            , bs::pack_<bs::logical_<Src>, X>
                            , bd::pointer_<bd::scalar_<bd::arithmetic_<Pointer>>,1u>
                            )
  {
    BOOST_FORCEINLINE void operator()(const Src& s, Pointer p) const
    {
      using s_t = typename Src::value_type::value_type;
      store( bitwise_cast<as_arithmetic_t<Src>>(s) , reinterpret_cast<s_t*>(p) );
    }
  };
} } }

#endif
