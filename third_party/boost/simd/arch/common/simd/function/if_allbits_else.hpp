//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_IF_ALLBITS_ELSE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_COMMON_SIMD_FUNCTION_IF_ALLBITS_ELSE_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/meta/is_bitwise_logical.hpp>
#include <boost/simd/function/bitwise_or.hpp>
#include <boost/simd/function/genmask.hpp>
#include <boost/simd/function/if_else.hpp>
#include <boost/simd/constant/allbits.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  BOOST_DISPATCH_OVERLOAD_IF( if_allbits_else_
                            , (typename A0, typename A1, typename X)
                            , (detail::is_native<X>)
                            , bd::cpu_
                            , bs::pack_<bd::fundamental_<A0>, X>
                            , bs::pack_<bd::fundamental_<A1>, X>
                            )
  {
    BOOST_FORCEINLINE A1 operator()(A0 const& a0, A1 const& a1) const
    {
      return do_(a0,a1,typename bs::is_bitwise_logical<A0>::type{});
    }

    BOOST_FORCEINLINE A1 do_(A0 const& a0, A1 const& a1, tt::true_type const&) const
    {
      return bitwise_or(a1, genmask(a0));
    }

    BOOST_FORCEINLINE A1 do_(A0 const& a0, A1 const& a1, tt::false_type const&) const
    {
      return if_else(a0, Allbits<A1>(), a1);
    }
  };
} } }

#endif

