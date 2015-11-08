//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2014 NUMSCALE SAS
//
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_SSE_AVX_EXTRACT_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_SSE_AVX_EXTRACT_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/memory/functions/extract.hpp>
#include <boost/simd/sdk/simd/meta/retarget.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>
#include <boost/mpl/modulus.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::extract_
                                    , boost::simd::tag::avx_
                                    , (A0)(A1)
                                    , ((simd_< integer_<A0>, boost::simd::tag::avx_ >))
                                      (mpl_integral_< scalar_< integer_<A1> > >)
                                    )
  {
    typedef typename meta::scalar_of<A0>::type   result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1) const
    {
      typedef typename meta::retarget<A0, tag::sse_>::type ltype;
      typedef typename meta::cardinal_of<ltype>::type card;

      ltype that = _mm256_extractf128_si256(a0(), A1::value / ltype::static_size);
      return extract(that, mpl::modulus< A1, card >());
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::extract_
                                    , boost::simd::tag::avx_
                                    , (A0)(A1)
                                    , ((simd_< single_<A0>, boost::simd::tag::avx_ >))
                                      (mpl_integral_< scalar_< integer_<A1> > >)
                                    )
  {
    typedef typename meta::scalar_of<A0>::type   result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1) const
    {
      typedef typename meta::retarget<A0, tag::sse_>::type ltype;
      typedef typename meta::cardinal_of<ltype>::type card;

      ltype that = _mm256_extractf128_ps(a0(), A1::value / ltype::static_size);
      return extract(that, mpl::modulus< A1, card >());
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::extract_
                                    , boost::simd::tag::avx_
                                    , (A0)(A1)
                                    , ((simd_< double_<A0>, boost::simd::tag::avx_ >))
                                      (mpl_integral_< scalar_< integer_<A1> > >)
                                    )
  {
    typedef typename meta::scalar_of<A0>::type   result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1) const
    {
      typedef typename meta::retarget<A0, tag::sse_>::type ltype;
      typedef typename meta::cardinal_of<ltype>::type card;

      ltype that = _mm256_extractf128_pd(a0(), A1::value / ltype::static_size);
      return extract(that, mpl::modulus< A1, card >());
    }
  };
} } }

#endif
#endif
