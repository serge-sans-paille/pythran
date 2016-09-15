//==================================================================================================
/**
  Copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
**/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_MAKE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_AVX_SIMD_FUNCTION_MAKE_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = ::boost::dispatch;
  namespace bs = ::boost::simd;

  //------------------------------------------------------------------------------------------------
  // make a pack of double
  BOOST_DISPATCH_OVERLOAD ( make_
                          , (typename Target, typename... Values)
                          , bs::avx_
                          , bd::target_<bs::pack_<bd::double_<Target>,bs::avx_>>
                          , bd::scalar_<bd::unspecified_<Values>>...
                          )
  {
    using target_t  = typename Target::type;

    static_assert ( sizeof...(Values) == 4
                  , "boost::simd::make - Invalid number of parameters"
                  );

    BOOST_FORCEINLINE target_t operator()(Target const&, Values const&... vs) const BOOST_NOEXCEPT
    {
      return _mm256_setr_pd(static_cast<typename target_t::value_type>(vs)...);
    }
  };

  //------------------------------------------------------------------------------------------------
  // make a pack of single
  BOOST_DISPATCH_OVERLOAD ( make_
                          , (typename Target, typename... Values)
                          , bs::avx_
                          , bd::target_<bs::pack_<bd::single_<Target>,bs::avx_>>
                          , bd::scalar_<bd::unspecified_<Values>>...
                          )
  {
    using target_t  = typename Target::type;

    static_assert ( sizeof...(Values) == 8
                  , "boost::simd::make - Invalid number of parameters"
                  );

    BOOST_FORCEINLINE target_t operator()(Target const&, Values const&... vs) const BOOST_NOEXCEPT
    {
      return _mm256_setr_ps(static_cast<typename target_t::value_type>(vs)...);
    }
  };

  //------------------------------------------------------------------------------------------------
  // make a pack of int64
  BOOST_DISPATCH_OVERLOAD ( make_
                          , (typename Target, typename... Values)
                          , bs::avx_
                          , bd::target_<bs::pack_<bd::ints64_<Target>,bs::avx_>>
                          , bd::scalar_<bd::unspecified_<Values>>...
                          )
  {
    using target_t  = typename Target::type;

    static_assert ( sizeof...(Values) == 4
                  , "boost::simd::make - Invalid number of parameters"
                  );

    BOOST_FORCEINLINE target_t operator()(Target const&, Values const&... vs) const BOOST_NOEXCEPT
    {
      using value_t = typename target_t::value_type;
      return _mm256_setr_epi64x( static_cast<value_t>(vs)... );
    }
  };

  //------------------------------------------------------------------------------------------------
  // make a pack of int32
  BOOST_DISPATCH_OVERLOAD ( make_
                          , (typename Target, typename... Values)
                          , bs::avx_
                          , bd::target_<bs::pack_<bd::ints32_<Target>,bs::avx_>>
                          , bd::scalar_<bd::unspecified_<Values>>...
                          )
  {
    using target_t  = typename Target::type;

    static_assert ( sizeof...(Values) == 8
                  , "boost::simd::make - Invalid number of parameters"
                  );

    BOOST_FORCEINLINE target_t operator()(Target const&, Values const&... vs) const BOOST_NOEXCEPT
    {
      return _mm256_setr_epi32(static_cast<typename target_t::value_type>(vs)...);
    }
  };

  //------------------------------------------------------------------------------------------------
  // make a pack of int16
  BOOST_DISPATCH_OVERLOAD ( make_
                          , (typename Target, typename... Values)
                          , bs::avx_
                          , bd::target_<bs::pack_<bd::ints16_<Target>,bs::avx_>>
                          , bd::scalar_<bd::unspecified_<Values>>...
                          )
  {
    using target_t  = typename Target::type;

    static_assert ( sizeof...(Values) == 16
                  , "boost::simd::make - Invalid number of parameters"
                  );

    BOOST_FORCEINLINE target_t operator()(Target const&, Values const&... vs) const BOOST_NOEXCEPT
    {
      return _mm256_setr_epi16(static_cast<typename target_t::value_type>(vs)...);
    }
  };

  //------------------------------------------------------------------------------------------------
  // make a pack of int8
  BOOST_DISPATCH_OVERLOAD ( make_
                          , (typename Target, typename... Values)
                          , bs::avx_
                          , bd::target_<bs::pack_<bd::ints8_<Target>,bs::avx_>>
                          , bd::scalar_<bd::unspecified_<Values>>...
                          )
  {
    using target_t  = typename Target::type;

    static_assert ( sizeof...(Values) == 32
                  , "boost::simd::make - Invalid number of parameters"
                  );

    BOOST_FORCEINLINE target_t operator()(Target const&, Values const&... vs) const BOOST_NOEXCEPT
    {
      return _mm256_setr_epi8(static_cast<typename target_t::value_type>(vs)...);
    }
  };
} } }

#endif
