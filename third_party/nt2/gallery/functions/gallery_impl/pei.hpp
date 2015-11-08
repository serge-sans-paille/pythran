//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_PEI_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_PEI_HPP_INCLUDED
#include <nt2/gallery/functions/pei.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/multiplies.hpp>
#include <nt2/include/constants/one.hpp>

namespace nt2
{
  namespace ext
  {

    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pei_, tag::cpu_,
                                (A0)(T),
                                (scalar_<integer_<A0> >)
                                (target_<scalar_<floating_<T> > > )
                              )
    {
      typedef typename T::type t_t;
      BOOST_DISPATCH_RETURNS_ARGS(2, (A0 const& n, T const& t), (A0 const& n, T const& ),
                             (nt2::pei(n, nt2::One<t_t>()))
                            )
        };

    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::pei_, tag::cpu_,
                                (A0)(A1),
                                (scalar_<integer_<A0> >)
                                (scalar_<floating_<A1> >)

                              )
    {
      BOOST_DISPATCH_RETURNS(2, (A0 const& n, A1 const& alpha),
                             (alpha*nt2::eye(n,nt2::meta::as_<A1>()) + nt2::ones(n,nt2::meta::as_<A1>()))
                            )
        };

  }


  meta::call<tag::pei_(const ptrdiff_t &, meta::as_<double> const &)>::type
  pei(ptrdiff_t n)
  {
    return nt2::pei(n,  meta::as_<double>());
  }
  template<class T>
  typename meta::call<tag::pei_(const ptrdiff_t &, typename meta::as_<T> const &)>::type
  pei(ptrdiff_t n)
  {
    return nt2::pei(n,  meta::as_<T>());
  }

}


#endif
