//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_LESLIE_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_LESLIE_HPP_INCLUDED
#include <nt2/gallery/functions/leslie.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/plus.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/expand.hpp>
#include <nt2/include/functions/numel.hpp>

namespace nt2 {
  namespace ext
  {

    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::leslie_, tag::cpu_,
                                (A0)(T),
                                (scalar_<integer_<A0> >)
                                (target_<scalar_<floating_<T> > > )
                              )
    {
      BOOST_DISPATCH_RETURNS_ARGS(2, (A0 const& n, T const& t),(A0 const& n, T const& ),
                             (nt2::leslie(nt2::ones(1, n, T()), nt2::ones(n-1, 1, T()))
                             )
                            )
        };
    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::leslie_, tag::cpu_,
                                (A0)(A1),
                                ((ast_<A0, nt2::container::domain >))
                                ((ast_<A1, nt2::container::domain >))

                              )
    {
      BOOST_DISPATCH_RETURNS(2, (A0 const& a0, A1 const& a1),
                             (nt2::from_diag(a1, -1)+ nt2::expand(nt2::rowvect(a0), nt2::numel(a0)))
                            )
        };

  }

  meta::call<tag::leslie_(const ptrdiff_t &, meta::as_<double> const &)>::type
  leslie(ptrdiff_t n)
  {
    return nt2::leslie(n,  meta::as_<double>());
  }
  template<class T>
  typename meta::call<tag::leslie_(const ptrdiff_t &, typename meta::as_<T> const &)>::type
  leslie(ptrdiff_t n)
  {
    return nt2::leslie(n,  meta::as_<T>());
  }


}

#endif
