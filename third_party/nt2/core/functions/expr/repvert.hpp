//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_REPVERT_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_REPVERT_HPP_INCLUDED

#include <nt2/core/functions/repvert.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // Generates repvert from 1 expression
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::repvert_, tag::cpu_
                            , (A0)
                            , ((ast_<A0, nt2::container::domain>))
                            )
  {
    typedef A0 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return a0;
    }
  };

  //============================================================================
  // Generates linearize_ from expression and integer
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::repvert_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_<integer_<A1> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, A1 const& n)
                          , (boost::proto::make_expr< nt2::tag::repvert_
                                                    , container::domain
                                                    > (boost::cref(a0), n)
                            )
                          )
  };
} }

#endif
