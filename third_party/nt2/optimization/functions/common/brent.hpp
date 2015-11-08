//==============================================================================
//         Copyright 2003 - 2012   LASMEA UMR 6602 CNRS/Univ. Clermont II
//         Copyright 2009 - 2012   LRI    UMR 8623 CNRS/Univ Paris Sud XI
//
//          Distributed under the Boost Software License, Version 1.0.
//                 See accompanying file LICENSE.txt or copy at
//                     http://www.boost.org/LICENSE_1_0.txt
//==============================================================================
#ifndef NT2_OPTIMIZATION_FUNCTIONS_COMMON_BRENT_HPP_INCLUDED
#define NT2_OPTIMIZATION_FUNCTIONS_COMMON_BRENT_HPP_INCLUDED

#include <nt2/optimization/functions/brent.hpp>
#include <nt2/include/functions/abs.hpp>
#include <nt2/include/functions/sign.hpp>
#include <nt2/include/functions/average.hpp>
#include <nt2/include/constants/nan.hpp>
#include <nt2/include/constants/two.hpp>
#include <nt2/include/constants/zero.hpp>
#include <nt2/include/constants/half.hpp>
#include <nt2/include/constants/cgold.hpp>
#include <nt2/optimization/output.hpp>

namespace nt2 { namespace ext
{
  NT2_FUNCTOR_IMPLEMENTATION( nt2::tag::brent_, tag::cpu_
                            , (F)(T)(O)
                            , (unspecified_< F >)
                              (generic_< floating_<T> >)
                              (generic_< floating_<T> >)
                              (generic_< floating_<T> >)
                              (unspecified_<O>)
                            )
  {
    typedef optimization::output<T,T> result_type;

    result_type operator()(F f, T const& x0, T const& l, T const& uu, O const& o)
    {
      // Iterations count
      std::size_t iter;

      // Local values used to perform Brent's iterations
      T ax(l), bx(x0), cx(uu);
      T d(Nan<T>()), e(Zero<T>());
      T a = (ax < cx ? ax : cx);
      T b = (ax > cx ? ax : cx);
      T v(bx),w(bx),x(bx);
      T tol = static_cast<T>(o.absolute_tolerance);
      T fx, fw, fv;
      fw = fv = fx = f(x);

      // Starts iterating ...
      for(iter=1;iter<=o.maximum_iterations;++iter)
      {
        T etemp,fu,p1,q,r,u = Zero<T>();

        T xm    = nt2::average(a, b);
        T tol1  = tol * nt2::abs(x) + Sqrteps<T>();
        T tol2  = Two<T>()*tol1;

        if( nt2::abs(x-xm) <= (tol2 - Half<T>()*(b-a)) )
        {
          // Successful convergence
          result_type that = {x,fx,iter,true,T(1)};
          return that;
        }

        if(nt2::abs(e) > tol1)
        {
          r   = (x-w)*(fx-fv);
          q   = (x-v)*(fx-fw);
          p1  = (x-v)*q-(x-w)*r;
          q   = Two<T>()*(q-r);

          if (q > Zero<T>()) p1 = -p1;

          q     = nt2::abs(q);
          etemp = e;
          e     = d;

          if( nt2::abs(p1) >= nt2::abs(Half<T>()*q*etemp)
            ||  (p1 <= q*(a-x))
            ||  (p1 >= q*(b-x)))
          {
            d = Cgold<T>()*(e=(x >= xm ? a-x : b-x));
          }
          else
          {
            d=p1/q;
            u=x+d;

            if (u-a < tol2 || b-u < tol2)
              d=tol1 * nt2::sign(xm-x);
          }
        }
        else
        {
          d = Cgold<T>() * (e=((x >= xm) ? a-x : b-x));
        }

        // New value to be computed
        u  = (nt2::abs(d) >= tol1 ? x+d : x + tol1 *  nt2::sign(d));
        fu = f(u);

        if (fu <= fx)
        {
          if(u >= x)  a=x;
          else        b=x;

          shift(v,w,x,u);
          shift(fv,fw,fx,fu);
        }
        else
        {
          if (u < x)  a=u;
          else        b=u;

          if(fu <= fw || w == x)
          {
            v=w;
            w=u;
            fv=fw;
            fw=fu;
          }
          else if (fu <= fv || v == x || v == w)
          {
            v=u;
            fv=fu;
          }
        }
      }

      // We didn't converged -- add message for this
      result_type that = {x,fx,iter,false,T(1)};
      return that;
    }

    private:
    static BOOST_FORCEINLINE void shift(T& a,T& b,T& c,T d)
    {
      a = b; b = c; c = d;
    }
  };
} }
#endif
