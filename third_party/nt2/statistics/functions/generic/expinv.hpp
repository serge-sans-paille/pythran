//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_GENERIC_EXPINV_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_GENERIC_EXPINV_HPP_INCLUDED
#include <nt2/statistics/functions/expinv.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/log1p.hpp>
#include <nt2/include/functions/all.hpp>
#include <nt2/include/functions/is_gtz.hpp>
#include <nt2/include/functions/if_allbits_else.hpp>
#include <nt2/include/functions/globalall.hpp>
#include <nt2/include/functions/norminv.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/uminus.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/core/container/table/table.hpp>

namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expinv0_, tag::cpu_
                            , (A0)
                            , (generic_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
    {
      return  nt2::if_allbits_else(nt2::is_ltz(a0), -log1p(-a0));
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expinv0_, tag::cpu_
                            , (A0)(A1)
                            , (generic_< floating_<A0> >)
                              (generic_< floating_<A1> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
    {
      BOOST_ASSERT_MSG(nt2::globalall(nt2::is_gtz(a1)), "mu parameter must be positive");
      return  a1*nt2::expinv(a0);
    }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expinv_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::expinv_, N0, nt2::container::domain>))
                              ((node_<A1, nt2::tag::tie_ , N1, nt2::container::domain>))
                            )
  {
    typedef void                                                    result_type;
    typedef typename boost::proto::result_of::child_c<A1&,0>::type         Out0;
    typedef typename boost::proto::result_of::child_c<A0&,0>::type          In0;
    typedef typename A0::value_type                                  value_type;
    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      doit(a0, a1, N0(), N1());
    }
    BOOST_FORCEINLINE static void doit(const A0&, A1&,
                                       boost::mpl::long_<1> const &, boost::mpl::long_<3> const & )
    {
      BOOST_ASSERT_MSG(false, "Must provide parameter variance to compute confidence bounds.");
    }
    BOOST_FORCEINLINE static void doit(const A0& a0,  A1& a1,
                                       boost::mpl::long_<2> const &, boost::mpl::long_<3> const & )
    {
      BOOST_ASSERT_MSG(false, "Must provide parameter variance to compute confidence bounds.");
      boost::proto::child_c<0>(a1) =  nt2::expinv(boost::proto::child_c<0>(a0),
                                                  boost::proto::child_c<1>(a0));
    }
    template < class T >
      BOOST_FORCEINLINE static void doit(const A0& a0, A1& a1,
                                         boost::mpl::long_<3> const &, T const & )
    {
      boost::proto::child_c<0>(a1) =  nt2::expinv(boost::proto::child_c<0>(a0));
    }
    template < class T >
      BOOST_FORCEINLINE static void doit(const A0& a0, A1& a1,
                                         boost::mpl::long_<4> const &, T const & )
    {
      boost::proto::child_c<0>(a1) =  nt2::expinv(boost::proto::child_c<0>(a0),
                                                  boost::proto::child_c<1>(a0));
    }
    BOOST_FORCEINLINE static void doit(const A0& a0, A1& a1,
                                       boost::mpl::long_<3> const &, boost::mpl::long_<3> const & )
    {
      conf_bounds(a0, a1, value_type(0.05));
    }
    BOOST_FORCEINLINE static void doit(const A0& a0, A1& a1,
                                       boost::mpl::long_<4> const &, boost::mpl::long_<3> const & )
    {
      conf_bounds(a0, a1, boost::proto::child_c<3>(a0));
    }
    BOOST_FORCEINLINE static void conf_bounds(const A0& a0, A1& a1,
                                              const value_type& alpha )
    {
      typedef typename boost::proto::result_of::child_c<A0&,1>::type          In1;
      value_type pcov =  boost::proto::child_c<2>(a0);
      BOOST_ASSERT_MSG(pcov >= Zero<value_type>(), "Variance pcov must be non-negative");
      const In0& q  = boost::proto::child_c<0>(a0);
      const In1& mu = boost::proto::child_c<1>(a0);
      BOOST_ASSERT_MSG(nt2::globalall(nt2::is_gtz(mu)), "mu parameter must be positive");
      BOOST_AUTO_TPL(x, (-nt2::log1p(-q)*mu));
      //      nt2::container::table<value_type> logx = nt2::log(q*mu);
      value_type normz = -nt2::norminv(alpha*nt2::Half<value_type>());
      BOOST_AUTO_TPL(halfwidth, normz * nt2::sqrt(pcov/nt2::sqr(mu)));
      BOOST_AUTO_TPL(exp_halfwidth, exp(halfwidth));
      boost::proto::child_c<0>(a1) = x;
      boost::proto::child_c<2>(a1) = x*exp_halfwidth;
      boost::proto::child_c<1>(a1) = x/exp_halfwidth;
    }
  };


} }

#endif
