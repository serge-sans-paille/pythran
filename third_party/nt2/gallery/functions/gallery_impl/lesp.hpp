//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_LESP_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_LESP_HPP_INCLUDED
#include <nt2/gallery/functions/lesp.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/tridiag.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/minusone.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/constants/mtwo.hpp>

namespace nt2
{
  namespace ext
  {

    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::lesp_, tag::cpu_,
                                (A0)(T),
                                (scalar_<integer_<A0> >)
                                (target_<scalar_<floating_<T> > > )
                              )
    {
      typedef typename T::type t_t;
      BOOST_DISPATCH_RETURNS_ARGS(2, (A0 const& n, T const& t),(A0 const& n, T const& ),
                             (nt2::tridiag( nt2::rec(_(t_t(2), t_t(n))),
                                            nt2::minusone(Mtwo<t_t>()*nt2::cath(_(t_t(2), t_t(n)), nt2::oneplus(t_t(n)))),
                                            _(t_t(2), t_t(n))
                                          )
                             )
                            )
        };
  }
  meta::call<tag::lesp_(const ptrdiff_t &, meta::as_<double> const &)>::type
  lesp(ptrdiff_t n)
  {
    return nt2::lesp(n,  meta::as_<double>());
  }
  template<class T>
  typename meta::call<tag::lesp_(const ptrdiff_t &, typename meta::as_<T> const &)>::type
  lesp(ptrdiff_t n)
  {
    return nt2::lesp(n,  meta::as_<T>());
  }


}


#endif
