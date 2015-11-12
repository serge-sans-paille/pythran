//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_TRIW_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_TRIW_HPP_INCLUDED
#include <nt2/gallery/functions/triw.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/tril.hpp>


namespace nt2{ namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::triw_, tag::cpu_,
                              (A0)(A1),
                              (scalar_<integer_<A0> > )
                              (scalar_<integer_<A1> > )
    )
  {
    typedef typename nt2::meta::call<nt2::tag::eye_(const A0&, const A1&)>::type        T1;
    typedef typename nt2::meta::call<nt2::tag::One(const A0&, const A1&)>::type         T2;
    typedef typename nt2::meta::call<nt2::tag::triu_(T2, size_t)>::type          T3;
    typedef typename nt2::meta::call<nt2::tag::minus_(T1, T3)>::type                    T4;
    typedef typename nt2::meta::call<nt2::tag::tril_(T4, size_t)>::type result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& m, A1 const& n) const
    {
      size_t k =  n-1;
      return  nt2::tril( nt2::eye(m,n) - nt2::triu(nt2::ones(m,n), size_t(1)), k);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::triw_, tag::cpu_,
                              (A0)(A1)(T),
                              (scalar_<integer_<A0> > )
                              (scalar_<integer_<A1> > )
                              (target_< scalar_<unspecified_<T> > > )
    )
  {
    typedef typename nt2::meta::call<nt2::tag::eye_(const A0&, const A1&, const T&)>::type       T1;
    typedef typename nt2::meta::call<nt2::tag::One(const A0&, const A1&, const T&)>::type        T2;
    typedef typename nt2::meta::call<nt2::tag::triu_(T2, size_t)>::type                   T3;
    typedef typename nt2::meta::call<nt2::tag::minus_(T1, T3)>::type                             T4;
    typedef typename nt2::meta::call<nt2::tag::tril_(T4, size_t)>::type          result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& m, A1 const& n, T const&) const
    {
      size_t k =  n-1;
      return  nt2::tril( nt2::eye(m,n,T()) - nt2::triu(nt2::ones(m,n,T()), size_t(1)), k);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::triw_, tag::cpu_,
                              (A0)(A1)(A2)(T),
                              (scalar_<integer_<A0> > )
                              (scalar_<integer_<A1> > )
                              (scalar_<floating_<A2> >)
                              (target_< scalar_<unspecified_<T> > > )
    )
  {
    typedef typename nt2::meta::call<nt2::tag::eye_(const A0&, const A1&, const T&)>::type       T1;
    typedef typename nt2::meta::call<nt2::tag::One(const A0&, const A1&, const T&)>::type        T2;
    typedef typename nt2::meta::call<nt2::tag::triu_(T2, size_t)>::type                   T3;
    typedef typename nt2::meta::call<nt2::tag::multiplies_(const A2&, T3)>::type                T3b;
    typedef typename nt2::meta::call<nt2::tag::plus_(T1, T3b)>::type                             T4;
    typedef typename nt2::meta::call<nt2::tag::tril_(T4, size_t)>::type          result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& m, A1 const& n, A2 const& alpha, T const&) const
    {
      size_t k =  n-1;
      return  nt2::tril( nt2::eye(m,n,T()) + alpha*nt2::triu(nt2::ones(m,n,T()), size_t(1)), k);
    }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::triw_, tag::cpu_,
                              (A0)(A1)(A2),
                              (scalar_<integer_<A0> > )
                              (scalar_<integer_<A1> > )
                              (scalar_<floating_<A2> >)
    )
  {
    typedef typename nt2::meta::as_<A2>                                                           T;
    typedef typename nt2::meta::call<nt2::tag::eye_(const A0&, const A1&, const T&)>::type       T1;
    typedef typename nt2::meta::call<nt2::tag::One(const A0&, const A1&, const T&)>::type        T2;
    typedef typename nt2::meta::call<nt2::tag::triu_(T2, size_t)>::type                   T3;
    typedef typename nt2::meta::call<nt2::tag::multiplies_(const A2&, T3)>::type                T3b;
    typedef typename nt2::meta::call<nt2::tag::plus_(T1, T3b)>::type                             T4;
    typedef typename nt2::meta::call<nt2::tag::tril_(T4, size_t)>::type          result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& m, A1 const& n, A2 const& alpha) const
    {
      size_t k =  n-1;
      return  nt2::tril( nt2::eye(m,n,T()) + alpha*nt2::triu(nt2::ones(m,n,T()), size_t(1)), k);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::triw_, tag::cpu_,
                              (A0)(A1)(A2)(A3),
                              (scalar_<integer_<A0> > )
                              (scalar_<integer_<A1> > )
                              (scalar_<floating_<A2> >)
                              (scalar_<integer_<A3> > )
    )
  {
    typedef typename nt2::meta::as_<A2>                                                           T;
    typedef typename nt2::meta::call<nt2::tag::eye_(const A0&, const A1&, const T&)>::type       T1;
    typedef typename nt2::meta::call<nt2::tag::One(const A0&, const A1&, const T&)>::type        T2;
    typedef typename nt2::meta::call<nt2::tag::triu_(T2, size_t)>::type                   T3;
    typedef typename nt2::meta::call<nt2::tag::multiplies_(const A2&, T3)>::type                T3b;
    typedef typename nt2::meta::call<nt2::tag::plus_(T1, T3b)>::type                             T4;
    typedef typename nt2::meta::call<nt2::tag::tril_(T4, const A3&)>::type       result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& m, A1 const& n, A2 const& alpha, A3 const& k) const
    {
      return  nt2::tril( nt2::eye(m,n,T()) + alpha*nt2::triu(nt2::ones(m,n,T()), size_t(1)), k);
    }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::triw_, tag::cpu_,
                              (A0)(A1)(A2)(A3)(T),
                              (scalar_<integer_<A0> > )
                              (scalar_<integer_<A1> > )
                              (scalar_<floating_<A2> >)
                              (scalar_<integer_<A3> > )
                              (target_< scalar_<unspecified_<T> > > )
    )
  {
    typedef typename nt2::meta::call<nt2::tag::eye_(const A0&, const A1&, const T&)>::type       T1;
    typedef typename nt2::meta::call<nt2::tag::One(const A0&, const A1&, const T&)>::type        T2;
    typedef typename nt2::meta::call<nt2::tag::triu_(T2, size_t)>::type                          T3;
    typedef typename nt2::meta::call<nt2::tag::multiplies_(const A2&, T3)>::type                T3b;
    typedef typename nt2::meta::call<nt2::tag::plus_(T1, T3b)>::type                             T4;
    typedef typename nt2::meta::call<nt2::tag::tril_(T4, const A3&)>::type              result_type;

    BOOST_FORCEINLINE result_type operator()(A0 const& m, A1 const& n, A2 const& alpha, A3 const& k) const
    {
      return  nt2::tril( nt2::eye(m,n,T()) + alpha*nt2::triu(nt2::ones(m,n,T()), size_t(1)), k);
    }
  };
} }


#endif

