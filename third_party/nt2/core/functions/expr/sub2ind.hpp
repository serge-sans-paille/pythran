#if !BOOST_PP_IS_ITERATING
//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_SUB2IND_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_SUB2IND_HPP_INCLUDED

#include <nt2/core/functions/sub2ind.hpp>
#include <nt2/sdk/parameters.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/include/functions/as_size.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>

namespace nt2 { namespace ext
{
  template <class Domain, class Expr, int N>
  struct  value_type<tag::sub2ind_,Domain,N,Expr>
        : meta::value_as<Expr, 1>
  {};

  template<class Domain, int N, class Expr>
  struct  size_of<tag::sub2ind_,Domain,N,Expr>
  {
    typedef typename boost::fusion::result_of::pop_front<Expr const>::type expr_t;
    typedef typename elementwise_size<expr_t const,N>::result_type result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      elementwise_size<expr_t const,N> callee;
      return callee(boost::fusion::pop_front(e));
    }
  };

  #define BOOST_PP_FILENAME_1 "nt2/core/functions/expr/sub2ind.hpp"
  #define BOOST_PP_ITERATION_LIMITS (2, BOOST_PP_INC(NT2_MAX_DIMENSIONS))
  #include BOOST_PP_ITERATE()
} }

#endif

#else

  #define N BOOST_PP_ITERATION()

  #define M0(z,n,txt) (A##n)
  #define M1(z,n,txt) (unspecified_<A##n>)
  #define M2(z,n,txt) nt2::run(boost::proto::child_c<BOOST_PP_INC(n)>(a0),p,t)

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::sub2ind_, tag::cpu_
                            , (SZ)BOOST_PP_REPEAT(N,M0,~)
                            , ((ast_<SZ,nt2::container::domain>))
                              BOOST_PP_REPEAT(N,M1,~)
                            )
  {
    BOOST_DISPATCH_RETURNS( BOOST_PP_INC(N)
                          , ( SZ const& sz
                            , BOOST_PP_ENUM_BINARY_PARAMS(N,A, const& a)
                            )
                          , ( nt2::sub2ind( nt2::as_size(sz)
                                          , BOOST_PP_ENUM_PARAMS(N,a)
                                          )
                            )
                          )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(State)(Data)
                            , ((node_ < A0, nt2::tag::sub2ind_
                                      , boost::mpl::long_<BOOST_PP_INC(N)>
                                      , nt2::container::domain
                                      >
                              ))
                              (generic_< integer_<State> >)
                              (target_< unspecified_<Data> >)
                            )
  {
    typedef typename Data::type                       result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, State const& p, Data const& t) const
    {
      return sub2ind( boost::proto::value(boost::proto::child_c<0>(a0))
                    , BOOST_PP_ENUM(N,M2,~)
                    );
    }
  };

  #undef M2
  #undef M1
  #undef M0
  #undef N
#endif
