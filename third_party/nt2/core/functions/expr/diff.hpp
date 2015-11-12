//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_DIFF_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_DIFF_HPP_INCLUDED

#include <nt2/core/functions/diff.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/include/functions/firstnonsingleton.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::diff_, tag::cpu_
                            , (A0)
                            , ((ast_<A0, nt2::container::domain>))
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::diff_
                                          , container::domain
                                          , A0 const&
                                          , std::size_t
                                          , std::size_t
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return boost::proto::make_expr< nt2::tag::diff_
                                    , container::domain
                                    > ( boost::cref(a0)
                                      , std::size_t(nt2::firstnonsingleton(a0)-1)
                                      , std::size_t(1)
                                      );
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::diff_, tag::cpu_
                            , (A0)(A1)(A2)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_<integer_<A1> >)
                              (scalar_<integer_<A2> >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::diff_
                                          , container::domain
                                          , A0 const&
                                          , std::size_t
                                          , std::size_t
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()( A0 const& a0
                                            , A1 const& order
                                            , A2 const& al
                                            ) const
    {
      return boost::proto::make_expr< nt2::tag::diff_
                                    , container::domain
                                    > ( boost::cref(a0)
                                      , std::size_t(al-1)
                                      , std::size_t(order)
                                      );
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::diff_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              (scalar_<integer_<A1> >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::diff_
                                          , container::domain
                                          , A0 const&
                                          , std::size_t
                                          , std::size_t
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0,
                                             A1 const& order ) const
    {
      return boost::proto::make_expr< nt2::tag::diff_
                                    , container::domain
                                    > ( boost::cref(a0)
                                      , std::size_t(nt2::firstnonsingleton(a0)-1)
                                      , std::size_t(order)
                                      );
    }
  };
} }

#endif
