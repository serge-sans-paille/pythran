//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_RIS_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_RIS_HPP_INCLUDED
#include <nt2/gallery/functions/ris.hpp>
#include <nt2/include/functions/cauchy.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/fma.hpp>
#include <nt2/include/constants/mtwo.hpp>

namespace nt2
{

  namespace ext
  {

    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ris_, tag::cpu_,
                                (A0)(T),
                                (scalar_<integer_<A0> >)
                                (target_<scalar_<floating_<T> > > )
                              )
    {
      typedef typename T::type t_t;
      BOOST_DISPATCH_RETURNS_ARGS(2, (A0 const& n, T const& t),(A0 const& n, T const& ),
                             (nt2::cauchy(nt2::fma(nt2::Mtwo<t_t>(), nt2::_(t_t(1), t_t(n)),(t_t(n+1.5)))))
                            )
        };

  }

  meta::call<tag::ris_(const ptrdiff_t &, meta::as_<double> const &)>::type
  ris(ptrdiff_t n)
  {
    return nt2::ris(n,  meta::as_<double>());
  }
  template<class T>
  typename meta::call<tag::ris_(const ptrdiff_t &, typename meta::as_<T> const &)>::type
  ris(ptrdiff_t n)
  {
    return nt2::ris(n,  meta::as_<T>());
  }

}


#endif
