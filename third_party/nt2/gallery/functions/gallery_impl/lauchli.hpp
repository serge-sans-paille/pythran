//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_LAUCHLI_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_LAUCHLI_HPP_INCLUDED
#include <nt2/gallery/functions/lauchli.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/vertcat.hpp>
#include <nt2/include/constants/sqrteps.hpp>

namespace nt2 {namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::lauchli_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<integer_<A0> >)
                              (scalar_<floating_<A1> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& n, A1 const& e)
                          , (nt2::catv( nt2::ones(1, n, meta::as_<A1>())
                                      , e*nt2::eye(n, meta::as_<A1>())
                                      )
                            )
                          )

  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::lauchli_, tag::cpu_
                            , (A0)
                            , (scalar_<integer_<A0> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 const& n)
                          , (nt2::lauchli(n, nt2::Sqrteps<double>()))
                          )

  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::lauchli_, tag::cpu_
                            , (A0)(T)
                            , (scalar_<integer_<A0> >)
                              (target_<scalar_<floating_<T> > > )
                            )
  {
    typedef typename T::type                   t_t;
    BOOST_DISPATCH_RETURNS_ARGS ( 2
                                , (A0 const& n, T const& t)
                                , (A0 const& n, T const&)
                                , (nt2::lauchli(n, nt2::Sqrteps<t_t>()))
                                )

  };

} }

#endif
