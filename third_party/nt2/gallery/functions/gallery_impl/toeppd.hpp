//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Patoeppd Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_TOEPPD_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_TOEPPD_HPP_INCLUDED
#include <nt2/gallery/functions/toeppd.hpp>
#include <nt2/include/functions/cauchy.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/cif.hpp>
#include <nt2/include/functions/minus.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/functions/reshape.hpp>
#include <nt2/include/functions/sx.hpp>
#include <nt2/include/functions/cospi.hpp>
#include <nt2/include/functions/sum.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/rand.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/one.hpp>

namespace nt2
{
  namespace ext
  {
    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::toeppd_, tag::cpu_,
                                (A0)(A1)(A2),
                                (scalar_<integer_<A0> >)
                                ((ast_<A1, nt2::container::domain>))
                                ((ast_<A2, nt2::container::domain>))
                              )
    {
      typedef typename A1::value_type                                                   v_t;
      typedef typename nt2::meta::as_<v_t>                                                T;
      typedef typename meta::call<tag::rif_(size_t, size_t, size_t, T)>::type            T1;
      typedef typename meta::call<tag::cif_(size_t, size_t, size_t, T)>::type            T2;
      typedef typename meta::call<tag::minus_(T1, T2)>::type                             T3;
      typedef typename meta::call<tag::multiplies_(v_t, T3)>::type                        E;
      typedef typename meta::call<tag::reshape_(A1 const&,size_t,size_t,size_t)>::type   WW;
      typedef typename meta::call<tag::reshape_(A2 const&,size_t,size_t,size_t)>::type   TT;
      typedef typename meta::call<tag::sx_(tag::multiplies_,E,TT)>::type                 T4;
      typedef typename meta::call<tag::cospi_(T4)>::type                                 T5;
      typedef typename meta::call<tag::sx_(tag::multiplies_,WW,T5)>::type                T6;
      typedef typename meta::call<tag::sum_(T6, size_t)>::type                  result_type;


      BOOST_FORCEINLINE result_type operator()(A0 const& nn,
                                               A1 const& w,
                                               A2 const& theta) const
      {
        size_t m = numel(w);
        size_t n = nn;
        size_t one = nt2::One<size_t>();
        BOOST_AUTO_TPL(e, nt2::Two<v_t>()*(nt2::rif(n, n, m, T())-nt2::cif(n, n, m, T())));
        BOOST_AUTO_TPL(ww, nt2::reshape(w,one,one,m));
        BOOST_AUTO_TPL(tt, nt2::reshape(theta,one,one,m));
        return nt2::sum(nt2::sx(tag::multiplies_(),ww, nt2::cospi(nt2::sx(tag::multiplies_(),e,tt))),size_t(3));
      }
    };

    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::toeppd_, tag::cpu_,
                                (A0)(A1)(T),
                                (scalar_<integer_<A0> >)
                                (scalar_<integer_<A1> >)
                                (target_<scalar_<floating_<T> > >)
                              )
    {
      BOOST_DISPATCH_RETURNS_ARGS(3, (A0 const& n, A1 const& m, T const& t), (A0 const& n, A1 const& m, T const& ),
                             (nt2::toeppd(n, nt2::rand(m, 1, T()), nt2::rand(m, 1, T())))
                            )

        };

  }

  nt2::meta::call<nt2::tag::toeppd_(const ptrdiff_t &, const ptrdiff_t &, nt2::meta::as_<double> const &)>::type
  toeppd(ptrdiff_t n)
  {
    return nt2::toeppd(n, n, nt2::meta::as_<double>());
  }
  nt2::meta::call<nt2::tag::toeppd_(const ptrdiff_t &, const ptrdiff_t &, nt2::meta::as_<double> const &)>::type
  toeppd(ptrdiff_t n, ptrdiff_t m)
  {
    return nt2::toeppd(n, m, nt2::meta::as_<double>());
  }
  template<class T>
  typename nt2::meta::call<nt2::tag::toeppd_(const ptrdiff_t &, const ptrdiff_t &, nt2::meta::as_<T> const &)>::type
  toeppd(ptrdiff_t n)
  {
    return nt2::toeppd(n, n, nt2::meta::as_<T>());
  }
  template<class T>
  typename nt2::meta::call<nt2::tag::toeppd_(const ptrdiff_t &, const ptrdiff_t &, typename nt2::meta::as_<T> const &)>::type
  toeppd(ptrdiff_t n, ptrdiff_t m)
  {
    return nt2::toeppd(n, m, nt2::meta::as_<T>());
  }

}



#endif
