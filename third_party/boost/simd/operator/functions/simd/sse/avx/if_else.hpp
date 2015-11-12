//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_SSE_AVX_IF_ELSE_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_SSE_AVX_IF_ELSE_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/operator/functions/if_else.hpp>
#include <boost/simd/include/functions/simd/bitwise_cast.hpp>
#include <boost/simd/include/functions/simd/genmask.hpp>
#include <boost/dispatch/meta/as_floating.hpp>
#include <boost/dispatch/attributes.hpp>

namespace boost { namespace simd { namespace ext
{
  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::if_else_
                                    , boost::simd::tag::avx_
                                    , (A0)(A1)
                                    , ((simd_<logical_<A0>, boost::simd::tag::avx_>))
                                      ((simd_<single_<A1> , boost::simd::tag::avx_>))
                                      ((simd_<single_<A1> , boost::simd::tag::avx_>))
                                    )
  {
    typedef A1 result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0,A1 const& a1,A1 const& a2) const
    {
      return _mm256_blendv_ps(a2, a1, bitwise_cast<A1>(genmask(a0)));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::if_else_
                                    , boost::simd::tag::avx_
                                    , (A0)(A1)
                                    , ((simd_<logical_<A0>, boost::simd::tag::avx_>))
                                      ((simd_<double_<A1> , boost::simd::tag::avx_>))
                                      ((simd_<double_<A1> , boost::simd::tag::avx_>))
                                    )
  {
    typedef A1 result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0,A1 const& a1,A1 const& a2) const
    {
      return _mm256_blendv_pd(a2, a1, bitwise_cast<A1>(genmask(a0)));
    }
  };

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::if_else_
                                    , boost::simd::tag::avx_
                                    , (A0)(A1)
                                    , ((simd_<logical_<A0>, boost::simd::tag::avx_>))
                                      ((simd_<floating_sized_<A1>, boost::simd::tag::avx_>))
                                      ((simd_<floating_sized_<A1>, boost::simd::tag::avx_>))
                                    )
  {
    typedef A1 result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0,A1 const& a1,A1 const& a2) const
    {
      typedef typename dispatch::meta::as_floating<A1>::type ctype;

      return bitwise_cast<A1> ( if_else ( a0
                                        , bitwise_cast<ctype>(a1)
                                        , bitwise_cast<ctype>(a2)
                                        )
                              );
    }
  };
} } }

#endif
#endif
