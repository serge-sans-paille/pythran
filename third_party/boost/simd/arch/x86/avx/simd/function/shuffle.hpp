//==================================================================================================
/**
  Copyright 2016 Numscale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_SHUFFLE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_SHUFFLE_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/shuffle.hpp>
#include <boost/simd/detail/shuffle/shuffler.hpp>
#include <boost/simd/arch/x86/avx/simd/function/topology.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd  =  boost::dispatch;
  namespace bs  =  boost::simd;
  namespace bsd =  boost::simd::detail;

  // -----------------------------------------------------------------------------------------------
  // Specific AVX shuffle on SSEx register
  // As there is no binary special intrinsic for those in AVX, we just let SSSE3 handle them
  BOOST_DISPATCH_OVERLOAD ( shuffle_
                          , (int... Ps, typename A0)
                          , bs::avx_
                          , bsd::pattern_<Ps...>
                          , bs::pack_<bd::type64_<A0>, bs::sse_>
                         )
  {
    static_assert ( sizeof...(Ps) == 2
                  , "boost::simd::shuffle - Invalid number of permutation indices"
                  );

    BOOST_FORCEINLINE A0 operator()(bsd::pattern_<Ps...> const&, const A0 & a0) const
    {
      return detail::shuffler<detail::avx_128_shuffle,detail::pattern_<Ps...>>::process(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( shuffle_
                          , (int... Ps, typename A0)
                          , bs::avx_
                          , bsd::pattern_<Ps...>
                          , bs::pack_<bd::ints32_<A0>, bs::sse_>
                         )
  {
    static_assert ( sizeof...(Ps) == 4
                  , "boost::simd::shuffle - Invalid number of permutation indices"
                  );

    BOOST_FORCEINLINE A0 operator()(bsd::pattern_<Ps...> const&, const A0 & a0) const
    {
      return detail::shuffler<detail::avx_128_shuffle,detail::pattern_<Ps...>>::process(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( shuffle_
                          , (int... Ps, typename A0)
                          , bs::avx_
                          , bsd::pattern_<Ps...>
                          , bs::pack_<bd::single_<A0>, bs::sse_>
                         )
  {
    static_assert ( sizeof...(Ps) == 4
                  , "boost::simd::shuffle - Invalid number of permutation indices"
                  );

    BOOST_FORCEINLINE A0 operator()(bsd::pattern_<Ps...> const&, const A0 & a0) const
    {
      return detail::shuffler<detail::avx_128_shuffle,detail::pattern_<Ps...>>::process(a0);
    }
  };

  // -----------------------------------------------------------------------------------------------
  // Specific AVX shuffle on AVX register - 8x32 case
  BOOST_DISPATCH_OVERLOAD ( shuffle_
                          , (int... Ps, typename A0)
                          , bs::avx_
                          , bsd::pattern_<Ps...>
                          , bs::pack_<bd::type32_<A0>, bs::avx_>
                         )
  {
    static_assert ( sizeof...(Ps) == 8
                  , "boost::simd::shuffle - Invalid number of permutation indices"
                  );

    BOOST_FORCEINLINE
    A0 operator()(bsd::pattern_<Ps...> const&, const A0 & a0) const
    {
      return detail::shuffler<detail::avx_256_shuffle,detail::pattern_<Ps...>>::process(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( shuffle_
                          , (int... Ps, typename A0)
                          , bs::avx_
                          , bsd::pattern_<Ps...>
                          , bs::pack_<bd::type32_<A0>, bs::avx_>
                          , bs::pack_<bd::type32_<A0>, bs::avx_>
                          )
  {
    static_assert ( sizeof...(Ps) == 8
                  , "boost::simd::shuffle - Invalid number of permutation indices"
                  );

    BOOST_FORCEINLINE
    A0 operator()(bsd::pattern_<Ps...> const&, const A0 & a0, const A0 & a1) const
    {
      return detail::shuffler<detail::avx_256_shuffle,detail::pattern_<Ps...>>::process(a0,a1);
    }
  };

  // -----------------------------------------------------------------------------------------------
  // Specific AVX shuffle on AVX register - 4x64 case
  BOOST_DISPATCH_OVERLOAD ( shuffle_
                          , (int... Ps, typename A0)
                          , bs::avx_
                          , bsd::pattern_<Ps...>
                          , bs::pack_<bd::type64_<A0>, bs::avx_>
                         )
  {
    static_assert ( sizeof...(Ps) == 4
                  , "boost::simd::shuffle - Invalid number of permutation indices"
                  );

    BOOST_FORCEINLINE
    A0 operator()(bsd::pattern_<Ps...> const&, const A0 & a0) const
    {
      return detail::shuffler<detail::avx_256_shuffle,detail::pattern_<Ps...>>::process(a0);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( shuffle_
                          , (int... Ps, typename A0)
                          , bs::avx_
                          , bsd::pattern_<Ps...>
                          , bs::pack_<bd::type64_<A0>, bs::avx_>
                          , bs::pack_<bd::type64_<A0>, bs::avx_>
                          )
  {
    static_assert ( sizeof...(Ps) == 4
                  , "boost::simd::shuffle - Invalid number of permutation indices"
                  );

    BOOST_FORCEINLINE
    A0 operator()(bsd::pattern_<Ps...> const&, const A0 & a0, const A0 & a1) const
    {
      return detail::shuffler<detail::avx_256_shuffle,detail::pattern_<Ps...>>::process(a0,a1);
    }
  };
} } }

#endif
