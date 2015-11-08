//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_MINIJ_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_MINIJ_HPP_INCLUDED
#include <nt2/gallery/functions/minij.hpp>
#include <nt2/include/functions/min.hpp>
#include <nt2/include/functions/cif.hpp>
#include <nt2/include/functions/rif.hpp>

namespace nt2 {namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::minij_, tag::cpu_,
                              (A0)(T),
                              (scalar_<integer_<A0> >)
                              (target_<scalar_<floating_<T> > >)
                             )
  {
    typedef typename T::type t_t;
    typedef typename meta::call<tag::minij_(const A0&, const A0&, T)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& n,T const &)
    {
      return minij(n, n, T());
    }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::minij_, tag::cpu_,
                              (A0)(A1)(T),
                              (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                              (target_<scalar_<floating_<T> > >)
                             )
  {
    typedef typename meta::call<tag::rif_(A0 const&, A1 const&, T)>::type T1;
    typedef typename meta::call<tag::cif_(A0 const&, A1 const&, T)>::type T2;
    typedef typename meta::call<tag::min_(T1, T2)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& m, A1 const& n, T const &)
    {
      return nt2::min(nt2::rif(m, n, T()), nt2::cif(m, n, T()));
    }
  };

} }

#endif
