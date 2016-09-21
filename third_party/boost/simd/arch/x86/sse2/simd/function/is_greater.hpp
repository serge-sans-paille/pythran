//==================================================================================================
/*!
    @file

    @Copyright 2016 Numscale SAS

    Distributed under the Boost Software License, Version 1.0.
    (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
*/
//==================================================================================================
#ifndef BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_IS_GREATER_HPP_INCLUDED
#define BOOST_SIMD_ARCH_X86_SSE2_SIMD_FUNCTION_IS_GREATER_HPP_INCLUDED
#include <boost/simd/detail/overload.hpp>

#include <boost/simd/meta/as_logical.hpp>
#include <boost/simd/function/bitwise_cast.hpp>
#include <boost/simd/function/is_equal.hpp>
#include <boost/simd/function/logical_and.hpp>
#include <boost/simd/function/logical_or.hpp>
#include <boost/simd/function/minus.hpp>
#include <boost/simd/function/shuffle.hpp>
#include <boost/simd/constant/signmask.hpp>
#include <boost/simd/detail/dispatch/meta/downgrade.hpp>

namespace boost { namespace simd { namespace ext
{
  namespace bd =  boost::dispatch;
  BOOST_DISPATCH_OVERLOAD ( is_greater_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::double_<A0>, bs::sse_>
                          , bs::pack_<bd::double_<A0>, bs::sse_>
                          )
  {
    BOOST_FORCEINLINE bs::as_logical_t<A0> operator() ( const A0 & a0
                                                      , const A0 & a1 ) const BOOST_NOEXCEPT
    {
      return _mm_cmpgt_pd(a0,a1);
    }
  };
  BOOST_DISPATCH_OVERLOAD ( is_greater_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::unsigned_<A0>, bs::sse_>
                          , bs::pack_<bd::unsigned_<A0>, bs::sse_>
                          )
  {
    using result = bs::as_logical_t<A0>;
    BOOST_FORCEINLINE result operator() ( const A0 & a0
                                        , const A0 & a1 ) const BOOST_NOEXCEPT
    {
      using s_t = bd::as_integer_t<A0, signed>;
      s_t sm = Signmask<s_t>();

      return  bitwise_cast<result>( is_greater(bitwise_cast<s_t>(a0) - sm,
                                               bitwise_cast<s_t>(a1) - sm
                                              )
                                  );
    }
  };

  BOOST_DISPATCH_OVERLOAD ( is_greater_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::int8_<A0>, bs::sse_>
                          , bs::pack_<bd::int8_<A0>, bs::sse_>
                          )
  {
    BOOST_FORCEINLINE bs::as_logical_t<A0> operator() ( const A0 & a0
                                                      , const A0 & a1 ) const BOOST_NOEXCEPT
    {
      return _mm_cmpgt_epi8(a0,a1);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( is_greater_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::int16_<A0>, bs::sse_>
                          , bs::pack_<bd::int16_<A0>, bs::sse_>
                          )
  {
    BOOST_FORCEINLINE bs::as_logical_t<A0> operator() ( const A0 & a0
                                        , const A0 & a1 ) const BOOST_NOEXCEPT
    {
      return _mm_cmpgt_epi16(a0,a1);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( is_greater_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::int32_<A0>, bs::sse_>
                          , bs::pack_<bd::int32_<A0>, bs::sse_>
                          )
  {
    BOOST_FORCEINLINE bs::as_logical_t<A0> operator() ( const A0 & a0
                                        , const A0 & a1 ) const BOOST_NOEXCEPT
    {
      return _mm_cmpgt_epi32(a0,a1);
    }
  };

  BOOST_DISPATCH_OVERLOAD ( is_greater_
                          , (typename A0)
                          , bs::sse2_
                          , bs::pack_<bd::int64_<A0>, bs::sse_>
                          , bs::pack_<bd::int64_<A0>, bs::sse_>
                          )
  {
    using result = bs::as_logical_t<A0>;
    BOOST_FORCEINLINE result operator() ( const A0 & a0
                                        , const A0 & a1 ) const BOOST_NOEXCEPT
    {
      using type = bd::downgrade_t<A0, signed>;
      using utype = bd::downgrade_t<A0, unsigned>;
      utype al = shuffle<0,0,2,2>(bitwise_cast<utype>(a0));
      utype bl = shuffle<0,0,2,2>(bitwise_cast<utype>(a1));
      type ah  = shuffle<1,1,3,3>(bitwise_cast<type >(a0));
      type bh  = shuffle<1,1,3,3>(bitwise_cast<type >(a1));

      return bitwise_cast<result>(logical_or(is_greater(ah,bh), logical_and(is_equal(ah,bh), is_greater(al,bl))));
    }
  };

} } }

#endif
