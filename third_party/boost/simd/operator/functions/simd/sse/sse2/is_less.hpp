//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_SSE_SSE2_IS_LESS_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_SSE_SSE2_IS_LESS_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_SSE2_SUPPORT

#include <boost/simd/operator/functions/is_less.hpp>
#include <boost/simd/swar/functions/details/shuffle.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/functions/simd/logical_and.hpp>
#include <boost/simd/include/functions/simd/logical_or.hpp>
#include <boost/simd/include/functions/simd/is_equal.hpp>
#include <boost/simd/include/functions/simd/minus.hpp>
#include <boost/simd/include/constants/signmask.hpp>
#include <boost/simd/sdk/meta/as_logical.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/meta/downgrade.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::is_less_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_<double_<A0>,boost::simd::tag::sse_>))
                                      ((simd_<double_<A0>,boost::simd::tag::sse_>))
                                    )
  {
    typedef typename meta::as_logical<A0>::type result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return _mm_cmplt_pd(a0,a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::is_less_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_<single_<A0>,boost::simd::tag::sse_>))
                                      ((simd_<single_<A0>,boost::simd::tag::sse_>))
                                    )
  {
    typedef typename meta::as_logical<A0>::type result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return _mm_cmplt_ps(a0,a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::is_less_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_<unsigned_<A0>,boost::simd::tag::sse_>))
                                      ((simd_<unsigned_<A0>,boost::simd::tag::sse_>))
                                    )
  {
    typedef typename meta::as_logical<A0>::type result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename dispatch::meta::as_integer<A0, signed>::type s_t;
      s_t sm = Signmask<s_t>();

      return  bitwise_cast<result_type> ( (bitwise_cast<s_t>(a0) - sm)
                                        < (bitwise_cast<s_t>(a1) - sm)
                                        );
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::is_less_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_<int8_<A0>,boost::simd::tag::sse_>))
                                      ((simd_<int8_<A0>,boost::simd::tag::sse_>))
                                    )
  {
    typedef typename meta::as_logical<A0>::type result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return _mm_cmplt_epi8(a0,a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::is_less_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_<int16_<A0>,boost::simd::tag::sse_>))
                                      ((simd_<int16_<A0>,boost::simd::tag::sse_>))
                                    )
  {
    typedef typename meta::as_logical<A0>::type result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return _mm_cmplt_epi16(a0,a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::is_less_
                                    , boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_<int32_<A0>,boost::simd::tag::sse_>))
                                      ((simd_<int32_<A0>,boost::simd::tag::sse_>))
                                    )
  {
    typedef typename meta::as_logical<A0>::type result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      return _mm_cmplt_epi32(a0,a1);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::is_less_, boost::simd::tag::sse2_
                                    , (A0)
                                    , ((simd_<int64_<A0>,boost::simd::tag::sse_>))
                                      ((simd_<int64_<A0>,boost::simd::tag::sse_>))
                                    )
  {
    typedef typename meta::as_logical<A0>::type result_type;

    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL_REPEAT(2)
    {
      typedef typename dispatch::meta::downgrade<A0, signed>::type type;
      typedef typename dispatch::meta::downgrade<A0, unsigned>::type utype;
      utype al = details::shuffle<0,0,2,2>(a0);
      utype bl = details::shuffle<0,0,2,2>(a1);
      type ah  = details::shuffle<1,1,3,3>(a0);
      type bh  = details::shuffle<1,1,3,3>(a1);

      return bitwise_cast<result_type>( l_or( boost::simd::lt(ah,bh)
                                            , l_and( boost::simd::eq(ah,bh)
                                                   , boost::simd::lt(al,bl)
                                                   )
                                            )
                                      );
    }
  };
} } }

#endif
#endif
