//==================================================================================================
/*!
    @file

    @Copyright 2016 Numscale SAS

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_NBTRUE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_NBTRUE_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/meta/as_logical.hpp>
#include <boost/simd/function/genmask.hpp>
#include <boost/simd/function/popcnt.hpp>
#include <boost/simd/meta/cardinal_of.hpp>
#include <boost/simd/detail/dispatch/meta/scalar_of.hpp>
#include <boost/simd/detail/make_dependent.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;
  BOOST_DISPATCH_OVERLOAD ( nbtrue_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::integer_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE std::size_t operator() ( const A0 & a0) const BOOST_NOEXCEPT
    {
      using i8type = typename detail::make_dependent<pack<int8_t,16>, A0>::type;
      i8type tmp = bitwise_cast<i8type>(genmask(a0));
      return bs::popcnt(_mm_movemask_epi8(tmp)) * bs::cardinal_of<A0>::value >> 4;
    }
  };
  BOOST_DISPATCH_OVERLOAD ( nbtrue_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bs::logical_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE std::size_t operator() ( const A0 & a0 ) const BOOST_NOEXCEPT
    {
      using i8type = typename detail::make_dependent<pack<int8_t,16>, A0>::type;
      i8type tmp = bitwise_cast<i8type>(genmask(a0));
      return bs::popcnt(_mm_movemask_epi8(tmp)) * bs::cardinal_of<A0>::value >> 4;
    }
  };
  BOOST_DISPATCH_OVERLOAD ( nbtrue_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::double_<A0>, bs::sse_>
                         )
  {
    BOOST_FORCEINLINE std::size_t operator() ( const A0 & a0) const BOOST_NOEXCEPT
    {
      return bs::popcnt(_mm_movemask_pd(genmask(a0)));
    }
  };

} } }

#endif

