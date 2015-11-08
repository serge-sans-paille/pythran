//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_INTEGRATION_FUNCTIONS_COMMON_QUADL_HPP_INCLUDED
#define NT2_INTEGRATION_FUNCTIONS_COMMON_QUADL_HPP_INCLUDED

#include <nt2/integration/functions/quadl.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/four.hpp>
#include <nt2/include/constants/valmax.hpp>
#include <nt2/include/constants/sqrt_1o_5.hpp>
#include <nt2/include/constants/sqrt_2o_3.hpp>
#include <nt2/include/constants/smallestposval.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/include/functions/eps.hpp>
#include <nt2/include/functions/diff.hpp>
#include <nt2/include/functions/cons.hpp>
#include <nt2/include/functions/fliplr.hpp>
#include <nt2/include/functions/is_gez.hpp>
#include <nt2/include/functions/fast_ldexp.hpp>
#include <nt2/include/functions/average.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/dot.hpp>
#include <nt2/include/functions/globalsum.hpp>
#include <nt2/include/functions/globalasum1.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/core/container/colon/colon.hpp>
#include <nt2/integration/output.hpp>
#include <nt2/integration/options.hpp>
#include <nt2/integration/waypoints.hpp>
#include <nt2/integration/fudge.hpp>


namespace nt2 { namespace details
{
  template<class T, class V> class quadl_impl
  {
  public :
    typedef T                                              input_t;
    typedef V                                              value_t;
    typedef typename meta::as_real<value_t>::type           real_t;
    typedef details::integration_settings<T, V, tag::quadl_>   o_t;
    typedef container::table<value_t>                       vtab_t;
    typedef container::table<input_t>                       itab_t;
    typedef container::table<real_t>                        rtab_t;
    typedef container::table<bool>                          btab_t;

    quadl_impl() :   err_(Nan<real_t>()),
                     fcnt_(0),
                     maxfcnt_(Valmax<size_t>()),
                     warn_(0),
                     res_(){}
    ~quadl_impl() {}

    size_t nbeval()        const { return fcnt_;             }
    real_t lasterror()     const { return err_/c1470_;       }
    bool   ok()            const { return warn_ == 0;        }
    const vtab_t & result()const { return res_;              }
    void setwarn(size_t w)       { if(w > warn_) warn_ =  w; }
    size_t  warn()         const { return warn_;             }

    template < class FUNC, class X>
    void compute( const FUNC& f, const X & x, const o_t & o)
    {
      real_t tmptol = tol_;
      init(o, x);
      BOOST_AUTO_TPL(dif, nt2::abs(nt2::diff(nt2::rowvect(wpts_))));
      real_t tol1= tol_/nt2::globalasum1(dif);
      size_t l = numel(dif);
      res_.resize(extent(wpts_));
      res_(1) = nt2::Zero<value_t>();
      tol_ = tol1*dif(1);
      res_(2) = compute<true>(f, wpts_(1), wpts_(2));
      for(size_t i=2; i < l; ++i)
      {
        tol_ = tol1*dif(i);
        res_(i+1) = res_(i)+compute<false>(f, wpts_(i), wpts_(i+1));
      }
      if (l >= 2)
      {
        tol_ = tol1*dif(l);
        res_(l+1) = res_(l)+compute<true>(f, wpts_(l), wpts_(l+1));
      }
      tol_ = tmptol;
      if (!o.return_waypoints)
      {
        res_(begin_) = res_(end_);
        res_.resize(nt2::of_size(1, 1));
      }
    }
   private :
    real_t         err_;
    size_t        fcnt_;
    size_t     maxfcnt_;
    bool    singular_a_;
    bool    singular_b_;
    size_t        warn_;
    ptrdiff_t   ifault_;
    real_t         tol_;
    vtab_t         res_;
    real_t        hmin_;
    itab_t        wpts_;
    real_t       c1470_;
    real_t        c245_;

  private:
    static const rtab_t& lobatto()
    {
      static const real_t cl[] = {real_t(1),real_t(5),real_t(5),real_t(1)};
      static const rtab_t l(of_size(1, 4), &cl[0], &cl[4]);
      return l;
    }
    static const rtab_t& kronrod()
    {
      static const real_t ck[] = {real_t(77),real_t(432),real_t(625),real_t(672),real_t(625),real_t(432),real_t(77)};
      static const rtab_t k(of_size(1, 7), &ck[0], &ck[7]);
      return k;
    }
    static const rtab_t& c1()
    {
      static const real_t alpha = nt2::Sqrt_2o_3<real_t>();
      static const real_t beta = nt2::Sqrt_1o_5<real_t>();
      static const real_t cc1[] = {-alpha, -beta, Zero<real_t>(), beta, alpha};
      static const rtab_t c(of_size(1, 5), &cc1[0], &cc1[5]);
      return c;
    }

    template < class X >
    void init( const o_t & o, const X&x)
    {
      details::prepare_waypoints(o, x, wpts_);
      warn_ = 0;
      fcnt_ = 0;
      maxfcnt_ = o.maxfunccnt;
      err_ = nt2::Zero<real_t>();
      singular_a_ = o.singular_a;
      singular_b_ = o.singular_b;
      c245_ = 245;
      c1470_ = 1470; // 245*6
      tol_ = o.abstol;
     }


    template <bool test,  class FUNC >
    value_t compute(const  FUNC &f, const input_t& a, const input_t& b)
    {
      typedef typename details::fudge<FUNC,1,vtab_t,input_t,test> fudge1;
      typedef typename details::fudge<FUNC,13,vtab_t,input_t,test> fudge13;
      input_t d =  b-a;
      real_t e = nt2::eps(nt2::abs(d));
      input_t c = nt2::average(a, b);
      input_t h = d*Half<real_t>();
      input_t se = e*sign(d);
      const real_t cs[] = {real_t(.942882415695480), nt2::Sqrt_2o_3<real_t>(),
                           real_t(.641853342345781),
                           nt2::Sqrt_1o_5<real_t>(), real_t(.236383199662150)};
      rtab_t s(nt2::of_size(1, 5), &cs[0], &cs[5]);
      itab_t z = h*s;
      itab_t x = nt2::cath(nt2::cath(nt2::cath(nt2::cath(a, c-z), c), c+nt2::fliplr(z)), b);
      vtab_t  y = f(x);
      fcnt_ = 13;
      fudge1::fdg(f, y, fcnt_, singular_a_, a,  se); // Fudge a to avoid infinities.
      fudge13::fdg(f, y, fcnt_, singular_b_, b, -se); // Fudge b to avoid infinities.
      // Call the recursive core integrator.
      // Increase tolerance if refinement appears to be effective.
      value_t Q1 = h*nt2::globalsum(lobatto()*y(nt2::_(1,4,13)))*c245_;
      value_t Q2 = h*nt2::globalsum(kronrod()*y(nt2::_(1,2,13)));
      const real_t cs1[] = {real_t(.0158271919734802),real_t(.094273840218850),real_t(.155071987336585),
                            real_t(.188821573960182),real_t(.199773405226859),real_t(.224926465333340)};
      rtab_t s1(nt2::of_size(1, 6), &cs1[0], &cs1[6]);
      rtab_t w = nt2::cath(nt2::cath(s1, real_t(.242611071901408)), nt2::fliplr(s1));
      value_t Q0 = h*nt2::globalsum(w*y)*c1470_;
      real_t r = nt2::abs((Q2-Q0)/(Q1-Q0+nt2::Smallestposval<real_t>()));
      if (r > 0 && r < 1) tol_ /= r;
      tol_*= c1470_;
      // Call the recursive core integrator.
      hmin_ = fast_ldexp(e, -10); //e/1024
      return quadlstep(f,a,b,y(1),y(13))/c1470_;
    }

    template < class FUNC >
    value_t quadlstep(const FUNC & f, const input_t & a,  const input_t & b,
                      const value_t &fa, const value_t& fb)
    {
      //  recursive core routine for function quadl.
      //  Evaluate integrand five times in interior of subinterval [a,b].
      input_t d = b-a;
      input_t c = nt2::average(a, b);
      input_t h = d*Half<real_t>();
      if (abs(h) < hmin_ || c == a || c == b ) //Minimum step size reached; singularity possible.
      {
        setwarn(1); return h*(fa+fb);
      }
      itab_t x = h*c1();
      x = c+x;
      vtab_t y = f(x);
      fcnt_ += 5;
      if (fcnt_ > maxfcnt_){ setwarn(2); return h*(fa+fb); }    // Maximum function count exceeded; singularity likely.
      itab_t x1 = nt2::cath(nt2::cath(a, x), b);  x = x1;
      vtab_t y1 = nt2::cath(nt2::cath(fa, y), fb);y = y1;
      value_t Q1 = h*nt2::globalsum(lobatto()*y(_(1, 2, 7)))*c245_; // Four point Lobatto quadrature times 1470.
      value_t Q = h*nt2::globalsum(kronrod()*y);                    // Seven point Kronrod refinement times 1470.
      if (nt2::is_invalid(Q)) { setwarn(3); return Q; }        // Infinite or Not-a-Number function value encountered.
      //  Check accuracy of integral over this subinterval.
      real_t curerr = nt2::abs(Q1 - Q);
      if (curerr <= tol_*nt2::abs(h))
      {
        err_+= curerr;
        setwarn(0);  return Q;
      }
      else //     % Subdivide into six subintervals.
      {
        setwarn(0);
        Q = Zero<value_t>();
        for(size_t k = 1; k <= 6; ++k)
        {
          Q += quadlstep(f, x(k), x(k+1), y(k), y(k+1));
        }
        return Q;
      }
    };
  };
} }


namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::quadl_, tag::cpu_
                              , (F)(X)(O)
                              , (unspecified_< F >)
                              ((ast_<X, nt2::container::domain>))
                              (unspecified_<O>)
    )
  {
    typedef typename O::value_t                                             value_t;
    typedef typename O::input_t                                             input_t;
    typedef typename O::real_t                                               real_t;
    typedef typename O::result_t                                           result_t;
    typedef typename O::restab_t                                           restab_t;
    typedef typename boost::is_same<input_t,real_t>::type           input_is_real_t;
    typedef nt2::integration::output<restab_t,real_t>                   result_type;

    result_type operator()(F f, X const& x, O const& o)
    {
      details::quadl_impl<input_t, value_t> q;
      q.compute(f, x, o);
      result_type that = {q.result(), q.lasterror(),q.nbeval(),q.ok(), q.warn()};
//      o.display_options();
      return that;
    }
  };
} }
#endif
