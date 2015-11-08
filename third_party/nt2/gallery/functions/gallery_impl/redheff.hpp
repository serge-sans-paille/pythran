//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_REDHEFF_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_REDHEFF_HPP_INCLUDED
#include <nt2/gallery/functions/redheff.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/whereij.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/rem.hpp>
#include <nt2/include/functions/logical_or.hpp>

namespace nt2
{
  namespace details
  {
    struct idivj
    {
      template < class I, class J> inline
      typename meta::as_logical<I>::type operator()(const I & i , const J& j) const
      {
        return nt2::logical_or(nt2::is_eqz(nt2::rem(nt2::oneplus(j), nt2::oneplus(i))), nt2::is_eqz(j));
      }
    };
  }

  namespace ext
  {

    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::redheff_, tag::cpu_,
                                (A0)(T),
                                (scalar_<integer_<A0> >)
                                (target_<scalar_<floating_<T> > > )
                              )
    {
      BOOST_DISPATCH_RETURNS_ARGS(2, (A0 const& n, T const& t), (A0 const& n, T const& ),
                             (nt2::whereij(details::idivj(), nt2::ones(n, T()), nt2::zeros(n, T())))
                            )
        };

  }


  meta::call<tag::redheff_(const ptrdiff_t &, meta::as_<double> const &)>::type
  redheff(ptrdiff_t n)
  {
    return nt2::redheff(n,  meta::as_<double>());
  }
  template<class T>
  typename meta::call<tag::redheff_(const ptrdiff_t &, typename meta::as_<T> const &)>::type
  redheff(ptrdiff_t n)
  {
    return nt2::redheff(n,  meta::as_<T>());
  }

}


#endif
