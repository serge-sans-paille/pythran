#ifndef BOOST_PP_IS_ITERATING
//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_COMMON_MAP_HPP_INCLUDED
#define BOOST_SIMD_OPERATOR_FUNCTIONS_SIMD_COMMON_MAP_HPP_INCLUDED

#include <boost/simd/operator/functions/map.hpp>
#include <boost/simd/include/functions/simd/insert.hpp>
#include <boost/simd/include/functions/simd/extract.hpp>
#include <boost/simd/include/functions/simd/make.hpp>
#include <boost/simd/operator/specific/utils.hpp>
#include <boost/simd/sdk/simd/meta/vector_of.hpp>
#include <boost/simd/sdk/meta/cardinal_of.hpp>
#include <boost/simd/sdk/meta/scalar_of.hpp>

#define BOOST_SIMD_MAX_LOG2_CARDINAL_MAKE_MAP 3

#if !defined(BOOST_SIMD_DONT_USE_PREPROCESSED_FILES)
#include <boost/simd/operator/functions/simd/common/preprocessed/map.hpp>
#else
#include <boost/dispatch/details/parameters.hpp>
#include <boost/dispatch/functor/preprocessor/call.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/slot/slot.hpp>
#if defined(__WAVE__) && defined(BOOST_SIMD_CREATE_PREPROCESSED_FILES) && __INCLUDE_LEVEL__ == 0
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/map.hpp")
#undef BOOST_FORCEINLINE
#endif

namespace boost { namespace simd { namespace ext
{
  #define M1(z,n,t) (generic_< unspecified_<A##n> >)
  #define M2(z,n,t) typename meta::scalar_of<A##n>::type
  #define M3(z,n,t) extract(a##n, t)
  #define M3s(z,n,t) extract<t>(a##n)
  #define M4(z,n,t) (A##n)
  #define M5(z,n,t) f(BOOST_PP_ENUM(t, M3s, n))
  #define M6(z,n,t) meta::cardinal_of<BOOST_PP_CAT(A,n)>::value

  #define BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_DISPATCH_MAX_ARITY, "boost/simd/operator/functions/simd/common/map.hpp"))
  #include BOOST_PP_ITERATE()

  #undef M6
  #undef M5
  #undef M4
  #undef M3s
  #undef M3
  #undef M2
  #undef M1
} } }

#if defined(__WAVE__) && defined(BOOST_SIMD_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif
#endif
#endif

#else
#if BOOST_PP_ITERATION_DEPTH() == 1

  #define BOOST_PP_VALUE BOOST_PP_ITERATION()
  #include BOOST_PP_ASSIGN_SLOT(1)
  #define n BOOST_PP_SLOT(1)

  #define BOOST_PP_VALUE 1
  #include BOOST_PP_ASSIGN_SLOT(2)

  BOOST_SIMD_FUNCTOR_IMPLEMENTATION( boost::simd::tag::map_, tag::cpu_
                            , (Func)BOOST_PP_REPEAT(n, M4, ~)
                            , (unspecified_<Func>)BOOST_PP_REPEAT(n,M1,~)
                            )
  {
    typedef typename dispatch::meta::
    result_of< Func const( BOOST_PP_ENUM(n,M2,~) )
             >::type
    rtype;

    static const std::size_t N = BOOST_DISPATCH_FOLD(n, cardinal_common<, >::value, M6, ~);

    typedef typename meta::
            vector_of< rtype
                     , N
                     >::type result_type;

    template<std::size_t N, class Dummy = void>
    struct impl
    {
      static result_type call(Func const& f, BOOST_PP_ENUM_BINARY_PARAMS(n, A, const & a))
      {
        result_type that;
        for(std::size_t i=0; i!=N; ++i)
          insert(f(BOOST_PP_ENUM(n, M3, i)), that, i);
        return that;
      }
    };

  #define BOOST_PP_ITERATION_PARAMS_2 (3, (1, BOOST_SIMD_MAX_LOG2_CARDINAL_MAKE_MAP, "boost/simd/operator/functions/simd/common/map.hpp"))
  #include BOOST_PP_ITERATE()

    BOOST_FORCEINLINE result_type operator()(Func const& f, BOOST_PP_ENUM_BINARY_PARAMS(n, A, const & a)) const
    {
      return impl<N>::call(f, BOOST_PP_ENUM_PARAMS(n, a));
    }
  };

  #undef n

#elif BOOST_PP_ITERATION_DEPTH() == 2

  #define BOOST_PP_VALUE BOOST_PP_SLOT(2)*2
  #include BOOST_PP_ASSIGN_SLOT(2)

    template<class Dummy>
    struct impl<BOOST_PP_SLOT(2), Dummy>
    {
      BOOST_FORCEINLINE static result_type call(Func const& f, BOOST_PP_ENUM_BINARY_PARAMS(n, A, const & a))
      {
        return make<result_type>(BOOST_PP_ENUM(BOOST_PP_SLOT(2), M5, n));
      }
    };

#endif
#endif
