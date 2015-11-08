//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_HILB_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_HILB_HPP_INCLUDED
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/minusone.hpp>
#include <nt2/include/functions/rif.hpp>
#include <nt2/include/functions/cif.hpp>

namespace nt2{ namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::hilb_, tag::cpu_,
                              (A0)(T),
                              (scalar_<integer_<A0> > )
                              (target_<scalar_<floating_<T> > >)
    )
  {
    typedef typename nt2::meta::call<nt2::tag::rif_(const A0&, T)>::type        r_t;
    typedef typename nt2::meta::call<nt2::tag::cif_(const A0&, T)>::type        c_t;
    typedef typename nt2::meta::call<nt2::tag::plus_(r_t, c_t)>::type            T0;
    typedef typename nt2::meta::call<nt2::tag::minusone_(T0)>::type              T1;
    typedef typename nt2::meta::call<nt2::tag::rec_(T1)>::type          result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& n,
                                             T const&) const
    {
      return nt2::rec(nt2::minusone(nt2::rif(n, T())+nt2::cif(n, T())));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::hilb_, tag::cpu_,
                              (A0),
                              (scalar_<integer_<A0> > )
    )
  {
    typedef typename nt2::meta::call<nt2::tag::hilb_(const A0&, nt2::meta::as_<double>)>::type           result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& a0) const
    {
      return hilb(a0, nt2::meta::as_<double>());
    }
  };

} }


#endif

