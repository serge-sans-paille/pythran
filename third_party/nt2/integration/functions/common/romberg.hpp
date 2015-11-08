//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_INTEGRATION_FUNCTIONS_COMMON_ROMBERG_HPP_INCLUDED
#define NT2_INTEGRATION_FUNCTIONS_COMMON_ROMBERG_HPP_INCLUDED

#include <nt2/integration/functions/romberg.hpp>
#include <nt2/integration/output.hpp>
#include <nt2/integration/options.hpp>
#include <nt2/integration/waypoints.hpp>
#include <nt2/integration/fudge.hpp>
#include <nt2/integration/order.hpp>
#include <nt2/integration/split.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/eps.hpp>
#include <nt2/include/functions/exp2.hpp>
#include <nt2/include/functions/fast_ldexp.hpp>
#include <nt2/include/functions/average.hpp>
#include <nt2/include/functions/diff.hpp>
#include <nt2/include/functions/globalsum.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/rowvect.hpp>
#include <nt2/core/container/table/table.hpp>
#include <nt2/sdk/complex/meta/is_complex.hpp>
#include <boost/mpl/bool.hpp>

namespace nt2 { namespace details
{
  template<class T, class V> class romberg_impl
  {
  public :
    typedef T                                                                input_t;
    typedef typename meta::as_logical<input_t>::type                            bi_t;
    typedef V                                                                value_t;
    typedef typename meta::is_complex<value_t>::type                     v_is_cplx_t;
    typedef typename boost::mpl::if_<v_is_cplx_t,value_t,input_t>::type     result_t;
    typedef typename meta::as_real<value_t>::type                             real_t;
    typedef details::integration_settings<T, V, tag::romberg_>                   o_t;
    typedef container::table<value_t>                                         vtab_t;
    typedef container::table<input_t>                                         itab_t;
    typedef container::table<real_t>                                          rtab_t;
    typedef container::table<result_t>                                      restab_t;
    typedef container::table<bi_t>                                           bitab_t;

    romberg_impl() :  errbnd_(Nan<real_t>()),
                      fcnt_(0),
                      maxfcnt_(Valmax<size_t>()),
                      warn_(0),
                      res_(){}
    ~romberg_impl() {}

    size_t nbeval()           const { return fcnt_;             }
    real_t lasterror()        const { return err_;              }
    bool   ok()               const { return warn_ == 0;        }
    const restab_t & result() const { return res_;              }
    void setwarn(size_t w)          { if(w > warn_) warn_ =  w; }
    size_t  warn()            const { return warn_;             }
    size_t  steps()           const { return steps_;            }


    template < class FUNC, class X>
    void compute( const FUNC& f, const X & x, const o_t & o)
    {
      init(o, x);
      real_t tmptol = tol_;
      BOOST_AUTO_TPL(dif, nt2::abs(nt2::diff(nt2::rowvect(wpts_))));
      real_t tol1= tol_/nt2::globalasum1(dif);
      size_t l = numel(dif);
      res_.resize(extent(wpts_));
      res_(1) = nt2::Zero<value_t>();
      tol_ = tol1*dif(1);
      res_(2) = compute<true>(f, wpts_(1), wpts_(2));
      err_= nt2::abs(dint_);
      for(size_t i=2; i < l; ++i)
      {
        tol_ = tol1*dif(i);
        res_(i+1) = res_(i)+compute<false>(f, wpts_(i), wpts_(i+1));
        err_+= nt2::abs(dint_);
      }
      if (l >= 2)
      {
        tol_ = tol1*dif(l);
        res_(l+1) = res_(l)+compute<true>(f, wpts_(l), wpts_(l+1));
        err_+= nt2::abs(dint_);
      }

      tol_ = tmptol;
      if (!o.return_waypoints)
      {
        res_(begin_) = res_(end_);
        res_.resize(nt2::of_size(1, 1));
      }
    }

  private :
    real_t      errbnd_;
    real_t         err_;
    size_t        fcnt_;
    size_t     maxfcnt_;
    size_t        warn_;
    size_t       steps_;
    real_t         tol_;
    vtab_t         res_;
    real_t        hmin_;
    itab_t        wpts_;
    size_t    nbextrap_;
    size_t     maxstep_;
    bool    singular_a_;
    bool    singular_b_;
    value_t int_, dint_, oldint_;
  private:
    template < class X >
    void init( const o_t & o, const X&x)
    {
      details::prepare_waypoints(o, x, wpts_);
      warn_ = 0;
      fcnt_ = 0;
      maxfcnt_ = o.maxfunccnt;
      err_ = nt2::Zero<real_t>();
      tol_ = fast_ldexp(o.abstol, -4);//give a 16 factor to tolerance
      nbextrap_ = o.nbextrap;
      maxstep_ = o.maxstep;
      singular_a_ = o.singular_a;
      singular_b_ = o.singular_b;
    }

    template <bool test, class FUNC>
    value_t compute(const  FUNC &f, const input_t& a, const input_t& b)
    {
      typedef typename details::fudge<FUNC,1,vtab_t,input_t,test> fudge1;
      typedef typename details::fudge<FUNC,0,vtab_t,input_t,test> fudgelast;
      input_t d =  b-a;
      real_t e = nt2::eps(d);
      input_t s = e*nt2::sign(d);
      size_t n = (1 << (nbextrap_-1))+1;
      itab_t points = nt2::linspace(a, b, n);
      vtab_t y = f(points);
      fudge1::fdg(f, y, fcnt_, singular_a_, a,  s); // Fudge a to avoid infinities.
      fudgelast::fdg(f, y, fcnt_, singular_b_, b, -s); // Fudge b to avoid infinities.
      fcnt_ = n;
      vtab_t t(of_size(1,nbextrap_+maxstep_));
      rtab_t h(extent(t));
      value_t extra = nt2::average(y(begin_), y(end_));
      h(nt2::_(1, nbextrap_)) = nt2::exp2(-nt2::_(Zero<real_t>(), nbextrap_-1));
      size_t pas = nt2::minusone(numel(y));
      for(size_t i=1; i <= nbextrap_; i++)
      {
        t(i)=d*h(i)*(nt2::globalsum(y(nt2::_(begin_, pas, end_)))-extra);
        pas >>= 1;
      }
      input_t h0 = h(nbextrap_)*d;
      h = nt2::sqr(h);
      int_ = zeroneville(h(nt2::_(1, nbextrap_)),t(nt2::_(1, nbextrap_)));
      oldint_ = Nan<value_t>();
      for (size_t i = nbextrap_-1;  i <= maxstep_+nbextrap_-1; i++)
      {
        real_t e1 = nt2::max(nt2::abs(dint_), (nt2::abs(int_-oldint_)));
//        if ( (nt2::abs(dint_) <= tol_*nt2::abs(int_)) && (nt2::abs(int_-oldint_) <= tol_))
        if ( (e1  <= tol_*nt2::max(nt2::abs(int_), One<real_t>())))
        {
         steps_ = i-nbextrap_+2;
         return int_;
        }
        h0 *= nt2::Half<real_t>();
        h(i+2)=h(i+1)*nt2::Quarter<real_t>();
        points = linspace(a+h0, b-h0, 1 << i);
        t(i+2) = (nt2::Half<real_t>()*t(i+1) + h0*globalsum(f(points)));
        fcnt_ += nt2::numel(points);
        oldint_ = int_;
        int_ = zeroneville(h(nt2::_(i-nbextrap_+2, i+2)),t(nt2::_(i-nbextrap_+2, i+2)));
      }
      setwarn(3);
      steps_ = maxstep_+1;
      return int_;
    }
    template < class XPR1, class XPR2>
    value_t zeroneville(const XPR1& h, const XPR2& s)
    // ZERONEVILLE    Extrapolation de neville en zero
    //                [y, dint_] = ZeroNeville( h, s)
    //                Calcule la valeur en zero (y) du polynome qui aux points h(i)
    //                prend les valeurs s(i)
    //                dint_ est de plus une évaluation de l'erreur absolue en ce point.
    {
      vtab_t  c(s),  d(s);
      dint_ = Zero<value_t>();
      size_t nearest = numel(s);
      size_t nbextrap = nearest;
      value_t rint = s(nbextrap);
      nearest--;
      for(size_t m = 1;  m <= nbextrap_-1; m++)
      {
        rtab_t ho = h(nt2::_(1, nbextrap-m));
        rtab_t hp = h(nt2::_(1+m, nbextrap));
        rtab_t den = ho-hp;
        for(size_t i = 1; i <= nbextrap-m;  i++)
        {
          value_t w  = c(i+1)-d(i);
          value_t deno = w/den(i);
          d(i) = hp(i)*deno;
          c(i) = ho(i)*deno;
        }
        if (2*nearest < nbextrap-m)
        {
          dint_ = c(nearest+1);
        }
        else
        {
          dint_ = d(nearest);
          nearest--;
        }
        rint += dint_;
      }
      return rint;
    }
  };
} }


namespace nt2 { namespace ext
                {
                  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::romberg_, tag::cpu_
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
      details::romberg_impl<input_t, value_t> q;
      q.compute(f, x, o);
      result_type that =  {q.result(), q.lasterror(),q.nbeval(),q.ok(),q.warn()};
      return that;
    }
  };
} }
#endif
