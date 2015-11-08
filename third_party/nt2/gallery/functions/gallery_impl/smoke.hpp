//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_SMOKE_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_SMOKE_HPP_INCLUDED
#include <nt2/gallery/functions/smoke.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/cumprod.hpp>
#include <nt2/include/functions/expipi.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/deltaf.hpp>
#include <nt2/include/functions/selsub.hpp>
namespace nt2
{

  namespace ext
  {

    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::smoke_, tag::cpu_,
                                (A0)(T),
                                (scalar_<integer_<A0> >)
                                (target_<scalar_<floating_<T> > > )
                              )
    {
      typedef typename T::type t_t;
      BOOST_DISPATCH_RETURNS_ARGS(2, (A0 const& n, T const& t),(A0 const& n, T const& ),
                             (nt2::from_diag(nt2::cumprod(nt2::repnum( nt2::expipi(Two<t_t>()/t_t(n)),nt2::of_size(1, n))))+
                              nt2::from_diag(nt2::ones(n-1, 1, T()), 1)+nt2::deltaf(n, 1, nt2::of_size(n, n), T())
                             )
                            )
        };
   NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::smoke_, tag::cpu_,
                                (A0)(A1)(T),
                                (scalar_<integer_<A0> >)
                                (scalar_<integer_<A1> >)
                                (target_<scalar_<floating_<T> > > )
                              )
   {
     typedef typename T::type t_t;
     typedef typename nt2::meta::as_<std::complex<t_t> > cT;
     BOOST_DISPATCH_RETURNS_ARGS(3, (A0 const& n, A1 const& k,T const& t),(A0 const& n, A1 const& k,T const& ),
                            (nt2::selsub(nt2::is_eqz(t_t(k)),
                                         nt2::smoke(n, T()),
                                         nt2::deltaf(n, 1, nt2::of_size(n, n), cT()))
                            )
                           )
       };
  }

  meta::call<tag::smoke_(const ptrdiff_t &, meta::as_<double> const &)>::type
  smoke(ptrdiff_t n)
  {
    return nt2::smoke(n,  meta::as_<double>());
  }
  template<class T>
  typename meta::call<tag::smoke_(const ptrdiff_t &, typename meta::as_<T> const &)>::type
  smoke(ptrdiff_t n)
  {
    return nt2::smoke(n,  meta::as_<T>());
  }
  meta::call<tag::smoke_(const ptrdiff_t &, const ptrdiff_t &, meta::as_<double> const &)>::type
  smoke(ptrdiff_t n, ptrdiff_t k)
  {
    return nt2::smoke(n, k, meta::as_<double>());
  }
  template<class T>
  typename meta::call<tag::smoke_(const ptrdiff_t &, const ptrdiff_t &, typename meta::as_<T> const &)>::type
  smoke(ptrdiff_t n, ptrdiff_t k)
  {
    return nt2::smoke(n, k, meta::as_<T>());
  }

}


#endif
