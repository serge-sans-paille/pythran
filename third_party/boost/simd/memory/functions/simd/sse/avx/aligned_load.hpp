//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2014               MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_SSE_AVX_ALIGNED_LOAD_HPP_INCLUDED
#define BOOST_SIMD_MEMORY_FUNCTIONS_SIMD_SSE_AVX_ALIGNED_LOAD_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/memory/functions/aligned_load.hpp>
#include <boost/simd/include/functions/simd/load.hpp>
#include <boost/simd/memory/functions/details/check_ptr.hpp>
#include <boost/simd/meta/is_pointing_to.hpp>
#include <boost/simd/sdk/simd/category.hpp>
#include <boost/simd/memory/is_aligned.hpp>
#include <boost/dispatch/meta/mpl.hpp>
#include <boost/dispatch/attributes.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_load_
                                    , boost::simd::tag::avx_
                                    , (A0)(A2)(A3)
                                    , (iterator_< scalar_< double_<A0> > >)
                                      ((target_ < simd_ < double_<A2>
                                                        , boost::simd::tag::sse_
                                                        >
                                                >
                                      ))
                                      ((simd_< logical_<A3>
                                             , boost::simd::tag::sse_
                                             >
                                      ))
                                    )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0, const A2&, const A3& a3) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR(a0, sizeof(result_type));
      return _mm_maskload_pd(a0,_mm_castpd_si128(a3));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_load_
                                    , boost::simd::tag::avx_
                                    , (A0)(A2)(A3)
                                    , (iterator_< scalar_< single_<A0> > >)
                                      ((target_ < simd_ < single_<A2>
                                                        , boost::simd::tag::sse_
                                                        >
                                                >
                                      ))
                                      ((simd_< logical_<A3>
                                             , boost::simd::tag::sse_
                                             >
                                      ))
                                    )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0, const A2&, const A3& a3) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR(a0, sizeof(result_type));
      return _mm_maskload_ps(a0,_mm_castps_si128(a3));
    }
  };

  /// INTERNAL ONLY - Regular SIMD mask load for double without offset, zero case
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_load_
                                    , boost::simd::tag::avx_
                                    , (A0)(A2)(A3)
                                    , (iterator_< scalar_< double_<A0> > >)
                                      ((target_ < simd_ < double_<A2>
                                                        , boost::simd::tag::avx_
                                                        >
                                                >
                                      ))
                                      ((simd_< logical_<A3>
                                             , boost::simd::tag::avx_
                                             >
                                      ))
                                    )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0, const A2&, const A3& a3) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR(a0, sizeof(result_type));
      return _mm256_maskload_pd(a0,_mm256_castpd_si256(a3));
    }
  };

  /// INTERNAL ONLY - Regular SIMD load for double without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_load_
                                    , boost::simd::tag::avx_
                                    , (A0)(A2)
                                    , (iterator_< scalar_< double_<A0> > >)
                                      ((target_ < simd_ < double_<A2>
                                                        , boost::simd::tag::avx_
                                                        >
                                                >
                                      ))
                                    )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0, const A2&) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR(a0, sizeof(result_type));
      return _mm256_load_pd(a0);
    }
  };

  /// INTERNAL ONLY - Regular SIMD mask load for double without offset, zero case
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_load_
                                    , boost::simd::tag::avx_
                                    , (A0)(A2)(A3)
                                    , (iterator_< scalar_< single_<A0> > >)
                                      ((target_ < simd_ < single_<A2>
                                                        , boost::simd::tag::avx_
                                                        >
                                                >
                                      ))
                                      ((simd_< logical_<A3>
                                             , boost::simd::tag::avx_
                                             >
                                      ))
                                    )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0, const A2&, const A3& a3) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR(a0, sizeof(result_type));
      return _mm256_maskload_ps(a0,_mm256_castps_si256(a3));
    }
  };

  /// INTERNAL ONLY - Regular SIMD load for single without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::aligned_load_
                                    , boost::simd::tag::avx_
                                    , (A0)(A2)
                                    , (iterator_< scalar_< single_<A0> > >)
                                      ((target_ < simd_ < single_<A2>
                                                        , boost::simd::tag::avx_
                                                        >
                                                >
                                      ))
                                    )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0, const A2&) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR(a0, sizeof(result_type));
      return _mm256_load_ps(a0);
    }
  };

  /// INTERNAL ONLY - Regular SIMD load for integers without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::aligned_load_
                                      , boost::simd::tag::avx_
                                      , (A0)(A2)
                                      , ( simd::meta::is_pointing_to
                                          < A0
                                          , typename A2::type::value_type
                                          >
                                        )
                                      , (iterator_< scalar_< integer_<A0> > >)
                                        ((target_ < simd_
                                                    < integer_<A2>
                                                    , boost::simd::tag::avx_
                                                    >
                                                  >
                                        ))
                                      )
  {
    typedef typename A2::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 a0, const A2&) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR(a0, sizeof(result_type));
      return _mm256_load_si256(reinterpret_cast<__m256i const*>(a0));
    }
  };

    /// INTERNAL ONLY - Masked misaligned load without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::aligned_load_
                                      , boost::simd::tag::avx_
                                      , (A0)(A2)(A3)(A4)(A5)
                                      , ( simd::meta::is_pointing_to
                                          < A0
                                          , typename A2::type::value_type
                                          >
                                        )
                                      , (iterator_< scalar_< arithmetic_<A0> > >)
                                        ((target_ < simd_ < arithmetic_<A2>
                                                          , boost::simd::tag::avx_
                                                          >
                                                  >
                                        ))
                                        (mpl_integral_< scalar_< integer_<A3> > >)
                                        ((simd_< logical_<A4>
                                               , boost::simd::tag::avx_
                                               >
                                        ))
                                        ((simd_<arithmetic_<A5>
                                               , boost::simd::tag::avx_
                                               >
                                        ))
                                      )
  {
    typedef typename A2::type result_type;

    typedef typename A3::value_type align_t;
    static const std::size_t cardinal    = meta::cardinal_of<result_type>::value;
    static const align_t     unalignment = A3::value % cardinal;

    typedef typename boost::mpl::if_c < unalignment
                                      , boost::simd::tag::load_
                                      , boost::simd::tag::aligned_load_
                                      >::type           func_t;

    BOOST_FORCEINLINE result_type operator()(A0 a0, const A2& a2, const A3&, const A4& a4, const A5& a5) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR(a0 - A3::value, sizeof(result_type));
      typename boost::dispatch::make_functor<func_t, A0>::type callee;
      return callee( a0, a2, a4, a5 );
    }
  };

  /// INTERNAL ONLY - Misaligned load without offset
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION_IF( boost::simd::tag::aligned_load_
                                      , boost::simd::tag::avx_
                                      , (A0)(A2)(A3)
                                      , ( simd::meta::is_pointing_to
                                          < A0
                                          , typename A2::type::value_type
                                          >
                                        )
                                      , (iterator_< scalar_< arithmetic_<A0> > >)
                                        ((target_ < simd_ < arithmetic_<A2>
                                                          , boost::simd::tag::avx_
                                                          >
                                                  >
                                        ))
                                        (mpl_integral_< scalar_< integer_<A3> > >)
                                      )
  {
    typedef typename A2::type result_type;

    typedef typename A3::value_type align_t;
    static const std::size_t cardinal    = meta::cardinal_of<result_type>::value;
    static const align_t     unalignment = A3::value % cardinal;

    typedef typename boost::mpl::if_c < unalignment
                                      , boost::simd::tag::load_
                                      , boost::simd::tag::aligned_load_
                                      >::type           func_t;

    BOOST_FORCEINLINE result_type operator()(A0 a0, const A2& a2, const A3&) const
    {
      BOOST_SIMD_DETAILS_CHECK_PTR(a0 - A3::value, sizeof(result_type));
      typename boost::dispatch::make_functor<func_t, A0>::type callee;
      return callee( a0, a2 );
    }
  };
} } }

#endif
#endif
