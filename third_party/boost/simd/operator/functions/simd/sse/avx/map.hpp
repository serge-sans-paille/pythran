#ifndef BOOST_PP_IS_ITERATING
//==============================================================================
//         Copyright 2003 - 2013 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2012 - 2013 MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_SSE_AVX_MAP_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_SSE_AVX_MAP_HPP_INCLUDED
#ifdef BOOST_SIMD_HAS_AVX_SUPPORT

#include <boost/simd/operator/functions/map.hpp>
#include <boost/simd/include/functions/simd/slice.hpp>
#include <boost/simd/include/functions/simd/combine.hpp>
#include <boost/simd/sdk/simd/category.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>

////////////////////////////////////////////////////////////////////////////////
// Implements a SIMD map that applies a given function to any AVX vector type.
// This is done by splitting it into 2 SSE vectors calling the functor on each
// and merging the two results.
////////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_SIMD_DONT_USE_PREPROCESSED_FILES)
#include <boost/simd/operator/functions/simd/sse/avx/preprocessed/map.hpp>
#else

#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/dispatch/details/parameters.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

#if defined(__WAVE__) && defined(BOOST_SIMD_CREATE_PREPROCESSED_FILES) && __INCLUDE_LEVEL__ == 0
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/map.hpp")
#undef BOOST_FORCEINLINE
#endif

namespace boost { namespace simd { namespace ext
{
  #define M0(z,n,h) ((simd_< unspecified_<A##n>, boost::simd::tag::avx_ >))
  #define M1(z,n,t) simd::native<typename meta::scalar_of<A##n>::type, tag::sse_> const&
  #define M2(z,n,t) (A##n)

  #define M3(z,n,t)                                                            \
  native<typename meta::scalar_of<A##n>::type,tag::sse_> a##0##n,a##1##n;      \
  boost::simd::slice(a##n,a##0##n,a##1##n);                                    \
  /**/

  #define BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_DISPATCH_MAX_ARITY, "boost/simd/operator/functions/simd/sse/avx/map.hpp"))
  #include BOOST_PP_ITERATE()

  #undef M3
  #undef M2
  #undef M1
  #undef M0
} } }

#if defined(__WAVE__) && defined(BOOST_SIMD_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif
#endif
#endif

#else
  #define n BOOST_PP_ITERATION()

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION ( boost::simd::tag::map_
                                    , boost::simd::tag::avx_
                                    , (Func)BOOST_PP_REPEAT(n, M2, ~)
                                    , (unspecified_<Func>)
                                      BOOST_PP_REPEAT(n,M0,~)
                                    )
  {
    typedef typename dispatch::meta::
    result_of< Func const( BOOST_PP_ENUM(n,M1,~) )>::type base;

    typedef simd::native< typename meta::scalar_of<base>::type
                        , boost::simd::tag::avx_
                        > result_type;

    BOOST_FORCEINLINE result_type
    operator()( Func const& f
              , BOOST_PP_ENUM_BINARY_PARAMS(n, A, const& a)
              ) const
    {
      BOOST_PP_REPEAT(n, M3, ~)
      return boost::simd::combine ( f(BOOST_PP_ENUM_PARAMS(n, a0) )
                                  , f(BOOST_PP_ENUM_PARAMS(n, a1) )
                                  );
    }
  };

  #undef n

#endif
