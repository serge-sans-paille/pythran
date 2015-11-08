//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_TABLE_FUNCTION_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_TABLE_FUNCTION_HPP_INCLUDED

#include <nt2/core/functions/function.hpp>
#include <nt2/include/functions/run.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (Expr)(State)(Data)(Arity)
                            , ((expr_< unspecified_<Expr>
                                     , nt2::tag::function_
                                     , Arity
                                     >
                              ))
                              (generic_< integer_<State> >)
                              (unspecified_<Data>)
                            )
  {
    typedef typename boost::proto::result_of::child_c<Expr&, 0>::type child0;
    typedef typename boost::proto::result_of::child_c<Expr&, 1>::type child1;

    typedef typename meta::call< tag::run_( child0
                                          , typename meta::call< tag::run_ ( child1
                                                                           , State const&
                                                                           , Data const&
                                                                           )
                                                               >::type
                                          , Data const&
                                          )
                               >::type                        result_type;

    BOOST_FORCEINLINE result_type
    operator()(Expr& expr, State const& state, Data const& data) const
    {
      return nt2::run( boost::proto::child_c<0>(expr)
                     , nt2::run( boost::proto::child_c<1>(expr)
                               , state
                               , data
                               )
                     , data
                     );
    }
  };
} }

#endif
