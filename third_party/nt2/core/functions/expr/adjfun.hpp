//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//         Copyright 2011 - 2012   MetaScale SAS
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_ADJFUN_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_ADJFUN_HPP_INCLUDED

#include <nt2/core/functions/adjfun.hpp>
#include <nt2/include/functions/firstnonsingleton.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::adjfun_, tag::cpu_
                            , (Functor)(A0)
                            , (unspecified_<Functor>)
                              ((ast_<A0, nt2::container::domain>))
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::adjfun_
                                          , container::domain
                                          , A0 const&
                                          , std::size_t
                                          , Functor
                                          >::type             result_type;

    BOOST_FORCEINLINE
    result_type operator()(Functor const& f, A0 const& a0) const
    {
      std::size_t along = nt2::firstnonsingleton(a0) - 1u;
      return boost::proto::make_expr< nt2::tag::adjfun_
                                    , container::domain
                                    >( boost::cref(a0), along, f );
    }
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::adjfun_, tag::cpu_
                            , (Functor)(A0)(Along)
                            , (unspecified_<Functor>)
                              ((ast_<A0, nt2::container::domain>))
                              (scalar_<integer_<Along> >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::adjfun_
                                          , container::domain
                                          , A0 const&
                                          , std::size_t
                                          , Functor
                                          >::type             result_type;

    BOOST_FORCEINLINE
    result_type operator()(Functor const& f, A0 const& a0, Along const& d) const
    {
      std::size_t along = d-1;
      return boost::proto::make_expr< nt2::tag::adjfun_
                                    , container::domain
                                    >( boost::cref(a0), along, f );
    }
  };
} }

#endif
