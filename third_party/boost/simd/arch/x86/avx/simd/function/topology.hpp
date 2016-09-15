//==================================================================================================
/**
  Copyright 2016 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_TOPOLOGY_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_TOPOLOGY_HPP_INCLUDED

#include <boost/simd/detail/shuffle.hpp>
#include <boost/simd/arch/common/simd/function/shuffle/repeat.hpp>
#include <boost/simd/arch/common/simd/function/shuffle/slide.hpp>
#include <boost/simd/arch/common/simd/function/shuffle/deinterleave.hpp>
#include <boost/simd/arch/common/simd/function/shuffle/interleave.hpp>
#include <boost/simd/arch/x86/avx/simd/function/shuffle/shuffle.hpp>
#include <boost/simd/arch/x86/avx/simd/function/shuffle/blend.hpp>
#include <boost/simd/arch/x86/avx/simd/function/shuffle/perm.hpp>
#include <boost/simd/arch/x86/avx/simd/function/shuffle/sse.hpp>
#include <boost/simd/function/combine.hpp>
#include <boost/simd/function/slice.hpp>

namespace boost { namespace simd { namespace detail
{
  // -----------------------------------------------------------------------------------------------
  // AVX shuffling patterns
  struct  avx_256_shuffle
        : default_matcher
        , repeat_shuffle, slide_shuffle
        , deinterleave_shuffle, interleave_shuffle
        , blend_shuffle, perm_shuffle, shuffle_shuffle
  {
    using default_matcher::process;
    using repeat_shuffle::process;
    using slide_shuffle::process;
    using deinterleave_shuffle::process;
    using interleave_shuffle::process;
    using blend_shuffle::process;
    using perm_shuffle::process;
    using shuffle_shuffle::process;

    // Random unary shuffling use the slice-then-shuffle strategy
    template<typename T,int... Ps> static BOOST_FORCEINLINE
    T process(const T& a0, pattern_<Ps...> const&)
    {
      auto s = slice(a0);
      return combine( shuffle<half_<false,Ps...>>(s[0],s[1])
                    , shuffle<half_<true ,Ps...>>(s[0],s[1])
                    );
    }
  };
} } }

#endif
