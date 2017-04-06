//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_SLICE_HIGH_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_SLICE_HIGH_HPP_INCLUDED

#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/meta/as_arithmetic.hpp>
#include <boost/simd/meta/hierarchy/simd.hpp>
#include <boost/simd/detail/dispatch/function/overload.hpp>
#include <boost/simd/detail/dispatch/hierarchy.hpp>
#include <boost/config.hpp>
#include <boost/simd/logical.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = boost::dispatch;
  namespace bs = boost::simd;

  // -----------------------------------------------------------------------------------------------
  // slice_high pack of AVX double
  BOOST_DISPATCH_OVERLOAD ( slice_high_
                          , (typename T)
                          , bs::avx_
                          , bs::pack_< bd::double_<T>, bs::avx_ >
                          )
  {
    static const std::size_t half = T::static_size/2;
    using result_t   = typename T::template resize<half>;

    BOOST_FORCEINLINE result_t operator()(T const& a0) const
    {
      return _mm256_extractf128_pd(a0, 1);
    }
  };

  // -----------------------------------------------------------------------------------------------
  // slice_high pack of AVX single
  BOOST_DISPATCH_OVERLOAD ( slice_high_
                          , (typename T)
                          , bs::avx_
                          , bs::pack_< bd::single_<T>, bs::avx_ >
                          )
  {
    static const std::size_t half = T::static_size/2;
    using result_t   = typename T::template resize<half>;

    BOOST_FORCEINLINE result_t operator()(T const& a0) const
    {
      return _mm256_extractf128_ps(a0, 1);
    }
  };

  // -----------------------------------------------------------------------------------------------
  // slice_high pack of AVX2 integer
  BOOST_DISPATCH_OVERLOAD ( slice_high_
                          , (typename T)
                          , bs::avx_
                          , bs::pack_< bd::integer_<T>, bs::avx_ >
                          )
  {
    static const std::size_t half = T::static_size/2;
    using result_t   = typename T::template resize<half>;

    BOOST_FORCEINLINE result_t operator()(T const& a0) const
    {
      return _mm256_extractf128_si256(a0, 1);
    }
  };

  // -----------------------------------------------------------------------------------------------
  // slice_high pack of AVX logical
  BOOST_DISPATCH_OVERLOAD ( slice_high_
                          , (typename T)
                          , bs::avx_
                          , bs::pack_< bs::logical_<T>, bs::avx_ >
                          )
  {
    static const std::size_t half = T::static_size/2;
    using result_t   = typename T::template resize<half>;
    using base_t   = as_arithmetic_t<T>;

    BOOST_FORCEINLINE result_t operator()(T const& a0) const
    {
      return bitwise_cast<result_t>( slice_high(bitwise_cast<base_t>(a0)) );
    }
  };
} } }

#endif
