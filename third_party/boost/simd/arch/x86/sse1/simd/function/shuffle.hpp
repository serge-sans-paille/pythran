//==================================================================================================
/**
  Copyright 2016 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE1_SIMD_FUNCTION_SHUFFLE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE1_SIMD_FUNCTION_SHUFFLE_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/shuffle.hpp>
#include <boost/simd/detail/shuffle/shuffler.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/arch/x86/sse1/simd/function/topology.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  namespace bs =  boost::simd;

  // -----------------------------------------------------------------------------------------------
  // Unary SSE 4xfloat shuffle
  BOOST_DISPATCH_OVERLOAD ( shuffle_
                          , (int... Ps, typename A0)
                          , bs::sse1_
                          , bs::detail::pattern_<Ps...>
                          , bs::pack_<bd::single_<A0>, bs::sse_>
                         )
  {
    static_assert ( sizeof...(Ps) == 4
                  , "boost::simd::shuffle - Invalid number of permutation indices"
                  );

    BOOST_FORCEINLINE
    A0 operator()(bs::detail::pattern_<Ps...> const&, const A0 & a0) const
    {
      return detail::shuffler<detail::sse1_shuffle,detail::pattern_<Ps...>>::process(a0);
    }
  };

  // -----------------------------------------------------------------------------------------------
  // Binary SSE 4xfloat shuffle
  BOOST_DISPATCH_OVERLOAD ( shuffle_
                          , (int... Ps, typename A0)
                          , bs::sse1_
                          , bs::detail::pattern_<Ps...>
                          , bs::pack_<bd::single_<A0>, bs::sse_>
                          , bs::pack_<bd::single_<A0>, bs::sse_>
                         )
  {
    static_assert ( sizeof...(Ps) == 4
                  , "boost::simd::shuffle - Invalid number of permutation indices"
                  );

    BOOST_FORCEINLINE
    A0 operator()(bs::detail::pattern_<Ps...> const&, const A0 & a0, const A0 & a1) const
    {
      return detail::shuffler<detail::sse1_shuffle,detail::pattern_<Ps...>>::process(a0,a1);
    }
  };
} } }

#endif
