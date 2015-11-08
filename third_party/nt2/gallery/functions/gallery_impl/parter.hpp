//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_PARTER_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_PARTER_HPP_INCLUDED
#include <nt2/gallery/functions/parter.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/cif.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/constants/half.hpp>

namespace nt2
{
  namespace ext
  {

    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::parter_, tag::cpu_,
                                (A0)(T),
                                (scalar_<integer_<A0> >)
                                (target_<scalar_<floating_<T> > > )
                              )
    {
      typedef typename T::type t_t;
      BOOST_DISPATCH_RETURNS_ARGS(2, (A0 const& n, T const& t), (A0 const& n, T const& ),
                             (nt2::rec(rif(n, T())-nt2::cif(n, T())+nt2::Half<t_t>()))
                            )
        };
  }


  meta::call<tag::parter_(const ptrdiff_t &, meta::as_<double> const &)>::type
  parter(ptrdiff_t n)
  {
    return nt2::parter(n,  meta::as_<double>());
  }
  template<class T>
  typename meta::call<tag::parter_(const ptrdiff_t &, typename meta::as_<T> const &)>::type
  parter(ptrdiff_t n)
  {
    return nt2::parter(n,  meta::as_<T>());
  }

}


#endif
