//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_LOOKUP_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_LOOKUP_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/meta/cardinal_of.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/extract.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD_IF( lookup_
                            , (typename A0, typename A1, typename X, typename Y)
                            , (nsm::equal_to<cardinal_of<A0>,cardinal_of<A1>>)
                            , bd::cpu_
                            , bs::pack_<bd::unspecified_<A0>, X>
                            , bs::pack_<bd::integer_<A1>, Y>
                            )
  {
    BOOST_FORCEINLINE A0 operator()(const A0& a0, const A1&  a1) const BOOST_NOEXCEPT
    {
      return do_(a0,a1, typename A0::traits::element_range{});
    }

    template<typename... N> BOOST_FORCEINLINE
    A0 do_(const A0& a0, const A1& a1, nsm::list<N...> const&) const BOOST_NOEXCEPT
    {
      return A0( a0[extract<N::value>(a1)]... );
    }
  };
} } }

#endif
