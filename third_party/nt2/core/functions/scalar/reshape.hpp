//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_RESHAPE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_RESHAPE_HPP_INCLUDED

#include <nt2/core/functions/reshape.hpp>
#include <nt2/core/functions/colon.hpp>
#include <nt2/include/functions/as_size.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/comparison/equal.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/facilities/identity.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_shifted_params.hpp>

namespace nt2 { namespace ext
{
  #define M6(z,n,t)  A##n const&                                               \
  BOOST_PP_IF ( BOOST_PP_EQUAL(n,t)                                            \
              , BOOST_PP_EMPTY                                                 \
              , BOOST_PP_IDENTITY(a ## n)                                      \
              )()                                                              \
  /**/

  #define M5(z,n,t) * BOOST_PP_CAT(a,n)

  #define M4(z,n,t) , BOOST_PP_CAT(a,n)

  #define M3(z,n,t)                                                            \
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::reshape_, tag::cpu_                    \
                            , BOOST_PP_REPEAT(BOOST_PP_INC(t),M2,~)            \
                            , ((ast_<A0, nt2::container::domain>))             \
                              BOOST_PP_REPEAT(n,M1,~)                          \
                              ((node_< BOOST_PP_CAT(A,BOOST_PP_INC(n))         \
                                     , nt2::tag::empty_colon_                  \
                                     , boost::mpl::long_<3>                    \
                                     , nt2::container::domain                  \
                                     >                                         \
                              ))                                               \
                              BOOST_PP_REPEAT_FROM_TO(BOOST_PP_INC(n),t,M1,~)  \
                            )                                                  \
  {                                                                            \
    BOOST_DISPATCH_RETURNS_ARGS                                                \
    ( BOOST_PP_INC(t)                                                          \
    , ( BOOST_PP_ENUM_BINARY_PARAMS( BOOST_PP_INC(t), const A, & a) )          \
    , ( BOOST_PP_ENUM( BOOST_PP_INC(t), M6, BOOST_PP_INC(n) ) )                \
    , nt2::reshape                                                             \
      ( a0                                                                     \
      , nt2::as_size( BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PP_INC(n), a)         \
                      BOOST_PP_COMMA_IF(n) numel(a0)/(                         \
                        1 BOOST_PP_REPEAT_FROM_TO(1, BOOST_PP_INC(n), M5, ~)   \
                        BOOST_PP_REPEAT_FROM_TO( BOOST_PP_INC(BOOST_PP_INC(n)) \
                                               , BOOST_PP_INC(t)               \
                                               , M5                            \
                                               , ~                             \
                                               )                               \
                      )                                                        \
                      BOOST_PP_REPEAT_FROM_TO( BOOST_PP_INC(BOOST_PP_INC(n))   \
                                             , BOOST_PP_INC(t)                 \
                                             , M4                              \
                                             , ~                               \
                                             )                                 \
                    )                                                          \
      )                                                                        \
    )                                                                          \
  };                                                                           \
  /**/

  #define M2(z,n,t) (BOOST_PP_CAT(A,n))
  #define M1(z,n,t) (scalar_< integer_<BOOST_PP_CAT(A,BOOST_PP_INC(n))> >)

  #define M0(z,n,t)                                                                                \
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::reshape_, tag::cpu_                                        \
                            , BOOST_PP_REPEAT(BOOST_PP_INC(n),M2,~)                                \
                            , ((ast_<A0, nt2::container::domain>))                                 \
                              BOOST_PP_REPEAT(n,M1,~)                                              \
                            )                                                                      \
  {                                                                                                \
    BOOST_DISPATCH_RETURNS( BOOST_PP_INC(n)                                                        \
                          , (BOOST_PP_ENUM_BINARY_PARAMS( BOOST_PP_INC(n)                          \
                                                        , const A, & a                             \
                                                        )                                          \
                            )                                                                      \
                          , (nt2::reshape                                                          \
                              ( a0                                                                 \
                              , nt2::as_size( BOOST_PP_ENUM_SHIFTED_PARAMS                         \
                                              ( BOOST_PP_INC(n), a )                               \
                                            )                                                      \
                              )                                                                    \
                            )                                                                      \
                          )                                                                        \
  };                                                                                               \
  BOOST_PP_REPEAT(n,M3,n)                                                                          \
  /**/

  BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(NT2_MAX_DIMENSIONS),M0,~)

  #undef M6
  #undef M5
  #undef M4
  #undef M3
  #undef M2
  #undef M1
  #undef M0
} }

#endif
