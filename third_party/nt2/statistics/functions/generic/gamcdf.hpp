//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_GENERIC_GAMCDF_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_GENERIC_GAMCDF_HPP_INCLUDED
#include <nt2/statistics/functions/gamcdf.hpp>
#include <nt2/include/functions/gammainc.hpp>
#include <nt2/include/functions/dgammainc.hpp>
#include <nt2/include/functions/gammaln.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/log.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/rec.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/norminv.hpp>
#include <nt2/include/functions/globalall.hpp>
#include <nt2/include/functions/is_gez.hpp>
#include <nt2/include/functions/logical_and.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/functions/tie.hpp>
#include <nt2/core/container/table/table.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gamcdf0_, tag::cpu_
                              , (A0)(A1)
                              , (generic_< floating_<A0> >)
                              (generic_< floating_<A1> >)
                              )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(2){ return nt2::gammainc(a1, a0); }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gamcdf0_, tag::cpu_
                              , (A0)(A1)(A2)
                              , (generic_< floating_<A0> >)
                              (generic_< floating_<A1> >)
                              (generic_< floating_<A2> >)
                              )
  {
    typedef A0 result_type;
    NT2_FUNCTOR_CALL(3)
      {
        return nt2::gammainc(a1, a0/a2);
      }
  };


  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::gamcdf_, tag::cpu_
                              , (A0)(N0)(A1)(N1)
                              , ((node_<A0, nt2::tag::gamcdf_, N0, nt2::container::domain>))
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
      boost::proto::child_c<0>(a1) =  nt2::gamcdf(boost::proto::child_c<0>(a0),
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
      boost::proto::child_c<0>(a1) =  nt2::gamcdf(boost::proto::child_c<0>(a0),
                                                   boost::proto::child_c<1>(a0),
                                                   boost::proto::child_c<2>(a0));
    }
    template < class T >
    BOOST_FORCEINLINE static void doit(const A0& a0, A1& a1,
                                       boost::mpl::long_<5> const &, T const & )
    {
      boost::proto::child_c<0>(a1) =  nt2::gamcdf(boost::proto::child_c<0>(a0),
                                                   boost::proto::child_c<1>(a0),
                                                   boost::proto::child_c<2>(a0));
    }
    ////////////////////////////////////////////
    // Regular cases
    ////////////////////////////////////////////
    BOOST_FORCEINLINE static void doit(const A0& a0, A1& a1,
                                       boost::mpl::long_<4> const &, boost::mpl::long_<3> const & )
    {
      const nt2::container::table<value_type> pcov =  boost::proto::child_c<3>(a0);
      pcovis2x2positive(pcov);
      const value_type normz =  -nt2::norminv(static_cast<value_type>(0.025));
      conf_bounds(a0, a1, pcov, normz, boost::proto::child_c<0>(a1));
    }
    BOOST_FORCEINLINE static void doit(const A0& a0, A1& a1,
                                       boost::mpl::long_<5> const &, boost::mpl::long_<3> const & )
    {
      const nt2::container::table<value_type> pcov =  boost::proto::child_c<3>(a0);
      pcovis2x2positive(pcov);
      const value_type normz =  -nt2::norminv(boost::proto::child_c<4>(a0));
      conf_bounds(a0, a1, pcov, normz, boost::proto::child_c<0>(a1));
    }

    template < class M2x2 >
    BOOST_FORCEINLINE static void conf_bounds(const A0& a0, A1& a1,
                                              const M2x2 pcov,
                                              const value_type& normz,
                                              Out0 & p)
    {
      typedef typename boost::proto::result_of::child_c<A1&,1>::type         Out1;
      typedef typename boost::proto::result_of::child_c<A1&,2>::type         Out2;

      p.resize(a0.extent());
      const In0& x  = boost::proto::child_c<0>(a0);
      const In1& a = boost::proto::child_c<1>(a0);
      const In2& b = boost::proto::child_c<2>(a0);
      BOOST_AUTO_TPL(z, x/b);
      p =  nt2::exp(z); //nt2::gammainc(z, a);
      BOOST_AUTO_TPL(itp, (p/nt2::oneminus(p)));
      BOOST_AUTO_TPL(dp, nt2::rec(p*oneminus(p))); // derivative of logit(p) w.r.t. p
      BOOST_AUTO_TPL(da, dgammainc(z,a)*dp);       // dlogitp/da = dp/da * dlogitp/dp
      BOOST_AUTO_TPL(db, -nt2::exp(a*nt2::log(z)-z-nt2::gammaln(a)-nt2::log(b))* dp); // dlogitp/db = dp/db * dlogitp/dp
      BOOST_AUTO_TPL(varLogitp, pcov(1,1)*sqr(da) + (Two<value_type>()*pcov(1,2)*da + pcov(2,2)*db)*db);
      BOOST_AUTO_TPL(exp_halfwidth, nt2::exp(normz*nt2::sqrt(varLogitp)));
      Out1 & plo = boost::proto::child_c<1>(a1);
      Out2 & pup = boost::proto::child_c<2>(a1);
      plo.resize(a0.extent());
      pup.resize(a0.extent());
      plo = itp*exp_halfwidth;
      pup = itp/exp_halfwidth;
      plo /= nt2::oneplus(plo);
      pup /= nt2::oneplus(pup);
    }
  private :
    template < class T > BOOST_FORCEINLINE static
    void pcovis2x2positive(const T & pcov)
    {
      BOOST_ASSERT_MSG((size(pcov, 1) == 2) && (size(pcov, 2) == 2), "pcov must be of size 2x2");
      BOOST_ASSERT_MSG(is_gez(pcov(1, 1)), "pcov must be positive") ;
      BOOST_ASSERT_MSG(is_gez(pcov(1, 1)*pcov(2, 2)-sqr(pcov(1, 2))),
                       "pcov must be positive") ;
    }
  };

} }

#endif
