#if !BOOST_PP_IS_ITERATING
//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_NDGRID_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_NDGRID_HPP_INCLUDED

#include <nt2/core/functions/ndgrid.hpp>
#include <nt2/sdk/meta/value_as.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/container/dsl/size.hpp>
#include <nt2/core/container/dsl/value_type.hpp>
#include <nt2/core/utility/of_size/mpl_value.hpp>
#include <nt2/include/functions/numel.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum.hpp>

namespace nt2 { namespace ext
{
  template <class Domain, class Expr, int N>
  struct  value_type<tag::ndgrid_,Domain,N,Expr>
        : meta::value_as<Expr, 1>
  {};

  #define BOOST_PP_FILENAME_1 "nt2/core/functions/expr/ndgrid.hpp"
  #define BOOST_PP_ITERATION_LIMITS (2, NT2_MAX_DIMENSIONS)
  #include BOOST_PP_ITERATE()

} }

#endif

#else

  #define N BOOST_PP_ITERATION()

  #define M1(z,n,txt) (scalar_< unspecified_<A0> >)
  #define M2(z,n,txt) nt2::numel( boost::proto::child_c<n>(e) )

  #define M3(z,n,txt)                                                          \
  typedef typename boost::proto::result_of::child_c<Expr&,n>::value_type c##n; \
  typedef typename                                                             \
          meta::call<tag::numel_(typename c##n::extent_type)>::type d##n;      \
  typedef typename mpl_value<d##n>::type s##n;                                 \
  /**/

  #define M4(z,n,txt) s##n::value

  template<class Domain, class Expr>
  struct  size_of<tag::ndgrid_,Domain,N,Expr>
  {
    BOOST_PP_REPEAT(N,M3,~)
    typedef of_size_<BOOST_PP_ENUM(N,M4,~)> result_type;

    BOOST_FORCEINLINE result_type operator()(Expr& e) const
    {
      result_type that( BOOST_PP_ENUM(N,M2,~) );
      return that;
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ndgrid_, tag::cpu_
                            , (A0)
                            , BOOST_PP_REPEAT(N,M1,~)
                            )
  {
    BOOST_DISPATCH_RETURNS( N
                          , ( BOOST_PP_ENUM_PARAMS(N, A0 a) )
                          , ( boost::proto::make_expr
                              < nt2::tag::ndgrid_
                              , nt2::container::domain
                              >
                              ( BOOST_PP_ENUM_PARAMS(N, a) )
                            )
                          );
  };

  #undef M4
  #undef M3
  #undef M2
  #undef M1

  #undef N

#endif
