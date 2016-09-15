//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_COMBINE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_COMBINE_HPP_INCLUDED

#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/meta/as_arithmetic.hpp>
#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/hierarchy.hpp>
#include <boost/config.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  // -----------------------------------------------------------------------------------------------
  // combine pack of AVX doubles
  BOOST_DISPATCH_OVERLOAD ( combine_
                          , (typename T)
                          , bs::avx_
                          , bs::pack_< bd::double_<T>, bs::sse_ >
                          , bs::pack_< bd::double_<T>, bs::sse_ >
                          )
  {
    using result_t = typename T::template resize<2 * T::static_size>;

    BOOST_FORCEINLINE result_t operator()(T const& a0, T const& a1) const
    {
      result_t  that = _mm256_castpd128_pd256(a0);
      return _mm256_insertf128_pd(that, a1, 1);
    }
  };

  // -----------------------------------------------------------------------------------------------
  // combine pack of AVX singles
  BOOST_DISPATCH_OVERLOAD ( combine_
                          , (typename T)
                          , bs::avx_
                          , bs::pack_< bd::single_<T>, bs::sse_ >
                          , bs::pack_< bd::single_<T>, bs::sse_ >
                          )
  {
    using result_t = typename T::template resize<2 * T::static_size>;

    BOOST_FORCEINLINE result_t operator()(T const& a0, T const& a1) const
    {
      result_t  that = _mm256_castps128_ps256(a0);
      return _mm256_insertf128_ps(that, a1, 1);
    }
  };

  // -----------------------------------------------------------------------------------------------
  // combine pack of AVX logical
  BOOST_DISPATCH_OVERLOAD ( combine_
                          , (typename T)
                          , bs::avx_
                          , bs::pack_< bs::logical_<T>, bs::sse_ >
                          , bs::pack_< bs::logical_<T>, bs::sse_ >
                          )
  {
    using result_t = typename T::template resize<2 * T::static_size>;
    using base_t   = as_arithmetic_t<T>;

    BOOST_FORCEINLINE result_t operator()(T const& a0, T const& a1) const
    {
      return bitwise_cast<result_t>( combine(bitwise_cast<base_t>(a0), bitwise_cast<base_t>(a1)) );
    }
  };

  // -----------------------------------------------------------------------------------------------
  // combine pack of AVX integer
  BOOST_DISPATCH_OVERLOAD ( combine_
                          , (typename T)
                          , bs::avx_
                          , bs::pack_< bd::integer_<T>, bs::sse_ >
                          , bs::pack_< bd::integer_<T>, bs::sse_ >
                          )
  {
    using result_t = typename T::template resize<2 * T::static_size>;

    BOOST_FORCEINLINE result_t operator()(T const& a0, T const& a1) const
    {
      result_t  that = _mm256_castsi128_si256(a0);
      return _mm256_insertf128_si256(that, a1, 1);
    }
  };
} } }

#endif
