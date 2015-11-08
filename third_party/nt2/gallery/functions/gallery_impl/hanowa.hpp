//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_HANOWA_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_HANOWA_HPP_INCLUDED
#include <nt2/include/functions/hanowa.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/constants/mone.hpp>

namespace nt2 {namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::hanowa_, tag::cpu_,
                              (A0)(A1)(T),
                              (scalar_<integer_<A0> >)
                              (scalar_<arithmetic_<A1> >)
                              (target_<scalar_<unspecified_<T> > >)
                            )
  {
    typedef typename T::type t_t;
    BOOST_DISPATCH_RETURNS_ARGS(3, (A0 const& m,A1 const& d,T const &t),(A0 const& m,A1 const& d,T const &),
                           ( t_t(d)*nt2::eye(2*m, T())+
                             nt2::from_diag( nt2::_(t_t(1), t_t(m)), -ptrdiff_t(m))+
                             nt2::from_diag(-nt2::_(t_t(1), t_t(m)), m))
                          )
      };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::hanowa_, tag::cpu_,
                              (A0)(T),
                              (scalar_<integer_<A0> >)
                              (target_<scalar_<unspecified_<T> > >)
                            )
  {
    typedef typename T::type t_t;
    BOOST_DISPATCH_RETURNS_ARGS(2, (A0 const& m,T const &t), (A0 const& m,T const &),
                           (nt2::hanowa(m, t_t(-1), T()))
                          )
      };


} }

#endif
