//==================================================================================================
/*!
  @file

  @copyright 2016 NumScale SAS

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_MAKE_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_MAKE_HPP_INCLUDED

#include <boost/simd/detail/overload.hpp>
#include <boost/simd/function/insert.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd = ::boost::dispatch;
  namespace bs = ::boost::simd;

  //------------------------------------------------------------------------------------------------
  // make a pack of double
  BOOST_DISPATCH_OVERLOAD ( make_
                          , (typename Target, typename... Values)
                          , bs::sse2_
                          , bd::target_<bs::pack_<bd::double_<Target>,bs::sse_>>
                          , bd::scalar_<bd::unspecified_<Values>>...
                          )
  {
    using target_t  = typename Target::type;
    using storage_t = typename target_t::storage_type;

    static_assert ( sizeof...(Values) == 2
                  , "boost::simd::make - Invalid number of parameters"
                  );

    BOOST_FORCEINLINE target_t operator()(Target const&, Values const&... vs) const BOOST_NOEXCEPT
    {
      return _mm_setr_pd(static_cast<typename target_t::value_type>(vs)...);
    }
  };

  //------------------------------------------------------------------------------------------------
  // make a pack of int64
  BOOST_DISPATCH_OVERLOAD ( make_
                          , (typename Target, typename V0, typename V1)
                          , bs::sse2_
                          , bd::target_<bs::pack_<bd::ints64_<Target>,bs::sse_>>
                          , bd::scalar_<bd::unspecified_<V0>>
                          , bd::scalar_<bd::unspecified_<V1>>
                          )
  {
    using target_t  = typename Target::type;

    BOOST_FORCEINLINE
    target_t operator()(Target const&, V0 const& v0, V1 const& v1) const BOOST_NOEXCEPT
    {
      target_t t;
      insert<0>(t,v0);
      insert<1>(t,v1);
      return t;
    }
  };

  //------------------------------------------------------------------------------------------------
  // make a pack of int32
  BOOST_DISPATCH_OVERLOAD ( make_
                          , (typename Target, typename... Values)
                          , bs::sse2_
                          , bd::target_<bs::pack_<bd::ints32_<Target>,bs::sse_>>
                          , bd::scalar_<bd::unspecified_<Values>>...
                          )
  {
    using target_t  = typename Target::type;

    static_assert ( sizeof...(Values) == 4
                  , "boost::simd::make - Invalid number of parameters"
                  );

    BOOST_FORCEINLINE target_t operator()(Target const&, Values const&... vs) const BOOST_NOEXCEPT
    {
      return _mm_setr_epi32(static_cast<typename target_t::value_type>(vs)...);
    }
  };

  //------------------------------------------------------------------------------------------------
  // make a pack of int16
  BOOST_DISPATCH_OVERLOAD ( make_
                          , (typename Target, typename... Values)
                          , bs::sse2_
                          , bd::target_<bs::pack_<bd::ints16_<Target>,bs::sse_>>
                          , bd::scalar_<bd::unspecified_<Values>>...
                          )
  {
    using target_t  = typename Target::type;

    static_assert ( sizeof...(Values) == 8
                  , "boost::simd::make - Invalid number of parameters"
                  );

    BOOST_FORCEINLINE target_t operator()(Target const&, Values const&... vs) const BOOST_NOEXCEPT
    {
      return _mm_setr_epi16(static_cast<typename target_t::value_type>(vs)...);
    }
  };

  //------------------------------------------------------------------------------------------------
  // make a pack of int8
  BOOST_DISPATCH_OVERLOAD ( make_
                          , (typename Target, typename... Values)
                          , bs::sse2_
                          , bd::target_<bs::pack_<bd::ints8_<Target>,bs::sse_>>
                          , bd::scalar_<bd::unspecified_<Values>>...
                          )
  {
    using target_t  = typename Target::type;

    static_assert ( sizeof...(Values) == 16
                  , "boost::simd::make - Invalid number of parameters"
                  );

    BOOST_FORCEINLINE target_t operator()(Target const&, Values const&... vs) const BOOST_NOEXCEPT
    {
      return _mm_setr_epi8(static_cast<typename target_t::value_type>(vs)...);
    }
  };
} } }

#endif
