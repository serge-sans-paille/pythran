//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_SPLAT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_SPLAT_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>

#ifdef BOOST_MSVC
# pragma warning(push)
# pragma warning(disable: 4244) // conversion loss of data
#endif

namespace boost { namespace simd { namespace ext
{
  namespace bd = ::boost::dispatch;
  namespace bs = ::boost::simd;

  //------------------------------------------------------------------------------------------------
  // splat from a scalar into a pack of double
  BOOST_DISPATCH_OVERLOAD ( splat_
                          , (typename Target, typename Value)
                          , bs::sse2_
                          , bd::scalar_< bd::unspecified_<Value> >
                          , bd::target_<bs::pack_<bd::double_<Target>,bs::sse_>>
                          )
  {
    using target = typename Target::type;

    BOOST_FORCEINLINE target operator()(Value const& v, Target const&) const BOOST_NOEXCEPT
    {
      return _mm_set1_pd( static_cast<double>(v) );
    }
  };

  //------------------------------------------------------------------------------------------------
  // splat from a scalar into a pack of (u)int8
  BOOST_DISPATCH_OVERLOAD ( splat_
                          , (typename Target, typename Value)
                          , bs::sse2_
                          , bd::scalar_< bd::unspecified_<Value> >
                          , bd::target_<bs::pack_<bd::ints8_<Target>,bs::sse_>>
                          )
  {
    using target = typename Target::type;

    BOOST_FORCEINLINE target operator()(Value const& v, Target const&) const BOOST_NOEXCEPT
    {
      return _mm_set1_epi8(v);
    }
  };

  //------------------------------------------------------------------------------------------------
  // splat from a scalar into a pack of (u)int16
  BOOST_DISPATCH_OVERLOAD ( splat_
                          , (typename Target, typename Value)
                          , bs::sse2_
                          , bd::scalar_< bd::unspecified_<Value> >
                          , bd::target_<bs::pack_<bd::ints16_<Target>,bs::sse_>>
                          )
  {
    using target = typename Target::type;

    BOOST_FORCEINLINE target operator()(Value const& v, Target const&) const BOOST_NOEXCEPT
    {
      return _mm_set1_epi16(v);
    }
  };

  //------------------------------------------------------------------------------------------------
  // splat from a scalar into a pack of (u)int32
  BOOST_DISPATCH_OVERLOAD ( splat_
                          , (typename Target, typename Value)
                          , bs::sse2_
                          , bd::scalar_< bd::unspecified_<Value> >
                          , bd::target_<bs::pack_<bd::ints32_<Target>,bs::sse_>>
                          )
  {
    using target = typename Target::type;

    BOOST_FORCEINLINE target operator()(Value const& v, Target const&) const BOOST_NOEXCEPT
    {
      return _mm_set1_epi32(v);
    }
  };

  //------------------------------------------------------------------------------------------------
  // splat from a scalar into a pack of (u)int64
  BOOST_DISPATCH_OVERLOAD ( splat_
                          , (typename Target, typename Value)
                          , bs::sse2_
                          , bd::scalar_< bd::unspecified_<Value> >
                          , bd::target_<bs::pack_<bd::ints64_<Target>,bs::sse_>>
                          )
  {
    using target = typename Target::type;

    BOOST_FORCEINLINE target operator()(Value const& v, Target const&) const BOOST_NOEXCEPT
    {
      return target(v,v);
    }
  };
} } }

#ifdef BOOST_MSVC
# pragma warning(pop)
#endif

#endif
