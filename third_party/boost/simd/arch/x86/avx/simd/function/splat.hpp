//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_SPLAT_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_SPLAT_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = ::boost::dispatch;
  namespace bs = ::boost::simd;

  //------------------------------------------------------------------------------------------------
  // splat from a scalar into a pack of float
  BOOST_DISPATCH_OVERLOAD ( splat_
                          , (typename Target, typename Value)
                          , bs::avx_
                          , bd::scalar_<bd::unspecified_<Value> >
                          , bd::target_<bs::pack_<bd::single_<Target>,bs::avx_>>
                          )
  {
    using target = typename Target::type;

    BOOST_FORCEINLINE target operator()(Value const& v, Target const&) const BOOST_NOEXCEPT
    {
      return _mm256_set1_ps( static_cast<float>(v) );
    }
  };

  //------------------------------------------------------------------------------------------------
  // splat from a scalar into a pack of double
  BOOST_DISPATCH_OVERLOAD ( splat_
                          , (typename Target, typename Value)
                          , bs::avx_
                          , bd::scalar_<bd::unspecified_<Value> >
                          , bd::target_<bs::pack_<bd::double_<Target>,bs::avx_>>
                          )
  {
    using target = typename Target::type;

    BOOST_FORCEINLINE target operator()(Value const& v, Target const&) const BOOST_NOEXCEPT
    {
      return _mm256_set1_pd( static_cast<double>(v) );
    }
  };

  //------------------------------------------------------------------------------------------------
  // splat from a scalar into a pack of 8 bits integers
  BOOST_DISPATCH_OVERLOAD ( splat_
                          , (typename Target, typename Value)
                          , bs::avx_
                          , bd::scalar_<bd::unspecified_<Value>>
                          , bd::target_<bs::pack_<bd::ints8_<Target>,bs::avx_>>
                          )
  {
    using target = typename Target::type;

    BOOST_FORCEINLINE target operator()(Value const& v, Target const&) const BOOST_NOEXCEPT
    {
      return _mm256_set1_epi8(v);
    }
  };

  //------------------------------------------------------------------------------------------------
  // splat from a scalar into a pack of 16 bits integers
  BOOST_DISPATCH_OVERLOAD ( splat_
                          , (typename Target, typename Value)
                          , bs::avx_
                          , bd::scalar_<bd::unspecified_<Value>>
                          , bd::target_<bs::pack_<bd::ints16_<Target>,bs::avx_>>
                          )
  {
    using target = typename Target::type;

    BOOST_FORCEINLINE target operator()(Value const& v, Target const&) const BOOST_NOEXCEPT
    {
      return _mm256_set1_epi16(v);
    }
  };

  //------------------------------------------------------------------------------------------------
  // splat from a scalar into a pack of 32 bits integers
  BOOST_DISPATCH_OVERLOAD ( splat_
                          , (typename Target, typename Value)
                          , bs::avx_
                          , bd::scalar_<bd::unspecified_<Value>>
                          , bd::target_<bs::pack_<bd::ints32_<Target>,bs::avx_>>
                          )
  {
    using target = typename Target::type;

    BOOST_FORCEINLINE target operator()(Value const& v, Target const&) const BOOST_NOEXCEPT
    {
      return _mm256_set1_epi32(v);
    }
  };

  //------------------------------------------------------------------------------------------------
  // splat from a scalar into a pack of 64 bits integers
  BOOST_DISPATCH_OVERLOAD ( splat_
                          , (typename Target, typename Value)
                          , bs::avx_
                          , bd::scalar_<bd::unspecified_<Value>>
                          , bd::target_<bs::pack_<bd::ints64_<Target>,bs::avx_>>
                          )
  {
    using target = typename Target::type;

    BOOST_FORCEINLINE target operator()(Value const& v, Target const&) const BOOST_NOEXCEPT
    {
      return _mm256_set1_epi64x(v);
    }
  };
} } }

#endif
