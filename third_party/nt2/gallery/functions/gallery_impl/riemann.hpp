//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_RIEMANN_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_RIEMANN_HPP_INCLUDED
#include <nt2/gallery/functions/riemann.hpp>
#include <nt2/include/functions/zeros.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/whereij.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/is_eqz.hpp>
#include <nt2/include/functions/rem.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/cif.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/if_zero_else_one.hpp>

namespace nt2
{
  namespace details
  {
    struct idivj1
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

    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::riemann_, tag::cpu_,
                                (A0)(T),
                                (scalar_<integer_<A0> >)
                                (target_<scalar_<floating_<T> > > )
                              )
    {
      BOOST_DISPATCH_RETURNS_ARGS(2, (A0 const& n, T const& t), (A0 const& n, T const& ),
                             (nt2::minusone((nt2::if_zero_else_one(nt2::rem(nt2::oneplus(nt2::cif(n, T())),
                                                                            nt2::oneplus(nt2::rif(n,T())))))*
                                            nt2::oneplus(nt2::rif(n, T()))))
                            )
        };

  }

  meta::call<tag::riemann_(const ptrdiff_t &, meta::as_<double> const &)>::type
  riemann(ptrdiff_t n)
  {
    return nt2::riemann(n,  meta::as_<double>());
  }
  template<class T>
  typename meta::call<tag::riemann_(const ptrdiff_t &, typename meta::as_<T> const &)>::type
  riemann(ptrdiff_t n)
  {
    return nt2::riemann(n,  meta::as_<T>());
  }

}


#endif
