//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_AVX_ALL_REDUCE_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_AVX_ALL_REDUCE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/swar/functions/all_reduce.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/simd/sdk/simd/category.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::all_reduce_
                                    , boost::simd::tag::avx_
                                    , (Tag)(A0)
                                    , ((simd_ < type64_<A0>
                                              , boost::simd::tag::avx_
                                              >
                                      ))
                                      ((target_< unspecified_<Tag> >))
                                    )
  {
    typedef typename Tag::type                              base;
    typedef typename dispatch::meta::call<base( A0 const&
                                              , A0 const&
                                              )>::type      result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, Tag const&) const
    {
      typedef typename dispatch::meta::as_floating<A0>::type ftype;
      dispatch::functor<base> op;

      ftype a = _mm256_permute_pd(bitwise_cast<ftype>(a0), _MM_SHUFFLE2(2,1));
      ftype b = _mm256_permute2f128_pd(a,a,1);
      result_type that = op( bitwise_cast<A0>(a)
                           , bitwise_cast<A0>(b)
                           );
      ftype pthat = _mm256_permute_pd(bitwise_cast<ftype>(that), _MM_SHUFFLE2(2,1));

      return op(that, bitwise_cast<result_type>(pthat));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::all_reduce_
                                    , boost::simd::tag::avx_
                                    , (Tag)(A0)
                                    , ((simd_ < type32_<A0>
                                              , boost::simd::tag::avx_
                                              >
                                      ))
                                      ((target_< unspecified_<Tag> >))
                                    )
  {
    typedef typename Tag::type                              base;
    typedef typename dispatch::meta::call<base( A0 const&
                                              , A0 const&
                                              )>::type      result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, Tag const&) const
    {
      typedef typename dispatch::meta::as_floating<A0>::type ftype;
      dispatch::functor<base> op;

      ftype a = _mm256_permute_ps(bitwise_cast<ftype>(a0), _MM_SHUFFLE( 0,3,2,1 ));
      ftype b = _mm256_permute2f128_ps(a,a,1);
      result_type that  = op( bitwise_cast<A0>(a)
                            , bitwise_cast<A0>(b)
                            );
      ftype pthat = _mm256_permute_ps(bitwise_cast<ftype>(that), _MM_SHUFFLE( 1,0,3,2 ));

      that  = op(that, bitwise_cast<result_type>(pthat));
      pthat = _mm256_permute_ps(bitwise_cast<ftype>(that), _MM_SHUFFLE(2,3,0,1));

      return op(that, bitwise_cast<result_type>(pthat));
    }
  };
} } }

#endif
#endif
