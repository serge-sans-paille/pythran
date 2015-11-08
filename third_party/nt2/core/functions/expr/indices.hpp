//==============================================================================
//         Copyright 2003 - 2011   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_CORE_FUNCTIONS_EXPR_INDICES_HPP_INCLUDED
#define NT2_CORE_FUNCTIONS_EXPR_INDICES_HPP_INCLUDED

#include <nt2/core/functions/indices.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/core/include/functions/as_size.hpp>

namespace nt2 { namespace ext
{
  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::indices_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              ((array_< scalar_< integer_<A1> >
                                      , boost::mpl::size_t<2>
                                      >
                              ))
                            )
  {
    BOOST_DISPATCH_RETURNS( 2, (A0 const& a0, A1 const& a1)
                          , (nt2::indices(nt2::as_size(a0),a1))
                          )
  };

  /// INTERNAL ONLY
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::indices_, tag::cpu_
                            , (A0)(A1)(T)
                            , ((ast_<A0, nt2::container::domain>))
                              ((array_< scalar_< integer_<A1> >
                                      , boost::mpl::size_t<2>
                                      >
                              ))
                              (target_< scalar_< unspecified_<T> > >)
                            )
  {
    BOOST_DISPATCH_RETURNS( 3, (A0 const& a0, A1 const& a1, T const& tgt)
                          , (nt2::indices(nt2::as_size(a0),a1,tgt))
                          )
  };
} }

#endif
