//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_IPJFACT_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_IPJFACT_HPP_INCLUDED

#include <nt2/gallery/functions/ipjfact.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/include/functions/is_odd.hpp>
#include <nt2/include/functions/hankel.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/prod.hpp>
#include <nt2/include/functions/cumprod.hpp>
#include <nt2/include/functions/colon.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ipjfact_, tag::cpu_
                            , (A0)(A1)(T)
                            , (scalar_<integer_<A0> > )
                              (scalar_<integer_<A1> > )
                              (target_<scalar_<floating_<T> > > )
                            )
  {
    BOOST_DISPATCH_RETURNS( 3
                          , (A0 n, A1 k, T const& t)
                          , ( boost::proto::make_expr < nt2::tag::ipjfact_
                                                      , container::domain
                                                      > ( n, k
                                                        , t
                                                        , nt2::of_size(n, n)
                                                        )
                            )
                          )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ipjfact_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<integer_<A0> > )
                              (scalar_<integer_<A1> > )
                            )
  {
    BOOST_DISPATCH_RETURNS(2
                          , (A0 n, A1 k)
                          , ( boost::proto::make_expr < nt2::tag::ipjfact_
                                                      , container::domain
                                                      > ( n, k
                                                        , meta::as_<double>()
                                                        , nt2::of_size(n, n)
                                                        )
                            )
                          )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ipjfact_, tag::cpu_
                            , (A0)(T)
                            , (scalar_<integer_<A0> > )
                              (target_<scalar_<floating_<T> > > )
                            )
  {
    BOOST_DISPATCH_RETURNS( 2
                          , (A0 n, T const& t)
                          , ( boost::proto::make_expr < nt2::tag::ipjfact_
                                                      , container::domain
                                                      > ( n, 0
                                                        , t
                                                        , nt2::of_size(n, n)
                                                        )
                            )
                          )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ipjfact_, tag::cpu_
                            , (A0)
                            , (scalar_<integer_<A0> > )
                            )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 n)
                          , ( boost::proto::make_expr < nt2::tag::ipjfact_
                                                      , container::domain
                                                      > ( n, 0
                                                        , meta::as_<double>()
                                                        , nt2::of_size(n, n)
                                                        )
                            )
                          )

  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::ipjfact_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::ipjfact_, N0, nt2::container::domain>))
                              ((node_<A1, nt2::tag::tie_ , N1, nt2::container::domain>))
                            )
  {
    typedef void                                                       result_type;
    typedef typename boost::proto::result_of::child_c<A0&,2>::type        tmp_type;
    typedef typename meta::strip<tmp_type>::type                         tmp1_type;
    typedef typename boost::dispatch::meta::semantic_of<tmp1_type >::type target_t;
    typedef typename target_t::type                                        value_t;

    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      size_t n = boost::proto::child_c<0>(a0);
      size_t k = boost::proto::child_c<1>(a0);
      compute(n, k, a1, N1());
    }

  private:
    BOOST_FORCEINLINE
      static void compute(const size_t & n, const size_t & k, A1& a1,
                   boost::mpl::long_<1> const&)
    {
      matrix_compute(n, k, a1);
    }

    BOOST_FORCEINLINE
     static void compute(const size_t & n, const size_t & k, A1 & a1,
                boost::mpl::long_<2> const&)
    {
      matrix_compute(n, k, a1);
      det_compute(n, k, a1);
    }
    BOOST_FORCEINLINE
      static void matrix_compute(const size_t & n, const size_t & k, A1 & a1)
    {
      typedef typename boost::proto::result_of::child_c<A1&,0>::type       a_t;
      a_t & a = boost::proto::child_c<0>(a1);
      BOOST_AUTO_TPL(c, nt2::cumprod(nt2::_(value_t(2), value_t(n+1))));
      BOOST_AUTO_TPL(d, nt2::cumprod(nt2::_(value_t(n+1), value_t(2*n)))*c(n-1));

      a = nt2::hankel(c, d);
      if (k) a = nt2::rec(a);
    }
    BOOST_FORCEINLINE
      static void det_compute(const size_t & n, const size_t & k, A1 & a1)
    {
      value_t d = One<value_t>();
      if (!k)
      {
        for(size_t i=1;  i <= n-1; ++i)
          d *= nt2::prod(nt2::_(value_t(1), value_t(i+1)))*nt2::prod(_(value_t(1), value_t(n-i)));
        d *= nt2::prod(nt2::_(value_t(1), value_t(n+1)));
      }
      else
      {
        for(size_t i=0;  i <= n-1; ++i)
          d = d*nt2::prod(nt2::_(value_t(1), value_t(i)))/nt2::prod(nt2::_(value_t(1), value_t(n+1+i)));
        if (nt2::is_odd(n*(n-1)/2)) d = -d;
      }
      boost::proto::child_c<1>(a1) = d;
    }

  };
} }

#endif
