//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_TOEPPEN_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_TOEPPEN_HPP_INCLUDED
#include <nt2/gallery/functions/toeppen.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/tridiag.hpp>
#include <nt2/include/functions/repnum.hpp>

namespace nt2
{
  namespace ext
  {

    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::toeppen_, tag::cpu_,
                                (A0)(T),
                                (scalar_<integer_<A0> >)
                                (target_<scalar_<floating_<T> > > )
                              )
    {
      typedef typename T::type t_t;
      BOOST_DISPATCH_RETURNS_ARGS(2, (A0 const& n, T const& t),(A0 const& n, T const& ),
                             (nt2::toeppen(n, t_t(1), t_t(-10), t_t(0), t_t(10), t_t(1)))
                            )
        };

    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::toeppen_, tag::cpu_,
                                (A0)(A1)(A2)(A3)(A4)(A5),
                                (scalar_<integer_<A0> >)
                                (scalar_<floating_<A1> >)
                                (scalar_<floating_<A2> >)
                                (scalar_<floating_<A3> >)
                                (scalar_<floating_<A4> >)
                                (scalar_<floating_<A5> >)
                              )
    {
      BOOST_DISPATCH_RETURNS(6, (A0 const& n, A1 const& a, A2 const& b, A3 const& c, A4 const& d, A5 const& e),
                             (nt2::tridiag(n, b, c, d)+nt2::from_diag(nt2::repnum(a, n-2, 1), -2)+nt2::from_diag(nt2::repnum(e, n-2, 1), 2))
                            )
        };

  }


  meta::call<tag::toeppen_(const ptrdiff_t &, meta::as_<double> const &)>::type
  toeppen(ptrdiff_t n)
  {
    return nt2::toeppen(n,  meta::as_<double>());
  }
  template<class T>
  typename meta::call<tag::toeppen_(const ptrdiff_t &, typename meta::as_<T> const &)>::type
  toeppen(ptrdiff_t n)
  {
    return nt2::toeppen(n,  meta::as_<T>());
  }

}


#endif
