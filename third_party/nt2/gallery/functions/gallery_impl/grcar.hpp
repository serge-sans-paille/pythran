//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_GRCAR_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_GRCAR_HPP_INCLUDED
#include <nt2/include/functions/grcar.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/tril.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/from_diag.hpp>

namespace nt2 {namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::grcar_, tag::cpu_,
                              (A0)(A1)(T),
                              (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                              (target_<scalar_<unspecified_<T> > >)
                            )
  {
    BOOST_DISPATCH_RETURNS_ARGS(3, (A0 const& n,A1 const& k,T const &t), (A0 const& n,A1 const& k,T const &),
                           ( nt2::tril(nt2::triu(nt2::ones(n,T())), k) - nt2::from_diag(nt2::ones(n-1,1,T()), -1))
                          )
      };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::grcar_, tag::cpu_,
                              (A0)(T),
                              (scalar_<integer_<A0> >)
                              (target_<scalar_<unspecified_<T> > >)
                            )
  {
    BOOST_DISPATCH_RETURNS_ARGS(2, (A0 const& n,T const &t), (A0 const& n,T const &),
                           ( nt2::grcar(n, 3, T()))
                          )
      };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::grcar_, tag::cpu_,
                              (A0)(A1),
                              (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& n,A1 const& k),
                           ( grcar(n, k, meta::as_<double>()))
                          )
      };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::grcar_, tag::cpu_,
                              (A0),
                              (scalar_<integer_<A0> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 const& n),
                           ( grcar(n, 3, meta::as_<double>()))
                          )
      };



} }

#endif
