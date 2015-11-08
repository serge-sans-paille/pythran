//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_FORSYTHE_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_FORSYTHE_HPP_INCLUDED
#include <nt2/gallery/functions/forsythe.hpp>
#include <nt2/include/functions/jordbloc.hpp>
#include <nt2/include/functions/deltaf.hpp>
#include <nt2/include/functions/ones.hpp>

namespace nt2 {namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::forsythe_, tag::cpu_,
                              (A0)(T),
                              (scalar_<integer_<A0> >)
                              (target_<scalar_<floating_<T> > >)
                            )
  {
    typedef typename T::type t_t;
    typedef typename nt2::meta::call<nt2::tag::forsythe_(const A0&, const t_t&, const t_t&, T)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& n, T const &)
    {
      return nt2::forsythe(n, nt2::Sqrteps<t_t>(), nt2::Zero<t_t>(), T());
    }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::forsythe_, tag::cpu_,
                              (A0)(A1)(T),
                              (scalar_<integer_<A0> >)
                              (scalar_<unspecified_<A1> >)
                              (target_<scalar_<floating_<T> > >)
                            )
  {
    typedef typename T::type t_t;
    typedef typename nt2::meta::call<nt2::tag::forsythe_(const A0&, const t_t&, const t_t&, T)>::type result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& n, A1 const& alpha, T const &)
    {
      return nt2::forsythe(n, t_t(alpha), nt2::Zero<t_t>(), T());
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::forsythe_, tag::cpu_,
                              (A0)(A1)(A2)(T),
                              (scalar_<integer_<A0> >)
                              (scalar_<unspecified_<A1> >)
                              (scalar_<unspecified_<A2> >)
                              (target_<scalar_<floating_<T> > >)
                            )
  {
    typedef typename T::type t_t;
    typedef typename meta::call<tag::jordbloc_(A0 const&, t_t)>::type           T1;
    typedef typename meta::call<tag::deltaf_(A0 const&, A0 const&, ptrdiff_t, T)>::type    T3;
    typedef typename meta::call<tag::multiplies_(t_t, T3) >::type               T5;
    typedef typename meta::call<tag::plus_(T1, T5)>::type              result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& n, A1 const& alpha, A2 const& l, T const &)
    {
      return nt2::jordbloc(n, t_t(l))+t_t(alpha)*nt2::deltaf(n, 1, n, n, T());
    }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::forsythe_, tag::cpu_,
                              (A0),
                              (scalar_<integer_<A0> >)
                            )
  {
    typedef double t_t;
    BOOST_DISPATCH_RETURNS(1, (A0 const& n),
                           (nt2::forsythe(n, nt2::meta::as_<double>()))
                          )
      };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::forsythe_, tag::cpu_,
                              (A0)(A1),
                              (scalar_<integer_<A0> >)
                              (scalar_<arithmetic_<A1> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& n, A1 const&alpha),
                           (nt2::forsythe(n, alpha, nt2::Zero<A1>(), nt2::meta::as_<A1>()))
                          )
      };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::forsythe_, tag::cpu_,
                              (A0)(A1)(A2),
                              (scalar_<integer_<A0> >)
                              (scalar_<arithmetic_<A1> >)
                              (scalar_<arithmetic_<A2> >)
                            )
  {
    BOOST_DISPATCH_RETURNS(3, (A0 const& n, A1 const& alpha, A2 const& l),
                           (nt2::forsythe(n, alpha, l, nt2::meta::as_<A1>()))
                          )
  };

} }

#endif
