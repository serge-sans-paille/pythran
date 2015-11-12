//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_GEARMAT_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_GEARMAT_HPP_INCLUDED
#include <nt2/include/functions/gearmat.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/iround.hpp>
#include <nt2/include/functions/deltaf.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/tridiag.hpp>
#include <nt2/include/functions/sign.hpp>

namespace nt2 {namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gearmat_, tag::cpu_,
                              (A0)(A1)(A2)(T),
                              (scalar_<integer_<A0> >)
                              (scalar_<arithmetic_<A1> >)
                              (scalar_<arithmetic_<A2> >)
                              (target_<scalar_<unspecified_<T> > >)
                            )
  {
    typedef typename T::type t_t;
    BOOST_DISPATCH_RETURNS(4, (A0 const& n,A1 const& i,A2 const& j,T const &t)
                          , ( nt2::tridiag(n, t_t(1), t_t(0), t_t(1))
                            + nt2::deltaf(1, nt2::iround(nt2::abs(i)), n, n, t)
                            * t_t(nt2::sign(i))
                            + nt2::deltaf(n, n+1-nt2::iround(nt2::abs(j)), n, n, t)
                            * t_t(nt2::sign(j))
                            )
                          )
      };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gearmat_, tag::cpu_,
                              (A0)(A1)(T),
                              (scalar_<integer_<A0> >)
                              (scalar_<arithmetic_<A1> >)
                              (target_<scalar_<unspecified_<T> > >)
                            )
  {
    BOOST_DISPATCH_RETURNS(3, (A0 const& n,A1 const& i,T const &t)
                          , ( nt2::gearmat(n, i, -ptrdiff_t(n), t))
                          )
      };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gearmat_, tag::cpu_,
                              (A0)(T),
                              (scalar_<integer_<A0> >)
                              (target_<scalar_<unspecified_<T> > >)
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& n,T const& t)
                          , ( nt2::gearmat(n, n, -ptrdiff_t(n), t) )
                          )
      };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gearmat_, tag::cpu_,
                              (A0)(A1)(A2),
                              (scalar_<integer_<A0> >)
                              (scalar_<floating_<A1> >)
                              (scalar_<arithmetic_<A2> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(3, (A0 const& n,A1 const& i,A2 const& j)
                          , ( nt2::gearmat(n, i, j, meta::as_<A1>()))
                          )
      };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gearmat_, tag::cpu_,
                              (A0)(A1)(A2),
                              (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                              (scalar_<floating_<A2> >)
                            )
  {

    BOOST_DISPATCH_RETURNS(3, (A0 const& n,A1 const& i,A2 const& j),
                           ( nt2::gearmat(n, i, j, meta::as_<A2>()))
                          )
      };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gearmat_, tag::cpu_,
                              (A0)(A1),
                              (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& n,A1 const& i),
                           ( gearmat(n, i, -ptrdiff_t(n), meta::as_<double>()))
                          )
      };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gearmat_, tag::cpu_,
                              (A0)(A1),
                              (scalar_<integer_<A0> >)
                              (scalar_<floating_<A1> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& n,A1 const& i),
                           ( gearmat(n, i, -ptrdiff_t(n), meta::as_<A1>()))
                          )
      };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gearmat_, tag::cpu_,
                              (A0),
                              (scalar_<integer_<A0> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 const& n),
                           ( gearmat(n, n, -ptrdiff_t(n), meta::as_<double>()))
                          )
      };
} }

#endif
