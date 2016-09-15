//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_LOAD_GATHER_128_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX2_SIMD_FUNCTION_LOAD_GATHER_128_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/detail/dispatch/adapted/common/pointer.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = ::boost::dispatch;
  namespace bs = ::boost::simd;

  //------------------------------------------------------------------------------------------------
  // loads with gather semantic for 128 bits targets with 32 bits indexes
  //------------------------------------------------------------------------------------------------

  //------------------------------------------------------------------------------------------------
  // gather single
  BOOST_DISPATCH_OVERLOAD ( load_
                          , (typename Pointer, typename Offset, typename Target)
                          , bs::avx2_
                          , bd::pointer_<bd::scalar_<bd::single_<Pointer>>,1u>
                          , bs::pack_<bd::ints32_<Offset>,bs::sse_>
                          , bd::target_<bs::pack_<bd::single_<Target>,bs::sse_>>
                          )
  {
    using target = typename Target::type;
    BOOST_FORCEINLINE target operator()(Pointer p, Offset const& o, Target const&) const
    {
      return _mm_i32gather_ps(p, o, sizeof(typename target::value_type));
    }
  };

  //------------------------------------------------------------------------------------------------
  // gather ints32
  BOOST_DISPATCH_OVERLOAD ( load_
                          , (typename Pointer, typename Offset, typename Target)
                          , bs::avx2_
                          , bd::pointer_<bd::scalar_<bd::ints32_<Pointer>>,1u>
                          , bs::pack_<bd::ints32_<Offset>,bs::sse_>
                          , bd::target_<bs::pack_<bd::ints32_<Target>,bs::sse_>>
                          )
  {
    using target = typename Target::type;
    BOOST_FORCEINLINE target operator()(Pointer p, Offset const& o, Target const&) const
    {
      return _mm_i32gather_epi32( (const int*)(p), o, sizeof(typename target::value_type));
    }
  };

  //------------------------------------------------------------------------------------------------
  // loads with gather semantic for 128 bits targets with 64 bits indexes
  //------------------------------------------------------------------------------------------------

  //------------------------------------------------------------------------------------------------
  // gather double
  BOOST_DISPATCH_OVERLOAD ( load_
                          , (typename Pointer, typename Offset, typename Target)
                          , bs::avx2_
                          , bd::pointer_<bd::scalar_<bd::double_<Pointer>>,1u>
                          , bs::pack_<bd::ints64_<Offset>,bs::sse_>
                          , bd::target_<bs::pack_<bd::double_<Target>,bs::sse_>>
                          )
  {
    using target = typename Target::type;
    BOOST_FORCEINLINE target operator()(Pointer p, Offset const& o, Target const&) const
    {
      return _mm_i64gather_pd(p, o, sizeof(typename target::value_type));
    }
  };

  //------------------------------------------------------------------------------------------------
  // gather ints64
  BOOST_DISPATCH_OVERLOAD ( load_
                          , (typename Pointer, typename Offset, typename Target)
                          , bs::avx2_
                          , bd::pointer_<bd::scalar_<bd::ints64_<Pointer>>,1u>
                          , bs::pack_<bd::ints64_<Offset>,bs::sse_>
                          , bd::target_<bs::pack_<bd::ints64_<Target>,bs::sse_>>
                          )
  {
    using target = typename Target::type;
    BOOST_FORCEINLINE target operator()(Pointer p, Offset const& o, Target const&) const
    {
      return _mm_i64gather_epi64( (long long int const*)(p), o, sizeof(typename target::value_type));
    }
  };
} } }

#endif
