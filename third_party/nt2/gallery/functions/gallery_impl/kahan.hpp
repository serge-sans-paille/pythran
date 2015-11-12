//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_KAHAN_HPP_INCLUDED
#define NT2_GALLERY_FUNCTIONS_GALLERY_IMPL_KAHAN_HPP_INCLUDED

#include <nt2/gallery/functions/kahan.hpp>
#include <nt2/include/functions/sincos.hpp>
#include <nt2/include/functions/expand.hpp>
#include <nt2/include/functions/from_diag.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/eye.hpp>
#include <nt2/include/functions/ones.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/cumprod.hpp>
#include <nt2/include/functions/repnum.hpp>
#include <nt2/include/functions/horzcat.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/constants/eps.hpp>
#include <nt2/core/container/dsl.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::kahan_, tag::cpu_,
                              (A0),
                              (unspecified_<A0>)
                            )
  {
    BOOST_DISPATCH_RETURNS(1, (A0 const& n),
                           (nt2::kahan(n, 1.2, 1.0e3, nt2::meta::as_<double>())
                           ))
      };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::kahan_, tag::cpu_,
                              (A0)(T),
                              (unspecified_<A0>)
                              (target_< scalar_< unspecified_<T> > >)
    )
  {
    typedef typename T::type value_t;
    BOOST_DISPATCH_RETURNS_ARGS(2, (A0 const& n, T  const& t),(A0 const& n, T  const& ),
                           (nt2::kahan(n, 1.2, 1.0e3, T())
                           ))
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::kahan_, tag::cpu_,
                              (A0)(A1),
                              (unspecified_<A0>)
                              (scalar_<floating_<A1> >)
    )
  {
    BOOST_DISPATCH_RETURNS(2, (A0 const& n, A1 const& theta),
                           (nt2::kahan(n, theta, A1(1.0e3), nt2::meta::as_<A1>())
                           ))
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::kahan_, tag::cpu_,
                              (A0)(A1)(A2),
                              (unspecified_<A0>)
                              (scalar_<floating_<A1> >)
                              (scalar_<floating_<A2> >)
    )
  {
    BOOST_DISPATCH_RETURNS(3, (A0 const& siz, A1 const& theta, A2 const& pert),
                           (nt2::kahan(siz, theta, A1(pert), nt2::meta::as_<A1>())
                           ))
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::kahan_, tag::cpu_,
                              (A0)(A1)(A2)(T),
                              (scalar_<integer_<A0> >)
                              (scalar_<floating_<A1> >)
                              (scalar_<floating_<A2> >)
                              (target_< scalar_< unspecified_<T> > >)
                            )
  {
    typedef typename T::type value_t;
    BOOST_DISPATCH_RETURNS_ARGS ( 4
                                , ( A0 const& n   , A1 const& theta
                                  , A2 const& pert, T  const& t
                                  )
                                , ( A0 const& n   , A1 const& theta
                                  , A2 const& pert, T  const&
                                  )
                                , (boost::proto::make_expr< nt2::tag::kahan_
                                                          , container::domain
                                                          >
                                                          ( value_t(theta)
                                                          , value_t(pert)
                                                          , of_size ( size_t(n)
                                                                    , size_t(n)
                                                                    )
                                                          )
                                  )
                                )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::kahan_, tag::cpu_,
                              (A0)(A1)(A2)(T),
                              (unspecified_<A0>)
                              (scalar_<floating_<A1> >)
                              (scalar_<floating_<A2> >)
                              (target_< scalar_< unspecified_<T> > >)
                            )
  {
    typedef typename T::type value_t;
    BOOST_DISPATCH_RETURNS_ARGS ( 4
                                , ( A0 const& n, A1 const& theta
                                  , A2 const& pert, T  const& t
                                  )
                                , ( A0 const& n   , A1 const& theta
                                  , A2 const& pert, T  const&
                                  )
                                ,(boost::proto::make_expr < nt2::tag::kahan_
                                                          , container::domain
                                                          >
                                                          ( value_t(theta)
                                                          , value_t(pert)
                                                          , n
                                                          )
                                  )
                                )
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::run_assign_, tag::cpu_
                              , (A0)(A1)(N)
                              , ((ast_<A0, nt2::container::domain>))
                              ((node_<A1,nt2::tag::kahan_,N,nt2::container::domain>))
    )
  {
    typedef A0&                                                         result_type;
    typedef typename  boost::proto::result_of::child_c<A1&,0>::type        tmp_type;
    typedef typename  meta::strip<tmp_type>::type                         tmp1_type;
    typedef typename  tmp1_type::value_type                                 value_t;
    result_type operator()(A0& out, const A1& in) const
    {
      BOOST_AUTO_TPL(siz,boost::proto::value( boost::proto::child_c<2>(in)));
      value_t theta =  boost::proto::child_c<0>(in);
      value_t pert  =  boost::proto::child_c<1>(in);
      size_t m = siz[0];
      size_t n = siz[1];
      out.resize(siz);
      value_t s, c;
      nt2::sincos(theta, s, c);
      BOOST_AUTO_TPL(z1, nt2::eye(n, nt2::meta::as_<value_t>()) - c*nt2::triu(nt2::ones(n,n,nt2::meta::as_<value_t>()), 1));
      BOOST_AUTO_TPL(z2, mtimes(nt2::from_diag(nt2::cath(nt2::One<value_t>(), nt2::cumprod(nt2::repnum(s,1, n-1)))), z1));
      BOOST_AUTO_TPL(z3, z2+pert*nt2::Eps<value_t>()*nt2::from_diag(nt2::_(value_t(n), value_t(-1), value_t(1))));
      out = expand(z3, m, n);
      return out;
    }
  };
} }

#endif
