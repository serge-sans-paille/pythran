//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_GCDMAT_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_GCDMAT_HPP_INCLUDED
#include <nt2/include/functions/gcdmat.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/gcd.hpp>
#include <nt2/include/functions/sx.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/cast.hpp>

namespace nt2 {namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gcdmat_, tag::cpu_,
                              (A0)(T),
                              (scalar_<integer_<A0> >)
                              (target_<scalar_<unspecified_<T> > >)
                             )
  {
    typedef typename T::type                                              t_t;
    typedef typename meta::call<tag::colon_(ptrdiff_t, ptrdiff_t)>::type   T1;
    typedef typename meta::call<tag::colvect_(T1)>::type                   T2;
    typedef typename meta::call<tag::sx_(tag::gcd_,T1,T2)>::type           T3;
    typedef typename meta::call<tag::cast_(T3, T)>::type          result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& n,T const &)
    {
       T1 c = nt2::_(ptrdiff_t(1), ptrdiff_t(n));
       return nt2::cast<t_t>(nt2::sx(tag::gcd_(), c, nt2::colvect(c)));
    }
  };
} }

#endif
