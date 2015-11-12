//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_SCALAR_RESIZE_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_SCALAR_RESIZE_HPP_INCLUDED

#include <nt2/core/functions/resize.hpp>
#include <nt2/include/functions/as_size.hpp>

#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates linearize_ from expression + N size value
  //============================================================================
  #define M2(z,n,t) (BOOST_PP_CAT(A,n))
  #define M1(z,n,t) (scalar_< integer_<BOOST_PP_CAT(A,BOOST_PP_INC(n))> >)

  #define M0(z,n,t)                                                           \
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::resize_, tag::cpu_                    \
                            , BOOST_PP_REPEAT(BOOST_PP_INC(n),M2,~)           \
                            , ((ast_<A0, nt2::container::domain>))            \
                              BOOST_PP_REPEAT(n,M1,~)                         \
                            )                                                 \
  {                                                                           \
    BOOST_DISPATCH_RETURNS( BOOST_PP_INC(n)                                   \
                          , (BOOST_PP_ENUM_BINARY_PARAMS( BOOST_PP_INC(n)     \
                                                        , const A, & a        \
                                                        )                     \
                            )                                                 \
                          , (nt2::resize                                      \
                              ( a0                                            \
                              , nt2::as_size( BOOST_PP_ENUM_SHIFTED_PARAMS    \
                                              ( BOOST_PP_INC(n), a )          \
                                            )                                 \
                              )                                               \
                            )                                                 \
                          )                                                   \
  };                                                                          \
  /**/

  BOOST_PP_REPEAT_FROM_TO(1,BOOST_PP_INC(NT2_MAX_DIMENSIONS),M0,~)

  #undef M2
  #undef M1
  #undef M0
} }

#endif
