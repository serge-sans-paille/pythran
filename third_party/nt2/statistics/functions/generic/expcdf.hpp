//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_GENERIC_EXPCDF_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_GENERIC_EXPCDF_HPP_INCLUDED
#include <nt2/statistics/functions/expcdf.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/norminv.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/expm1.hpp>
#include <nt2/include/functions/is_nan.hpp>
#include <nt2/include/functions/if_zero_else.hpp>
#include <nt2/include/functions/is_ltz.hpp>
#include <nt2/include/functions/isscalar.hpp>
#include <nt2/include/functions/globalall.hpp>
#include <nt2/include/functions/havesamesize.hpp>
#include <nt2/include/functions/assign.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/core/container/table/table.hpp>
namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expcdf0_, tag::cpu_
                              , (A0)
                              , (generic_< floating_<A0> >)
                              )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1)
      {
        return -nt2::expm1(-nt2::if_zero_else(nt2::is_ltz(a0), a0));
      }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expcdf0_, tag::cpu_
                              , (A0)(A1)
                              , (generic_< floating_<A0> >)
                              (generic_< floating_<A1> >)
                              )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2)
      {
        BOOST_ASSERT_MSG(nt2::globalall(nt2::is_gtz(a1)), "mu parameter must be positive");
        return nt2::expcdf(a0/a1);
      }
   };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::expcdf_, tag::cpu_
                              , (A0)(N0)(A1)(N1)
                              , ((node_<A0, nt2::tag::expcdf_, N0, nt2::container::domain>))
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
    BOOST_FORCEINLINE static void doit(const A0& , A1& ,
                                       boost::mpl::long_<1> const &, boost::mpl::long_<3> const & )
    {
      BOOST_ASSERT_MSG(false, "Must provide parameter variance to compute confidence bounds.");
    }
    BOOST_FORCEINLINE static void doit(const A0& a0,  A1& a1,
                                       boost::mpl::long_<2> const &, boost::mpl::long_<3> const & )
    {
      BOOST_ASSERT_MSG(false, "Must provide parameter variance to compute confidence bounds.");
      boost::proto::child_c<0>(a1) =  nt2::expcdf(boost::proto::child_c<0>(a0),
                                                   boost::proto::child_c<1>(a0));
    }
    template < class T >
    BOOST_FORCEINLINE static void doit(const A0& a0, A1& a1,
                                       boost::mpl::long_<3> const &, T const & )
    {
      boost::proto::child_c<0>(a1) =  nt2::expcdf(boost::proto::child_c<0>(a0));
    }
    template < class T >
    BOOST_FORCEINLINE static void doit(const A0& a0, A1& a1,
                                       boost::mpl::long_<4> const &, T const & )
    {
      boost::proto::child_c<0>(a1) =  nt2::expcdf(boost::proto::child_c<0>(a0),
                                                  boost::proto::child_c<1>(a0));
    }
    BOOST_FORCEINLINE static void doit(const A0& a0, A1& a1,
                                       boost::mpl::long_<3> const &, boost::mpl::long_<3> const & )
    {
      BOOST_ASSERT_MSG(boost::proto::child_c<2>(a0)>= Zero<value_type>(), "Variance pcov must be non-negative");
      value_type normz = -nt2::norminv(static_cast<value_type>(0.025));
      conf_bounds(a0, a1, normz);
    }
    BOOST_FORCEINLINE static void doit(const A0& a0, A1& a1,
                                       boost::mpl::long_<4> const &, boost::mpl::long_<3> const & )
    {
      value_type pcov =  boost::proto::child_c<2>(a0);
      BOOST_ASSERT_MSG(pcov >= Zero<value_type>(), "Variance pcov must be non-negative");
      value_type normz = -nt2::norminv(boost::proto::child_c<3>(a0)*nt2::Half<value_type>());
      conf_bounds(a0, a1, pcov, normz);
    }
    BOOST_FORCEINLINE static void conf_bounds(const A0& a0, A1& a1,
                                              const value_type& pcov,
                                              const value_type& normz )
    {
      typedef typename boost::proto::result_of::child_c<A0&,1>::type          In1;
      //      value_type pcov =  boost::proto::child_c<2>(a0);
      //      BOOST_ASSERT_MSG(pcov >= Zero<value_type>(), "Variance pcov must be non-negative");
      const In0& x  = boost::proto::child_c<0>(a0);
      const In1& mu = boost::proto::child_c<1>(a0);
      BOOST_ASSERT_MSG(nt2::globalall(is_gtz(mu)), "mu parameter must be positive");
      BOOST_AUTO_TPL(z, nt2::if_zero_else(nt2::is_ltz(x), (x/mu)));
      //      BOOST_AUTO_TPL(logz, nt2::log(x/mu));
      //      value_type normz = -nt2::norminv(alpha*nt2::Half<value_type>());
      BOOST_AUTO_TPL(halfwidth, normz * nt2::sqrt(pcov/nt2::sqr(mu)));
      BOOST_AUTO_TPL(exp_halfwidth, exp(halfwidth));

      boost::proto::child_c<0>(a1) = -nt2::expm1(-z);
      boost::proto::child_c<2>(a1) = -nt2::expm1(-z*exp_halfwidth);
      boost::proto::child_c<1>(a1) = -nt2::expm1(-z/exp_halfwidth);

//       boost::proto::child_c<1>(a1) = if_zero_else(nt2::is_nan(logz), oneminus(nt2::exp(-nt2::exp(logz-halfwidth))));
//       boost::proto::child_c<2>(a1) = if_zero_else(nt2::is_nan(logz), oneminus(nt2::exp(-nt2::exp(logz+halfwidth))));
    }

  };

} }

#endif
