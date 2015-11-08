//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2014 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_AVX_BROADCAST_HPP_INCLUDED
#define BOOST_SIMD_SWAR_FUNCTIONS_SIMD_SSE_AVX_BROADCAST_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/swar/functions/broadcast.hpp>
#include <boost/simd/include/functions/simd/combine.hpp>
#include <boost/simd/sdk/simd/meta/retarget.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::broadcast_
                                    , boost::simd::tag::avx_
                                    , (A0)(A1)
                                    , ((simd_ < double_<A0>
                                              , boost::simd::tag::avx_
                                              >
                                      ))
                                      (mpl_integral_< scalar_< integer_<A1> > >)
                                    )
  {
    typedef A0 result_type;

    typedef boost::mpl::int_<(A1::value >= A0::static_size/2) ? 1 : 0>      sel_t;
    typedef boost::mpl::int_<A1::value - sel_t::value*(A0::static_size/2)>  idx_t;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      typedef typename meta::retarget<A0,boost::simd::tag::sse_>::type s_t;

      s_t half = _mm256_extractf128_pd(a0, sel_t::value);
          half = broadcast<idx_t::value>(half);

      return combine(half,half);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::broadcast_
                                    , boost::simd::tag::avx_
                                    , (A0)(A1)
                                    , ((simd_ < single_<A0>
                                              , boost::simd::tag::avx_
                                              >
                                      ))
                                      (mpl_integral_< scalar_< integer_<A1> > >)
                                    )
  {
    typedef A0 result_type;

    typedef boost::mpl::int_<(A1::value >= A0::static_size/2) ? 1 : 0>      sel_t;
    typedef boost::mpl::int_<A1::value - sel_t::value*(A0::static_size/2)>  idx_t;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      typedef typename meta::retarget<A0,boost::simd::tag::sse_>::type s_t;

      s_t half = _mm256_extractf128_ps(a0, sel_t::value);
          half = broadcast<idx_t::value>(half);

      return combine(half,half);
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::broadcast_
                                    , boost::simd::tag::avx_
                                    , (A0)(A1)
                                    , ((simd_ < integer_<A0>
                                              , boost::simd::tag::avx_
                                              >
                                      ))
                                      (mpl_integral_< scalar_< integer_<A1> > >)
                                    )
  {
    typedef A0 result_type;

    typedef boost::mpl::int_<(A1::value >= A0::static_size/2) ? 1 : 0>      sel_t;
    typedef boost::mpl::int_<A1::value - sel_t::value*(A0::static_size/2)>  idx_t;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const&) const
    {
      typedef typename meta::retarget<A0,boost::simd::tag::sse_>::type s_t;

      s_t half = _mm256_extractf128_si256(a0, sel_t::value);
          half = broadcast<idx_t::value>(half);

      return combine(half,half);
    }
  };
} } }

#endif
#endif
