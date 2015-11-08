//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_SSE_AVX_TOFLOAT_HPP_INCLUDED
#define BOOST_SIMD_ARITHMETIC_FUNCTIONS_SIMD_SSE_AVX_TOFLOAT_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT
#include <boost/simd/arithmetic/functions/tofloat.hpp>
#include <boost/simd/include/functions/simd/bitwise_andnot.hpp>
#include <boost/simd/include/functions/simd/if_else.hpp>
#include <boost/simd/include/functions/simd/plus.hpp>
#include <boost/simd/include/functions/simd/is_gez.hpp>
#include <boost/simd/include/functions/simd/make.hpp>
#include <boost/simd/include/constants/int_splat.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/dispatch/meta/as_integer.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::tofloat_
                                    , boost::simd::tag::avx_
                                    , (A0)
                                    , ((simd_<int32_<A0>,boost::simd::tag::avx_>))
                                    )
  {
    typedef typename dispatch::meta::as_floating<A0>::type  result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return _mm256_cvtepi32_ps(a0);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::tofloat_
                                    , boost::simd::tag::avx_
                                    , (A0)
                                    , ((simd_<uint32_<A0>,boost::simd::tag::avx_>))
                                    )
  {
    typedef typename dispatch::meta::as_floating<A0>::type  result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      typedef typename dispatch::meta::scalar_of<result_type>::type stype;
      typedef native < stype, boost::simd::tag::sse_ > htype;

      htype h1 = make<htype>(a0[0],a0[1],a0[2],a0[3]);
      htype h2 = make<htype>(a0[4],a0[5],a0[6],a0[7]);
      result_type r = _mm256_castps128_ps256(h1);
      r =  _mm256_insertf128_ps(r, h2, 1);
      return r;
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::tofloat_
                                    , boost::simd::tag::avx_
                                    , (A0)
                                    , ((simd_<int64_<A0>,boost::simd::tag::avx_>))
                                    )
  {
    typedef typename dispatch::meta::as_floating<A0>::type  result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return make<result_type>(a0[0], a0[1], a0[2], a0[3]);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::tofloat_
                                    , boost::simd::tag::avx_
                                    , (A0)
                                    , ((simd_<uint64_<A0>,boost::simd::tag::avx_>))
                                    )
  {
    typedef typename dispatch::meta::as_floating<A0>::type  result_type;
    BOOST_FORCEINLINE BOOST_SIMD_FUNCTOR_CALL(1)
    {
      return make<result_type>(a0[0], a0[1], a0[2], a0[3]);
    }
  };
} } }

#endif
#endif
