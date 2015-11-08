//==============================================================================
//         Copyright 2003 - 2011 LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2011 LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_POLYNOM_FUNCTIONS_EXPR_POLYFIT_HPP_INCLUDED
#define NT2_POLYNOM_FUNCTIONS_EXPR_POLYFIT_HPP_INCLUDED

#include <nt2/polynom/functions/polyfit.hpp>
#include <nt2/core/functions/tie.hpp>

#include <nt2/core/container/table/table.hpp>
#include <nt2/table.hpp>

#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/vandermonde.hpp>
#include <nt2/include/functions/colvect.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/linsolve.hpp>
#include <nt2/include/functions/globalnorm2.hpp>
#include <nt2/include/functions/length.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/subs.hpp>
#include <nt2/include/functions/gels.hpp>
#include <nt2/include/functions/height.hpp>
#include <nt2/include/functions/width.hpp>
#include <nt2/include/functions/colon.hpp>
#include <nt2/include/functions/triu.hpp>
#include <nt2/include/functions/mtimes.hpp>
#include <nt2/include/functions/stdev.hpp>
#include <nt2/include/functions/mean.hpp>
#include <nt2/include/functions/globalstdev.hpp>
#include <nt2/include/functions/globalmean.hpp>
#include <nt2/include/functions/minus.hpp>

namespace nt2 {

  template < class T> struct polyfit_infos
  {
    typedef T value_type;
//      polyfit_infos is a structure containing three elements: the triangular factor from a
//      qr decomposition of the vandermonde matrix, the degrees of freedom and
//      the norm of the residuals.
    nt2::container::table<value_type> r;
    size_t df;
    value_type normr;
  };


  namespace ext
  {
    //============================================================================
    // This version of polyfit is called whenever a tie(...) = balance(...) is captured
    // before assign is resolved. As a tieable function, balance retrieves rhs/lhs
    // pair as inputs
    //============================================================================
    NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::polyfit_, tag::cpu_
                              , (A0)(N0)(A1)(N1)
                              , ((node_<A0, nt2::tag::polyfit_, N0, nt2::container::domain>))
                                ((node_<A1, nt2::tag::tie_ , N1, nt2::container::domain>))
                              )
    {
      typedef void                                                     result_type;
      typedef typename boost::proto::result_of::child_c<A1&,0>::value_type  p_type;
      typedef typename boost::proto::result_of::child_c<A0&,0>::value_type  x_type;
      typedef typename boost::proto::result_of::child_c<A0&,1>::value_type  y_type;
      typedef typename p_type::value_type                               value_type;
      typedef polyfit_infos<value_type>                                     s_type;

      BOOST_FORCEINLINE result_type operator()( A0& a0, A1& a1 ) const
      {
        // Copy data in output first
        x_type  x = boost::proto::child_c<0>(a0);
        y_type  y = boost::proto::child_c<1>(a0);
        size_t l = lval(a0, N0());
        polcoefs(a1, x, y, l, N1());
      }

    private:
      BOOST_FORCEINLINE size_t lval(A0& a0, boost::mpl::long_<3> const &) const
      {
        return size_t(boost::proto::child_c<2>(a0))+1;
      }
      template < class T > BOOST_FORCEINLINE size_t lval(A0& a0, T const &) const
      {
        return nt2::numel(boost::proto::child_c<0>(a0));
      }

      BOOST_FORCEINLINE
        void polcoefs(A1& a1, x_type const & x, y_type const &y,
                      const size_t & l, boost::mpl::long_<1> const &) const
      {
        BOOST_AUTO_TPL(p, boost::proto::child_c<0>(a1));
        BOOST_AUTO_TPL(vnd, nt2::vandermonde(nt2::colvect(x), l));
        p = nt2::rowvect(nt2::linsolve(vnd, nt2::colvect(y)));
        p.resize(of_size(nt2::width(vnd),1u ));
      }

      BOOST_FORCEINLINE
        void polcoefs(A1 &a1, x_type const & x, y_type const &y,
                      const size_t & l, boost::mpl::long_<2> const &) const
      {
        BOOST_AUTO_TPL(p, boost::proto::child_c<0>(a1));
        BOOST_AUTO_TPL(s, boost::proto::child_c<1>(a1));
        BOOST_AUTO_TPL(vnd, nt2::vandermonde(nt2::colvect(x), l));
        typedef typename nt2::meta::call<nt2::tag::colvect_(y_type const &)>::type cy_t;
        typedef typename nt2::meta::call<nt2::tag::vandermonde_(cy_t const &, size_t const &)>::type vnd_t;
        nt2::container::table<value_type> fact = vnd;
        p = nt2::colvect(y);
        nt2::gels( boost::proto::value(fact),boost::proto::value(p) );
        s.r = nt2::triu(fact(nt2::_(1, std::min(nt2::height(fact),nt2::width(fact))), nt2::_) );
        p.resize(of_size(nt2::width(vnd),1u ));
        s.df = nt2::subs(nt2::length(y), nt2::oneplus(l));
        s.normr = nt2::globalnorm2(colvect(y)-nt2::mtimes(vnd, p));
      }

      BOOST_FORCEINLINE
      void polcoefs(A1 &a1, x_type const & x, y_type const &y,
                    const size_t & l, boost::mpl::long_<4> const &) const
      {
        typedef typename boost::proto::result_of::child_c<A1&,2>::value_type  cdf_type;
        typedef typename cdf_type::value_type df_type;
        BOOST_AUTO_TPL(p, boost::proto::child_c<0>(a1));
        BOOST_AUTO_TPL(r, boost::proto::child_c<1>(a1));
        BOOST_AUTO_TPL(df, boost::proto::child_c<2>(a1));
        BOOST_AUTO_TPL(normr, boost::proto::child_c<3>(a1));
        BOOST_AUTO_TPL(vnd, nt2::vandermonde(nt2::colvect(x), l));
        typedef typename nt2::meta::call<nt2::tag::colvect_(x_type const &)>::type cx_t;
        typedef typename nt2::meta::call<nt2::tag::vandermonde_(cx_t const &, size_t const &)>::type vnd_t;
        nt2::container::table<value_type> fact = vnd;
        p = colvect(y);
        nt2::gels(boost::proto::value(fact),boost::proto::value(p) );
        r = nt2::triu(fact(nt2::_(1, std::min(nt2::height(fact),nt2::width(fact))), nt2::_) );
        p.resize(of_size(nt2::width(vnd),1u ));
        df = df_type(nt2::subs(nt2::numel(y), l));
        normr = nt2::globalnorm2(colvect(y)-nt2::mtimes(vnd, p));
      }

      BOOST_FORCEINLINE
        void polcoefs(A1 &a1, x_type const & x, y_type const &y,
                      const size_t & l, boost::mpl::long_<5> const &) const
      {
        typedef typename boost::proto::result_of::child_c<A1&,2>::value_type  cdf_type;
        typedef typename cdf_type::value_type df_type;
        BOOST_AUTO_TPL(mu, boost::proto::child_c<4>(a1));
        mu.resize(nt2::of_size(1, 2));
        //      BOOST_AUTO_TPL(mm, nt2::mean(nt2::colvect(x))(1));
        //      BOOST_AUTO_TPL(ss, nt2::stdev(nt2::colvect(x))(1));
        mu(1) = globalmean(x);
        mu(2) = globalstdev(x);
        BOOST_AUTO_TPL(p, boost::proto::child_c<0>(a1));
        BOOST_AUTO_TPL(r, boost::proto::child_c<1>(a1));
        BOOST_AUTO_TPL(df, boost::proto::child_c<2>(a1));
        BOOST_AUTO_TPL(normr, boost::proto::child_c<3>(a1));
        BOOST_AUTO_TPL(vnd, nt2::vandermonde( (nt2::colvect(x)-mu(1))/mu(2), l));
        nt2::container::table<value_type> fact = vnd;
        p = colvect(y);
        nt2::gels(boost::proto::value(fact),boost::proto::value(p) );
        r = nt2::triu(fact(nt2::_(1, std::min(nt2::height(fact),nt2::width(fact))), nt2::_) );
        p.resize(of_size(nt2::width(vnd),1u ));
        df = df_type(nt2::subs(nt2::numel(y), l));
        normr = nt2::globalnorm2(colvect(y)-nt2::mtimes(vnd, p));
      }


    };
  }
}


#endif
