//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_INTEGRATION_INT_TRANSFORMS_HPP_INCLUDED
#define NT2_INTEGRATION_INT_TRANSFORMS_HPP_INCLUDED
#include <nt2/include/functions/diff.hpp>

#include <nt2/include/constants/mone.hpp>
#include <nt2/include/constants/one.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/three.hpp>
#include <nt2/include/constants/hundred.hpp>
#include <nt2/include/constants/eps.hpp>

#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/asin.hpp>
#include <nt2/include/functions/asinh.hpp>
#include <nt2/include/functions/average.hpp>
#include <nt2/include/functions/find.hpp>
#include <nt2/include/functions/isempty.hpp>
#include <nt2/include/functions/is_less_equal.hpp>
#include <nt2/include/functions/linspace.hpp>
#include <nt2/include/functions/max.hpp>
#include <nt2/include/functions/numel.hpp>
#include <nt2/include/functions/oneminus.hpp>
#include <nt2/include/functions/oneplus.hpp>
#include <nt2/include/functions/sin.hpp>
#include <nt2/include/functions/sqr.hpp>
#include <nt2/include/functions/tanh.hpp>


namespace nt2
{
  namespace details
  {
    template <class RTAB, class X> static inline
    bool  check_spacing(const X& x)
    {
      typedef typename RTAB::value_type real_t;
      typedef RTAB rtab_t;
      rtab_t ax = nt2::abs(x);
      BOOST_AUTO_TPL(tcidx , nt2::find(nt2::le(nt2::abs(nt2::diff(x)),
                                               nt2::Hundred<real_t>()*Eps<real_t>()*nt2::max(ax(nt2::_(begin_, end_-1)),
                                                                                             ax(nt2::_(begin_+1, end_)))),1));
      bool too_close = !isempty(tcidx);
//      if (too_close){ setwarn(4); }
      return too_close;
//             warning('MATLAB:quadgk:MinStepSize', ...
//                 'Minimum step size reached near x = %g; singularity possible.', ...
//                 x(tcidx));
    }

    template <class RTAB, class VTAB, class FUNC, class X >
    static inline VTAB
    evalfun(const FUNC & f, const X& x, bool & tooclose, bool& firstfunceval, size_t& fcnt)
    {

      if(firstfunceval)
      {
        tooclose = false;
        BOOST_AUTO_TPL(fx, f(x));
        fcnt+= numel(x);
//        final_input_checks(x, fx);
        firstfunceval = false;
        return fx;
      }
      else
      {
        tooclose = check_spacing<RTAB>(x);
        if (tooclose)
        {
          return VTAB();
        }
        else
        {
          fcnt+= numel(x);
          return f(x);
        }
      }
    }


    template < class FUNC,
               template < class, class, class>  class TRANS,
               class INPUT,
               class VALUE>
    struct transform : TRANS<FUNC,INPUT, VALUE>

    {
      typedef INPUT                                 input_t;
      typedef VALUE                                 value_t;
      typedef meta::as_real<value_t>                 real_t;
      typedef typename container::table<real_t>      rtab_t;
      typedef typename container::table<value_t>     vtab_t;
      typedef typename container::table<input_t>     itab_t;
      typedef TRANS<FUNC,input_t,value_t>           trans_t;
      template<class T>
      transform(const FUNC & f, const input_t& a, const input_t& b, const T& tinterv)
        : trans_t(f, a, b, tinterv)
      {};
    };


    template < class FUNC, class INPUT, class VALUE>
    struct no_transform
    {
      typedef INPUT                                 input_t;
      typedef VALUE                                 value_t;
      typedef typename meta::as_real<value_t>::type  real_t;
      typedef typename container::table<real_t>      rtab_t;
      typedef typename container::table<value_t>     vtab_t;
      typedef typename container::table<input_t>     itab_t;
      template < class T > inline
      no_transform(const FUNC & f, const input_t& a, const input_t& b, const T & interv) :
        f_(f), a_(a), b_(b),firstfunceval_(true), fcnt_(0)
      {
        bounds_from(interv);
      };
      template < class X > inline
      vtab_t operator()(const X& t)
      {
        return evalfun<rtab_t, vtab_t>(f_, t, tooclose_, firstfunceval_, fcnt_);
      }
      template < class IN>
      void bounds_from(const IN& interv)
      {
        interval_ = interv;
      }

      bool tooclose() const {return tooclose_; }
      size_t   fcnt() const {return fcnt_; }
      FUNC             f_;
      input_t      a_, b_;
      bool      tooclose_;
      bool firstfunceval_;
      size_t        fcnt_;
      itab_t    interval_;
    };

    template < class FUNC, class INPUT, class VALUE>
    struct fina_finb
    {
      typedef INPUT                                 input_t;
      typedef VALUE                                 value_t;
      typedef typename meta::as_real<value_t>::type  real_t;
      typedef typename container::table<real_t>      rtab_t;
      typedef typename container::table<value_t>     vtab_t;
      typedef typename container::table<input_t>     itab_t;
      template < class T > inline
      fina_finb(const FUNC & f, const input_t& a, const input_t& b, const T & interv) :
        f_(f), a_(a), b_(b), firstfunceval_(true), fcnt_(0)
      {
        bounds_from(interv);
      };
      template < class IN>
      void bounds_from(const IN& interv)
      {
        if (nt2::numel(interv) > 2)
        {
          // Analytical transformation suggested by K.L. Metlov:
          BOOST_AUTO_TPL(alpha, Two<real_t>()*nt2::sin(nt2::asin((a_+b_- Two<real_t>()*interv(nt2::_(begin_+1, end_-1)))/(a_ - b_))/Three<real_t>() ));
          interval_ = nt2::cath(nt2::cath(nt2::Mone<input_t>(), alpha), nt2::One<input_t>());
        }
        else
        {
          interval_ = nt2::linspace(nt2::Mone<input_t>(), nt2::One<input_t>(), 2);
        }
      }
      template < class X > inline
      vtab_t operator()(const X& t)
      {
        // Transform to weaken singularities at both ends: [a,b] -> [-1,1]
        itab_t tt =  nt2::Quarter<real_t>()*(b_-a_)*t*(nt2::Three<real_t>() - nt2::sqr(t)) + nt2::average(a_, b_);
        vtab_t y =  evalfun<rtab_t, vtab_t>(f_, tt, tooclose_, firstfunceval_, fcnt_);
        if (!tooclose_) y *= real_t(0.75)*(b_-a_)*(nt2::oneminus(nt2::sqr(t)));
        return y;
      }
      bool tooclose() const {return tooclose_; }
      size_t   fcnt() const {return fcnt_; }
      FUNC             f_;
      input_t      a_, b_;
      bool      tooclose_;
      bool firstfunceval_;
      size_t        fcnt_;
      itab_t    interval_;
    };

// %--------------------------------------------------------------------------

//     function [y,too_close] = fina_infb(t)
//         % Transform to weaken singularity at left end: [a,Inf) -> [0,Inf).
//         % Then transform to finite interval: [0,Inf) -> [0,1].
//         tt = t ./ (1 - t);
//         t2t = A + tt.^2;
//         [y,too_close] = evalFun(t2t);
//         if ~too_close
//             y =  2*tt .* y ./ (1 - t).^2;
//         end
//     end % fina_infb

    template < class FUNC, class INPUT, class VALUE>
    struct fina_infb
    {
      typedef INPUT                                 input_t;
      typedef VALUE                                 value_t;
      typedef typename meta::as_real<value_t>::type  real_t;
      typedef typename container::table<real_t>      rtab_t;
      typedef typename container::table<value_t>     vtab_t;
      typedef typename container::table<input_t>     itab_t;
      template < class T > inline
      fina_infb(const FUNC & f, const input_t& a, const input_t& b, const T & interv) :
        f_(f), a_(a), b_(b), firstfunceval_(true), fcnt_(0)
      {
        bounds_from(interv);
      };
      template < class IN>
      void bounds_from(const IN& interv)
      {
          if  (nt2::numel(interv) > 2)
          {
            BOOST_AUTO_TPL(alpha, nt2::sqrt(interv(2, end_-1) - a_));
            interval_ = nt2::cath(nt2::cath(nt2::Zero<input_t>(), alpha/oneplus(alpha)),nt2::One<input_t>());
          }
          else
            interval_ = nt2::linspace(nt2::Zero<input_t>(), nt2::One<input_t>(), 2);
        }
      template < class X > inline
      vtab_t operator()(const X& t)
      {
        // Transform to weaken singularity at left end: [a,Inf) -> [0,Inf).
        // Then transform to finite interval: [0,Inf) -> [0,1].
        itab_t tt = t/nt2::oneminus(t);
        itab_t t2t = a_+ nt2::sqr(tt);
        vtab_t y =  evalfun<rtab_t, vtab_t>(f_, t2t, tooclose_, firstfunceval_, fcnt_);
        if (!tooclose_) y *= Two<real_t>()*tt/nt2::sqr(nt2::oneminus(t));
        return y;
      }
      bool tooclose() const {return tooclose_; }
      size_t   fcnt() const {return fcnt_; }
      FUNC             f_;
      input_t          a_;
      input_t          b_;
      bool      tooclose_;
      bool firstfunceval_;
      size_t        fcnt_;
      itab_t    interval_;
    };

// %--------------------------------------------------------------------------

//     function [y,too_close] = infa_finb(t)
//         % Transform to weaken singularity at right end: (-Inf,b] -> (-Inf,b].
//         % Then transform to finite interval: (-Inf,b] -> (-1,0].
//         tt = t ./ (1 + t);
//         t2t = B - tt.^2;
//         [y,too_close] = evalFun(t2t);
//         if ~too_close
//             y = -2*tt .* y ./ (1 + t).^2;
//         end
//     end % infa_finb
    template < class FUNC, class INPUT, class VALUE>
    struct infa_finb
    {
      typedef INPUT                                 input_t;
      typedef VALUE                                 value_t;
      typedef typename meta::as_real<value_t>::type  real_t;
      typedef typename container::table<real_t>      rtab_t;
      typedef typename container::table<value_t>     vtab_t;
      typedef typename container::table<input_t>     itab_t;
      template < class T > inline
      infa_finb(const FUNC & f, const input_t& a, const input_t& b, const T & interv) :
        f_(f), a_(a), b_(b), firstfunceval_(true), fcnt_(0)
      {
        bounds_from(interv);
      };
      template < class IN>
      void bounds_from(const IN& interv)
      {
        if  (nt2::numel(interv) > 2)
        {
          BOOST_AUTO_TPL(alpha, nt2::sqrt(b_-interv(2, end_-1)));
          interval_ = nt2::cath(nt2::cath(nt2::Mone<input_t>(), -alpha/oneplus(alpha)),nt2::Zero<input_t>());
        }
        else
          interval_ = nt2::linspace(nt2::Mone<input_t>(), nt2::Zero<input_t>(), 2);
      }
      template < class X > inline
      vtab_t operator()(const X& t)
      {
        // Transform to weaken singularity at left end:  (-Inf,b] -> (-Inf,b].
        // Then transform to finite interval: (-Inf,b] -> (-1,0].
        itab_t tt = t/nt2::oneplus(t);
        itab_t t2t = b_- nt2::sqr(tt);
        vtab_t y = evalfun<rtab_t, vtab_t>(f_, t2t, tooclose_, firstfunceval_, fcnt_);
        if (!tooclose_) y *= Mtwo<real_t>()*tt/nt2::sqr(nt2::oneplus(t));
        return y;
      }
      bool tooclose() const {return tooclose_; }
      size_t   fcnt() const {return fcnt_; }
      FUNC             f_;
      input_t      a_, b_;
      bool      tooclose_;
      bool firstfunceval_;
      size_t        fcnt_;
      itab_t    interval_;
    };

// %--------------------------------------------------------------------------

//     function [y,too_close] = infa_infb(t)
//         % Transform to finite interval: (-Inf,Inf) -> (-1,1).
//         tt = t ./ (1 - t.^2);
//         [y,too_close] = evalFun(tt);
//         if ~too_close
//             y = y .* (1 + t.^2) ./ (1 - t.^2).^2;
//         end
//     end % infa_infb
    template < class FUNC, class INPUT, class VALUE>
    struct infa_infb
    {
      typedef INPUT                                 input_t;
      typedef VALUE                                 value_t;
      typedef typename meta::as_real<value_t>::type  real_t;
      typedef typename container::table<real_t>      rtab_t;
      typedef typename container::table<value_t>     vtab_t;
      typedef typename container::table<input_t>     itab_t;
      template < class T > inline
      infa_infb(const FUNC & f, const input_t& a, const input_t& b, const T & interv) :
        f_(f), a_(a), b_(b), firstfunceval_(true), fcnt_(0)
      {
        bounds_from(interv);
      };
      template < class IN>
      void bounds_from(const IN& interv)
      {
        if  (nt2::numel(interv) > 2)
        {
          BOOST_AUTO_TPL(alpha, nt2::tanh(nt2::asinh(Two<input_t>()*interv(2, end_-1))*Half<input_t>()));
          interval_ = nt2::cath(nt2::cath(nt2::Mone<input_t>(), alpha), nt2::One<input_t>());
        }
        else
          interval_ = nt2::linspace(nt2::Mone<input_t>(), nt2::One<input_t>(), 2);
      }
      template < class X > inline
      vtab_t operator()(const X& t)
      {
        // Transform to weaken singularity at left end:  (-Inf,b] -> (-Inf,b].
        // Then transform to finite interval: (-Inf,b] -> (-1,0].
        itab_t tt =  t/oneminus(nt2::sqr(t));
        vtab_t y = evalfun<rtab_t, vtab_t>(f_, tt, tooclose_, firstfunceval_, fcnt_);
        if (!tooclose_)
          return y *= nt2::oneplus(nt2::sqr(t))/nt2::sqr(oneminus(nt2::sqr(t)));
          return y;
      }
      bool tooclose() const {return tooclose_; }
      size_t   fcnt() const {return fcnt_; }
      FUNC             f_;
      input_t      a_, b_;
      bool      tooclose_;
      bool firstfunceval_;
      size_t        fcnt_;
      itab_t    interval_;
    };
  }
}


#endif
