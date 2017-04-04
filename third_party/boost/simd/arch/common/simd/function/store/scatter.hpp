//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_STORE_SCATTER_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_STORE_SCATTER_HPP_INCLUDED

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
  // Whenever we have no clue how to store
  BOOST_DISPATCH_OVERLOAD( store_
                          , ( typename Src, typename X
                            , typename Pointer
                            , typename Offset, typename Y
                            )
                          , bd::cpu_
                          , bs::pack_<bd::unspecified_<Src>, X>
                          , bd::pointer_<bd::scalar_<bd::unspecified_<Pointer>>,1u>
                          , bs::pack_<bd::integer_<Offset>, Y>
                          )
  {
    static_assert ( int(Offset::static_size) == int(Src::static_size)
                  , "boost::simd::store - Mismatched scatter offset cardinal"
                  );

    BOOST_FORCEINLINE void operator()(const Src& s, Pointer p, Offset const o) const
    {
      do_(s, p, o, typename Src::storage_kind{}, typename Src::traits::element_range{} );
    }

    // aggregate pack are calling store twice
    template<typename... N> static BOOST_FORCEINLINE
    void do_( Src const & s, Pointer p, Offset const o
            , aggregate_storage const&, nsm::list<N...> const&
            )
    {
      store(slice_low(s) , p, slice_low(o) );
      store(slice_high(s), p, slice_high(o));
    }

    // other pack are storing N times
    template<typename I> static BOOST_FORCEINLINE void sto_(const Src& s, Pointer  p, Offset const o)
    {
      using s_t = typename boost::pointee<Pointer>::type;
      p[extract<I::value>(o)] = static_cast<s_t>(extract<I::value>(s));
    }

    template<typename K, typename... N>
    static BOOST_FORCEINLINE void do_ ( Src const & s, Pointer p, Offset const o
                                      , K const&, nsm::list<N...> const&
                                      )
    {
      (void)(std::initializer_list<bool>{(sto_<N>(s,p,o),true)...});
    }
  };
} } }

#endif
