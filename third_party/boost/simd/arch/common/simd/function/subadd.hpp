//==================================================================================================
/**
  Copyright 2017 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SUBADD_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_SUBADD_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/traits.hpp>
#include <boost/simd/function/slice.hpp>
#include <boost/simd/function/combine.hpp>
#include <boost/simd/function/fma.hpp>
#include <boost/simd/meta/hierarchy/simd.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD ( subadd_
                          , (typename A0, typename X)
                          , bd::cpu_
                          , bs::pack_<bd::arithmetic_<A0>, X>
                          , bs::pack_<bd::arithmetic_<A0>, X>
                          )
   {

      template<typename... N>
      BOOST_FORCEINLINE A0 do_( const A0& a0, const A0& a1
                              , scalar_storage const&,  nsm::list<N...> const&
                              ) const BOOST_NOEXCEPT
      {
        return A0 ( (nsm::bool_<N::value%2>::value ? extract<N::value>(a0) + extract<N::value>(a1)
                                                   : extract<N::value>(a0) - extract<N::value>(a1)
                    )...
                  );
      }

      template<typename ... N>
      BOOST_FORCEINLINE A0 do_( const A0& a0, const A0& a1
                              , native_storage const&, nsm::list<N...> const&
                              ) const BOOST_NOEXCEPT
      {
        A0 twd( nsm::ptrdiff_t<(N::value%2 ?  1 : -1)>::value... );
        return fma(a1,twd,a0);
      }

      template<typename L>
      BOOST_FORCEINLINE A0 do_( const A0& a0, const A0& a1
                              , aggregate_storage const&, L const&
                              ) const BOOST_NOEXCEPT
      {
        auto h0 = slice_high(a0);
        auto h1 = slice_high(a1);
        auto l0 = slice_low(a0);
        auto l1 = slice_low(a1);
        return combine( subadd(l0,l1), subadd(h0,h1) );
      }

      BOOST_FORCEINLINE A0 operator()(const A0& a0, const A0& a1) const BOOST_NOEXCEPT
      {
        return do_(a0, a1, typename A0::storage_kind{}, typename A0::traits::element_range{});
      }
   };
} } }

#endif
