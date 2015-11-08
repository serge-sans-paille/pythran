//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_FIEDLER_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_FIEDLER_HPP_INCLUDED
#include <nt2/gallery/functions/fiedler.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/sx.hpp>
#include <nt2/include/functions/abs.hpp>


namespace nt2{ namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fiedler_, tag::cpu_,
                              (A0),
                              (scalar_<floating_<A0> > )
    )
  {
    typedef typename nt2::meta::call<nt2::tag::colon_(A0, const A0&)>::type    T1;
    typedef typename nt2::meta::call<nt2::tag::fiedler_(T1)>::type     result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& c) const
    {
      return nt2::fiedler(nt2::_(One<A0>(), c));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::fiedler_, tag::cpu_,
                              (A0),
                              ((ast_<A0, nt2::container::domain> ))
    )
  {
    typedef typename nt2::meta::call<nt2::tag::rowvect_(const A0&)>::type       T1;
    typedef typename nt2::meta::call<nt2::tag::colvect_(const A0&)>::type       T2;
    typedef typename nt2::meta::call<nt2::tag::sx_(tag::minus_,T1,T2)>::type    T3;
    typedef typename nt2::meta::call<nt2::tag::abs_(T3)>::type         result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& c) const
    {
      return nt2::abs(nt2::sx(nt2::tag::minus_(), rowvect(c), colvect(c)));
    }
  };
} }


#endif

