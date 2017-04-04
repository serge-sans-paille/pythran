//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_BITWISE_CAST_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_BITWISE_CAST_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = ::boost::dispatch;
  namespace bs = ::boost::simd;

  //------------------------------------------------------------------------------------------------
  // bitwise cast float<->double
  BOOST_DISPATCH_OVERLOAD ( bitwise_cast_
                          , (typename A0, typename Target)
                          , bs::sse2_
                          , bs::pack_<bd::single_<A0>,bs::sse_>
                          , bd::target_<bs::pack_<bd::double_<Target>,bs::sse_>>
                          )
  {
    using target = typename Target::type;
    BOOST_FORCEINLINE target operator()(A0 const& a0, Target const&) const
    {
      return _mm_castps_pd(a0);
    }
  };

  //------------------------------------------------------------------------------------------------
  // bitwise cast double<->float
  BOOST_DISPATCH_OVERLOAD ( bitwise_cast_
                          , (typename A0, typename Target)
                          , bs::sse2_
                          , bs::pack_<bd::double_<A0>,bs::sse_>
                          , bd::target_<bs::pack_<bd::single_<Target>,bs::sse_>>
                          )
  {
    using target = typename Target::type;
    BOOST_FORCEINLINE target operator()(A0 const& a0, Target const&) const
    {
      return _mm_castpd_ps(a0);
    }
  };

  //------------------------------------------------------------------------------------------------
  // bitwise cast float<->integer
  BOOST_DISPATCH_OVERLOAD ( bitwise_cast_
                          , (typename A0, typename Target)
                          , bs::sse2_
                          , bs::pack_<bd::single_<A0>,bs::sse_>
                          , bd::target_<bs::pack_<bd::integer_<Target>,bs::sse_>>
                          )
  {
    using target = typename Target::type;
    BOOST_FORCEINLINE target operator()(A0 const& a0, Target const&) const
    {
      return _mm_castps_si128(a0);
    }
  };

  //------------------------------------------------------------------------------------------------
  // bitwise cast double<->integer
  BOOST_DISPATCH_OVERLOAD ( bitwise_cast_
                          , (typename A0, typename Target)
                          , bs::sse2_
                          , bs::pack_<bd::double_<A0>,bs::sse_>
                          , bd::target_<bs::pack_<bd::integer_<Target>,bs::sse_>>
                          )
  {
    using target = typename Target::type;
    BOOST_FORCEINLINE target operator()(A0 const& a0, Target const&) const
    {
      return _mm_castpd_si128(a0);
    }
  };

  //------------------------------------------------------------------------------------------------
  // bitwise cast integer<->float
  BOOST_DISPATCH_OVERLOAD ( bitwise_cast_
                          , (typename A0, typename Target)
                          , bs::sse2_
                          , bs::pack_<bd::integer_<A0>,bs::sse_>
                          , bd::target_<bs::pack_<bd::single_<Target>,bs::sse_>>
                          )
  {
    using target = typename Target::type;
    BOOST_FORCEINLINE target operator()(A0 const& a0, Target const&) const
    {
      return _mm_castsi128_ps(a0);
    }
  };

  //------------------------------------------------------------------------------------------------
  // bitwise cast double<->integer
  BOOST_DISPATCH_OVERLOAD ( bitwise_cast_
                          , (typename A0, typename Target)
                          , bs::sse2_
                          , bs::pack_<bd::integer_<A0>,bs::sse_>
                          , bd::target_<bs::pack_<bd::double_<Target>,bs::sse_>>
                          )
  {
    using target = typename Target::type;
    BOOST_FORCEINLINE target operator()(A0 const& a0, Target const&) const
    {
      return _mm_castsi128_pd(a0);
    }
  };

  //------------------------------------------------------------------------------------------------
  // bitwise cast integer<->integer
  BOOST_DISPATCH_OVERLOAD ( bitwise_cast_
                          , (typename A0, typename Target)
                          , bs::sse2_
                          , bs::pack_<bd::integer_<A0>,bs::sse_>
                          , bd::target_<bs::pack_<bd::integer_<Target>,bs::sse_>>
                          )
  {
    using target = typename Target::type;
    BOOST_FORCEINLINE target operator()(A0 const& a0, Target const&) const
    {
      return a0.storage();
    }
  };
} } }

#endif
