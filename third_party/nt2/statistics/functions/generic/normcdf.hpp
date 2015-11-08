//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_GENERIC_NORMCDF_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_GENERIC_NORMCDF_HPP_INCLUDED
#include <nt2/statistics/functions/normcdf.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/norminv.hpp>
#include <nt2/include/functions/atanpi.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/erfc.hpp>
#include <nt2/include/functions/globalall.hpp>
#include <nt2/include/functions/is_gez.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/sqrt_2o_2.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/core/container/table/table.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::normcdf0_, tag::cpu_
                            , (A0)
                            , (generic_< floating_<A0> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(1){ return Half<A0>()*nt2::erfc(-Sqrt_2o_2<A0>()*a0); }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::normcdf0_, tag::cpu_
                            , (A0)(A1)
                            , (generic_<floating_<A0> > )
                              (generic_<floating_<A1> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2){ return Half<A0>()*nt2::erfc(Sqrt_2o_2<A0>()*(a1-a0)); }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::normcdf0_, tag::cpu_
                            , (A0)(A1)(A2)
                            , (generic_< floating_<A0> >)
                              (generic_< floating_<A1> >)
                              (generic_< floating_<A2> >)
                            )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(3)
    {
      BOOST_ASSERT_MSG(nt2::globalall(nt2::is_gez(nt2::colvect(a2))), "sigma(s) must be positive");
      return Half<A0>()*nt2::erfc(Sqrt_2o_2<A0>()*((a1-a0)/a2));
    }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::normcdf_, tag::cpu_
                            , (A0)(N0)(A1)(N1)
                            , ((node_<A0, nt2::tag::normcdf_, N0, nt2::container::domain>))
                              ((node_<A1, nt2::tag::tie_ , N1, nt2::container::domain>))
                            )
  {
    typedef void                                                    result_type;
    typedef typename boost::proto::result_of::child_c<A1&,0>::type         Out0;
    typedef typename boost::proto::result_of::child_c<A0&,0>::type          In0;
    typedef typename boost::proto::result_of::child_c<A0&,1>::type          In1;
    typedef typename boost::proto::result_of::child_c<A0&,2>::type          In2;
    typedef typename A0::value_type                                  value_type;
    BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
    {
      doit(a0, a1, N0(), N1());
    }
    ////////////////////////////////////////////
    // Not enough inputs to computes all ouputs
    ////////////////////////////////////////////
    BOOST_FORCEINLINE static void doit(const A0&, A1&,
                                       boost::mpl::long_<1> const &, boost::mpl::long_<3> const & )
    {
      BOOST_ASSERT_MSG(false, "Must provide parameter variance to compute confidence bounds.");
    }
    BOOST_FORCEINLINE static void doit(const A0& a0,  A1& a1,
                                       boost::mpl::long_<2> const &, boost::mpl::long_<3> const & )
    {
      BOOST_ASSERT_MSG(false, "Must provide parameter variance to compute confidence bounds.");
      boost::proto::child_c<0>(a1) =  nt2::normcdf(boost::proto::child_c<0>(a0),
                                                   boost::proto::child_c<1>(a0));
    }
    BOOST_FORCEINLINE static void doit(const A0&,  A1&,
                                       boost::mpl::long_<3> const &, boost::mpl::long_<3> const & )
    {
      BOOST_ASSERT_MSG(false, "Must provide parameter variance to compute confidence bounds.");

    }
    ////////////////////////////////////////////
    // Not enough output to computes all ouputs
    ////////////////////////////////////////////
    template < class T >
      BOOST_FORCEINLINE static void doit(const A0& a0, A1& a1,
                                         boost::mpl::long_<4> const &, T const & )
    {
      boost::proto::child_c<0>(a1) =  nt2::normcdf(boost::proto::child_c<0>(a0),
                                                   boost::proto::child_c<1>(a0),
                                                   boost::proto::child_c<2>(a0));
    }
    template < class T >
      BOOST_FORCEINLINE static void doit(const A0& a0, A1& a1,
                                         boost::mpl::long_<5> const &, T const & )
    {
      boost::proto::child_c<0>(a1) =  nt2::normcdf(boost::proto::child_c<0>(a0),
                                                   boost::proto::child_c<1>(a0),
                                                   boost::proto::child_c<2>(a0));
    }
    ////////////////////////////////////////////
    // Regular cases
    ////////////////////////////////////////////
    BOOST_FORCEINLINE static void doit(const A0& a0, A1& a1,
                                       boost::mpl::long_<4> const &, boost::mpl::long_<3> const & )
    {
      conf_bounds(a0, a1, value_type(0.05));
    }
    BOOST_FORCEINLINE static void doit(const A0& a0, A1& a1,
                                       boost::mpl::long_<5> const &, boost::mpl::long_<3> const & )
    {
      conf_bounds(a0, a1,boost::proto::child_c<4>(a0));
    }


    BOOST_FORCEINLINE static void conf_bounds(const A0& a0, A1& a1,
                                              const value_type& alpha )
    {
      nt2::container::table<value_type> pcov =  boost::proto::child_c<3>(a0);
      const In0& x  = boost::proto::child_c<0>(a0);
      const In1& mu = boost::proto::child_c<1>(a0);
      const In2& sigma = boost::proto::child_c<2>(a0);
      BOOST_AUTO_TPL(z, (x-mu)/sigma);
      BOOST_AUTO_TPL(zvar, pcov(1,1) + (Two<value_type>()*pcov(1,2) + pcov(2,2)*z)*z);
      BOOST_ASSERT_MSG(nt2::globalall(nt2::is_gez(zvar)), "Covariance matrix must be positive");
      value_type normz = -nt2::norminv(alpha*nt2::Half<value_type>());
      BOOST_AUTO_TPL(halfwidth, normz*nt2::sqrt(zvar)/sigma);
      boost::proto::child_c<0>(a1) = Half<value_type>()*nt2::erfc(-Sqrt_2o_2<value_type>()*z);
      boost::proto::child_c<1>(a1) = Half<value_type>()*nt2::erfc(-Sqrt_2o_2<value_type>()*(z-halfwidth));
      boost::proto::child_c<2>(a1) = Half<value_type>()*nt2::erfc(-Sqrt_2o_2<value_type>()*(z+halfwidth));
    }

  };

} }

#endif
