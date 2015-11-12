//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_EXPAND_TO_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_EXPAND_TO_HPP_INCLUDED

#include <nt2/core/functions/expand_to.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/include/functions/isexpandable_to.hpp>
#include <nt2/include/functions/repnum.hpp>

#include <boost/assert.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expand_to_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              (fusion_sequence_<A1>)
                            )
  {
    typedef typename  boost::remove_const<A1>::type sizes_t;
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::expand_to_
                                          , container::domain
                                          , A0 const&
                                          , sizes_t
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& a1) const
    {
      BOOST_ASSERT_MSG( isexpandable_to(a0, a1)
                      , "Incompatible expansion pattern"
                      );

      return  boost::proto::
              make_expr < nt2::tag::expand_to_
                        , container::domain
                        > ( boost::cref(a0), a1 );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expand_to_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              ((ast_<A1, nt2::container::domain>))
                            )
  {
    BOOST_DISPATCH_RETURNS( 2, (A0 const& a0, A1 const& a1)
                          , nt2::expand_to(a0,nt2::as_size(a1))
                          )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expand_to_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<unspecified_<A0> > )
                              (unspecified_<A1>)
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& a0, A1 const& a1), repnum(a0, a1) )
  };
} }

#endif
