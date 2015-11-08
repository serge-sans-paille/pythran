//==============================================================================
//         Copyright 2003 - 2013 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2013 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_STATISTICS_FUNCTIONS_TESTS_KSTEST_HPP_INCLUDED
#define NT2_STATISTICS_FUNCTIONS_TESTS_KSTEST_HPP_INCLUDED

#include <nt2/statistics/functions/kstest.hpp>
#include <nt2/core/container/dsl.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/sqrt.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/globalmax.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/dist.hpp>
#include <nt2/include/functions/exp.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/sqrteps.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <nt2/core/container/colon/colon.hpp>

namespace nt2 { namespace ext
{

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::kstest_
                            , tag::cpu_
                            , (A0)(A1)(A2)
                            ,  ((ast_<A0, nt2::container::domain>))
                              ((unspecified_< A1 >))
                              ((scalar_< floating_<A2> >))
                              ((scalar_< floating_<A2> >))
                            )
  {
    typedef void result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& cdf,A2 & d, A2&p) const
    {
      //a0 is supposed to be sorted;
      uint32_t nn = numel(a0);
      A2 n =  A2(nn);
      BOOST_AUTO_TPL(fn, nt2::colon(nt2::Zero<A2>(), n)/n);
      BOOST_AUTO_TPL(ff, cdf(rowvect(a0)));
      d = globalmax(nt2::max(dist(fn(_(1, nn)), ff),
                             dist(fn(_(2, nn+1)), ff)));
      n = nt2::sqrt(n);
      p = pks((n+ A2(0.12)+A2(0.11)/n)*d);
    }
  private :
    static inline A2 pks(const A2& lam)
    {
      const A2 eps1 = A2(0.001);
      const A2 eps2 = nt2::Sqrteps<A2>();
      A2 fac = Two<A2>();
      A2 a2 =  -fac*nt2::sqr(lam);
      A2 r = nt2::Zero<A2>();
      A2 termbf =   nt2::Zero<A2>();
      for(uint32_t i=1; i < 100u; ++i)
      {
        A2 term = fac*nt2::exp(a2*nt2::sqr(i));
        r+= term;
        if ((nt2::abs(term) <= eps1*termbf)||(nt2::abs(term) < eps2*r))
          return r;
        fac*= nt2::Mone<A2>();
        termbf =  nt2::abs(term);
      }
      return nt2::One<A2>();
    }

  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::kstest_, tag::cpu_
                            , (A0)(A1)
                            , ((ast_<A0, nt2::container::domain>))
                              ((unspecified_< A1 >))
                            )
  {
    typedef typename nt2::meta::scalar_of<A0>::type r_t;
    typedef std::pair<r_t, r_t>                      result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0, A1 const& cdf) const
    {
      r_t first, second;
      kstest(a0, cdf, first, second);
      return result_type(first, second);
    }
  };

  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::kstest_, tag::cpu_
                            , (A0)(A1)(A2)
                            , ((ast_<A0, nt2::container::domain>))
                              ((unspecified_<A1 >))
                              ((scalar_< floating_<A2> >))
                            )
  {
    typedef A2 result_type;
    BOOST_FORCEINLINE result_type operator()(A0 const& a0,A1 & cdf,A2 & a3) const
    {
      A2 a2;
      kstest(a0, cdf, a2, a3);
      return a2;
    }
  };

} }

#endif
