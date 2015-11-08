#ifndef BOOST_PP_IS_ITERATING
//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_SPECIFIC_COMMON_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_SPECIFIC_COMMON_HPP_INCLUDED

////////////////////////////////////////////////////////////////////////////////
// By default, any SIMD implementation falls down to scalar map application if
// nothing is implemented for doing otherwise.
////////////////////////////////////////////////////////////////////////////////
#include <boost/simd/sdk/simd/category.hpp>
#include <boost/simd/include/functions/simd/map.hpp>
#include <boost/simd/include/functions/simd/splat.hpp>
#include <boost/dispatch/functor/meta/call.hpp>
#include <boost/dispatch/meta/print.hpp>
#include <boost/dispatch/meta/any.hpp>
#include <boost/dispatch/meta/enable_if_type.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/or.hpp>
#include <boost/proto/traits.hpp>

#include <boost/simd/operator/specific/utils.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/simd/meta/extension_of.hpp>

#ifdef BOOST_SIMD_LOG_MAP
namespace boost { namespace simd { namespace details
{
  template<class Sig>
  struct MAP_FALLBACK;
} } }
#define BOOST_SIMD_MAP_LOG(Sig) typedef typename boost::dispatch::meta::print< boost::simd::details::MAP_FALLBACK<Sig> >::type _;
#else
#define BOOST_SIMD_MAP_LOG(Sig)
#endif

#if !defined(BOOST_SIMD_DONT_USE_PREPROCESSED_FILES)
#include <boost/simd/operator/specific/preprocessed/common.hpp>
#else
#include <boost/dispatch/details/parameters.hpp>
#include <boost/simd/sdk/functor/preprocessor/dispatch.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/control/expr_if.hpp>
#if defined(__WAVE__) && defined(BOOST_SIMD_CREATE_PREPROCESSED_FILES) && __INCLUDE_LEVEL__ == 0
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/common.hpp")
#undef BOOST_SIMD_MAP_LOG
#undef BOOST_FORCEINLINE
#endif

////////////////////////////////////////////////////////////////////////////////
// Register all tag and extension agnostic call for common code sharing
////////////////////////////////////////////////////////////////////////////////

namespace boost { namespace simd { namespace ext
{
  #define M0(z,n,t) (A##n)
  #define M1(z,n,t) (unspecified_<A##n>)
  #define M2(z,n,t) unspecified_<A##n>
  #define M3(z,n,t) typename meta::extension_of<BOOST_PP_CAT(A,n)>::type
  #define M4(z,n,t) meta::cardinal_of<BOOST_PP_CAT(A,n)>::value
  #define M5(z,n,t) typename vector_on_ext< typename meta::scalar_of<A##n>::type, N, X >::type
  #define M5r(z,n,t) M5(z,n,t) const&
  #define M6(z,n,t) splat<M5(z,n,t)>(a##n)
  #define M7(z,n,t) BOOST_PP_EXPR_IF(n, ||) (meta::cardinal_of<A##n>::value == 1u)
  #define M8(z,n,t) typename meta::scalar_of<A##n>::type

  #define BOOST_PP_ITERATION_PARAMS_1 (3, ( 1, BOOST_DISPATCH_MAX_ARITY, "boost/simd/operator/specific/common.hpp"))
  #include BOOST_PP_ITERATE()

  #undef M8
  #undef M7
  #undef M6
  #undef M5r
  #undef M5
  #undef M4
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

#else
#define n BOOST_PP_ITERATION()

  template<BOOST_PP_ENUM_PARAMS(n, class A), class X, std::size_t N, class Callee, class Result = boost::dispatch::meta::result_of<Callee(BOOST_PP_ENUM(n, M5r, ~))>, class Enable = void>
  struct BOOST_PP_CAT(splat_impl, n)
  {
  };

  template<BOOST_PP_ENUM_PARAMS(n, class A), class X, std::size_t N, class Callee, class Result>
  struct BOOST_PP_CAT(splat_impl, n)<BOOST_PP_ENUM_PARAMS(n, A), X, N, Callee, Result, typename boost::dispatch::meta::enable_if_type<typename Result::type>::type>
  {
    typedef typename Result::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, const & a)) const
    {
      return Callee()(BOOST_PP_ENUM(n, M6, ~));
    }
  };

  template<class Tag, BOOST_PP_ENUM_PARAMS(n, class A), class X, std::size_t N, bool B = N != 1
                                      && !is_same<X, dispatch::meta::na_>::value
                                      && (BOOST_PP_REPEAT(n, M7, ~))>
  struct BOOST_PP_CAT(splat_or_map_choose, n);

  template<class Tag, BOOST_PP_ENUM_PARAMS(n, class A), class X, std::size_t N>
  struct BOOST_PP_CAT(splat_or_map_choose, n)<Tag, BOOST_PP_ENUM_PARAMS(n, A), X, N, true>
       : BOOST_PP_CAT(splat_impl, n)< BOOST_PP_ENUM_PARAMS(n, A)
                                    , X, N
                                    , typename boost::dispatch::meta::
                                      dispatch_call<Tag(BOOST_PP_ENUM(n, M5r, ~))>::type
                                    >
  {
  };

  template<class Tag, BOOST_PP_ENUM_PARAMS(n, class A), class SResult, class Enable = void>
  struct BOOST_PP_CAT(map_impl, n)
  {
  };

  template<class Tag, BOOST_PP_ENUM_PARAMS(n, class A), class SResult>
  struct BOOST_PP_CAT(map_impl, n)<Tag, BOOST_PP_ENUM_PARAMS(n, A), SResult, typename boost::dispatch::meta::enable_if_type<typename SResult::type>::type>
  {
    BOOST_SIMD_MAP_LOG(Tag)

    typedef typename boost::dispatch::meta::
            call<tag::map_( boost::dispatch::functor<Tag>
                          , BOOST_PP_ENUM_BINARY_PARAMS(n, A, const & BOOST_PP_INTERCEPT)
                          )
                >::type result_type;

    BOOST_FORCEINLINE result_type
    operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, const & a)) const
    {
      return map( dispatch::functor<Tag>(), BOOST_PP_ENUM_PARAMS(n, a) );
    }
  };

  template<class Tag, BOOST_PP_ENUM_PARAMS(n, class A), class X, std::size_t N>
  struct BOOST_PP_CAT(splat_or_map_choose, n)<Tag, BOOST_PP_ENUM_PARAMS(n, A), X, N, false>
       : BOOST_PP_CAT(map_impl, n)< Tag, BOOST_PP_ENUM_PARAMS(n, A)
                                  , boost::dispatch::meta::
                                    call<Tag(BOOST_PP_ENUM(n, M8, ~))>
                                  >
  {
  };

  template<class Tag, BOOST_PP_ENUM_PARAMS(n, class A)>
  struct BOOST_PP_CAT(splat_or_map, n)
       : BOOST_PP_CAT(splat_or_map_choose, n)< Tag, BOOST_PP_ENUM_PARAMS(n, A)
                                             , BOOST_DISPATCH_FOLD(n, typename ext_common<, >::type, M3, ~)
                                             , BOOST_DISPATCH_FOLD(n, cardinal_common<, >::value, M4, ~)
                                             >
  {
  };

  BOOST_SIMD_REGISTER_DISPATCH_TO_IF( elementwise_<Tag> , tag::formal_
                                    , (Tag)BOOST_PP_REPEAT(n,M0,~)
                                    , (mpl::not_< any <  mpl::or_
                                                         < boost::proto::
                                                           is_expr<mpl::_>
                                                         , boost::dispatch::
                                                           meta::is_proxy<mpl::_>
                                                         >
                                                      , BOOST_PP_ENUM_PARAMS(n,A)
                                                      >
                                                >
                                      )
                                    , BOOST_PP_REPEAT(n,M1,~)
                                    , (boost::simd::ext::BOOST_PP_CAT(splat_or_map, n)< Tag, BOOST_PP_ENUM_PARAMS(n, A) >)
                                    )

#undef n
#endif
