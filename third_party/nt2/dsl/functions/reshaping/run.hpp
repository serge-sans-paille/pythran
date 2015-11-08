//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_DSL_FUNCTIONS_RESHAPING_RUN_HPP_INCLUDED
#define NT2_DSL_FUNCTIONS_RESHAPING_RUN_HPP_INCLUDED

#include <nt2/dsl/functions/run.hpp>
#include <nt2/sdk/meta/reshaping_hierarchy.hpp>

namespace nt2 { namespace ext
{
  //============================================================================
  // reshaping expression forward to its inner member
  //============================================================================
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_, tag::cpu_
                            , (A0)(Tag)(State)(Data)(N)
                            , ((node_ < A0, reshaping_<Tag>
                                      , N , nt2::container::domain
                                      >
                              ))
                              (generic_< integer_<State> >)
                              ((unspecified_<Data>))
                            )
  {
    typedef typename
            meta::call< nt2::tag::run_
                      ( typename  boost::proto::result_of::child_c<A0&,0>::type
                      , State const&
                      , Data const&
                      )
                      >::type                                   result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0& a0, State const& p, Data const& t) const
    {
      return nt2::run(boost::proto::child_c<0>(a0), p ,t);
    }
  };
} }

#endif
