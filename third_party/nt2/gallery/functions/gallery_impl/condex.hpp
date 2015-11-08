//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_CONDEX_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_CONDEX_HPP_INCLUDED

#include <nt2/gallery/functions/condex.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/core/container/dsl.hpp>

#include <nt2/include/constants/four.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/expand.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/cospi.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/transpose.hpp>
#include <nt2/include/functions/minusone.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/orth.hpp>
#include <nt2/include/functions/triw.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::condex_, tag::cpu_
                            , (A0)(A1)
                            , (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::condex_
                                          , container::domain
                                          , A0 const&, A1 const&
                                          , double, _2D
                                          >::type             result_type;

    BOOST_FORCEINLINE  result_type operator()(A0 const& a0, A1 const& a1) const
    {
      return  boost::proto::make_expr < nt2::tag::condex_
                                      , container::domain
                                      > ( boost::cref(a0)
                                        , boost::cref(a1)
                                        , 100.0, _2D(a0,a0)
                                        );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::condex_, tag::cpu_
                            , (A0)(A1)(T)
                            , (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                              (target_< scalar_< floating_<T> > >)
                            )
  {
    typedef typename T::type value_type;
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::condex_
                                          , container::domain
                                          , A0 const&
                                          , A1 const&
                                          , value_type
                                          , _2D
                                          >::type             result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0, A1 const& a1, T const&) const
    {
      return  boost::proto::make_expr < nt2::tag::condex_
                                      , container::domain
                                      > ( boost::cref(a0)
                                        , boost::cref(a1)
                                        , value_type(100)
                                        , _2D(a0,a0)
                                        );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::condex_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (scalar_< integer_<A0> > )
                              (scalar_< integer_<A1> > )
                              (scalar_< floating_<A2> >)
                            )
  {
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::condex_
                                          , container::domain
                                          , A0 const&
                                          , A1 const&
                                          , A2 const&
                                          , _2D
                                          >::type             result_type;

    BOOST_FORCEINLINE
    result_type operator()(A0 const& a0, A1 const& a1, A2  const& a2) const
    {
      return  boost::proto::make_expr < nt2::tag::condex_
                                      , container::domain
                                      > ( boost::cref(a0)
                                        , boost::cref(a1)
                                        , boost::cref(a2)
                                        , _2D(a0,a0)
                                        );
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::condex_, tag::cpu_
                            , (A0)(A1)(A2)(T)
                            , (scalar_<integer_<A0> >)
                              (scalar_<integer_<A1> >)
                              (scalar_< floating_<A2> >)
                              (target_< scalar_< floating_<T> > >)
                            )
  {
    typedef typename T::type value_type;
    typedef typename  boost::proto::
                      result_of::make_expr< nt2::tag::condex_
                                          , container::domain
                                          , A0 const&
                                          , A1 const&
                                          , value_type
                                          , _2D
                                          >::type             result_type;

    BOOST_FORCEINLINE result_type
    operator()(A0 const& a0, A1 const& a1, A2 const& a2, T const&) const
    {
      return  boost::proto::make_expr < nt2::tag::condex_
                                      , container::domain
                                      > ( boost::cref(a0)
                                        , boost::cref(a1)
                                        , value_type(a2)
                                        , _2D(a0,a0)
                                        );
    }
  };

  //////////////////////////////////////////////////////////////////////////////
  //     condex
  //////////////////////////////////////////////////////////////////////////////

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                              , (A0)(A1)(N)
                              , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::condex_,N,nt2::container::domain>))
    )
  {
    typedef A0&                                                     result_type;
    typedef typename A0::value_type                                         v_t;
    result_type operator()(A0& out, const A1& in) const
    {
      size_t n =  boost::proto::child_c<0>(in);
      size_t k =  boost::proto::child_c<1>(in);
      k =  nt2::min(k, Four<size_t>());
      size_t theta =  boost::proto::child_c<2>(in);
      if (n == 0)
      {
        out.resize(of_size(0, 1));
        return out;
      }
      out.resize(of_size(n, n));
      compute(out, n, k, theta);
      return out;
    }
  private :
    static void compute(A0& out, size_t n,  size_t k, v_t theta)
    {
      if (k == 1)   // Cline and Rew (1983), Example B.
      {
        out = nt2::trans(cons<v_t>(nt2::of_size(4, 4),
                                   1,  -1,  -2*theta,           0,
                                   0,   1,     theta,      -theta,
                                   0,   1,   1+theta,  -(theta+1),
                                   0,   0,         0,       theta
                           ));

      }
      else if (k == 2)   // Cline and Rew (1983), Example C.
      {
        out = nt2::trans(cons<v_t>(nt2::of_size(3, 3),
                           1,   1-2/nt2::sqr(theta),        -2,
                           0,       nt2::rec(theta),  -1/theta,
                           0,                     0,         1
                           ));
      }
      else if (k == 3)    // Cline and Rew (1983), Example D.
      {
        out = nt2::trans(nt2::triw(n,n,v_t(-1)));
        out(n,n) = -1;
      }
      else //if k == 4    Higham (1988), p. 390; Higham (1996), p. 296.
      {
        nt2::container::table<v_t> x = nt2::ones(n,3,meta::as_<v_t>());  //  First col is e
        x(nt2::_(2, n),2) = nt2::zeros(n-1,1, meta::as_<v_t>()); //  Second col is e(1)
        //Third col is special vector b.
        v_t nm1 =  nt2::minusone(n);
        BOOST_AUTO_TPL(z, nt2::_(nt2::Zero<v_t>(), nm1));
        x(nt2::_, 3) = nt2::colvect(nt2::cospi(z)*(nt2::oneplus(z/nm1)));
        nt2::container::table<v_t> q = nt2::orth(x);  //  q*q' is now the orthogonal projector onto span(e(1),e,b)).
        nt2::container::table<v_t> p = nt2::eye(n,meta::as_<v_t>()) - nt2::mtimes(q, nt2::trans(q));
        out = nt2::eye(n,meta::as_<v_t>()) + theta*p;
      }
      // Pad out with identity as necessary.
      size_t m = length(out);
      if (m < n)
      {
        nt2::table<v_t> out1 = nt2::expand(out, n, n); out =  out1;  //ALIASING
        for(size_t i=m+1; i <= n; ++i) out(i,i) = nt2::One<v_t>();
      }
    }

  };

} }

#endif
