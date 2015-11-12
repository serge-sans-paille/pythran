//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_LOTKIN_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_LOTKIN_HPP_INCLUDED
#include <nt2/gallery/functions/lotkin.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/hilb.hpp>
#include <nt2/include/functions/whereij.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/sdk/meta/as_logical.hpp>

namespace nt2
{
  namespace details
  {
    struct isifirst
    {
      template < class I, class J> inline
      typename meta::as_logical<I>::type operator()(const I & i , const J&) const
      {
        return nt2::is_eqz(i);
      }
    };
  }
  namespace ext
  {

    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::lotkin_, tag::cpu_,
                                (A0)(T),
                                (scalar_<integer_<A0> >)
                                (target_<scalar_<floating_<T> > > )
                              )
    {

      BOOST_DISPATCH_RETURNS_ARGS(2, (A0 const& n, T const&t ),(A0 const& n, T const& ),
                             (nt2::whereij(nt2::details::isifirst(), nt2::ones(n, T()), nt2::hilb(n, T()))
                             )
                            )
        };
  }

  meta::call<tag::lotkin_(const ptrdiff_t &, meta::as_<double> const &)>::type
  lotkin(ptrdiff_t n)
  {
    return nt2::lotkin(n,  meta::as_<double>());
  }
  template<class T>
  typename meta::call<tag::lotkin_(const ptrdiff_t &, typename meta::as_<T> const &)>::type
  lotkin(ptrdiff_t n)
  {
    return nt2::lotkin(n,  meta::as_<T>());
  }

}


#endif
