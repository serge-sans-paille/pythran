//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_SSE_AVX_LOAD_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_SSE_AVX_LOAD_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/memory/functions/load.hpp>
#include <boost/simd/sdk/simd/category.hpp>
#include <boost/simd/meta/is_pointing_to.hpp>
#include <boost/dispatch/meta/mpl.hpp>

namespace boost { namespace simd { namespace ext
{
  /// INTERNAL ONLY - load double without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::load_
                                    , boost::simd::tag::avx_
                                    , (A0)(A1)
                                    , (iterator_< scalar_< double_<A0> > >)
                                      ((target_ < simd_ < double_<A1>
                                                        , boost::simd::tag::avx_
                                                        >
                                                >
                                      ))
                                    )
  {
    typedef typename A1::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0, const A1&) const
    {
      return _mm256_loadu_pd(a0);
    }
  };

  /// INTERNAL ONLY - load single without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::load_
                                    , boost::simd::tag::avx_
                                    , (A0)(A1)
                                    , (iterator_< scalar_< single_<A0> > >)
                                      ((target_ < simd_ < single_<A1>
                                                        , boost::simd::tag::avx_
                                                        >
                                                >
                                      ))
                                    )
  {
    typedef typename A1::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0, const A1&) const
    {
      return _mm256_loadu_ps(a0);
    }
  };

  /// INTERNAL ONLY - load integers without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::load_
                                      , boost::simd::tag::avx_
                                      , (A0)(A1)
                                      , ( simd::meta::is_pointing_to
                                          < A0
                                          , typename A1::type::value_type
                                          >
                                        )
                                      , (iterator_< scalar_< integer_<A0> > >)
                                        ((target_ < simd_ < integer_<A1>
                                                          , boost::simd::tag::avx_
                                                          >
                                                  >
                                        ))
                                      )
  {
    typedef typename A1::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0, const A1&)const
    {
      return _mm256_loadu_si256(reinterpret_cast<__m256i const*>(a0));
    }
  };
} } }

#endif
#endif
